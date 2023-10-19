from typing import Any, Callable, TypedDict
from typing_extensions import Unpack, NotRequired


class DecoratorArgs(TypedDict):
    """NekoPyBinding plugin interface and entry point"""
    id: str
    """the plugin id, the value must be GUID string and unique"""
    name: str
    """the plugin name, the value is not displayed in CLIP STUDIO PAINT but used for internal in NekoPyBinding"""
    description: NotRequired[str]
    """the plugin description, the value is not displayed in CLIP STUDIO PAINT but used for internal in NekoPyBinding"""
    author: NotRequired[str]
    """the plugin author, the value is not displayed in CLIP STUDIO PAINT but used for internal in NekoPyBinding"""
    api_version: NotRequired[tuple[int, int, int]]
    """the plugin api version, this value must be (2021, 8, 27), it is same as CLIP STUDIO PAINT SDK version"""
    csp_version: NotRequired[tuple[int, int, int]]
    """the clip studio paint version, the value is not displayed in CLIP STUDIO PAINT but used for internal in NekoPyBinding"""
    sdk_version: NotRequired[tuple[int, int, int]]
    """the plugin sdk version, the value is not displayed in CLIP STUDIO PAINT but used for internal in NekoPyBinding"""
    version: NotRequired[tuple[int, int, int]]
    """the plugin version, the value is not displayed in CLIP STUDIO PAINT but used for internal in NekoPyBinding"""


def plugin(*args: Any, **kwargs: Unpack[DecoratorArgs]) -> Callable[[Any], Any]:  # type: ignore
    pass
