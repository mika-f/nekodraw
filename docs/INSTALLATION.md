# INSTALLATION

ここでは、 NekoDraw を CLIP STUDIO PAINT で使用できるようにするためのインストール～設定について記述します。

## Requirements

以下の環境が必須です

### ソフトウェア要件

- Windows 10 以上 (古い Windows でも動きますが、サポートしません)
- [VC++ Runtime 2015-2022](https://docs.microsoft.com/ja-jp/cpp/windows/latest-supported-vc-redist?view=msvc-170#visual-studio-2015-2017-2019-and-2022)
  - これについて、後々使用している C++ のバージョンを下げるなどを行い、 CLIP STUDIO PAINT とバージョンを合わせる予定です
- CLIP STUDIO PAINT EX (EX のみプラグインが使用可能です)

### ハードウェア要件 (推奨)

- 32GB 以上のメモリ
  - 手元の PC では、 512x512px の画像 (img2img) にて、 ~19GB のメモリを消費しています
- GeForce RTX 3060 もしくは VRAM か 8GB 以上のビデオカード (NVIDIA 製)
  - 手元の PC では、 512x512px の画像 (img2img) にて、 ~3GB のメモリを消費しています

### 心構え

- 作業中のデータが落ちてもわたしを責めないでください、自己責任でご利用ください

## ダウンロード

下記から、2 つのファイルをダウンロードしてください。

1. NekoDraw プラグイン本体
   1. CLIP STUDIO PAINT 公式ストアから配布されるまでは、個別にお問い合わせください : [@6jz](https://twitter.com.6jz)
   2. もしくは、自前で Stable Diffusion が実行可能な Python 環境を用意し、ビルドすることでも可能です
2. Stable Diffusion 学習済みモデル
   1. [Hugging Face の該当ページ](https://huggingface.co/CompVis/stable-diffusion-v-1-4-original)から、最新の `sd-v1-4.ckpt` をダウンロードしてください
   2. ※数 GB ありますのでご注意ください

## 解凍

以下のファイルについて、解凍を行ってください。  
**なお、ランタイム内にある zip ファイル (`python310.zip` および `stable-diffusion.zip`) については解凍を行わないでください。**

1. `NekoDraw-Plugin-vx.x.x.zip`

## 配置

各ファイルについて所定の場所に設置します。

### `NekoDraw` フォルダー

解凍後にでてくる `NekoDraw` フォルダーは、以下に配置してください。

```
%APPDATA%\CELSYSUserData\CELSYS\CLIPStudioModule\PlugIn\PAINT
```

### `sd-v1-4.ckpt`

ダウンロードした Stable Diffusion のモデルデータは、ランタイムの中に設置します。  
`NekoDraw` のフォルダー以下の、 `models\ldm\stable-diffusion-v1` に、名前を変更せずに設置してください。

## 起動

ここまでくれば、あとは CLIP STUDIO PAINT EX を起動するだけで、フィルター項目に「Stable Diffusion」が追加されています。  
おつかれさまでした。

## 不明点について

不明点などがありましたら、 Twitter アカウント [@6jz](https://twitter.com/6jz) までご連絡ください。

## サポートについて

サポートについては GitHub アカウントをお持ちの方は Issue もしくは PR にて、その他の方は上記 Twitter までご連絡ください。  
専用ではないですが、創作 Discord もありますので、こちらでも受け付け可能です。

https://discord.gg/vpjhenyT29 (#nekodraw channel)
