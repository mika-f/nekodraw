#pragma once
#include <utility>

#include "pch.h"

namespace py = pybind11;

using namespace py::literals;

class PyStdErrOutStreamRedirect
{
private:
    // std
    py::object _stdout;
    py::object _stdout_buffer;
    py::object _stderr;
    py::object _stderr_buffer;

public:
    explicit PyStdErrOutStreamRedirect(py::module sys)
    {
        _stdout = sys.attr("stdout");
        _stderr = sys.attr("stderr");

        const auto stringio = py::module::import("io").attr("StringIO");
        _stdout_buffer = stringio();
        _stderr_buffer = stringio();

        sys.attr("stdout") = _stdout_buffer;
        sys.attr("stderr") = _stderr_buffer;
    }

    std::string ReadStdtOut()
    {
        _stdout_buffer.attr("seek")(0);
        return py::str(_stdout_buffer.attr("read")());
    }

    std::string ReadStdErr()
    {
        _stderr_buffer.attr("seek")(0);
        return py::str(_stderr_buffer.attr("read")());
    }

    ~PyStdErrOutStreamRedirect()
    {
        const auto sys = py::module::import("sys");
        sys.attr("stdout") = _stdout;
        sys.attr("stderr") = _stderr;
    }
};

class StableDiffusion
{
private:
    std::string root;

    // variables
    py::object globals;

    // redirects
    PyStdErrOutStreamRedirect* redirect;

    // imports
    py::object contextlib;
    py::object einops;
    py::object itertools;
    py::object ldm;
    py::object numpy;
    py::object omegaconf;
    py::object os;
    py::object pandas;
    py::object pil;
    py::object pytorchlightning;
    py::object sys;
    py::object time;
    py::object torch;
    py::object torchvision;
    py::object tqdm;
    py::object transformers;
    py::object random;

    // Python Interfaces
    py::object LoadModelFromConfig(py::object sckpt) const;
    void SplitWeightedSubprompts(std::string text, std::vector<std::string>* pSubprompts, std::vector<float>* pWeights) const;

public:
    explicit StableDiffusion(std::string root)
    {
        this->root = std::move(root);

        py::initialize_interpreter();

        this->globals = py::globals();
        this->redirect = new PyStdErrOutStreamRedirect(py::module::import("sys"));
    }

    void Dispose()
    {
        delete this->redirect;

        py::finalize_interpreter();
    }

    // C++ Interfaces
    bool Initialize();
    bool Run(StableDiffusionPrompt* prompt) const;
};
