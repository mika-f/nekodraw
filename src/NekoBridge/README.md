# NekoBridge

NekoBridge is a Python binding API for CLIP STUDIO PAINT. It enables developers to write plugins using Python and provides a straightforward and accessible programming experience, even for beginners.

## Features

- Enables writing plugins for CLIP STUDIO PAINT using Python
- Provides an easy-to-use programming experience for both beginners and experts
- Allows defining user interfaces and other features using standard Python syntax

## Installation

1. Download `NekoBridge-vx.x.x.zip` from [GitHub Releases](https://github.com/mika-f/nekodraw/releases/latest)
2. Extract downloaded zip archive into `%APPDATA%/CELSYSUserData/CELSYS/CLIPStudioModule/Plugin/PAINT%`
3. Create a NekoBridge plugins directory at `%APPDATA%/CELSYSUserData/CELSYS/CLIPStudioModule/Plugin/NekoBridge`
4. Download NekoBridge plugins into the above directory.
5. Launch CLIP STUDIO PAINT EX

## Development Plugin

To use NekoBridge, import the neko module and start writing your plugin using Python:

```python
import nekobridge

@nekobridge.plugin(name="MyPlugin", id="201A2468-4DBA-4080-811D-04EA344C543B", version=(1, 0, 0), api_version=(1, 0, 0), csp_version=(2, 0, 0), sdk_version=(2021, 8, 27))
class MyPlugin(nekobridge.Plugin):
    def __init__(self):
      pass

    def register(self):
      pass

    def unregister(self):
      pass

    def initialize(self):
      pass

    def run(self):
      pass

    def terminate(self):
      pass
```

### Development Extension

To develop NekoBridge, you must require the following instructions:

- Visual Studio 2022
- CLIP STUDIO PAINT SDK
- git
- cmake

and run the following command:

- `cmake -S ./ -B ./build/`

## License

NekoBridge is licensed under the MIT License. See LICENSE for more information.

## Contributing

Contributions to NekoBridge are always welcome! If you want to contribute, please read CONTRIBUTING.md for more information on how to get started.

## Contact

If you have any questions or issues, please feel free to contact us at `me@natsuneko.cat` with including "NekoBridge" in subject.
