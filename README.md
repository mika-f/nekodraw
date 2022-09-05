# NekoDraw: CLIP STUDIO PAINT Filter Plugin

[English](./README.md) | [日本語](./README.ja.md)

> THIS PROJECT IS EXPERIMENTAL. USE IT AT YOUR OWN RISK.

CLIP STUDIO PAINT filter plugin for executing Stable Diffusion txt2img, img2img processor.  
This plugin filter runs Stable Diffusion in local environment.  
So if you want to use this filter, greater than 12GB (allocated) of RAM and greater than 8GB (filters to 512x512) of VRAM.

## Videos

- Text to Image : https://twitter.com/6jz/status/1566052868016054272
- Image to Image : TODO

## Requirements

- Windows 10 or greater (maybe worked on older Windows, but not supported)
- &gt;= 16GB Memory (12GB Free)
- GeForce RTX 3060 Video Card (>= 8GB VRAM) or equivalent GPU.
- NekoDraw Runtime
  - I want to distribute this runtime in the future in this GitHub page.
  - This runtime requires 40GB of free HDD/SSD spaces (including Stable Diffusion models)

## Usage

1. Download Plugin (`.cpm`) from GitHub Releases : [Download](https://github.com)
2. Download Runtime from Natsuneko Laboratory S3 : [Download](https://archive.natsuneko.moe)
3. Configure `NekoDraw.ini` in CLIP STUDIO PAINT : [Help Doc](https://docs.natsuneko.moe)

## Configure

Open `NekoDraw.ini` in your favorite text editor and edit below:

```txt
[NekoDraw]
NekoDrawRuntimeUri=[FULL_PATH_OF_NEKODRAW_RUNTIME]
```

For Example:

```txt[NekoDraw]
NekoDrawRuntimeUri=M:\repos\github.com\mika-f\nekodraw\runtime\NekoDraw
```

and place it `NekoDraw.cpm` into same plugin directory.  
Plugin is usually stored `%APPDATA%/CELSYSUserData\CELSYS\CLIPStudioModule\PlugIn\PAINT`.

## License

Not specified.
