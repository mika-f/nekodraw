from typing import Callable, Optional
import nekobridge.types


def VoidProperty(
    name: str,
    description: str,
    shortcut: str,
    kind: Optional[int] = None,
    callback: Optional[Callable[[], None]] = None
) -> nekobridge.types.VoidProperty:  # type: ignore
    """
    Returns a new void property definition.

    Arguments:
        name        - property name
        description - property description
        shortcut    - shortcut key for accessing this property, must be one character
        kind        - kind of property

    Returns:
        nekobridge.types.VoidProperty
    """
    pass


def BoolProperty(
    name: str,
    description: str,
    shortcut: str,
    kind: Optional[int] = None,
    default: bool = False,
    callback: Optional[Callable[[bool], None]] = None
) -> nekobridge.types.BoolProperty:  # type: ignore
    pass


def EnumProperty(
    name: str,
    description: str,
    shortcut: str,
    kind: Optional[int] = None,
    items: list[nekobridge.types.EnumValue] = [],
    callback: Optional[Callable[[nekobridge.types.EnumValue], None]] = None
) -> nekobridge.types.EnumProperty:  # type: ignore
    pass


def EnumValue(
    name: str,
    description: str,
    value: int,
    shortcut: str
) -> nekobridge.types.EnumValue:  # type: ignore
    pass


def IntProperty(
    name: str,
    description: str,
    shortcut: str,
    kind: Optional[int] = None,
    default: Optional[int] = None,
    min: Optional[int] = None,
    max: Optional[int] = None,
    callback: Optional[Callable[[int], None]] = None
) -> nekobridge.types.IntProperty:  # type: ignore
    pass


def DecimalProperty(
    name: str,
    description: str,
    shortcut: str,
    kind: Optional[int] = None,
    default: Optional[float] = None,
    min: Optional[float] = None,
    max: Optional[float] = None,
    callback: Optional[Callable[[int], None]] = None
) -> nekobridge.types.DecimalProperty:  # type: ignore
    pass


def PointProperty(
    name: str,
    description: str,
    shortcut: str,
    kind: Optional[int] = None,
    default: Optional[nekobridge.types.PointValue] = None,
    default_kind: Optional[int] = None,
    min: Optional[nekobridge.types.PointValue] = None,
    max: Optional[nekobridge.types.PointValue] = None,
    min_max_kind: Optional[int] = None,
    callback: Optional[Callable[[int], None]] = None
) -> nekobridge.types.PointProperty:  # type: ignore
    pass


def StringProperty(
    name: str,
    description: str,
    shortcut: str,
    kind: Optional[int] = None,
    default: Optional[str] = None,
    min_length: Optional[int] = None,
    max_length: Optional[int] = None,
    callback: Optional[Callable[[str], None]] = None
) -> nekobridge.types.StringProperty:  # type: ignore
    pass
