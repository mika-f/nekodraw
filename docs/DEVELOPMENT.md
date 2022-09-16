# DEVELOPMENT

ここでは、 NekoDraw を開発するための方法を記述します。

## Requirements

以下の環境が必要です

### ソフトウェア要件

- Windows 10 以上
- 開発ツール
  - Visual Studio 2022
  - [VC++ Runtime 2015-2022](https://docs.microsoft.com/ja-jp/cpp/windows/latest-supported-vc-redist?view=msvc-170#visual-studio-2015-2017-2019-and-2022)
    - これについて、後々使用している C++ のバージョンを下げるなどを行い、 CLIP STUDIO PAINT とバージョンを合わせる予定です
  - cmake
- CLIP STUDIO PAINT
  - CLIP STUDIO PAINT EX (EX のみプラグインが使用可能です)
  - CLIP STUDIO PAINT SDK

### ハードウェア要件 (推奨)

- 32GB 以上のメモリ
  - 手元の PC では、 512x512px の画像 (img2img) にて、 ~19GB のメモリを消費しています
- GeForce RTX 3060 もしくは VRAM か 8GB 以上のビデオカード (NVIDIA 製)
  - 手元の PC では、 512x512px の画像 (img2img) にて、 ~3GB のメモリを消費しています

## ダウンロード

下記から、4 つのファイルをダウンロードしてください。

1. NekoDraw ソースコード
   1. clone してください
2. NekoDraw ランタイム
   1. [Natsuneko Laboratory Archives](https://archive.natsuneko.moe/n/e/NekoDraw/Runtime/NekoDraw-Runtime-v0.1.0.zip) から、最新の `NekoDraw-Runtime-vx.x.x.zip` をダウンロードしてください
   2. ※数 GB ありますのでご注意ください
3. NekoDraw 設定構成ファイル
   1. [GitHub Releases ページ](https://github.com/mika-f/nekodraw/releases/latest)から、最新の `NekoDraw-Conf-vx.x.x.zip` をダウンロードしてください
4. Stable Diffusion 学習済みモデル
   1. [Hugging Face の該当ページ](https://huggingface.co/CompVis/stable-diffusion-v-1-4-original)から、最新の `sd-v1-4.ckpt` をダウンロードしてください
   2. ※数 GB ありますのでご注意ください

## コード編集

`src/NekoDraw` で `cmake CMakeLists.txt` したあと、 `build` に生えた `NekoDraw.sln` を開いて編集してください。

## ビルド

`src/NekoDraw` で `cmake CMakeLists.txt` したあと、 `build` に生えたソリューションをビルドしてください。
