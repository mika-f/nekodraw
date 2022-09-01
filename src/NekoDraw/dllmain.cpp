// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "pluginmain.h"

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        {
            MessageBoxA(nullptr, "", "", 0);

            TCHAR lpFilename[_MAX_PATH];
            GetModuleFileName(hModule, lpFilename, _MAX_PATH);

            const auto path = std::filesystem::path(lpFilename);
            SetRootDirectory(path.parent_path().string());

            break;
        }

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;

    default:
        break;
    }
    return TRUE;
}
