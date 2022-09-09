#pragma once

#include "pch.h"

namespace py = pybind11;


class PyImage
{
private:
    py::object _globals;

public:
    explicit PyImage(py::object array)
    {
        const auto numpy = py::module::import("numpy");
        const auto pil = py::module::import("PIL");

        this->_globals = py::globals();
        this->_globals["__image__"] = pil.attr("Image").attr("fromarray")(
            array.attr("astype")(numpy.attr("uint8"))
        );
    }

    ~PyImage()
    {
        exec("del __image__", this->_globals);
    }

    void Save(std::string path) const;
};
