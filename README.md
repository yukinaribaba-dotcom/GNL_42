This project has been created as part of the 42 curriculum by ybaba.

# get_next_line

## Description

get_next_lineは、ファイルディスクリプタから1行ずつテキストを読み取る関数です。この課題の目的は、静的変数の使い方を学び、ファイル読み込みとメモリ管理の理解を深めることです。

主な機能：
- ファイルや標準入力から改行文字(`\n`)までの1行を返す
- 複数回呼び出すことで、ファイル全体を1行ずつ読み取れる
- `BUFFER_SIZE`を変更しても正しく動作する

## Instructions

### コンパイル

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

`BUFFER_SIZE`は任意の正の整数に変更可能です。

### 使用例

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## アルゴリズムの説明

### 概要

本プロジェクトでは「静的変数によるバッファリング方式」を採用しています。

### 処理の流れ

1. **読み込み (`read_until_newline`)**
   - `read()`でファイルから`BUFFER_SIZE`バイトずつ読み込む
   - 読み込んだデータを静的変数`backup`に連結して保存
   - 改行文字(`\n`)が見つかるか、EOFに達するまで繰り返す

2. **行の抽出 (`extract_line`)**
   - `backup`から改行文字までの部分を切り出して返す
   - 残りのデータは`backup`に保持し、次回の呼び出しで使用

3. **静的変数の役割**
   - `static char *backup`：関数呼び出し間でデータを保持
   - 前回の読み込みで余った文字列を次回に引き継ぐ

### この方式を選んだ理由

- **効率性**: 一度読み込んだデータを無駄にせず、次の行読み取りに再利用できる
- **シンプルさ**: 静的変数1つで状態管理が完結する
- **メモリ効率**: 必要な分だけメモリを確保・解放する

### 補助関数

| 関数 | 説明 |
|------|------|
| `ft_strlen` | 文字列の長さを返す |
| `ft_strchr` | 文字列内の文字を検索 |
| `ft_strjoin` | 2つの文字列を連結 |
| `ft_substr` | 部分文字列を抽出 |

## Resources

### 参考資料

- [42 Docs - get_next_line](https://harm-smits.github.io/42docs/projects/get_next_line)
- [プロジェクトついて - ガイド](https://42-cursus.gitbook.io/guide/1-rank-01/get_next_line)

### AIの使用について

本プロジェクトでは、以下の目的でAIを使用しました：
- README.mdで作成した文章の改善
- 自身が書いたコードのReview
