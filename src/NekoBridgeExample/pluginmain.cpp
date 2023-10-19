#include "pluginmain.h"


void TRIGLAV_PLUGIN_API TriglavPluginCall(TriglavPlugInInt* pResult, TriglavPlugInPtr* pData, const TriglavPlugInInt selector, TriglavPlugInServer* pPluginServer, TriglavPlugInPtr reserved)
{
    NekoBridgeEntryPoint(pResult, pData, selector, pPluginServer, reserved);
}
