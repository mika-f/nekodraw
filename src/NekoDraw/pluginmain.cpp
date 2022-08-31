#include "pch.h"
#include "data.h"

static constexpr int kItemKeyFormat = 1;
static constexpr int kItemKeySubject = 2;
static constexpr int kItemKeySubjectCaption = 3;
static constexpr int kItemKeyServant = 4;
static constexpr int kItemKeyFormatCaption = 5;
static constexpr int kItemKeyFlavor = 6;

static constexpr int kStringIDFilterCategoryName = 101;
static constexpr int kStringIDFilterName = 102;
static constexpr int kStringIDFormat = 103;
static constexpr int kStringIDSubject = 104;
static constexpr int kStringIDSubjectCaption = 105;
static constexpr int kStringIDServant = 106;
static constexpr int kStringIDFormatCaption = 107;
static constexpr int kStringIDFlavor = 108;

void SetPropertyValueIfChanged(TriglavPlugInInt* pResult, std::u16string* ref, const TriglavPlugInStringService* pStringService, TriglavPlugInStringObject newValueObject)
{
    TriglavPlugInInt len = 0;
    pStringService->getUnicodeLengthProc(&len, newValueObject);

    const TriglavPlugInUniChar* str{};
    pStringService->getUnicodeCharsProc(&str, newValueObject);

    const auto newValue = std::u16string{reinterpret_cast<const char16_t*>(str), static_cast<size_t>(len)};

    if (*ref != newValue)
    {
        *ref = newValue;
        *pResult = kTriglavPlugInPropertyCallBackResultModify;
    }
}

static void TRIGLAV_PLUGIN_CALLBACK TriglavPlugInFilterPropertyCallBack(TriglavPlugInInt* pResult, TriglavPlugInPropertyObject propertyObject, TriglavPlugInInt itemKey, TriglavPlugInInt notify, TriglavPlugInPtr data)
{
    *pResult = kTriglavPlugInPropertyCallBackResultNoModify;

    auto pFilterInfo = static_cast<StableDiffusionPrompt*>(data);
    if (pFilterInfo != nullptr)
    {
        const auto pStringService = (*pFilterInfo).pStringService;
        const auto pPropertyService2 = (*pFilterInfo).pPropertyService2;

        if (notify != kTriglavPlugInPropertyCallBackNotifyValueChanged)
            return;

        TriglavPlugInStringObject newValueObject = nullptr;
        (*pPropertyService2).getStringValueProc(&newValueObject, propertyObject, itemKey);

        switch (itemKey)
        {
        case kItemKeyFormat:
            SetPropertyValueIfChanged(pResult, &pFilterInfo->format, pStringService, newValueObject);
            break;

        case kItemKeySubject:
            SetPropertyValueIfChanged(pResult, &pFilterInfo->subject, pStringService, newValueObject);
            break;

        case kItemKeySubjectCaption:
            SetPropertyValueIfChanged(pResult, &pFilterInfo->subjectCaption, pStringService, newValueObject);
            break;

        case kItemKeyServant:
            SetPropertyValueIfChanged(pResult, &pFilterInfo->servant, pStringService, newValueObject);
            break;

        case kItemKeyFormatCaption:
            SetPropertyValueIfChanged(pResult, &pFilterInfo->formatCaption, pStringService, newValueObject);
            break;

        case kItemKeyFlavor:
            SetPropertyValueIfChanged(pResult, &pFilterInfo->flavor, pStringService, newValueObject);
            break;

        default:
            break;
        }
    }
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
            pFilterInfo->pStringService = pStringService;
            pFilterInfo->pPropertyService = (*pPluginServer).serviceSuite.propertyService;
            pFilterInfo->pPropertyService2 = (*pPluginServer).serviceSuite.propertyService2;

            *pData = pFilterInfo;
            *pResult = kTriglavPlugInAPIResultSuccess;

            MessageBoxA(nullptr, "Hello, World", "Hello, World", 0);
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

        TriglavPlugInFilterInitializeSetProperty(pRecordSuite, hostObject, propertyObject);
        TriglavPlugInFilterInitializeSetPropertyCallBack(pRecordSuite, hostObject, TriglavPlugInFilterPropertyCallBack, *pData);

        (*pPropertyService).releaseProc(propertyObject);
        *pResult = kTriglavPlugInCallResultSuccess;
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
            break;

        case kTriglavPlugInSelectorFilterTerminate:
            TerminatePluginFilter(pResult, pData, pPluginServer);
            break;

        default:
            break;
        }
    }
}
