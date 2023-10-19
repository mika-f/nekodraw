#include "compat/windows/path.h"

HINSTANCE hInstance = nullptr;

std::filesystem::path GetCurrentPath()
{
  char szModulePath[MAX_PATH];

  GetModuleFileNameA(hInstance, szModulePath, MAX_PATH);

  const auto executable = std::filesystem::path(szModulePath);
  return executable.parent_path();
}
