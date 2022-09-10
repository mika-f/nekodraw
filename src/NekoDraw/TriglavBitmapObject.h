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
    TriglavPlugInInt _width;
    TriglavPlugInInt _height;

    explicit TriglavBitmapObject(TriglavPlugInBitmapService* pBitmapService, TriglavPlugInBitmapObject bitmapObject, TriglavPlugInInt width, TriglavPlugInInt height, Channels channels)
    {
        this->_pBitmapService = pBitmapService;
        this->_bitmapObject = bitmapObject;
        this->_width = width;
        this->_height = height;
        this->_r = std::get<0>(channels);
        this->_g = std::get<1>(channels);
        this->_b = std::get<2>(channels);
    }

public:
    [[nodiscard]] TriglavPlugInInt getWidth() const;
    [[nodiscard]] TriglavPlugInInt getHeight() const;
    [[nodiscard]] Color getColorFrom(TriglavPlugInPoint point) const;
    void setColorTo(TriglavPlugInPoint point, Color color) const;
    void copyFrom(const TriglavPlugInOffscreenService* pOffscreenService, TriglavPlugInOffscreenObject sourceObject, const TriglavPlugInPoint* sourcePoint) const;
    void copyTo(const TriglavPlugInOffscreenService* pOffscreenService, TriglavPlugInOffscreenObject destinationObject, const TriglavPlugInPoint* destinationPoint) const;
    void Release() const;

    //
    static TriglavBitmapObject* create(TriglavPlugInBitmapService* pBitmapService, TriglavPlugInInt width, TriglavPlugInInt height, Channels channels);
};
