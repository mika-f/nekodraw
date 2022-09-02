// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include <codecvt>
#include <filesystem>
#include <string>
#include <numeric>
#include <utility>

#include "TriglavPlugInSDK.h"

#include "data.h"
#include "framework.h"

#include <pybind11/embed.h>
#include <pybind11/eval.h>
#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


#endif //PCH_H
