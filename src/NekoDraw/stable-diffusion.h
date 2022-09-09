#pragma once
#include <utility>

#include "pch.h"
#include "PyStdOutRedirect.h"
#include "PyStdErrRedirect.h"

namespace py = pybind11;

using namespace py::literals;

#define Pixels std::vector<std::vector<std::vector<float>>>

class StableDiffusion
{
private:
    // instance management
    std::string root;
    bool isInitializeInterpreter;
    bool isInitializeModels;

    // scope variables
    py::object globals;

    // redirects
    PyStdOutRedirect* _stdout;
    PyStdErrRedirect* _stderr;

    // imports
    py::object contextlib;
    py::object einops;
    py::object ldm;
    py::object numpy;
    py::object omegaconf;
    py::object os;
    py::object pytorchlightning;
    py::object sys;
    py::object torch;
    py::object random;

    // Python Interfaces
    py::object LoadModelFromConfig(py::object sckpt) const;
    void SplitWeightedSubprompts(std::string text, std::vector<std::string>* pSubprompts, std::vector<float>* pWeights) const;

public:
    explicit StableDiffusion(std::string root)
    {
        this->root = std::move(root);
        this->isInitializeInterpreter = false;
        this->isInitializeModels = false;

        py::initialize_interpreter();

        this->globals = py::globals();
        this->_stdout = new PyStdOutRedirect();
        this->_stderr = new PyStdErrRedirect();
    }

    ~StableDiffusion()
    {
        delete this->_stdout;
        delete this->_stderr;

        py::finalize_interpreter();
    }

    // C++ Interfaces
    [[nodiscard]] bool InitializeInterpreter();
    [[nodiscard]] bool InitializeModels();
    [[nodiscard]] bool IsInterpreterInitialized() const;
    [[nodiscard]] bool IsModelsInitialized() const;
    [[nodiscard]] bool ShuffleSeed() const;
    [[nodiscard]] static std::tuple<int, int> GetMinimalAvailableSize(int width, int height);
    [[nodiscard]] static std::string GetPromptString(StableDiffusionPrompt* prompt);
    bool RunText2ImageProcessor(StableDiffusionPrompt* prompt, int width, int height, Pixels* pArray, int* pWidth, int* pHeight) const;
    bool RunImage2ImageProcessor(StableDiffusionPrompt* prompt, Pixels array, Pixels* pArray, int* pWidth, int* pHeight) const;
};
