from contextlib import contextmanager
from typing import Optional
from nekobridge.types import BitmapObject, OffscreenObject


@contextmanager  # type: ignore
def create_bitmap(width: int, height: int, depth: int, scan_line: int) -> Optional[BitmapObject]:  # type: ignore
    """
    create a bitmap object.
    it is equivalent of BitmapService#createProc.
    """
    pass


@contextmanager  # type: ignore
def create_offscreen(width: int, height: int, depth: int) -> OffscreenObject:  # type: ignore
    """
    create the offscreen object.
    it is equivalent of OffscreenService#createProc.
    """
    pass
