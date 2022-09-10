#include "pch.h"
#include "PyWith.h"

void with(py::object scope, std::function<void()> runner)
{
    scope.attr("__enter__")();

    try
    {
        runner();
    }
    catch (py::error_already_set& e)
    {
        OutputDebugStringA(e.what());
    }

    scope.attr("__exit__")(nullptr, nullptr, nullptr);
}
