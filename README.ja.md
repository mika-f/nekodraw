# NekoDraw: CLIP STUDIO PAINT Filter Plugin

[English](./README.md) | [日本語](./README.ja.md)

> このプロジェクトは実験的なものです。自身の責任の下ご利用ください。

Stable Diffusion の txt2img, img2img プロセッサを実行する CLIP STUDIO PAINT プラグインです。  
このプラグインでは、 Stable Diffusion をローカル環境で実行します。  
そのため、 12GB 以上の RAM と、 8GB 以上 (512x512px の場合) の VRAM が必要です。

## 動画

- Text to Image : https://twitter.com/6jz/status/1566052868016054272
- Image to Image : TODO

## 必須事項

- Windows 10 以上 (たぶん古い Windows でも動きますが、サポートはしません)
- 16GB 以上のメモリ (12GB Free)
- GeForce RTX 3060 ビデオカード (>= 8GB VRAM) もしくは同等のビデオカード、
- NekoDraw ランタイム
  - 今後このページにて配布予定です
  - なお、このランタイムには Stable Diffusion のモデルを含んで最大 40GB のディスクスペースが必要です

## Usage

1. Download Plugin (`.cpm`) from GitHub Releases : [Download](https://github.com)
2. Download Runtime from Natsuneko Laboratory S3 : [Download](https://archive.natsuneko.moe)
3. Configure `NekoDraw.ini` in CLIP STUDIO PAINT : [Help Doc](https://docs.natsuneko.moe)

## Configure

`NekoDraw.ini` をテキストエディタで開き、下記のように編集してください：

```txt
[NekoDraw]
NekoDrawRuntimeUri=[NekoDraw ランタイムのフルパス]
```

例:

```txt[NekoDraw]
NekoDrawRuntimeUri=M:\repos\github.com\mika-f\nekodraw\runtime\NekoDraw
```

そして、 `NekoDraw.ini` をプラグインと同じ場所に置いてください。
通常、プラグインは `%APPDATA%/CELSYSUserData\CELSYS\CLIPStudioModule\PlugIn\PAINT` に置かれています。

## License

誰か最適なライセンス教えてくれ
