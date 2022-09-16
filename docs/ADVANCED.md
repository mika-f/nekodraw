# ADVANCED

ここでは、上級的な使い方について説明します。

## 別バージョンの Stable Diffusion を使いたい

Stable Diffusion の実行コードに互換性があるモデルなら、どんなモデルでも使用できます。
例えば、以下のモデルは Stable Diffusion のコードと互換性があるので、実行が可能です。

- [Stable Diffusion v1.1](https://huggingface.co/CompVis/stable-diffusion-v-1-1-original)
- [Stable Diffusion v1.2](https://huggingface.co/CompVis/stable-diffusion-v-1-2-original)
- [Stable Diffusion v1.3](https://huggingface.co/CompVis/stable-diffusion-v-1-3-original)
- [Stable Diffusion v1.4](https://huggingface.co/CompVis/stable-diffusion-v-1-4-original)
- [Waifu Diffusion](https://huggingface.co/hakurei/waifu-diffusion)

モデルの差し替えについては、現時点では、 `sd-v1.4.ckpt` を設置した箇所に、ファイルを `sd-v1.4.ckpt` と設置することで切り替えることが可能です。
