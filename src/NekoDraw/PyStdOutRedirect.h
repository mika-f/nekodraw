#pragma once

#include "pch.h"

namespace py = pybind11;

class PyStdOutRedirect
{
private:
    py::object _stdout;

public:
    explicit PyStdOutRedirect()
    {
        const auto sys = py::module::import("sys");
        _stdout = sys.attr("stdout");

        sys.attr("stdout") = py::module::import("redirect_sys_stdout").attr("stdout_redirect");
    }

    ~PyStdOutRedirect()
    {
        const auto sys = py::module::import("sys");
        sys.attr("stdout") = _stdout;
    }
};

