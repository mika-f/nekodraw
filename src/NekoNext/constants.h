#pragma once

#include "pch.h"


namespace NekoNext::Constants
{
    enum class ApiResult
    {
        Success = kTriglavPlugInAPIResultSuccess,
        Failed = kTriglavPlugInAPIResultFailed,
    };

    enum class BitmapScanLine
    {
        HorizontalLeftTop = kTriglavPlugInBitmapScanlineHorizontalLeftTop,
        HorizontalRightTop = kTriglavPlugInBitmapScanlineHorizontalRightTop,
        HorizontalLeftBottom = kTriglavPlugInBitmapScanlineHorizontalLeftBottom,
        HorizontalRightBottom = kTriglavPlugInBitmapScanlineHorizontalRightBottom,
        VerticalLeftTop = kTriglavPlugInBitmapScanlineVerticalLeftTop,
        VerticalRightTop = kTriglavPlugInBitmapScanlineVerticalRightTop,
        VerticalLeftBottom = kTriglavPlugInBitmapScanlineVerticalLeftBottom,
        VerticalRightBottom = kTriglavPlugInBitmapScanlineVerticalRightBottom,
    };

    enum class Boolean
    {
        True = kTriglavPlugInBoolTrue,
        False = kTriglavPlugInBoolFalse,
    };

    enum class CallResult
    {
        Success = kTriglavPlugInCallResultSuccess,
        Failed = kTriglavPlugInCallResultFailed,
    };

    enum class FilterRunProcessState
    {
        Start = kTriglavPlugInFilterRunProcessStateStart,
        Continue = kTriglavPlugInFilterRunProcessStateContinue,
        End = kTriglavPlugInFilterRunProcessStateEnd,
        Abort = kTriglavPlugInFilterRunProcessStateAbort,
    };

    enum class FilterRunProcessResult
    {
        Continue = kTriglavPlugInFilterRunProcessResultContinue,
        Restart = kTriglavPlugInFilterRunProcessResultRestart,
        Exit = kTriglavPlugInFilterRunProcessResultExit,
    };

    enum class FilterTargetKindRasterLayer
    {
        GrayAlpha = kTriglavPlugInFilterTargetKindRasterLayerGrayAlpha,
        RgbAlpha = kTriglavPlugInFilterTargetKindRasterLayerRGBAlpha,
        CmykAlpha = kTriglavPlugInFilterTargetKindRasterLayerCMYKAlpha,
        Alpha = kTriglavPlugInFilterTargetKindRasterLayerAlpha,
        BinarizationAlpha = kTriglavPlugInFilterTargetKindRasterLayerBinarizationAlpha,
        BinarizationGrayAlpha = kTriglavPlugInFilterTargetKindRasterLayerBinarizationGrayAlpha,
    };

    enum class OffscreenChannelOrder
    {
        Alpha = kTriglavPlugInOffscreenChannelOrderAlpha,
        GrayAlpha = kTriglavPlugInOffscreenChannelOrderGrayAlpha,
        RgbAlpha = kTriglavPlugInOffscreenChannelOrderRGBAlpha,
        CymkAlpha = kTriglavPlugInOffscreenChannelOrderCMYKAlpha,
        BinarizationAlpha = kTriglavPlugInOffscreenChannelOrderBinarizationAlpha,
        BinarizationGrayAlpha = kTriglavPlugInOffscreenChannelOrderBinarizationGrayAlpha,
        SelectArea = kTriglavPlugInOffscreenChannelOrderSelectArea,
        Plane = kTriglavPlugInOffscreenChannelOrderPlane,
    };

    enum class OffscreenCopyMode
    {
        Normal = kTriglavPlugInOffscreenCopyModeNormal,
        Image = kTriglavPlugInOffscreenCopyModeImage,
        Gray = kTriglavPlugInOffscreenCopyModeGray,
        Red = kTriglavPlugInOffscreenCopyModeRed,
        Green = kTriglavPlugInOffscreenCopyModeGreen,
        Blue = kTriglavPlugInOffscreenCopyModeBlue,
        Cyan = kTriglavPlugInOffscreenCopyModeCyan,
        Magenta = kTriglavPlugInOffscreenCopyModeMagenta,
        Yellow = kTriglavPlugInOffscreenCopyModeYellow,
        KeyPlate = kTriglavPlugInOffscreenCopyModeKeyPlate,
        Alpha = kTriglavPlugInOffscreenCopyModeAlpha,
    };

    enum class PropertyValueType
    {
        Void = kTriglavPlugInPropertyValueTypeVoid,
        Boolean = kTriglavPlugInPropertyValueTypeBoolean,
        Enumeration = kTriglavPlugInPropertyValueTypeEnumeration,
        Integer = kTriglavPlugInPropertyValueTypeInteger,
        Decimal = kTriglavPlugInPropertyValueTypeDecimal,
        Point = kTriglavPlugInPropertyValueTypePoint,
        String = kTriglavPlugInPropertyValueTypeString,
    };

    enum class PropertyInputKind
    {
        Hide = kTriglavPlugInPropertyInputKindHide,
        Defualt = kTriglavPlugInPropertyInputKindDefault,
        PushButton = kTriglavPlugInPropertyInputKindPushButton,
        Canvas = kTriglavPlugInPropertyInputKindCanvas,
    };

    enum class PropertyValueKind
    {
        Default = kTriglavPlugInPropertyValueKindDefault,
        Pixel = kTriglavPlugInPropertyValueKindPixel,
    };

    enum class PropertyPointDefaultValueKind
    {
        Default = kTriglavPlugInPropertyPointDefaultValueKindDefault,
        CanvasLeftTop = kTriglavPlugInPropertyPointDefaultValueKindCanvasLeftTop,
        CanvasRightTop = kTriglavPlugInPropertyPointDefaultValueKindCanvasRightTop,
        CanvasLeftBottom = kTriglavPlugInPropertyPointDefaultValueKindCanvasLeftBottom,
        CanvasRightBottom = kTriglavPlugInPropertyPointDefaultValueKindCanvasRightBottom,
        CanvasCenter = kTriglavPlugInPropertyPointDefaultValueKindCanvasCenter,
        SelectAreaLeftTop = kTriglavPlugInPropertyPointDefaultValueKindSelectAreaLeftTop,
        SelectAreaRightTop = kTriglavPlugInPropertyPointDefaultValueKindSelectAreaRightTop,
        SelectAreaLeftBottom = kTriglavPlugInPropertyPointDefaultValueKindSelectAreaLeftBottom,
        SelectAreaRightBottom = kTriglavPlugInPropertyPointDefaultValueKindSelectAreaRightBottom,
        SelectAreaCenter = kTriglavPlugInPropertyPointDefaultValueKindSelectAreaCenter,
    };

    enum class PropertyPointMinMaxValueKind
    {
        Default = kTriglavPlugInPropertyPointMinMaxValueKindDefault,
        No = kTriglavPlugInPropertyPointMinMaxValueKindNo,
    };

    enum class PropertyCallbackNotify
    {
        ValueChanged = kTriglavPlugInPropertyCallBackNotifyValueChanged,
        ButtonPushed = kTriglavPlugInPropertyCallBackNotifyButtonPushed,
        ValueCheck = kTriglavPlugInPropertyCallBackNotifyValueCheck,
    };

    enum class PropertyCallbackResult
    {
        NoModify = kTriglavPlugInPropertyCallBackResultNoModify,
        Modify = kTriglavPlugInPropertyCallBackResultModify,
        Invalid = kTriglavPlugInPropertyCallBackResultInvalid,
    };

    enum class Selector
    {
        ModuleInitialize = kTriglavPlugInSelectorModuleInitialize,
        ModuleTerminate = kTriglavPlugInSelectorModuleTerminate,
        FilterInitialize = kTriglavPlugInSelectorFilterInitialize,
        FilterRun = kTriglavPlugInSelectorFilterRun,
        FilterTerminate = kTriglavPlugInSelectorFilterTerminate,
    };
}
