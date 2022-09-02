#include "pch.h"
#include "stable-diffusion.h"
#include "strings.h"


bool StableDiffusion::Initialize()
{
    try
    {
        sys = py::module::import("sys");
        os = py::module::import("os");

        sys.attr("path").attr("insert")(0, os.attr("path").attr("join")(root, "lib", "site-packages"));
        sys.attr("path").attr("insert")(0, os.attr("path").attr("join")(root, "src", "taming-transformers"));
        sys.attr("path").attr("insert")(0, os.attr("path").attr("join")(root, "src", "clip"));

        torch = py::module::import("torch");
        numpy = py::module::import("numpy");
        random = py::module::import("random");
        omegaconf = py::module::import("omegaconf");
        pil = py::module::import("PIL");
        tqdm = py::module::import("tqdm");
        itertools = py::module::import("itertools");
        einops = py::module::import("einops");
        torchvision = py::module::import("torchvision.utils");
        time = py::module::import("time");
        pytorchlightning = py::module::import("pytorch_lightning");
        contextlib = py::module::import("contextlib");
        ldm = py::module::import("ldm.util");
        transformers = py::module::import("transformers");
        pandas = py::module::import("pandas");

        globals["config"] = os.attr("path").attr("join")(root, "configs", "v1-inference.yaml");
        globals["ckpt"] = os.attr("path").attr("join")(root, "models", "ldm", "stable-diffusion-v1", "sd-v1-4.ckpt");
        globals["seed"] = random.attr("randint")(0, 1000000);

        return true;
    }
    catch (py::error_already_set& e)
    {
        MessageBoxA(nullptr, e.what(), "Stable Diffusion Error :: Initialize", 0);
        return false;
    }
}

bool StableDiffusion::Run(StableDiffusionPrompt* prompt) const
{
    try
    {
        /*
         * seed_everything(seed)
         * sd = load_model_from_config(ckpt);
         */
        pytorchlightning.attr("seed_everything")(globals["seed"]);
        globals["sd"] = this->LoadModelFromConfig(globals["ckpt"]);

        /**
         * config = OmegaConf.load(config);
         */
        globals["config"] = omegaconf.attr("OmegaConf").attr("load")(globals["config"]);

        /*
         * model = instantiate_from_config(config.modelUNet);
         * _, _ = model.load_state_dict(sd, strict=False);
         * model.eval();
         * model.unet_bs = opt.unet_bs # default: 1
         * model.cdevice = opt.device  # default: cuda
         * model.turbo   = opt.turbo   # default: False
         */
        globals["model"] = ldm.attr("instantiate_from_config")(globals["config"].attr("modelUNet"));
        globals["model"].attr("load_state_dict")(globals["sd"], "strict"_a = false);
        globals["model"].attr("eval")();
        globals["model"].attr("unet_bs") = 1;
        globals["model"].attr("cdevice") = "cuda";
        globals["model"].attr("turbo") = false;

        /**
         * modelCS = instantiate_from_config(config.modelCondStage)
         * _, _ = modelCS.load_state_dict(sd, strict=False)
         * modelCS.eval()
         * modelCS.cond_stage_model.device = opt.device
         */
        globals["modelCS"] = ldm.attr("instantiate_from_config")(globals["config"].attr("modelCondStage"));
        globals["modelCS"].attr("load_state_dict")(globals["sd"], "strict"_a = false);
        globals["modelCS"].attr("eval")();
        globals["modelCS"].attr("cond_stage_model").attr("device") = "cuda";

        /**
         * modelFS = instantiate_from_config(config.modelFirstStage)
         * _, _ = modelFS.load_state_dict(sd, strict=False)
         * modelFS.eval()
         */
        globals["modelFS"] = ldm.attr("instantiate_from_config")(globals["config"].attr("modelFirstStage"));
        globals["modelFS"].attr("load_state_dict")(globals["sd"], "strict"_a = false);
        globals["modelFS"].attr("eval")();

        /**
         * del sd;
         */
        globals["sd"] = nullptr;

        /**
         * model.half();
         * modelCS.half();
         *
         * start_code = None
         */
        globals["model"].attr("half")();
        globals["modelCS"].attr("half")();
        globals["start_code"] = nullptr;

        /**
         * batch_size = opt.n_samples;
         * n_rows = opt.n_rows if opt.n_rows > 0 else batch_size
         * prompt = opt.prompt
         * data = [batch_size * [prompt]]
         */
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
        const auto vec = std::vector{
            convert.to_bytes(prompt->format),
            convert.to_bytes(prompt->subject),
            convert.to_bytes(prompt->subjectCaption),
            convert.to_bytes(prompt->servant),
            convert.to_bytes(prompt->formatCaption),
            convert.to_bytes(prompt->flavor)
        };
        const auto delimiter = " ";
        std::ostringstream os;
        std::ranges::copy(vec, std::ostream_iterator<std::string>(os, delimiter));
        std::string s = trim_c(os.str());

        if (s.empty())
            return false;

        globals["batch_size"] = 1;
        globals["n_rows"] = 1;
        globals["prompt"] = trim_c(s);
        globals["prompt_a"] = std::vector{globals["prompt"]};
        globals["data"] = std::vector{globals["batch_size"] * globals["prompt_a"]};

        /**
         * precision_scope = autocast
         * seeds = ""
         */
        globals["precision_scope"] = torch.attr("autocast");
        globals["seeds"] = "";

        /**
         * with torch.no_grad():
         */
        {
            const auto no_grad_scope = torch.attr("no_grad")();
            no_grad_scope.attr("__enter__")();

            try
            {
                /**
                 * all_samples = list()
                 */
                globals["all_samples"] = py::list();

                /**
                 * for n in trange(opt.n_iter, desc="Sampling") #opt.n_iter = 1
                 */
                const py::list data = globals["data"];
                for (const py::handle& prompts : data)
                {
                    /**
                     * sample_path = os.path.join(outpath, "_".join(re.split(":| ", prompts[0])))[:150]
                     * os.makedirs(sample_path, exists_ok=True)
                     * base_count = len(os.listdir(sample_path))
                     */

                    /*
                     * with precision_scope("cuda"):
                     */
                    const auto precision_scope = globals["precision_scope"]("cuda");
                    precision_scope.attr("__enter__")();

                    try
                    {
                        /**
                         * modelCS.to(opt.device) # opt.device => cuda
                         * uc = None
                         * if opt.scale != 1.0:
                         *    uc = modelCS.get_learned_conditioning(batch_size * [""]);
                         * if isinstance(prompts, tuple):
                         *    prompts = list(prompts)
                         */
                        globals["modelCS"].attr("to")("cuda");
                        globals["uc"] = nullptr;

                        if constexpr (true)
                        {
                            globals["t"] = std::vector<std::string>{""};
                            globals["uc"] = globals["modelCS"].attr("get_learned_conditioning")(globals["batch_size"] * globals["t"]);
                        }

                        const auto tuple = py::tuple();
                        if (isinstance(prompts, tuple))
                        {
                            globals["prompts"] = py::list(py::tuple(prompts.cast<py::object>()));
                        }
                        else
                        {
                            globals["prompts"] = prompts;
                        }

                        /**
                         * subprompts, weights = split_weighted_subprompts(prompts[0])
                         * if len(subprompts) > 1:
                         */
                        std::vector<std::string> subprompts;
                        std::vector<float> weights;
                        auto prompts = globals["prompts"].cast<std::vector<std::string>>();
                        this->SplitWeightedSubprompts(prompts[0], &subprompts, &weights);

                        globals["subprompts"] = subprompts;
                        globals["weights"] = weights;

                        /**
                         * if len(subprompts) > 1
                         */
                        if (subprompts.size() > 1)
                        {
                            /**
                             * c = torch.zeros_like(uc);
                             * totalWeight = sum(weights);
                             */
                            globals["c"] = torch.attr("zeros_like")(globals["uc"]);
                            const auto totalWeight = std::accumulate(weights.begin(), weights.end(), 0.0f);

                            /**
                             * for i in range(len(subprompts)):
                             */
                            for (auto i = 0; i < subprompts.size(); i++)
                            {
                                /**
                                 * weight = weights[i]
                                 * weight = weight / totalWeight
                                 * c = torch.add(c, modelCS.get_learned_conditioning(subprompts[i]), alpha=weight)
                                 */
                                const auto weight = weights[i] / totalWeight;
                                globals["c"] = torch.attr("add")(globals["c"], globals["modelCS"].attr("get_learned_conditioning")(subprompts[i]), "alpha"_a = weight);
                            }
                        }
                        else
                        {
                            /**
                             * c = modelCS.get_learned_conditioning(prompts)
                             */
                            globals["c"] = globals["modelCS"].attr("get_learned_conditioning")(prompts);
                        }

                        /**
                         * shape = [opt.C, opt.H // opt.f, opt.W // opt.f];
                         */
                        globals["shape"] = std::vector{/* opt.C*/ 4, static_cast<int>(floor(/* opt.H */ 512 / 8)), static_cast<int>(floor(/* opt.W */ 512 / 8))};

                        /**
                         * if opt.device != "cpu":
                         *     mem = torch.cuda.memory_allocated() / 1e6
                         *     modelCS.to("cpu")
                         *     while torch.cuda.memoty_allocated() / 1e6 >= mem:
                         *         time.sleep(1)
                         */
                        const auto mem = torch.attr("cuda").attr("memory_allocated")().cast<double>() / 0.000001;
                        globals["modelCS"].attr("to")("cpu");

                        while (torch.attr("cuda").attr("memory_allocated")().cast<double>() / 0.000001 >= mem)
                            Sleep(1000);

                        /**
                         * sample_ddim = model.sample(...)
                         * modelFS.to(opt.device)
                         */
                        globals["sample_ddim"] = globals["model"].attr("sample")(
                            "S"_a = 50, /* opt.ddim_steps: default: 50 */
                            "conditioning"_a = globals["c"],
                            "batch_size"_a = 1,
                            "seed"_a = globals["seed"],
                            "shape"_a = globals["shape"],
                            "verbose"_a = false,
                            "unconditional_guidance_scale"_a = 7.5, /* opt.scale: default: 7.5 */
                            "unconditional_conditioning"_a = globals["uc"],
                            "eta"_a = 0.0, /* opt.ddim_dta: default: 0.0 */
                            "x_T"_a = globals["start_code"]
                        );

                        globals["modelFS"].attr("to")("cuda");

                        // for i in range(batch_size):
                        // batch_size is always one.
                        for (auto i = 0; i < globals["batch_size"].cast<int>(); i++)
                        {
                            /**
                            * x_sample_ddim = modelFS.decode_first_stage(samples_ddim[i].unsqueeze(0));
                            * x_sample = torch.clamp((x_sample_ddim + 1.0) / 2.0, min=0.0, max=1.0)
                            * x_sample = 255.0 * rearrange(x_sample[0].cpu().numpy(), "c h w -> h w c")
                            * Image.fromarray(x_sample.astype(np.uint8)).save(...)
                            */

                            globals["x_sample_ddim"] = globals["modelFS"].attr("decode_first_stage")(globals["sample_ddim"].attr("__getitem__")(i).attr("unsqueeze")(0));
                            globals["t"] = eval("(x_sample_ddim + 1.0) / 2.0", globals);
                            globals["x_sample"] = torch.attr("clamp")(globals["t"], "min"_a = 0.0, "max"_a = 1.0);
                            globals["t"] = einops.attr("rearrange")(globals["x_sample"].attr("__getitem__")(0).attr("cpu")().attr("numpy")(), "c h w -> h w c");
                            globals["x_sample"] = eval("255.0 * t", globals);

                            py::print(globals["x_sample"]);

                            MessageBoxA(nullptr, redirect->ReadStdtOut().c_str(), "", 0);
                        }
                    }
                    catch (py::error_already_set& e)
                    {
                        MessageBoxA(nullptr, e.what(), "Stable Diffusion Error :: Run", 0);
                    }

                    precision_scope.attr("__exit__")(nullptr, nullptr, nullptr);
                }
            }
            catch (py::error_already_set& e)
            {
                MessageBoxA(nullptr, e.what(), "Stable Diffusion Error :: Run", 0);
            }

            no_grad_scope.attr("__exit__")(nullptr, nullptr, nullptr);
        }

        return true;
    }
    catch (py::error_already_set& e)
    {
        MessageBoxA(nullptr, e.what(), "Stable Diffusion Error :: Run", 0);
        return false;
    }
}

py::object StableDiffusion::LoadModelFromConfig(py::object ckpt) const
{
    try
    {
        const auto pl_sd = torch.attr("load")(ckpt, "map_location"_a = "cpu");
        return pl_sd["state_dict"];
    }
    catch (py::error_already_set& e)
    {
        MessageBoxA(nullptr, e.what(), "Stable Diffusion Error :: LoadModelFromConfig", 0);
        return py::object();
    }
}


void StableDiffusion::SplitWeightedSubprompts(std::string text, std::vector<std::string>* pSubprompts, std::vector<float>* pWeights) const
{
    auto locals = py::dict();
    auto remaining = static_cast<int>(text.length());

    auto prompts = std::vector<std::string>{};
    auto weights = std::vector<float>{};

    while (remaining > 0)
    {
        if (text.find(':') != std::string::npos)
        {
            auto idx = text.find(':');
            auto prompt = text.substr(0, idx);
            remaining -= idx;
            text = text.substr(idx + 1);

            if (text.find(' ') != std::string::npos)
            {
                idx = text.find(' ');
            }
            else
            {
                idx = static_cast<int>(text.length());
            }

            auto weight = 0.0f;

            if (idx > 0)
            {
                try
                {
                    weight = std::stof(text.substr(0, idx));
                }
                catch (std::invalid_argument& e)
                {
                    weight = 1.0f;
                }
            }

            remaining -= idx;
            text = text.substr(idx + 1);

            prompts.push_back(prompt);
            weights.push_back(weight);
        }
        else
        {
            if (text.length() > 0)
            {
                prompts.push_back(text);
                weights.push_back(1.0f);
            }

            remaining = 0;
        }
    }

    *pSubprompts = prompts;
    *pWeights = weights;
}
