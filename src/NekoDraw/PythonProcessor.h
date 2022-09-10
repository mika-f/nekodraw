#pragma once

#include "pch.h"
#include "Processor.h"
#include "PyStdErrRedirect.h"
#include "PyStdOutRedirect.h"

namespace py = pybind11;

/**
 * \brief  Polymorphic "Text2Image", "Image2Image" Processor, Backend is Python
 */
class PythonProcessor : public Processor
{
private:
    // redirects
    PyStdOutRedirect* _stdout;
    PyStdErrRedirect* _stderr;

protected:
    py::object _globals;

public:
    PythonProcessor()
    {
        py::initialize_interpreter();

        this->_globals = py::globals();

        this->_stdout = new PyStdOutRedirect();
        this->_stderr = new PyStdErrRedirect();
    }

    ~PythonProcessor() override
    {
        delete this->_stderr;
        delete this->_stdout;

        py::finalize_interpreter();
    }
};
