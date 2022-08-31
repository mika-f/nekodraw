#include "pch.h"

void InitializePluginModule(TriglavPlugInInt* pResult, TriglavPlugInServer* pPluginServer)
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

            // TODO: need to initialize global plugin variables

            *pResult = kTriglavPlugInAPIResultSuccess;

            MessageBoxA(nullptr, "Hello, World", "Hello, World", 0);
        }
    }
}

void TerminatePluginModule(TriglavPlugInInt* pResult, TriglavPlugInPtr* pData)
{
    *pResult = kTriglavPlugInAPIResultSuccess;
    *pData = nullptr;
}

void TRIGLAV_PLUGIN_API TriglavPluginCall(TriglavPlugInInt* pResult, TriglavPlugInPtr* pData, TriglavPlugInInt selector, TriglavPlugInServer* pPluginServer,
                                          TriglavPlugInPtr reserved)
{
    *pResult = kTriglavPlugInAPIResultFailed;

    if (pPluginServer != nullptr)
    {
        switch (selector)
        {
        case kTriglavPlugInSelectorModuleInitialize:
            InitializePluginModule(pResult, pPluginServer);
            break;

        case kTriglavPlugInSelectorModuleTerminate:
            TerminatePluginModule(pResult, pData);
            break;

        case kTriglavPlugInSelectorFilterInitialize:
            break;

        case kTriglavPlugInSelectorFilterRun:
            break;

        case kTriglavPlugInSelectorFilterTerminate:
            break;

        default:
            break;
        }
    }
}
