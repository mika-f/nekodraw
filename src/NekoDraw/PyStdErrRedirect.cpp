#include "pch.h"
#include "PyStdErrRedirect.h"

PYBIND11_EMBEDDED_MODULE(redirect_sys_stderr, m)
{
    struct StdErrRedirect
    {
        StdErrRedirect() = default;
        StdErrRedirect(const StdErrRedirect&) = default;
        StdErrRedirect(StdErrRedirect&&) = default;
    };

    py::class_<StdErrRedirect> StdRedirect(m, "stderr_redirect");

    StdRedirect.def_static("write", [](const py::object buffer)
    {
        std::cerr << buffer.cast<std::string>();
        OutputDebugStringA(buffer.cast<std::string>().c_str());
    });

    StdRedirect.def_static("flush", []()
    {
        std::cerr << std::flush;
    });
}
