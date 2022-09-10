#pragma once

#include "pch.h"

class TriglavBitmapObject
{
private:
    TriglavPlugInBitmapService* _pBitmapService;
    TriglavPlugInBitmapObject _bitmapObject;
    TriglavPlugInInt _r;
    TriglavPlugInInt _g;
    TriglavPlugInInt _b;

public:
    explicit TriglavBitmapObject(TriglavPlugInBitmapService* pBitmapService, TriglavPlugInBitmapObject bitmapObject, TriglavPlugInInt r, TriglavPlugInInt g, TriglavPlugInInt b)
    {
        this->_pBitmapService = pBitmapService;
        this->_bitmapObject = bitmapObject;
        this->_r = r;
        this->_g = g;
        this->_b = b;
    }

    Color getColorFrom(TriglavPlugInPoint point) const;
    void setColorTo(TriglavPlugInPoint point, Color color);
};
