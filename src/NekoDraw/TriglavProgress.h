#pragma once

#include "pch.h"

class TriglavProgress
{
private:
    const TriglavPlugInRecordSuite* _suite;
    const TriglavPlugInHostObject* _hostObject;

    TriglavPlugInInt _total;

public:
    explicit TriglavProgress(const TriglavPlugInRecordSuite* suite, const TriglavPlugInHostObject* hostObject, TriglavPlugInInt total)
    {
        this->_suite = suite;
        this->_hostObject = hostObject;
        this->_total = total;

        TriglavPlugInFilterRunSetProgressTotal(this->_suite, (*this->_hostObject), total);
    }

    void SetProgress(TriglavPlugInInt value) const;
    void SetDone() const;
};
