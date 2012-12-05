
・概要
Lispを参考に計算機を作ります。
/src -> 計算機のソースコード。全部でmain.c, tokenize.c, parse.c, print.c, check.c, eval.c
/include -> ヘッダーファイル。main.hのみ。
/doc -> 書くcファイルに関するドキュメント。API設計など
/test -> test コード。
/README.txt -> 説明書。
/CMakeLists.txt -> cmakeの設定ファイル
/TIME.txt -> この計算機を作るのにかかった時間&作業内容

・コンパイル&実行方法：
hoge $ git clone https://github.com/leejonggun/calculator.git
hoge $ cd calculator
hoge $ mkdir build
hoge $ cd build
build $ cmake ..
build $ make
build $ ./JOSEPH_CALC
build $ ./JOSEPH_CALC [filename]	ex)$./JOSEPH_CALC ../test/nest.txt

・できることは以下の通りです。
四則演算+,-,*,/

・特徴
まだ実装できていませんが、変数定義&呼び出し、関数定義&呼び出し、
if文、while文、比較演算など機能拡張することができます。

・アプリケーション終了方法
Ctrl-cを押す(quitと入力することでアプリ終了にする予定)

・シンタックスは次の通りです。
'('と')'の数は一致しなければいけない
四則演算
例)
( 1 + 2 )->return 3
( 1 + (3 + 4) - 2 )->return 6
(1+(3-4)+(5+6))->return 11
(2)->return 2

ERRORS
( 1 + + 2 )->no number between operators
( 1 2 )->no operator between numbers
(1+)->operator can't be just before ')'
(+1)->operator can't be just after '('
(111111111111 + 1111111111111111)->Too big number
()->No token between '('~')'
