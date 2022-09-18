# REQUIREMENTS - HARDWARE

ここでは、 NekoDraw (および Stable Diffusion) を実行するのに必要なハードウェア要件を説明しています。

## Requirements

以下のハードウェア構成を推奨しています。

- 32GB 以上のメモリ
  - 手元の PC では、 512x512px の画像 (img2img) にて、 sd-v1-4.ckpt にて、 ~19GB のメモリを消費しています
  - これは、使用するモデルによります、 Waifu Diffusion の場合は手元で 24GB のメモリを消費しています
- GeForce RTX 3060 もしくは VRAM が 8GB 以上のビデオカード (NVIDIA 製)
  - 手元の PC では、 512x512px の画像 (img2img) にて、 ~3GB のメモリを消費しています
  - [Optimized SD](https://github.com/basujindal/stable-diffusion) を使用しているので、実際には通常の Stable Diffusion のように、 8GB も必要はありません

## キャンバス・フィルターサイズ

NekoDraw では、 CLIP STUDIO PAINT がクラッシュするのを防ぐため、 GPU メモリの割り当てに失敗した場合、処理を停止し、キャンバスの置き換えを行いません。  
目安として、以下の VRAM 容量の場合、次のキャンバスサイズおよびフィルターサイズの画像が生成可能です。  
なお、内部的には、どのようなキャンバス・フィルターサイズでも、縦横が 64 の倍数になるように内部的に調整されます。  
たとえば、 504x321 の画像に対して実行した場合、内部的には 512x384 へとリサイズを行い、 img2img を実行します。  
そのため、下記テーブルについて、自身が実行を行いたいサイズを満たす最小サイズについて見るのが正しい見方です。

## Stable Diffusion

オプションにて、 `WITH_FORCE_F16_PRECISION=OFF` を有効にした状態でビルドしたものを使用した場合、このモードが使用されます。  
ダウンロード版の場合は、 `NekoDraw.dll` を `NekoDraw.cpm` にリネームした場合、こちらが使われます。  
オリジナルの Stable Diffusion と同じ動作をするため、他のものに比べて高速ですが、より多くの VRAM を必要とします。  
※デフォルトの `stable-diffusion.zip` を使用してください。

| Size \ VRAM | 8GB (GeForce RTX 2070 SUPER) | 12GB (GeForce RTX 3060) | 16GB (GeForce RTX A4000) |
| :---------: | :--------------------------: | :---------------------: | :----------------------: |
|   512x512   |              ?               |            ?            |            ?             |
|   576x576   |              ?               |            ?            |            ?             |
|   640x640   |              ?               |            ?            |            ?             |
|   704x704   |              ?               |            ?            |            ?             |
|   768x768   |              ?               |            ?            |            ?             |
|   832x832   |              ?               |            ?            |            ?             |
|   896x896   |              ?               |            ?            |            ?             |
|   960x960   |              ?               |            ?            |            ?             |
|  1024x1024  |              ?               |            ?            |            ?             |

## Optimized Stable Diffusion (Fork of @basujindal)

デフォルトの `stable-diffusion.zip` を使用した場合、この Fork が使用されます。  
速度とサイズのバランスがちょうど良いモードです。

| Size \ VRAM | 8GB (GeForce RTX 2070 SUPER) | 12GB (GeForce RTX 3060) | 16GB (GeForce RTX A4000) |
| :---------: | :--------------------------: | :---------------------: | :----------------------: |
|   512x512   |              o               |            o            |            ?             |
|   576x576   |              o               |            o            |            ?             |
|   640x640   |              o               |            o            |            ?             |
|   704x704   |              o               |            o            |            ?             |
|   768x768   |              o               |            o            |            ?             |
|   832x832   |      x (Out of Memory)       |    x (Out of Memory)    |            ?             |
|   896x896   |              x               |            x            |            ?             |
|   960x960   |              x               |            x            |            ?             |
|  1024x1024  |              x               |            x            |            ?             |

## Optimized Stable Diffusion (Fork of @neonsecret)

別途 `stable-diffusion.zip` (Optimized Fork) 版をダウンロードして置き換えた場合、この Fork が使用されます。  
多くの処理を CPU で行うため速度を犠牲にしますが、より少ない VRAM 消費量で、他のバージョンに比べて大きなサイズの画像が生成可能です。

| Size \ VRAM | 8GB (GeForce RTX 2070 SUPER) | 12GB (GeForce RTX 3060) | 16GB (GeForce RTX A4000) |
| :---------: | :--------------------------: | :---------------------: | :----------------------: |
|   512x512   |              o               |            o            |            ?             |
|   576x576   |              ?               |            o            |            ?             |
|   640x640   |              ?               |            o            |            ?             |
|   704x704   |              ?               |            o            |            ?             |
|   768x768   |              ?               |            o            |            ?             |
|   832x832   |              ?               |            o            |            ?             |
|   896x896   |              ?               |            o            |            ?             |
|   960x960   |              ?               |            o            |            ?             |
|  1024x1024  |              ?               |            o            |            ?             |
|  1088x1088  |              ?               |            o            |            ?             |
|  1152x1152  |              ?               |            ?            |            ?             |
|  1216x1216  |              ?               |            ?            |            ?             |
|  1280x1280  |              ?               |            ?            |            ?             |
