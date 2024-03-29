Written by Joseph
・概要
Lispを参考に計算機を作ります。
/src -> 計算機のソースコード。全部でmain.c, tokenize.c, parse.c, print.c, check.c, eval.c, i_calculate.c, f_calculate.c
/include -> ヘッダーファイル。main.hのみ。
/doc -> 各cファイルに関するドキュメント。API設計など
/test -> test コード。
/README.txt -> この文書。説明書。
/CMakeLists.txt -> cmakeの設定ファイル
/TIME.txt -> この計算機を作るのにかかった時間&作業内容

・コンパイル&実行方法1：
hoge $ git clone https://github.com/leejonggun/calculator.git
hoge $ cd calculator
hoge $ mkdir build
hoge $ cd build
build $ cmake ..
build $ make
build $ ./JOSEPH_CALC
build $ ./JOSEPH_CALC [filename]	ex)$./JOSEPH_CALC ../test/nest.txt
・コンパイル&実行方法2：
eclipseでソースコードをc/c++プロジェクトとしてインポートします。(CDTが必要)
メニューバーからbuildを選択してコンパイルします。
メニューバーから実行を押して、コンソールに計算式を入力します。
あるいは、引数を設定して実行を押して、/testの中にあるテストファイルを指定すると計算結果が得られます。(式が長かったり、複雑だったりするとファイル読み込みで実行させた方が楽です。)

・できることは以下の通りです。
四則演算+,-,*,/,^(累乗),!(階乗)

・特徴
1.まだ実装できていませんが、変数定義&呼び出し、関数定義&呼び出し、
  if文、while文、比較演算など機能拡張することができます。(tokenize, parse, evalに処理の追加)
2.tokenize, parseで文字も読み込む処理を書けたら(そんなに難しくありません)、evalに関数を一つ追加するだけで文法を一つ拡張できる。
  Syntax 'Ans'追加。Ansは前の計算結果を返します。
3.関数ポインタを用いて、計算する関数の処理が短くしました。
4.parse, evalを再帰的に呼び出しているので、入れ子構造(カッコが入力されても)になっても四則演算の優先順位を守りつつ計算することができます。
  ex) 1 + 2 * ( 3 * 4 + 5) -> 1 + 2 * ( 12 + 5) -> 1 + 2 * 17 -> 1 + 34 -> 35

・アプリケーション終了方法
Ctrl-cを押す(quitと入力することでアプリ終了にする予定)

・シンタックスは次の通りです。
1.'('と')'の数は一致しなければいけない
例)
1 + 2->return 3
1 + (3 + 4) - 2->return 6
1+(3-4)+(5+6)->return 11
2->return 2

3.階乗はカッコ付きで使う
例)
(3!)->return 6
((5!)/(3!))->return 20

ERROR HANDLING
( 1 + + 2 )->no number between operators
( 1 2 )->no operator between numbers
(1+)->operator can't be just before ')'
(+1)->operator can't be just after '('
(111111111111 + 1111111111111111)->Too big number
()->No token between '('~')'

BUGS
( 1 + (+1)) -> SEGV
( 1 + (-1)) -> SEGV
(3!-1) -> SEGV
