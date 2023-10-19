import nekobridge


@nekobridge.decorators.plugin(
    name="MyPlugin", id="201A2468-4DBA-4080-811D-04EA344C543B", version=(1, 0, 0)
)
class SamplePlugin:  # (nekobridge.types.Filter):
    # _enum_a = nekobridge.props.EnumValue("A", "Enum A", 0, "a")
    # _enum_b = nekobridge.props.EnumValue("B", "Enum B", 1, "b")
    # _enum_c = nekobridge.props.EnumValue("C", "Enum C", 2, "c")

    # _void = nekobridge.props.VoidProperty("Void", "This is a void property via NekoBridge", "a")
    # _bool = nekobridge.props.BoolProperty("Bool", "This is a bool property via NekoBridge", "b", default=True)
    # _enum = nekobridge.props.EnumProperty("Enum", "This is a enum property via NekoBridge", "c", items=[_enum_a, _enum_b, _enum_c])
    # _int = nekobridge.props.IntProperty("Int", "This is a int property via NekoBridge", "d", default=50, min=0, max=100)
    # _decimal = nekobridge.props.DecimalProperty("Decimal", "This is a decimal property via NekoBridge", "e", default=0.5, min=0, max=1)
    # _point = nekobridge.props.PointProperty("Point", "This is a point property via NekoBridge", "f")
    # _string = nekobridge.props.StringProperty("String", "This is a string property via NekoBridge", "g", default="Hello", min_length=1, max_length=100)

    def __init__(self) -> None:
        print("class created")
        pass

    def __del__(self) -> None:
        print("class destroyed")
        pass

    def register(self) -> None:
        print("Are you ready?")
        pass
        # return super().register()

    def unregister(self) -> None:
        pass
        # return super().unregister()

    def initialize(self) -> None:
        pass
        # return super().initialize()

    def run(self) -> None:
        pass
        # return super().run()

    def terminate(self) -> None:
        pass
        # return super().terminate()
