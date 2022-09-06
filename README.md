# NekoDraw: CLIP STUDIO PAINT Filter Plugin

[English](./README.md) | [日本語](./README.ja.md)

> THIS PROJECT IS EXPERIMENTAL. USE IT AT YOUR OWN RISK.

CLIP STUDIO PAINT filter plugin for executing Stable Diffusion txt2img, img2img processor.  
This plugin filter runs Stable Diffusion in local environment.  
So if you want to use this filter, greater than 12GB (allocated) of RAM and greater than 8GB (filters to 512x512) of VRAM.

## Videos

- Text to Image : https://twitter.com/6jz/status/1566052868016054272
- Image to Image : https://twitter.com/6jz/status/1566812883433902080

## Installation

Please visit [INSTALLATION](./docs/INSTALLATION.md) (Japanese).

## Usage

Please visit below documents:

- [PROMPT](./docs/PROMPT.md) (Japanese)

## FAQ

### Why use local environment?

Basically, we believe that publishing illustrations in progress on the Internet or on services that can be censored, such as Google, would lead to the leakage of confidential information.  
And they will also be at risk of account loss.

## License

MIT by [@6jz](https://twitter.com/6jz)

### Third Party Notices

Dependencies are not optimized. Some packages will be removed in future updates.

#### Apache Version 2

- [`absl-py`](https://pypi.org/project/absl-py/)
- [`aiohttp`](https://pypi.org/project/aiohttp/)
- [`aiosignal`](https://pypi.org/project/aiosignal/)
- [`async-timeout`](https://pypi.org/project/async-timeout/)
- [`frozenlist`](https://pypi.org/project/frozenlist/)
- [`google-auth`](https://pypi.org/project/google-auth/)
- [`google-auth-oauthlib`](https://pypi.org/project/google-auth-oauthlib/)
- [`grpcio`](https://pypi.org/project/grpcio/)
- [`huggingface-hub`](https://pypi.org/project/huggingface-hub/)
- [`importlib-metadata`](https://pypi.org/project/importlib-metadata/)
- [`kornia`](https://pypi.org/project/kornia/)
- [`multidict`](https://pypi.org/project/multidict/)
- [`packaging`](https://pypi.org/project/packaging/) - or BSD 2 Clause
- [`pyarrow`](https://pypi.org/project/pyarrow/)
- [`pydeck`](https://pypi.org/project/pydeck/)
- [`Pympler`](https://pypi.org/project/Pympler/)
- [`python-dateutil`](https://pypi.org/project/python-dateutil/) - or BSD
- [`pytorch-lightning`](https://pypi.org/project/pytorch-lightning/)
- [`pytz-deprecation-shim`](https://pypi.org/project/pytz-deprecation-shim/)
- [`regex`](https://pypi.org/project/regex/)
- [`requests`](https://pypi.org/project/requests/)
- [`rsa`](https://pypi.org/project/rsa/)
- [`streamlit`](https://pypi.org/project/streamlit/)
- [`tensorboard`](https://pypi.org/project/tensorboard/)
- [`tensorboard-data-server`](https://pypi.org/project/tensorboard-data-server/)
- [`tensorboard-plugin-wit`](https://pypi.org/project/tensorboard-plugin-wit/)
- [`torch-fidelity`](https://pypi.org/project/torch-fidelity/)
- [`torchmetrics`](https://pypi.org/project/torchmetrics/)
- [`tornado`](https://pypi.org/project/tornado/)
- [`transformers`](https://pypi.org/project/transformers/)
- [`tzdata`](https://pypi.org/project/tzdata/)
- [`watchdog`](https://pypi.org/project/watchdog/)
- [`yarl`](https://pypi.org/project/yarl/)

#### BSD

- [`antlr4-python3-runtime`](https://pypi.org/project/antlr4-python3-runtime/)
- [`colorama`](https://pypi.org/project/colorama/)
- [`fsspec`](https://pypi.org/project/fsspec/)
- [`gitdb`](https://pypi.org/project/gitdb/)
- [`GitPython`](https://pypi.org/project/GitPython/)
- [`Markdown`](https://pypi.org/project/Markdown/)
- [`networkx`](https://pypi.org/project/networkx/)
- [`numpy`](https://pypi.org/project/numpy/)
- [`oauthlib`](https://pypi.org/project/oauthlib/)
- [`omegaconf`](https://pypi.org/project/omegaconf/)
- [`pyasn1`](https://pypi.org/project/pyasn1/)
- [`Pygments`](https://pypi.org/project/Pygments/)
- [`requests-oauthlib`](https://pypi.org/project/requests-oauthlib/)
- [`scipy`](https://pypi.org/project/scipy/)
- [`semver`](https://pypi.org/project/semver/)
- [`smmap`](https://pypi.org/project/smmap/)
- [`tifffile`](https://pypi.org/project/tifffile/)
- [`tokenizers`](https://pypi.org/project/tokenizers/)
- [`toolz`](https://pypi.org/project/toolz/)
- [`torchaudio`](https://pypi.org/project/torchaudio/)
- [`torchvision`](https://pypi.org/project/torchvision/)
- [`pybind11`](https://github.com/pybind/pybind11)

#### BSD 2-Clause

- [`imageio`](https://pypi.org/project/imageio/)
- [`imageio-ffmpeg`](https://pypi.org/project/imageio-ffmpeg/)
- [`pyasn1-modules`](https://pypi.org/project/pyasn1-modules/)

#### BSD 3-Clause

- [`altair`](https://pypi.org/project/altair/)
- [`click`](https://pypi.org/project/click/)
- [`commonmark`](https://pypi.org/project/commonmark/)
- [`idna`](https://pypi.org/project/idna/)
- [`Jinja2`](https://pypi.org/project/Jinja2/)
- [`MarkupSafe`](https://pypi.org/project/MarkupSafe/)
- [`pandas`](https://pypi.org/project/pandas/)
- [`protobuf`](https://pypi.org/project/protobuf/)
- [`torch`](https://pypi.org/project/torch/)
- [`Werkzeug`](https://pypi.org/project/Werkzeug/)

#### Modified BSD

- [`scikit-image`](https://pypi.org/project/scikit-image/)

#### New BSD

- [`decorator`](https://pypi.org/project/decorator/)

#### CreativeML Open RAIL-M

- [`stable-diffusion`](https://github.com/CompVis/stable-diffusion)
- [`stable-diffusion (optimized)`](https://github.com/basujindal/stable-diffusion)

#### Historical Permission Notice and Disclaimer

- [`Pillow`](https://pypi.org/project/Pillow/)

#### LGPL

- [urwid](https://pypi.org/project/urwid/)

#### MIT

- [`albumentations`](https://pypi.org/project/albumentations/)
- [`attrs`](https://pypi.org/project/attrs/)
- [`blinker`](https://pypi.org/project/blinker/)
- [`cachetools`](https://pypi.org/project/cachetools/)
- [`charset-normalizer`](https://pypi.org/project/charset-normalizer/)
- [`einops`](https://pypi.org/project/einops/)
- [`entrypoints`](https://pypi.org/project/entrypoints/)
- [`ftfy`](https://pypi.org/project/ftfy/)
- [`future`](https://pypi.org/project/future/)
- [`imgaug`](https://pypi.org/project/imgaug/)
- [`jsonschema`](https://pypi.org/project/jsonschema/)
- [`latent-diffusion`](https://github.com/CompVis/latent-diffusion)
- [`opencv-python`](https://pypi.org/project/opencv-python/)
- [`opencv-python-headless`](https://pypi.org/project/opencv-python-headless/)
- [`pip`](https://pypi.org/project/pip/)
- [`pubd`](https://pypi.org/project/pudb/)
- [`pyDeprecate`](https://pypi.org/project/pyDeprecate/)
- [`pyparsing`](https://pypi.org/project/pyparsing/)
- [`pyrsistent`](https://pypi.org/project/pyrsistent/)
- [`pytz`](https://pypi.org/project/pytz/)
- [`PyWavelets`](https://pypi.org/project/PyWavelets/)
- [`PyYAML`](https://pypi.org/project/PyYAML/)
- [`rich`](https://pypi.org/project/rich/)
- [`setuptools`](https://pypi.org/project/setuptools/)
- [`six`](https://pypi.org/project/six/)
- [`test-tube`](https://pypi.org/project/test-tube/)
- [`toml`](https://pypi.org/project/toml/)
- [`tqdm`](https://pypi.org/project/tqdm/) - or MPL 2.0
- [`tzlocal`](https://pypi.org/project/tzlocal/)
- [`urllib3`](https://pypi.org/project/urllib3/)
- [`validators`](https://pypi.org/project/validators/)
- [`wcwidth`](https://pypi.org/project/wcwidth/)
- [`wheel`](https://pypi.org/project/wheel/)
- [`zipp`](https://pypi.org/project/zipp/)
- [`git+CLIP`](https://github.com/openai/CLIP)
- [`git+taming-transformers`](https://github.com/CompVis/taming-transformers)

#### MPL 2.0

- [`certifi`](https://pypi.org/project/certifi/)

#### Public Domain

- [`filelock`](https://pypi.org/project/filelock/)

#### Python Software Foundation

- [`typing-extensions`](https://pypi.org/project/typing-extensions/)
