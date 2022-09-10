#include "pch.h"

#include "TriglavProgress.h"

void TriglavProgress::SetProgress(TriglavPlugInInt value) const
{
    TriglavPlugInFilterRunSetProgressDone(this->_suite, *this->_hostObject, value);
}

void TriglavProgress::SetDone() const
{
    TriglavPlugInFilterRunSetProgressDone(this->_suite, *this->_hostObject, this->_total);
}
