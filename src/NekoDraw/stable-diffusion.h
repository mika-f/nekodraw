#pragma once
#include <utility>

#include "pch.h"

namespace py = pybind11;

using namespace py::literals;

class StableDiffusion
{
private:
    std::string root;

    // variables
    py::object globals;

    // std
    py::object _stdout;
    py::object _stdout_buffer;
    py::object _stderr;
    py::object _stderr_buffer;

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

public:
    explicit StableDiffusion(std::string root)
    {
        this->root = std::move(root);

        py::initialize_interpreter();

        this->globals = py::globals();
    }

    void Dispose()
    {
        py::finalize_interpreter();
    }

    // C++ Interfaces
    bool Initialize();
    void RedirectStdOut();
    bool Run();
};
