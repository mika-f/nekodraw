#include "pch.h"
#include "PyImage.h"

void PyImage::Save(std::string path) const
{
    this->_globals["__image__"].attr("save")(path);
}
