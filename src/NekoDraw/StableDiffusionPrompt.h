#pragma once

#include "pch.h"

struct StableDiffusionPrompt
{
    std::u16string format;
    std::u16string subject;
    std::u16string subjectCaption;
    std::u16string servant;
    std::u16string formatCaption;
    std::u16string flavor;
    bool isImg2ImgMode;
    float strength;

    TriglavPlugInStringService* pStringService;
    TriglavPlugInPropertyService* pPropertyService;
    TriglavPlugInPropertyService2* pPropertyService2;

    std::string toString() const;
};
