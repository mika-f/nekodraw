// DllMain for Windows

#include "pch.h"
#include "compat/windows/compat.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ulReasonForCall, LPVOID lpReserved)
{
  switch (ulReasonForCall)
  {
  case DLL_PROCESS_ATTACH:
    hInstance = hModule;
    break;

  case DLL_PROCESS_DETACH:
    break;

  case DLL_THREAD_ATTACH:
    break;

  case DLL_THREAD_DETACH:
    break;

  default:
    break;
  }

  return TRUE;
}
