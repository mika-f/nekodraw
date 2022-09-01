#include "pch.h"
#include "stable-diffusion.h"

bool StableDiffusion::Initialize()
{
    try
    {
        sys = py::module::import("sys");
        os = py::module::import("os");

        this->RedirectStdOut();

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

        globals["config"] = os.attr("path").attr("join")(root, "configs", "v1-interface.yaml");
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

void StableDiffusion::RedirectStdOut()
{
    _stdout = sys.attr("stdout");
    _stderr = sys.attr("stderr");

    const auto stringio = py::module::import("io").attr("StringIO");
    _stdout_buffer = stringio();
    _stderr_buffer = stringio();

    sys.attr("stdout") = _stdout_buffer;
    sys.attr("stderr") = _stderr_buffer;
}

bool StableDiffusion::Run()
{
}
