#pragma once

#include "pch.h"

namespace py = pybind11;

class PyStdErrRedirect
{
private:
    py::object _stderr;

public:
    explicit PyStdErrRedirect()
    {
        const auto sys = py::module::import("sys");
        _stderr = sys.attr("stderr");

        sys.attr("stderr") = py::module::import("redirect_sys_stderr").attr("stderr_redirect");
    }

    ~PyStdErrRedirect()
    {
        const auto sys = py::module::import("sys");
        sys.attr("stderr") = _stderr;
    }
};
