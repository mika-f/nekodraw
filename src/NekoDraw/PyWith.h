#pragma once

#include "pch.h"

namespace py = pybind11;

void with(py::object scope, std::function<void()> runner);
