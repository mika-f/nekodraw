#include "pch.h"
#include "PyStdOutRedirect.h"

PYBIND11_EMBEDDED_MODULE(redirect_sys_stdout, m)
{
    struct StdOutRedirect
    {
        StdOutRedirect() = default;
        StdOutRedirect(const StdOutRedirect&) = default;
        StdOutRedirect(StdOutRedirect&&) = default;
    };

    py::class_<StdOutRedirect> StdRedirect(m, "stdout_redirect");

    StdRedirect.def_static("write", [](const py::object buffer)
    {
        std::cout << buffer.cast<std::string>();
        OutputDebugStringA(buffer.cast<std::string>().c_str());
    });

    StdRedirect.def_static("flush", []()
    {
        std::cout << std::flush;
    });
}
