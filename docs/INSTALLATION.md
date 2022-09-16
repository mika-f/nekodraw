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

下記から、4 つのファイルをダウンロードしてください。

1. NekoDraw プラグイン本体
   1. CLIP STUDIO PAINT 公式ストアから配布されるまでは、個別にお問い合わせください : [@6jz](https://twitter.com.6jz)
   2. もしくは、自前でビルドすることも可能です
2. NekoDraw ランタイム
   1. [Natsuneko Laboratory Archives](https://archive.natsuneko.moe/n/e/NekoDraw/Runtime/NekoDraw-Runtime-v0.1.0.zip) から、最新の `NekoDraw-Runtime-vx.x.x.zip` をダウンロードしてください
   2. ※数 GB ありますのでご注意ください
3. NekoDraw 設定構成ファイル
   1. [GitHub Releases ページ](https://github.com/mika-f/nekodraw/releases/latest)から、最新の `NekoDraw-Conf-vx.x.x.zip` をダウンロードしてください
4. Stable Diffusion 学習済みモデル
   1. [Hugging Face の該当ページ](https://huggingface.co/CompVis/stable-diffusion-v-1-4-original)から、最新の `sd-v1-4.ckpt` をダウンロードしてください
   2. ※数 GB ありますのでご注意ください

## 解凍

以下のファイルについて、解凍を行ってください。  
**なお、ランタイム内にある zip ファイル (`python310.zip`) については解凍を行わないでください。**

1. `NekoDraw-Plugin-vx.x.x.zip`
2. `NekoDraw-Runtime-vx.x.x.zip`
3. `NekoDraw-Conf-vx.x.x.zip`

## 配置

各ファイルについて所定の場所に設置します。

### `NekoDraw.cpm`

`NekoDraw-Plugin-vx.x.x.zip` を解凍した中にあるフォルダー (`NekoDraw`) は、以下の場所に設置してください。

```
%APPDATA%\CELSYSUserData\CELSYS\CLIPStudioModule\PlugIn\PAINT
```

エクスプローラーを開いて、アドレスバーにそのまま打ち込むことで移動が可能です。  
すでに他のプラグインを導入している場合、すでに何らかの `cpm` ファイルやフォルダーが存在していますが、同様に設置してください。

### `NekoDraw`

`NekoDraw-Runtime-vx.x.x.zip` を解凍した中にある `NekoDraw` フォルダーは、任意の場所に設置することが出来ます。  
ただし、上記プラグインと同じ場所に設置すると、 CLIP STUDIO PAINT の起動時間がとてつもなく長くなるので、出来れば別の場所に設置してください。  
設置した場所は、この後の構成ファイルの設定にて使用しますので、メモしておいてください。

### `NekoDraw.ini`

`NekoDraw-Conf-vx.x.x.zip` を解凍した中にある `NekoDraw.ini` は、 `NekoDraw.cpm` と同じ場所に設置してください。  
このとき、中身を編集する必要があります。

```ini
[NekoDraw]
NekoDrawRuntimeUri=M:\repos\github.com\mika-f\nekodraw\runtime\NekoDraw
```

初期値では、上記のように設定されています。  
このままでは動きませんので、 `=` より後ろの文字列を、先ほどランタイムを置いた場所に修正してください。  
例えば、 `NekoDraw` フォルダーを `C:\Users\natsuneko\Documents` に設置した場合は、以下のように設定します。

```ini
[NekoDraw]
NekoDrawRuntimeUri=C:\Users\natsuneko\Documents\NekoDraw
```

### `sd-v1-4.ckpt`

ダウンロードした Stable Diffusion のモデルデータは、ランタイムの中に設置します。  
ランタイムのフォルダー以下の、 `models\ldm\stable-diffusion-v1` に、名前を変更せずに設置してください。

## 起動

ここまでくれば、あとは CLIP STUDIO PAINT EX を起動するだけで、フィルター項目に「Stable Diffusion」が追加されています。  
おつかれさまでした。

## 不明点について

不明点などがありましたら、 Twitter アカウント [@6jz](https://twitter.com/6jz) までご連絡ください。
サポートについては GitHub アカウントをお持ちの方は Issue もしくは PR にて、その他の方は上記 Twitter までご連絡ください。
