#pragma once

#include "pch.h"
#include "PythonProcessor.h"

namespace py = pybind11;

class StableDiffusionProcessor : public PythonProcessor
{
private:
    // C++ objects
    std::string _root;
    std::string _debug;
    bool _isBackendInitialized;
    bool _isModelsInitialized;
    int _seed;
    bool _isEnforceUseNonHalfModels;

    // Python objects
    py::object _contextlib;
    py::object _einops;
    py::object _gc;
    py::object _ldm;
    py::object _numpy;
    py::object _omegaconf;
    py::object _os;
    py::object _pytorchlightning;
    py::object _sys;
    py::object _torch;

    static std::tuple<int, int> GetAvailableSquareSize(int width, int height);
    static void SplitWeightedSubPrompts(std::string text, std::vector<std::string>* pSubPrompts, std::vector<float>* pWeights);
public:
    explicit StableDiffusionProcessor(std::string root, std::string debug)
    {
        this->_root = std::move(root);
        this->_debug = std::move(debug);
        this->_isBackendInitialized = false;
        this->_isModelsInitialized = false;
        this->_seed = 0;
        this->_isEnforceUseNonHalfModels = false;
    }

    ~StableDiffusionProcessor() override = default;

    bool InitializeBackend() override;
    bool IsBackendInitialized() const override;
    bool InitializeModels(std::string ckpt) override;
    bool IsModelsInitialized() const override;
    bool ShuffleSeed() override;
    bool RunText2ImageProcessor(std::string prompt, int width, int height, std::vector<std::vector<std::vector<float>>>* pArray) const override;
    bool RunImage2ImageProcessor(std::string prompt, float strength, std::vector<std::vector<std::vector<float>>> array, std::vector<std::vector<std::vector<float>>>* pArray) const override;
    bool Dispose() override;
};
