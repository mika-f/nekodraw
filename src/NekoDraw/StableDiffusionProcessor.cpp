#include "pch.h"

#include "PyImage.h"
#include "PyWith.h"
#include "StableDiffusionProcessor.h"
#include "strings.h"

using namespace py::literals;

std::tuple<int, int> StableDiffusionProcessor::GetAvailableSquareSize(int width, int height)
{
    constexpr auto kBaseSize = 64;

    auto newWidth = (width + (kBaseSize - 1)) / kBaseSize * kBaseSize;
    auto newHeight = (height + (kBaseSize - 1)) / kBaseSize * kBaseSize;

    return {newWidth, newHeight};
}

void StableDiffusionProcessor::SplitWeightedSubPrompts(std::string text, std::vector<std::string>* pSubPrompts, std::vector<float>* pWeights)
{
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

    *pSubPrompts = prompts;
    *pWeights = weights;
}

bool StableDiffusionProcessor::InitializeBackend()
{
    try
    {
        this->_os = py::module::import("os");
        this->_sys = py::module::import("sys");

#ifdef _DEBUG

        // Debug build of NekoDraw does not including paths of self container(s).
        // Maybe Python.lib ignores PYTHON_HOME environment variables in Debug build.

        py::print(_sys.attr("path"));

        this->_sys.attr("path").attr("insert")(0, "");
        this->_sys.attr("path").attr("insert")(0, this->_os.attr("path").attr("join")(this->_root, "python310.zip"));
        this->_sys.attr("path").attr("insert")(0, this->_os.attr("path").attr("join")(this->_root, "stable-diffusion.zip"));
        this->_sys.attr("path").attr("insert")(0, this->_os.attr("path").attr("join")(this->_root, "site-packages"));
        this->_sys.attr("path").attr("insert")(0, this->_os.attr("path").attr("join")(this->_root));
        this->_sys.attr("path").attr("insert")(0, this->_os.attr("path").attr("join")(this->_root, "DLLs"));
        this->_sys.attr("path").attr("insert")(0, this->_os.attr("path").attr("join")(this->_root, "lib"));

#endif

        this->_sys.attr("path").attr("insert")(0, this->_os.attr("path").attr("join")(this->_root, "python310.zip"));
        this->_sys.attr("path").attr("insert")(0, this->_os.attr("path").attr("join")(this->_root, "stable-diffusion.zip"));
        this->_sys.attr("path").attr("insert")(0, this->_os.attr("path").attr("join")(this->_root, "site-packages"));
        this->_sys.attr("path").attr("insert")(0, this->_os.attr("path").attr("join")(this->_root, "src", "taming-transformers"));
        this->_sys.attr("path").attr("insert")(0, this->_os.attr("path").attr("join")(this->_root, "src", "clip"));

        this->_contextlib = py::module::import("contextlib");
        this->_einops = py::module::import("einops");
        this->_ldm = py::module::import("ldm.util");
        this->_numpy = py::module::import("numpy");
        this->_omegaconf = py::module::import("omegaconf");
        this->_pytorchlightning = py::module::import("pytorch_lightning");
        this->_torch = py::module::import("torch");

        this->_isBackendInitialized = true;

        // check running environment is GTX 16xx?
        // if running on GTX 16xx, enforce to use full precision because floating points calculation bug in stable diffusion.
        // maybe buggy on A4000, and others????
        const auto name = this->_torch.attr("cuda").attr("get_device_name")().cast<std::string>();
        if (name.starts_with("GeForce GTX 16") || name.starts_with("A4000"))
        {
            this->_isEnforceUseNonHalfModels = true;
        }

        return true;
    }
    catch (py::error_already_set& e)
    {
        OutputDebugStringA(e.what());
        return false;
    }
}

bool StableDiffusionProcessor::IsBackendInitialized() const
{
    return this->_isBackendInitialized;
}

bool StableDiffusionProcessor::InitializeModels(std::string ckpt)
{
    try
    {
        const auto path = this->_os.attr("path").attr("join")(this->_root, ckpt);
        const auto sd = py::object(this->_torch.attr("load")(path, "map_location"_a = "cpu")["state_dict"]);

        const auto li = py::list();
        const auto lo = py::list();

        for (auto tuple : sd.attr("items")())
        {
            const auto key = tuple.attr("__getitem__")(0);
            const auto value = tuple.attr("__getitem__")(1);
            const auto sp = split(key.cast<std::string>(), ".");

            if (sp[0] == "model")
            {
                if (const auto isInputBlocks = std::ranges::find(sp, "input_blocks"); isInputBlocks != sp.end())
                {
                    li.attr("append")(key);
                }
                else if (const auto isMiddleBlock = std::ranges::find(sp, "middle_block"); isMiddleBlock != sp.end())
                {
                    li.attr("append")(key);
                }
                else if (const auto isTimeEmbed = std::ranges::find(sp, "time_embed"); isTimeEmbed != sp.end())
                {
                    li.attr("append")(key);
                }
                else
                {
                    lo.attr("append")(key);
                }
            }
        }

        for (auto handle : li)
        {
            const auto key = std::string("model1.") + handle.cast<std::string>().substr(6);
            sd[py::str(key)] = sd.attr("pop")(handle);
        }
        for (auto handle : lo)
        {
            const auto key = std::string("model2.") + handle.cast<std::string>().substr(6);
            sd[py::str(key)] = sd.attr("pop")(handle);
        }

        const auto conf = this->_os.attr("path").attr("join")(this->_root, "configs", "v1-inference.yaml");
        const auto config = this->_omegaconf.attr("OmegaConf").attr("load")(conf);

        const auto model = this->_ldm.attr("instantiate_from_config")(config["modelUNet"]);
        model.attr("load_state_dict")(sd, "strict"_a = false);
        model.attr("eval")();
        model.attr("unet_bs") = 1;
        model.attr("cdevice") = "cuda";
        model.attr("turbo") = false;

        const auto modelCS = this->_ldm.attr("instantiate_from_config")(config["modelCondStage"]);
        modelCS.attr("load_state_dict")(sd, "strict"_a = false);
        modelCS.attr("eval")();
        modelCS.attr("cond_stage_model").attr("device") = "cuda";

        const auto modelFS = this->_ldm.attr("instantiate_from_config")(config["modelFirstStage"]);
        modelFS.attr("load_state_dict")(sd, "strict"_a = false);
        modelFS.attr("eval")();

        if (this->_isEnforceUseNonHalfModels)
        {
            // noop
        }
        else
        {
            model.attr("half")();
            modelCS.attr("half")();
            modelFS.attr("half")();
        }

        this->_globals["model"] = model;
        this->_globals["modelCS"] = modelCS;
        this->_globals["modelFS"] = modelFS;
        this->_isModelsInitialized = true;

        return true;
    }
    catch (py::error_already_set& e)
    {
        OutputDebugStringA(e.what());
        return false;
    }
    catch (std::exception& e)
    {
        OutputDebugStringA(e.what());
        return false;
    }
}

bool StableDiffusionProcessor::IsModelsInitialized() const
{
    return this->_isModelsInitialized;
}

bool StableDiffusionProcessor::ShuffleSeed()
{
    try
    {
        std::random_device rnd;
        std::mt19937 mt(rnd());
        std::uniform_int_distribution rand(0, 1000000);

        this->_seed = rand(mt);

        this->_pytorchlightning.attr("seed_everything")(this->_seed);

        return true;
    }
    catch (py::error_already_set& e)
    {
        OutputDebugStringA(e.what());
        return false;
    }
}

bool StableDiffusionProcessor::RunText2ImageProcessor(std::string prompt, int width, int height, std::vector<std::vector<std::vector<float>>>* pArray) const
{
    try
    {
        const auto [newWidth, newHeight] = GetAvailableSquareSize(width, height);

        this->_globals["prompt"] = prompt;
        this->_globals["data"] = std::vector{py::int_(1) * eval("[prompt]", this->_globals)};
        this->_globals["precision_scope"] = this->_isEnforceUseNonHalfModels ? this->_contextlib.attr("nullcontext") : this->_torch.attr("autocast");

        with(this->_torch.attr("no_grad")(), [this, newWidth, newHeight, pArray]
        {
            for (const py::handle& prompts : this->_globals["data"])
            {
                with(this->_globals["precision_scope"]("cuda"), [this, prompts, newWidth, newHeight, pArray]
                {
                    this->_globals["modelCS"].attr("to")("cuda");
                    py::object uc;

                    if constexpr (true)
                    {
                        uc = this->_globals["modelCS"].attr("get_learned_conditioning")(py::eval("1 * [\"\"]"));
                    }

                    const auto tuple = py::tuple();
                    if (isinstance(prompts, tuple))
                    {
                        this->_globals["prompts"] = py::list(py::tuple(prompts.cast<py::object>()));
                    }
                    else
                    {
                        this->_globals["prompts"] = prompts;
                    }

                    std::vector<std::string> subPrompts;
                    std::vector<float> weights;
                    const auto prompts = this->_globals["prompts"].cast<std::vector<std::string>>();

                    SplitWeightedSubPrompts(prompts[0], &subPrompts, &weights);

                    py::object c;
                    if (subPrompts.size() > 1)
                    {
                        c = this->_torch.attr("zeros_like")(uc);

                        const auto totalWeight = std::accumulate(weights.begin(), weights.end(), 0.0f);

                        for (auto i = 0; i < subPrompts.size(); i++)
                        {
                            const auto weight = weights[i] / totalWeight;
                            c = this->_torch.attr("add")(c, this->_globals["modelCS"].attr("get_learned_conditioning")(subPrompts[i]), "alpha"_a = weight);
                        }
                    }
                    else
                    {
                        c = this->_globals["modelCS"].attr("get_learned_conditioning")(prompts);
                    }

                    const auto shape = std::vector{4, static_cast<int>(floor(newHeight / 8)), static_cast<int>(floor(newWidth / 8))};
                    const auto mem = this->_torch.attr("cuda").attr("memory_allocated")().cast<double>() / 0.000001;
                    this->_globals["modelCS"].attr("to")("cpu");

                    while (this->_torch.attr("cuda").attr("memory_allocated")().cast<double>() / 0.000001 >= mem)
                        Sleep(1000);

                    const auto samples_ddim = this->_globals["model"].attr("sample")(
                        "S"_a = 50,
                        "conditioning"_a = c,
                        "batch_size"_a = 1,
                        "seed"_a = this->_seed,
                        "shape"_a = shape,
                        "verbose"_a = false,
                        "unconditional_guidance_scale"_a = 7.5,
                        "unconditional_conditioning"_a = uc,
                        "eta"_a = 0.0,
                        "x_T"_a = nullptr
                    );

                    this->_globals["modelFS"].attr("to")("cuda");

                    const auto locals = py::dict();
                    const auto x_samples_ddim = this->_globals["modelFS"].attr("decode_first_stage")(samples_ddim.attr("__getitem__")(0).attr("unsqueeze")(0));
                    locals["x_samples_ddim"] = x_samples_ddim;
                    locals["t"] = eval("(x_samples_ddim + 1.0) / 2.0", this->_globals, locals);
                    locals["x_sample"] = this->_torch.attr("clamp")(locals["t"], "min"_a = 0.0, "max"_a = 1.0);
                    locals["t"] = this->_einops.attr("rearrange")(locals["x_sample"].attr("__getitem__")(0).attr("cpu")().attr("numpy")(), "c h w -> h w c");
                    locals["x_sample"] = eval("255.0 * t", this->_globals, locals);

#ifdef _DEBUG
                    const auto img = new PyImage(locals["x_sample"]);
                    const auto dest = this->_os.attr("path").attr("join")(this->_debug, "dest.png");
                    img->Save(dest.cast<std::string>());
#endif

                    *pArray = locals["x_sample"].cast<std::vector<std::vector<std::vector<float>>>>();
                });
            }
        });
    }
    catch (py::error_already_set& e)
    {
        OutputDebugStringA(e.what());
        return false;
    }
    catch (std::exception& e)
    {
        OutputDebugStringA(e.what());
        return false;
    }

    return true;
}

bool StableDiffusionProcessor::RunImage2ImageProcessor(std::string prompt, float strength, Image array, Image* pArray) const
{
    bool hResult = false;

    try
    {
        const auto locals = py::dict();

        const auto height = static_cast<int>(array.size());
        const auto width = static_cast<int>(array[0].size());
        const auto [newWidth, newHeight] = GetAvailableSquareSize(width, height);
        const auto image = this->_numpy.attr("zeros")(std::vector{newHeight, newWidth, 3}, "dtype"_a = this->_numpy.attr("uint8"));

        for (auto i = 0; i < height; i++)
        {
            const auto line = array[i];

            for (auto j = 0; j < width; j++)
            {
                const auto r = static_cast<int>(floor(line[j][0]));
                const auto g = static_cast<int>(floor(line[j][1]));
                const auto b = static_cast<int>(floor(line[j][2]));

                image.attr("__setitem__")(std::tuple{i, j}, std::vector{r, g, b});
            }
        }

#ifdef _DEBUG
        {
            const auto img = new PyImage(image);
            const auto dest = this->_os.attr("path").attr("join")(this->_debug, "src.png");
            img->Save(dest.cast<std::string>());
        }
#endif

        locals["image"] = image/*.attr("transpose")(1, 0, 2)*/.attr("astype")(this->_numpy.attr("float32"));
        locals["image"] = eval("image / 255.0", this->_globals, locals);
        locals["image"] = eval("image[None].transpose(0, 3, 1, 2)", this->_globals, locals);
        locals["image"] = this->_torch.attr("from_numpy")(locals["image"]);

        locals["init_image"] = eval("2.0 * image - 1.0", this->_globals, locals);

        if (this->_isEnforceUseNonHalfModels)
        {
            // noop
        }
        else
        {
            locals["init_image"] = locals["init_image"].attr("half")();
        }

        locals["prompt"] = prompt;
        locals["data"] = std::vector{py::int_(1) * eval("[prompt]", this->_globals, locals)};
        this->_globals["precision_scope"] = this->_isEnforceUseNonHalfModels ? this->_contextlib.attr("nullcontext") : this->_torch.attr("autocast");

        this->_globals["modelFS"].attr("to")("cuda");
        locals["init_image"] = locals["init_image"].attr("to")("cuda");
        locals["init_image"] = this->_einops.attr("repeat")(locals["init_image"], "1 ... -> b ...", "b"_a = 1);

        locals["init_latent"] = this->_globals["modelFS"].attr("encode_first_stage")(locals["init_image"]);
        locals["init_latent"] = this->_globals["modelFS"].attr("get_first_stage_encoding")(locals["init_latent"]);

        const auto mem = this->_torch.attr("cuda").attr("memory_allocated")().cast<double>() / 0.000001;
        this->_globals["modelFS"].attr("to")("cpu");

        while (this->_torch.attr("cuda").attr("memory_allocated")().cast<double>() / 0.000001 >= mem)
            Sleep(1000);

        locals["t_enc"] = static_cast<int>(floor(strength * 50));

        with(this->_torch.attr("no_grad")(), [this, locals, pArray]
        {
            for (const py::handle& prompts : locals["data"])
            {
                with(locals["precision_scope"]("cuda"), [this, locals, prompts, pArray]
                {
                    this->_globals["modelCS"].attr("to")("cuda");
                    py::object uc;

                    if constexpr (true)
                    {
                        uc = this->_globals["modelCS"].attr("get_learned_conditioning")(py::eval("1 * [\"\"]"));
                    }

                    const auto tuple = py::tuple();
                    if (isinstance(prompts, tuple))
                    {
                        locals["prompts"] = py::list(py::tuple(prompts.cast<py::object>()));
                    }
                    else
                    {
                        locals["prompts"] = prompts;
                    }

                    std::vector<std::string> subPrompts;
                    std::vector<float> weights;
                    const auto prompts = locals["prompts"].cast<std::vector<std::string>>();

                    SplitWeightedSubPrompts(prompts[0], &subPrompts, &weights);

                    py::object c;
                    if (subPrompts.size() > 1)
                    {
                        c = this->_torch.attr("zeros_like")(uc);

                        const auto totalWeight = std::accumulate(weights.begin(), weights.end(), 0.0f);

                        for (auto i = 0; i < subPrompts.size(); i++)
                        {
                            const auto weight = weights[i] / totalWeight;
                            c = this->_torch.attr("add")(c, this->_globals["modelCS"].attr("get_learned_conditioning")(subPrompts[i]), "alpha"_a = weight);
                        }
                    }
                    else
                    {
                        c = this->_globals["modelCS"].attr("get_learned_conditioning")(prompts);
                    }

                    const auto mem = this->_torch.attr("cuda").attr("memory_allocated")().cast<double>() / 0.000001;
                    this->_globals["modelCS"].attr("to")("cpu");

                    while (this->_torch.attr("cuda").attr("memory_allocated")().cast<double>() / 0.000001 >= mem)
                        Sleep(1000);

                    const auto z_enc = this->_globals["model"].attr("stochastic_encode")(
                        locals["init_latent"],
                        this->_torch.attr("tensor")(eval("[t_enc] * 1", this->_globals, locals)).attr("to")("cuda"),
                        this->_seed,
                        0.0,
                        50
                    );

                    const auto samples_ddim = this->_globals["model"].attr("decode")(
                        z_enc,
                        c,
                        locals["t_enc"],
                        "unconditional_guidance_scale"_a = 7.5,
                        "unconditional_conditioning"_a = uc
                    );

                    this->_globals["modelFS"].attr("to")("cuda");

                    locals["x_samples_ddim"] = this->_globals["modelFS"].attr("decode_first_stage")(samples_ddim.attr("__getitem__")(0).attr("unsqueeze")(0));
                    locals["t"] = eval("(x_samples_ddim + 1.0) / 2.0", this->_globals, locals);
                    locals["x_sample"] = this->_torch.attr("clamp")(locals["t"], "min"_a = 0.0, "max"_a = 1.0);
                    locals["t"] = this->_einops.attr("rearrange")(locals["x_sample"].attr("__getitem__")(0).attr("cpu")().attr("numpy")(), "c h w -> h w c");
                    locals["x_sample"] = eval("255.0 * t", this->_globals, locals);

#ifdef _DEBUG
                    const auto img = new PyImage(locals["x_sample"]);
                    const auto dest = this->_os.attr("path").attr("join")(this->_debug, "dest.png");
                    img->Save(dest.cast<std::string>());
#endif

                    *pArray = locals["x_sample"].cast<std::vector<std::vector<std::vector<float>>>>();
                });
            }
        });

        hResult = true;
    }
    catch (py::error_already_set& e)
    {
        OutputDebugStringA(e.what());
        return false;
    }
    catch (std::exception& e)
    {
        OutputDebugStringA(e.what());
        return false;
    }

    return true;
}

bool StableDiffusionProcessor::Dispose()
{
    return true;
}
