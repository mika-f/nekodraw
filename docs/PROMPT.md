# PROMPT

ここでは、 NekoDraw における Stable Diffusion のプロンプト (呪文) の指定方法およびオプションについて説明します。

## Requirements

すでに [INSTALLATION](./INSTALLATION.md) を終わらせた前提です。

## プロンプトについて

NekoDraw では、 [Stable Diffusion の効果的なフォーマット](https://zenn.dev/hagakun_dev/articles/b178e669b2dbe0) に合わせてフォームが分かれています。  
上記記事にあるとおり、 NekoDraw では以下のフォームになっています：

```txt
<全体フォーマット> <主題> <主題 (補足)> <作者・スタイル> <全体フォーマット (補足)> <フレーバー>
```

たとえば、下記のようなどら焼きの画像から、写真のような画像を生成したい場合は、下記のように入力します。

![](../assets/image.png)

| プロンプトフォーム      | 内容                        |
| ----------------------- | --------------------------- |
| 全体フォーマット        | `Photographic of`           |
| 主題                    | `Japanese Macarons`         |
| 主題 (補足)             | なし                        |
| 作者・スタイル          | なし                        |
| 全体フォーマット (補足) | `perfect lighting, morning` |
| フレーバー              | `Sony, 35mm Lens, f1.8`     |

このとき、 `img2img モード` にチェックを入れ、ストレングスを指定します。  
ストレングスについては、下記の記事が詳しいです：

https://blog.ch3cooh.jp/entry/2022/09/02/093000

入力後、**初回の実行については、モデル読み込みが行われるため、数分程度時間がかかります。**  
Windows においては、 CLIP STUDIO PAINT EX が動作を停止しているように認識される場合がありますが、バックグラウンドで動作しているので、**強制終了させたりしないでください**。

数分後、**現在のレイヤーを置き換える形で、 `img2img` にて出力された画像が出力されます**。  
上記のプロンプトの場合、下記のような画像が生成されます。

![](../assets/image2.png)

また、無から画像を生成する場合、 CLIP STUDIO PAINT の制約上、何らかの色で塗りつぶしを行った後、フィルターを書けることで利用できるようになります。  
この場合は、 `img2img モード` のチェックを外せば、 `text2img` モードとして動作します。  
この場合も、現在参照しているレイヤーに対して、出力が行われます。

なお、各フォームについて、内部的には上記のように半角スペース (` `) 区切りで結合されていますので、1 文で記述しても問題ありません。同等の結果が出力されます。  
例えば、今回の例の場合は、「全体フォーマット」などの 1 つのフォームに、以下の文章を入力しても、結果は同じとなります。

```
Photographic of Japanese Macarons perfect lighting, morning Sony, 33mm Lens, f1.8
```
