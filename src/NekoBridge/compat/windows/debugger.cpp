#include "compat/windows/debugger.h"

void DebuggerBreak()
{
  MessageBoxA(nullptr, "", "", MB_OK);
}
