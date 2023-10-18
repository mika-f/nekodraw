#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#if defined(_WIN64)
// Windows x64
#include "compat/windows/compat.h"
#elif
// Windows x86
#endif // defined(_WIN64)
#elif __APPLE__
#include <TargetConditionals.h>

#if TARGET_OS_MACCATALYST
// macOS Catalyst
#include "compat/macos/catalyst-compat.h"
#elif TARGET_OS_MAC
// macOS older
#include "compat/macos/compat.h"
#endif // __APPLE__
#elif __linux__
// Linux
#elif __unix__
// Unix
#else
#error "unknown compiler platform"
#endif
