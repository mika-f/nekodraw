#include "pch.h"
#include "pluginmain.h"
#include "stable-diffusion.h"

static constexpr int kItemKeyFormat = 1;
static constexpr int kItemKeySubject = 2;
static constexpr int kItemKeySubjectCaption = 3;
static constexpr int kItemKeyServant = 4;
static constexpr int kItemKeyFormatCaption = 5;
static constexpr int kItemKeyFlavor = 6;
static constexpr int kItemKeyMode = 7;
static constexpr int kItemKeyStrength = 8;

static constexpr int kStringIDFilterCategoryName = 101;
static constexpr int kStringIDFilterName = 102;
static constexpr int kStringIDFormat = 103;
static constexpr int kStringIDSubject = 104;
static constexpr int kStringIDSubjectCaption = 105;
static constexpr int kStringIDServant = 106;
static constexpr int kStringIDFormatCaption = 107;
static constexpr int kStringIDFlavor = 108;
static constexpr int kStringIDMode = 109;
static constexpr int kStringIDStrength = 110;

static bool isPythonInterfaceInitialized = false;

static std::string PluginRootDirectory;
static std::string RuntimePath;
static std::string LibraryPath;
static std::string RootPath;

static StableDiffusion* spStableDiffusion;

void SetRootDirectory(std::string dir)
{
    PluginRootDirectory = dir;
}

void SetPropertyValueIfChanged(TriglavPlugInInt* pResult, std::u16string* ref, const TriglavPlugInStringService* pStringService, const TriglavPlugInPropertyService2* pPropertyService2, const TriglavPlugInPropertyObject propertyObject, TriglavPlugInInt itemKey)
{
    TriglavPlugInStringObject newValueStringObject = nullptr;
    (*pPropertyService2).getStringValueProc(&newValueStringObject, propertyObject, itemKey);

    TriglavPlugInInt len = 0;
    pStringService->getUnicodeLengthProc(&len, newValueStringObject);

    const TriglavPlugInUniChar* str{};
    pStringService->getUnicodeCharsProc(&str, newValueStringObject);

    const auto newValue = std::u16string{reinterpret_cast<const char16_t*>(str), static_cast<size_t>(len)};

    if (*ref != newValue)
    {
        *ref = newValue;
        *pResult = kTriglavPlugInPropertyCallBackResultModify;
    }
}

void SetPropertyValueIfChanged(TriglavPlugInInt* pResult, bool* ref, const TriglavPlugInPropertyService* pPropertyService, const TriglavPlugInPropertyObject propertyObject, const TriglavPlugInInt itemKey)
{
    TriglavPlugInBool newValueBoolObject;
    (*pPropertyService).getBooleanValueProc(&newValueBoolObject, propertyObject, itemKey);

    if (*ref != newValueBoolObject)
    {
        *ref = newValueBoolObject;
        *pResult = kTriglavPlugInPropertyCallBackResultModify;
    }
}

void SetPropertyValueIfChanged(TriglavPlugInInt* pResult, float* ref, const TriglavPlugInPropertyService* pPropertyService, const TriglavPlugInPropertyObject propertyObject, const TriglavPlugInInt itemKey)
{
    TriglavPlugInDouble newValueFloatObject;
    (*pPropertyService).getDecimalValueProc(&newValueFloatObject, propertyObject, itemKey);

    const float newValueFloat = static_cast<float>(newValueFloatObject);

    if (*ref != newValueFloat)
    {
        *ref = newValueFloat;
        *pResult = kTriglavPlugInPropertyCallBackResultModify;
    }
}

static void TRIGLAV_PLUGIN_CALLBACK TriglavPlugInFilterPropertyCallBack(TriglavPlugInInt* pResult, TriglavPlugInPropertyObject propertyObject, TriglavPlugInInt itemKey, TriglavPlugInInt notify, TriglavPlugInPtr data)
{
    *pResult = kTriglavPlugInPropertyCallBackResultNoModify;

    const auto pFilterInfo = static_cast<StableDiffusionPrompt*>(data);
    if (pFilterInfo != nullptr)
    {
        const auto pStringService = (*pFilterInfo).pStringService;
        const auto pPropertyService = (*pFilterInfo).pPropertyService;
        const auto pPropertyService2 = (*pFilterInfo).pPropertyService2;

        if (notify != kTriglavPlugInPropertyCallBackNotifyValueChanged)
            return;


        switch (itemKey)
        {
        case kItemKeyFormat:
            SetPropertyValueIfChanged(pResult, &pFilterInfo->format, pStringService, pPropertyService2, propertyObject, itemKey);
            break;

        case kItemKeySubject:
            SetPropertyValueIfChanged(pResult, &pFilterInfo->subject, pStringService, pPropertyService2, propertyObject, itemKey);
            break;

        case kItemKeySubjectCaption:
            SetPropertyValueIfChanged(pResult, &pFilterInfo->subjectCaption, pStringService, pPropertyService2, propertyObject, itemKey);
            break;

        case kItemKeyServant:
            SetPropertyValueIfChanged(pResult, &pFilterInfo->servant, pStringService, pPropertyService2, propertyObject, itemKey);
            break;

        case kItemKeyFormatCaption:
            SetPropertyValueIfChanged(pResult, &pFilterInfo->formatCaption, pStringService, pPropertyService2, propertyObject, itemKey);
            break;

        case kItemKeyFlavor:
            SetPropertyValueIfChanged(pResult, &pFilterInfo->flavor, pStringService, pPropertyService2, propertyObject, itemKey);
            break;

        case kItemKeyMode:
            SetPropertyValueIfChanged(pResult, &pFilterInfo->isImg2ImgMode, pPropertyService, propertyObject, itemKey);
            break;

        case kItemKeyStrength:
            SetPropertyValueIfChanged(pResult, &pFilterInfo->strength, pPropertyService, propertyObject, itemKey);

        default:
            break;
        }
    }
}

std::string GetRuntimePath(wchar_t* runtime)
{
    const auto path = std::filesystem::path(runtime);
    return (path / "python.exe").string();
}

std::string GetLibraryPath(wchar_t* runtime)
{
    const auto path = std::filesystem::path(runtime);
    const auto a = (path / "python310.zip").string();
    const auto b = (path).string();
    const std::vector v = {a, b};
    const auto delimiter = ";";

    std::ostringstream os;
    std::ranges::copy(v, std::ostream_iterator<std::string>(os, delimiter));

    auto s = os.str();
    s.erase(s.size() - std::char_traits<char>::length(delimiter));

    return s;
}

std::string GetRootPath(wchar_t* runtime)
{
    return std::filesystem::path(runtime).string();
}

std::string GetPipPath()
{
    const auto path = std::filesystem::path(RuntimePath);
    return (path / "get-pip.py").string();
}

wchar_t* AsWcharT(const std::string str)
{
    size_t chars = 0;
    auto wcstring = new wchar_t[str.size() + 1];
    mbstowcs_s(&chars, wcstring, str.size() + 1, str.c_str(), _TRUNCATE);

    return wcstring;
}

void SetRuntimePaths()
{
    const auto path = std::filesystem::path(PluginRootDirectory) / "NekoDraw.ini";
    constexpr TCHAR runtime[MAX_PATH] = {};
    GetPrivateProfileString(
        L"NekoDraw",
        L"NekoDrawRuntimeUri",
        L"",
        LPWSTR(runtime),
        MAX_PATH,
        AsWcharT(path.string())
    );


    const auto wr = (wchar_t*)runtime;
    RuntimePath = GetRuntimePath(wr);
    LibraryPath = GetLibraryPath(wr);
    RootPath = GetRootPath(wr);
}

void InitializePluginModule(TriglavPlugInInt* pResult, TriglavPlugInPtr* pData, const TriglavPlugInServer* pPluginServer)
{
    const auto pModuleInitializeRecord = (*pPluginServer).recordSuite.moduleInitializeRecord;
    const auto pStringService = (*pPluginServer).serviceSuite.stringService;

    if (pModuleInitializeRecord != nullptr && pStringService != nullptr)
    {
        const auto hostObject = (*pPluginServer).hostObject;

        TriglavPlugInInt hostVersion;
        (*pModuleInitializeRecord).getHostVersionProc(&hostVersion, hostObject);

        if (hostVersion >= kTriglavPlugInNeedHostVersion)
        {
            TriglavPlugInStringObject moduleId = nullptr;
            const auto moduleIdString = "C4C3EC47-D997-4ACD-93E7-3454C2EEC32B";

            (*pStringService).createWithAsciiStringProc(&moduleId, moduleIdString, static_cast<TriglavPlugInInt>(strlen(moduleIdString)));
            (*pModuleInitializeRecord).setModuleIDProc(hostObject, moduleId);
            (*pStringService).releaseProc(moduleId);
            (*pModuleInitializeRecord).setModuleKindProc(hostObject, kTriglavPlugInModuleKindFilter);

            const auto pFilterInfo = new StableDiffusionPrompt;
            *pData = pFilterInfo;

            // Initialize Python Interface
            if (!isPythonInterfaceInitialized)
            {
                isPythonInterfaceInitialized = true;
                SetRuntimePaths();

                _putenv_s("PYTHONHOME", RootPath.c_str());
                _putenv_s("PYTHONPATH", LibraryPath.c_str());

                *pResult = kTriglavPlugInAPIResultSuccess;
            }
            else
            {
                *pResult = kTriglavPlugInAPIResultSuccess;
            }
        }
    }
}

void TerminatePluginModule(TriglavPlugInInt* pResult, TriglavPlugInPtr* pData, const TriglavPlugInServer* pPluginServer)
{
    const auto pFilterInfo = static_cast<StableDiffusionPrompt*>(*pData);
    delete pFilterInfo;

    *pResult = kTriglavPlugInAPIResultSuccess;
    *pData = nullptr;
}

void CreateStringProperty(TriglavPlugInHostObject hostObject, TriglavPlugInPropertyObject propertyObject, const TriglavPlugInStringService* pStringService, const TriglavPlugInPropertyService* pPropertyService, const int stringId, const int itemKey, const char shortcut)
{
    TriglavPlugInStringObject caption = nullptr;
    (*pStringService).createWithStringIDProc(&caption, stringId, hostObject);

    (*pPropertyService).addItemProc(propertyObject, itemKey, kTriglavPlugInPropertyValueTypeString, kTriglavPlugInPropertyInputKindDefault, kTriglavPlugInPropertyInputKindDefault, caption, shortcut);
    (*pStringService).releaseProc(caption);
}

void CreateBooleanProperty(TriglavPlugInHostObject hostObject, TriglavPlugInPropertyObject propertyObject, const TriglavPlugInStringService* pStringService, const TriglavPlugInPropertyService* pPropertyService, const int stringId, const int itemKey, const bool def, const char shortcut)
{
    TriglavPlugInStringObject caption = nullptr;
    (*pStringService).createWithStringIDProc(&caption, stringId, hostObject);

    (*pPropertyService).addItemProc(propertyObject, itemKey, kTriglavPlugInPropertyValueTypeBoolean, kTriglavPlugInPropertyInputKindDefault, kTriglavPlugInPropertyInputKindDefault, caption, shortcut);
    (*pPropertyService).setBooleanDefaultValueProc(propertyObject, itemKey, def);
    (*pStringService).releaseProc(caption);
}

void CreateDecimalProperty(TriglavPlugInHostObject hostObject, TriglavPlugInPropertyObject propertyObject, const TriglavPlugInStringService* pStringService, const TriglavPlugInPropertyService* pPropertyService, const int stringId, const int itemKey, const float def, const float min, const float max, const char shortcut)
{
    TriglavPlugInStringObject caption = nullptr;
    (*pStringService).createWithStringIDProc(&caption, stringId, hostObject);

    (*pPropertyService).addItemProc(propertyObject, itemKey, kTriglavPlugInPropertyValueTypeDecimal, kTriglavPlugInPropertyInputKindDefault, kTriglavPlugInPropertyInputKindDefault, caption, shortcut);
    (*pPropertyService).setDecimalMinValueProc(propertyObject, itemKey, min);
    (*pPropertyService).setDecimalMaxValueProc(propertyObject, itemKey, max);
    (*pPropertyService).setDecimalDefaultValueProc(propertyObject, itemKey, def);
    (*pStringService).releaseProc(caption);
}

void InitializePluginFilter(TriglavPlugInInt* pResult, TriglavPlugInPtr* pData, const TriglavPlugInServer* pPluginServer)
{
    const auto pRecordSuite = &(*pPluginServer).recordSuite;
    const auto hostObject = (*pPluginServer).hostObject;
    const auto pStringService = (*pPluginServer).serviceSuite.stringService;
    const auto pPropertyService = (*pPluginServer).serviceSuite.propertyService;

    if (TriglavPlugInGetFilterInitializeRecord(pRecordSuite) != nullptr && pStringService != nullptr && pPropertyService != nullptr)
    {
        TriglavPlugInStringObject filterCategoryName = nullptr;
        TriglavPlugInStringObject filterName = nullptr;
        (*pStringService).createWithStringIDProc(&filterCategoryName, kStringIDFilterCategoryName, hostObject);
        (*pStringService).createWithStringIDProc(&filterName, kStringIDFilterName, hostObject);

        TriglavPlugInFilterInitializeSetFilterCategoryName(pRecordSuite, hostObject, filterCategoryName, 's');
        TriglavPlugInFilterInitializeSetFilterName(pRecordSuite, hostObject, filterName, 'p');

        (*pStringService).releaseProc(filterCategoryName);
        (*pStringService).releaseProc(filterName);

        constexpr TriglavPlugInInt targets[] = {kTriglavPlugInFilterTargetKindRasterLayerRGBAlpha};
        TriglavPlugInFilterInitializeSetTargetKinds(pRecordSuite, hostObject, targets, 1);

        TriglavPlugInPropertyObject propertyObject = nullptr;
        (*pPropertyService).createProc(&propertyObject);

        CreateStringProperty(hostObject, propertyObject, pStringService, pPropertyService, kStringIDFormat, kItemKeyFormat, 'f');
        CreateStringProperty(hostObject, propertyObject, pStringService, pPropertyService, kStringIDSubject, kItemKeySubject, 's');
        CreateStringProperty(hostObject, propertyObject, pStringService, pPropertyService, kStringIDSubjectCaption, kItemKeySubjectCaption, 'a');
        CreateStringProperty(hostObject, propertyObject, pStringService, pPropertyService, kStringIDServant, kItemKeyServant, 'h');
        CreateStringProperty(hostObject, propertyObject, pStringService, pPropertyService, kStringIDFormatCaption, kItemKeyFormatCaption, 'd');
        CreateStringProperty(hostObject, propertyObject, pStringService, pPropertyService, kStringIDFlavor, kItemKeyFlavor, 'l');
        CreateBooleanProperty(hostObject, propertyObject, pStringService, pPropertyService, kStringIDMode, kItemKeyMode, true, 'm');
        CreateDecimalProperty(hostObject, propertyObject, pStringService, pPropertyService, kStringIDStrength, kItemKeyStrength, 0.75, 0.0, 1.0, 's');

        TriglavPlugInFilterInitializeSetProperty(pRecordSuite, hostObject, propertyObject);
        TriglavPlugInFilterInitializeSetPropertyCallBack(pRecordSuite, hostObject, TriglavPlugInFilterPropertyCallBack, *pData);

        (*pPropertyService).releaseProc(propertyObject);
        *pResult = kTriglavPlugInCallResultSuccess;
    }
}

void RunPluginFilter(TriglavPlugInInt* pResult, const TriglavPlugInPtr* pData, const TriglavPlugInServer* pPluginServer)
{
    const auto pRecordSuite = &(*pPluginServer).recordSuite;
    const auto pOffscreenService = (*pPluginServer).serviceSuite.offscreenService;
    const auto pPropertyService = (*pPluginServer).serviceSuite.propertyService;
    const auto pPropertyService2 = (*pPluginServer).serviceSuite.propertyService2;
    const auto pStringService = (*pPluginServer).serviceSuite.stringService;
    const auto pBitmapService = (*pPluginServer).serviceSuite.bitmapService;

    if (TriglavPlugInGetFilterRunRecord(pRecordSuite) != nullptr && pOffscreenService != nullptr && pPropertyService != nullptr && pPropertyService2 != nullptr && pStringService != nullptr && pBitmapService != nullptr)
    {
        const auto hostObject = (*pPluginServer).hostObject;

        TriglavPlugInPropertyObject propertyObject = nullptr;
        TriglavPlugInFilterRunGetProperty(pRecordSuite, &propertyObject, hostObject);

        TriglavPlugInOffscreenObject sourceOffscreenObject = nullptr;
        TriglavPlugInFilterRunGetSourceOffscreen(pRecordSuite, &sourceOffscreenObject, hostObject);

        TriglavPlugInOffscreenObject destinationOffscreenObject = nullptr;
        TriglavPlugInFilterRunGetDestinationOffscreen(pRecordSuite, &destinationOffscreenObject, hostObject);

        TriglavPlugInRect selectAreaRect;
        TriglavPlugInFilterRunGetSelectAreaRect(pRecordSuite, &selectAreaRect, hostObject);

        TriglavPlugInOffscreenObject selectAreaOffscreenObject = nullptr;
        TriglavPlugInFilterRunGetSelectAreaOffscreen(pRecordSuite, &selectAreaOffscreenObject, hostObject);

        TriglavPlugInInt r, g, b;
        (*pOffscreenService).getRGBChannelIndexProc(&r, &g, &b, destinationOffscreenObject);

        TriglavPlugInInt width;
        TriglavPlugInInt height;
        TriglavPlugInInt top;
        TriglavPlugInInt left;

        if (selectAreaOffscreenObject != nullptr)
        {
            (*pOffscreenService).getWidthProc(&width, selectAreaOffscreenObject);
            (*pOffscreenService).getHeightProc(&height, selectAreaOffscreenObject);
            top = selectAreaRect.top;
            left = selectAreaRect.left;
        }
        else
        {
            top = 0;
            left = 0;
            (*pOffscreenService).getWidthProc(&width, destinationOffscreenObject);
            (*pOffscreenService).getHeightProc(&height, destinationOffscreenObject);
        }

        TriglavPlugInBitmapObject destinationBitmapObject = nullptr;
        (*pBitmapService).createProc(&destinationBitmapObject, width, height, 3, kTriglavPlugInBitmapScanlineHorizontalLeftTop);

        TriglavPlugInFilterRunSetProgressTotal(pRecordSuite, hostObject, 100);

        const auto pFilterInfo = static_cast<StableDiffusionPrompt*>(*pData);
        (*pFilterInfo).pStringService = pStringService;
        (*pFilterInfo).pPropertyService = pPropertyService;
        (*pFilterInfo).pPropertyService2 = pPropertyService2;
        (*pFilterInfo).format = u"";
        (*pFilterInfo).subject = u"";
        (*pFilterInfo).subjectCaption = u"";
        (*pFilterInfo).servant = u"";
        (*pFilterInfo).formatCaption = u"";
        (*pFilterInfo).flavor = u"";
        (*pFilterInfo).strength = 0.75;

        bool restart = true;

        while (true)
        {
            if (restart)
            {
                restart = false;

                TriglavPlugInInt result;
                TriglavPlugInFilterRunProcess(pRecordSuite, &result, hostObject, kTriglavPlugInFilterRunProcessStateStart);

                if (result == kTriglavPlugInFilterRunProcessResultExit)
                {
                    break;
                }

                try
                {
                    TriglavPlugInFilterRunSetProgressTotal(pRecordSuite, hostObject, 10);

                    if (spStableDiffusion == nullptr)
                    {
                        spStableDiffusion = new StableDiffusion(RootPath);
                    }

                    if (!spStableDiffusion->IsInterpreterInitialized())
                    {
                        if (const auto isInitialized = spStableDiffusion->InitializeInterpreter(); !isInitialized)
                        {
                            TriglavPlugInFilterRunSetProgressDone(pRecordSuite, hostObject, 100);
                            *pResult = kTriglavPlugInCallResultFailed;
                            break;
                        }
                    }

                    if (!spStableDiffusion->IsModelsInitialized())
                    {
                        if (const auto isInitialized = spStableDiffusion->InitializeModels(); !isInitialized)
                        {
                            TriglavPlugInFilterRunSetProgressDone(pRecordSuite, hostObject, 100);
                            *pResult = kTriglavPlugInCallResultFailed;
                            break;
                        }
                    }

                    if (const auto isShuffled = spStableDiffusion->ShuffleSeed(); !isShuffled)
                    {
                        TriglavPlugInFilterRunSetProgressDone(pRecordSuite, hostObject, 100);
                        *pResult = kTriglavPlugInCallResultFailed;
                        break;
                    }

                    std::vector<std::vector<std::vector<float>>> array;
                    int destWidth, destHeight;

                    if (pFilterInfo->isImg2ImgMode)
                    {
                        TriglavPlugInBitmapObject sourceBitmapObject = nullptr;
                        (*pBitmapService).createProc(&sourceBitmapObject, width, height, 3, kTriglavPlugInBitmapScanlineHorizontalLeftTop);

                        TriglavPlugInPoint bitmapSourcePoint{0, 0};
                        TriglavPlugInPoint offScreenSourcePoint{0, 0};

                        std::vector<std::vector<std::vector<float>>> pixels;

                        if (selectAreaOffscreenObject != nullptr)
                        {
                            (*pOffscreenService).getBitmapProc(sourceBitmapObject, &bitmapSourcePoint, selectAreaOffscreenObject, &offScreenSourcePoint, width, height, kTriglavPlugInOffscreenCopyModeImage);
                        }
                        else
                        {
                            (*pOffscreenService).getBitmapProc(sourceBitmapObject, &bitmapSourcePoint, sourceOffscreenObject, &offScreenSourcePoint, width, height, kTriglavPlugInOffscreenCopyModeImage);
                        }

                        for (auto i = 0; i < height; i++)
                        {
                            std::vector<std::vector<float>> line;

                            for (auto j = 0; j < width; j++)
                            {
                                std::vector<float> pixel;

                                TriglavPlugInPtr address;
                                TriglavPlugInPoint point = {i, j};
                                (*pBitmapService).getAddressProc(&address, sourceBitmapObject, &point);

                                if (address != nullptr)
                                {
                                    const auto srcAddress = static_cast<const BYTE*>(address);

                                    pixel.push_back(srcAddress[r]);
                                    pixel.push_back(srcAddress[g]);
                                    pixel.push_back(srcAddress[b]);
                                }
                                else
                                {
                                    // filled by white (255, 255, 255)
                                    pixel.push_back(255.0);
                                    pixel.push_back(255.0);
                                    pixel.push_back(255.0);
                                }

                                line.push_back(pixel);
                            }

                            pixels.push_back(line);
                        }

                        if (const auto isSuccess = spStableDiffusion->RunImage2ImageProcessor(pFilterInfo, pixels, &array, &destWidth, &destHeight); !isSuccess)
                        {
                            TriglavPlugInFilterRunSetProgressDone(pRecordSuite, hostObject, 100);
                            *pResult = kTriglavPlugInCallResultFailed;
                            break;
                        }
                    }
                    else
                    {
                        if (const auto isSuccess = spStableDiffusion->RunText2ImageProcessor(pFilterInfo, width, height, &array, &destWidth, &destHeight); !isSuccess)
                        {
                            TriglavPlugInFilterRunSetProgressDone(pRecordSuite, hostObject, 100);
                            *pResult = kTriglavPlugInCallResultFailed;
                            break;
                        }
                    }

                    TriglavPlugInFilterRunSetProgressDone(pRecordSuite, hostObject, 75);

                    for (auto i = 0; i < destWidth; i++)
                    {
                        for (auto j = 0; j < destHeight; j++)
                        {
                            TriglavPlugInPtr address;
                            TriglavPlugInPoint point = {j, i};
                            (*pBitmapService).getAddressProc(&address, destinationBitmapObject, &point);

                            if (address != nullptr)
                            {
                                const auto dstAddress = static_cast<BYTE*>(address);
                                dstAddress[r] = static_cast<BYTE>(floor(array[i][j][0]));
                                dstAddress[g] = static_cast<BYTE>(floor(array[i][j][1]));
                                dstAddress[b] = static_cast<BYTE>(floor(array[i][j][2]));
                            }


                            const auto percentage = (destWidth * i + j) / (destWidth * destHeight) * 100.0f / 4;
                            TriglavPlugInFilterRunSetProgressDone(pRecordSuite, hostObject, floor(75.0f + percentage));
                        }
                    }


                    TriglavPlugInFilterRunSetProgressDone(pRecordSuite, hostObject, 100);
                    *pResult = kTriglavPlugInCallResultSuccess;
                }
                catch (std::exception& e)
                {
                    MessageBoxA(nullptr, e.what(), "", 0);
                    *pResult = kTriglavPlugInCallResultFailed;
                    break;
                }
            }

            TriglavPlugInInt result;
            TriglavPlugInFilterRunProcess(pRecordSuite, &result, hostObject, kTriglavPlugInFilterRunProcessStateEnd);

            if (result == kTriglavPlugInFilterRunProcessResultRestart)
            {
                restart = true;
            }
            else if (result == kTriglavPlugInFilterRunProcessResultExit)
            {
                break;
            }
        }


        if (*pResult == kTriglavPlugInCallResultSuccess)
        {
            TriglavPlugInPoint offscreenPos{left, top};
            TriglavPlugInPoint bitmapPos{0, 0};
            (*pOffscreenService).setBitmapProc(destinationOffscreenObject, &offscreenPos, destinationBitmapObject, &bitmapPos, width, height, kTriglavPlugInOffscreenCopyModeImage);

            if (selectAreaOffscreenObject == nullptr)
            {
                const TriglavPlugInRect rect{0, 0, width, height};
                TriglavPlugInFilterRunUpdateDestinationOffscreenRect(pRecordSuite, hostObject, &rect);
            }
            else
            {
                TriglavPlugInFilterRunUpdateDestinationOffscreenRect(pRecordSuite, hostObject, &selectAreaRect);
            }
        }

        (*pBitmapService).releaseProc(destinationBitmapObject);
    }
}

void TerminatePluginFilter(TriglavPlugInInt* pResult, TriglavPlugInPtr* pData, TriglavPlugInServer* pPluginServer)
{
    *pResult = kTriglavPlugInCallResultSuccess;
}

void TRIGLAV_PLUGIN_API TriglavPluginCall(TriglavPlugInInt* pResult, TriglavPlugInPtr* pData, const TriglavPlugInInt selector, TriglavPlugInServer* pPluginServer, TriglavPlugInPtr reserved)
{
    *pResult = kTriglavPlugInAPIResultFailed;

    if (pPluginServer != nullptr)
    {
        switch (selector)
        {
        case kTriglavPlugInSelectorModuleInitialize:
            InitializePluginModule(pResult, pData, pPluginServer);
            break;

        case kTriglavPlugInSelectorModuleTerminate:
            TerminatePluginModule(pResult, pData, pPluginServer);
            break;

        case kTriglavPlugInSelectorFilterInitialize:
            InitializePluginFilter(pResult, pData, pPluginServer);
            break;

        case kTriglavPlugInSelectorFilterRun:
            RunPluginFilter(pResult, pData, pPluginServer);
            break;

        case kTriglavPlugInSelectorFilterTerminate:
            TerminatePluginFilter(pResult, pData, pPluginServer);
            break;

        default:
            break;
        }
    }
}
