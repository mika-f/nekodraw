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

[REQUIREMENTS-HARDWARE](./REQUIREMENTS-HARDWARE.md) を参照ください。

## ダウンロード

下記から、4 つのファイルをダウンロードしてください。

1. NekoDraw ソースコード
   1. clone してください
2. Stable Diffusion 学習済みモデル
   1. [Hugging Face の該当ページ](https://huggingface.co/CompVis/stable-diffusion-v-1-4-original)から、最新の `sd-v1-4.ckpt` をダウンロードしてください
   2. ※数 GB ありますのでご注意ください

## コード編集

```bash
$ cmake -S ./src/NekoDraw -B ./build
```

したあと、 `build/NekoDraw.sln` を開きます。

## ビルド

```bash
$ cmake -S ./src/NekoDraw -B ./build
```

したあと、 `build/NekoDraw.sln` をビルドします。

## オプション

以下のコンパイルオプションが利用可能です。

- `FORCE_16BIT_FLOAT=(ON|OFF)`
  - VRAM のサイズにかかわらず、強制的に半精度のモデルを使用します
  - デフォルトは OFF で、 10GB より少ないメモリの場合のみ半精度のモデルを使用します

実行例：

```bash
$ cmake -S ./src/NekoDraw -B ./build -DFORCE_16BIT_FLOAT=ON
```
