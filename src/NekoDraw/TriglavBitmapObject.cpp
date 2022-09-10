#include "pch.h"

#include "TriglavBitmapObject.h"

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

void TriglavBitmapObject::setColorTo(TriglavPlugInPoint point, Color color)
{
    TriglavPlugInPtr address;

    (*this->_pBitmapService).getAddressProc(&address, this->_bitmapObject, &point);

    const auto dstAddress = static_cast<BYTE*>(address);
    dstAddress[this->_r] = std::get<0>(color);
    dstAddress[this->_g] = std::get<1>(color);
    dstAddress[this->_b] = std::get<2>(color);
}
