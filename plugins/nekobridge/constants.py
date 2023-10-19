from typing import Literal


class _const:
    pass


class Boolean(_const):
    """
    Plugin boolean constants.
    """
    TRUE: Literal[1] = 1
    """
    Plugin boolean value representing "true".
    """

    FALSE: Literal[0] = 0
    """
    Plugin boolean value representing "false".
    """


class CallResult(_const):
    """
    Plugin return value constants.
    """
    SUCCESS: Literal[0] = 0
    """
    Plugin return value representing "success".
    This value should be used as the return value of `register()` and `unregister()` functions.
    """

    FAILED: Literal[-1] = -1
    """
    Plugin return value representing "failure".
    This value should be used as the return value of `register()` and `unregister()` functions.
    """


class ApiResult(_const):
    """
    Plugin api return value constants.
    """
    SUCCESS: Literal[0] = 0
    """
    Plugin return value representing "success".
    """

    FAILED: Literal[-1] = -1
    """
    Plugin return value representing "failure".
    """


class FilterRunProcessState(_const):
    """
    Enum class representing the processing state of the plugin filter execution.
    """
    START: Literal[0x0101] = 0x0101
    """
    Represents the start of the processing.
    """
    CONTINUE: Literal[0x0102] = 0x0102
    """
    Represents the continuation of the processing.
    """
    END: Literal[0x0103] = 0x0103
    """
    Represents the end of the processing.
    """
    ABORT: Literal[0x0104] = 0x0104
    """
    Represents the abortion of the processing.
    """


class FilterRunProcessResult(_const):
    CONTINUE: Literal[0x0201]
    RESTART: Literal[0x0202]
    EXIT: Literal[0x0203]


class FilterTargetKindRasterLayer(_const):
    GRAY_ALPHA: Literal[0x0101]
    RGB_ALPHA: Literal[0x0102]
    CMYK_ALPHA: Literal[0x0103]
    ALPHA: Literal[0x0104]
    BINARIZATION_ALPHA: Literal[0x0105]
    BINARIZATION_GRAY_ALPHA: Literal[0x0106]


class BitmapScanLine(_const):
    HORIZONTAL_LEFT_TOP: Literal[0x10]
    HORIZONTAL_RIGHT_TOP: Literal[0x11]
    HORIZONTAL_LEFT_BOTTOM: Literal[0x12]
    HORIZONTAL_RIGHT_BOTTOM: Literal[0x13]
    VERTICAL_LEFT_TOP: Literal[0x14]
    VERTICAL_RIGHT_TOP: Literal[0x15]
    VERTICAL_LEFT_BOTTOM: Literal[0x16]
    VERTICAL_RIGHT_BOTTOM: Literal[0x17]


class OffscreenChannelOrder(_const):
    ALPHA: Literal[0x01]
    GRAY_ALPHA: Literal[0x02]
    RGB_ALPHA: Literal[0x03]
    CMYK_ALPHA: Literal[0x04]
    BINARIZATION_ALPHA: Literal[0x05]
    BINARIZATION_GRAY_ALPHA: Literal[0x06]
    SELECT_AREA: Literal[0x10]
    PLANE: Literal[0x20]


class OffscreenCopyMode(_const):
    NORMAL: Literal[0x01]
    IMAGE: Literal[0x02]
    GRAY: Literal[0x03]
    RED: Literal[0x04]
    GREEN: Literal[0x05]
    BLUE: Literal[0x06]
    CYAN: Literal[0x07]
    MAGENTA: Literal[0x08]
    YELLOW: Literal[0x09]
    KEY_PLATE: Literal[0x10]
    ALPHA: Literal[0x11]


class PropertyValueType(_const):
    VOID: Literal[0x00]
    BOOLEAN: Literal[0x01]
    ENUMERATION: Literal[0x02]
    INTEGER: Literal[0x11]
    DECIMAL: Literal[0x12]
    POINT: Literal[0x21]
    STRING: Literal[0x31]


class PropertyInputKind(_const):
    HIDE: Literal[0x10]
    DEFAULT: Literal[0x11]
    PUSH_BUTTON: Literal[0x21]
    CANVAS: Literal[0x31]


class PropertyValueKind(_const):
    DEFAULT: Literal[0x11]
    PIXEL: Literal[0x21]


class PropertyPointDefaultValueKind(_const):
    DEFAULT: Literal[0x11]
    CANVAS_LEFT_TOP: Literal[0x21]
    CANVAS_RIGHT_TOP: Literal[0x22]
    CANVAS_LEFT_BOTTOM: Literal[0x23]
    CANVAS_RIGHT_BOTTOM: Literal[0x24]
    CANVAS_CENTER: Literal[0x25]
    SELECT_AREA_LEFT_TOP: Literal[0x31]
    SELECT_AREA_RIGHT_TOP: Literal[0x32]
    SELECT_AREA_LEFT_BOTTOM: Literal[0x33]
    SELECT_AREA_RIGHT_BOTTOM: Literal[0x34]
    SELECT_AREA_CENTER: Literal[0x35]


class PropertyPointMinMaxValueKind(_const):
    DEFAULT: Literal[0x21]
    NO: Literal[0x22]


class PropertyCallbackNotify(_const):
    VALUE_CHANGED: Literal[0x11]
    BUTTON_PUSHED: Literal[0x21]
    VALUE_CHECK: Literal[0x31]


class PropertyCallbackResult(_const):
    NO_MODIFY: Literal[0x01]
    MODIFY: Literal[0x02]
    INVALID: Literal[0x03]
