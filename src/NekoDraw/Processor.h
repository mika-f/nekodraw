#pragma once

#include "pch.h"

/**
 * \brief  Polymorphic "Text2Image", "Image2Image" Processor
 */
class Processor
{
public:
    [[nodiscard]] virtual bool InitializeBackend() = 0;
    [[nodiscard]] virtual bool InitializeModels(std::string model) = 0;
    [[nodiscard]] virtual bool IsBackendInitialized() const = 0;
    [[nodiscard]] virtual bool IsModelsInitialized() const = 0;
    [[nodiscard]] virtual bool ShuffleSeed() = 0;
    [[nodiscard]] virtual bool RunText2ImageProcessor(std::string prompt, int width, int height, std::vector<std::vector<std::vector<float>>>* pArray) const = 0;
    [[nodiscard]] virtual bool RunImage2ImageProcessor(std::string prompt, float strength, std::vector<std::vector<std::vector<float>>> array, std::vector<std::vector<std::vector<float>>>* pArray) const = 0;
    [[nodiscard]] virtual bool Dispose() = 0;

    virtual ~Processor()
    {
        //
    }
};
