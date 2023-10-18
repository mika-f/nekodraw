from abc import ABC, abstractmethod
from typing import Any, Generic, TypeVar


class Filter(ABC):
    @abstractmethod
    def register(self) -> None:
        """
        Register the filter to be called by the NekoBridge.

        Returns:
            None
        """
        pass

    @abstractmethod
    def unregister(self) -> None:
        """
        Unregister the filter from the NekoBridge.

        Returns:
            None
        """
        pass

    @abstractmethod
    def initialize(self) -> None:
        """
        Initializes the filter before running.

        Returns:
            None
        """
        pass

    @abstractmethod
    def run(self) -> None:
        """
        Runs the filter on the current image.

        Returns:
            None
        """
        pass

    @abstractmethod
    def terminate(self) -> None:
        """
        Cleans up the filter after running.

        Returns:
            None
        """
        pass


class EnumValue():
    """
    The value of enum
    """
    value: int


class PointValue():
    x: int
    y: int


class SizeValue():
    width: int
    height: int


class RectValue():
    left: int
    top: int
    right: int
    bottom: int


class RGBColorValue():
    red: int
    green: int
    blue: int


class CMYKColor():
    cyan: int
    magenta: int
    yellow: int
    key_plate: int


TValue = TypeVar("TValue")


class _Property(Generic[TValue]):
    value: TValue
    '''
    The value for stored in declared property
    '''


class VoidProperty(_Property[None]):
    '''
    Equivalent to kTriglavPlugInPropertyValueTypeVoid
    '''
    pass


class BoolProperty(_Property[bool]):
    '''
    Equivalent to kTriglavPlugInPropertyValueTypeBoolean
    '''
    pass


class EnumProperty(_Property[int]):
    '''
    Equivalent to kTriglavPlugInPropertyValueTypeEnumeration
    '''
    pass


class IntProperty(_Property[int]):
    '''
    Equivalent to kTriglavPlugInPropertyValueTypeInteger
    '''
    pass


class DecimalProperty(_Property[float]):
    '''
    Equivalent to kTriglavPlugInPropertyValueTypeDecimal
    '''
    pass


class PointProperty(_Property[PointValue]):
    '''
    Equivalent to kTriglavPlugInPropertyValueTypePoint
    '''
    pass


class StringProperty(_Property[str]):
    '''
    Equivalent to kTriglavPlugInPropertyValueTypeString
    '''
    pass


class Disposable:
    def dispose(self) -> None:
        """
        release the object explicitly
        """
        pass

    def __enter__(self):
        pass

    def __exit__(self, type: Any, value: Any, traceback: Any):
        pass


class BitmapObject(Disposable):
    def get_width(self) -> int:  # type: ignore
        """
        get width of bitmap object.
        it is equivalent of BitmapObject#getWidthProc().
        """
        pass

    def get_height(self) -> int:  # type: ignore
        """
        get height of bitmap object.
        it is equivalent of BitmapObject#getHeightProc().
        """
        pass

    def get_depth(self) -> int:  # type: ignore
        """
        get depth of bitmap object.
        it is equivalent of BitmapObject#getDepthProc().
        """
        pass

    def get_scan_line(self) -> int:  # type: ignore
        pass

    def get_address(self, point: PointValue) -> int:  # type: ignore
        pass

    def get_row_bytes(self) -> int:  # type: ignore
        pass

    def get_pixel_bytes(self) -> int:  # type: ignore
        pass


class OffscreenObject(Disposable):
    def get_width(self) -> int:  # type: ignore
        pass

    def get_height(self) -> int:  # type: ignore
        pass

    def get_rect(self) -> RectValue:  # type: ignore
        pass

    def get_extent_rect(self) -> RectValue:  # type: ignore
        pass

    def get_depth(self) -> int:  # type: ignore
        pass

    def get_channel_order(self) -> int:  # type: ignore
        pass

    def get_rgb_channel_index(self) -> tuple[int, int, int]:  # type: ignore
        pass

    def get_cmyk_channel_index(self) -> tuple[int, int, int, int]:  # type: ignore
        pass

    def get_block_rect_count(self, bounds: RectValue) -> int:  # type: ignore
        pass

    def get_block_rect(self, index: int, bounds: RectValue) -> int:  # type: ignore
        pass

    def get_block_image(self, pos: PointValue) -> tuple[int, int, int, RectValue]:  # type: ignore
        pass

    def get_block_alpha(self, pos: PointValue) -> tuple[int, int, int, RectValue]:  # type: ignore
        pass

    def get_block_select_area(self, pos: PointValue) -> tuple[int, int, int, RectValue]:  # type: ignore
        pass
