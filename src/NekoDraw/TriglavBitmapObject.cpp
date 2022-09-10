#include "pch.h"

#include "TriglavBitmapObject.h"

TriglavPlugInInt TriglavBitmapObject::getWidth() const
{
    return this->_width;
}

TriglavPlugInInt TriglavBitmapObject::getHeight() const
{
    return this->_height;
}

Color TriglavBitmapObject::getColorFrom(TriglavPlugInPoint point) const
{
    TriglavPlugInPtr address;

    (*this->_pBitmapService).getAddressProc(&address, this->_bitmapObject, &point);

    const auto srcAddress = static_cast<BYTE*>(address);
    const auto r = srcAddress[this->_r];
    const auto g = srcAddress[this->_g];
    const auto b = srcAddress[this->_b];

    return {r, g, b};
}

void TriglavBitmapObject::setColorTo(TriglavPlugInPoint point, Color color) const
{
    TriglavPlugInPtr address;

    (*this->_pBitmapService).getAddressProc(&address, this->_bitmapObject, &point);

    const auto dstAddress = static_cast<BYTE*>(address);
    dstAddress[this->_r] = std::get<0>(color);
    dstAddress[this->_g] = std::get<1>(color);
    dstAddress[this->_b] = std::get<2>(color);
}

void TriglavBitmapObject::copyFrom(const TriglavPlugInOffscreenService* pOffscreenService, TriglavPlugInOffscreenObject sourceObject, const TriglavPlugInPoint* sourcePoint) const
{
    constexpr TriglavPlugInPoint bitmapSource{0, 0};
    (*pOffscreenService).getBitmapProc(this->_bitmapObject, &bitmapSource, sourceObject, sourcePoint, this->_width, this->_height, kTriglavPlugInOffscreenCopyModeImage);
}

void TriglavBitmapObject::copyTo(const TriglavPlugInOffscreenService* pOffscreenService, TriglavPlugInOffscreenObject destinationObject, const TriglavPlugInPoint* destinationPoint) const
{
    constexpr TriglavPlugInPoint bitmapSource{0, 0};
    (*pOffscreenService).setBitmapProc(destinationObject, destinationPoint, this->_bitmapObject, &bitmapSource, this->_width, this->_height, kTriglavPlugInOffscreenCopyModeImage);
}

void TriglavBitmapObject::Release() const
{
    (*this->_pBitmapService).releaseProc(this->_bitmapObject);
}


TriglavBitmapObject* TriglavBitmapObject::create(TriglavPlugInBitmapService* pBitmapService, TriglavPlugInInt width, TriglavPlugInInt height, Channels channels)
{
    TriglavPlugInBitmapObject bitmapObject = nullptr;
    (*pBitmapService).createProc(&bitmapObject, width, height, 3, kTriglavPlugInBitmapScanlineHorizontalLeftTop);

    return new TriglavBitmapObject(pBitmapService, bitmapObject, width, height, std::move(channels));
}
