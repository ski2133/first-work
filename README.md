# first-work  説明
#### このリポジトリはフィックスターズ奨学金のプログラム提出に使うためのものです。
２つプログラムを作りました。２つとも見て頂けると嬉しいのですが、
もし一つのプログラムで判断する場合、
アルゴリズムを重視しているならC言語のcode1.c、  
機能を重視しているならcode2.pyを見てください

## 導入方法
まず、
```
git clone https://github.com/ski2133/first-work
```
とターミナルなどで入力し、
```
cd first-work
```
で移動して、c言語のプログラムなら
```
gcc code1.c
./a.out
```
pythonのプログラムなら
```
python3 code2.py
```
と入力  

## 概要
#### code1.c
文字列を操作するプログラムです。  
具体的には場所をランダムに、文字列の配置を逆にする(abcdeならedcbaのように)、母音子音
をのける。大文字小文字変換、アルファベットを指定した数字分だけアルファベット順にずらす、  
昇順降順に並び替えるという機能があります。  
＊ただし、100文字以上の文字列の入力はできません  
(#define MAX 100 の設定を変えればできます)。
##### 使用方法
1.まず
```
文字列を入力してください(アルファベット以外は削除されます)>    
```
と表示されるので任意の文字列を入力する  
2.次に
```
[0]終了[1]場所シャッフル[2]リバース[3]母音抜き[4]子音抜き
[5]アルファベットの大文字小文字変換
[6]選択された数字分アルファベットを後にずらす
[7]選択された数字分アルファベットを前にずらす
[8]昇順(A->Z)[9]降順(Z->A)
選択肢の数字を入力してください
>
```
と出力されるので任意の数字を入力する。終了する場合は0を入力する  
仮に数字ではなく文字列を入力すると
```
エラー。もう一度入力してください
>
```
と出力される。ただし、N*100文字(Nは1以上の整数)の文字列だと
```
エラー。もう一度入力してください
>エラー。もう一度入力してください(N=1)
>エラー。もう一度入力してください(N=2)

...

>エラー。もう一度入力してください(N=N)
>
```
となってしまうのでエラー処理が気になる場合は  
大きすぎる文字列をいれるのはやめるか、#define MAX 100 の設定を変えてください。  

---

#### code2.py
日付を操作するプログラムです。  
現在の時刻、現在の時刻から後の時刻、  
現在の時刻より前の時刻を扱えます。一応紀元前も扱えます。  
年月日時間分曜日、その日がなんの記念日なのかまで出力してくれます。  
(例: 2024年12月27日15時04分金曜日 - 浅草仲見世記念日)  
記念日の確認には
*`wikipedia api`* 
を使いました。  
元のページ:
https://ja.wikipedia.org/wiki/%E6%97%A5%E6%9C%AC%E3%81%AE%E8%A8%98%E5%BF%B5%E6%97%A5%E4%B8%80%E8%A6%A7  
＊10000年など大きすぎる年単位の値は扱えません（エラーは起きないようにしました）。
##### 使用方法
1.まず
```
現在か過去か未来か決めてください
[0]現在[1]過去[2]未来>
```
と出てくるのでどれかを選択する。ここで0を入力した場合、  
```
2024年12月27日15時33分金曜日 - 浅草仲見世記念日
```
のように出力される。  
＊なお数字を打つべきところで文字列をいれると  
invalid literal for int() with base 10:とエラーが出る  

2. 1か2を入力した場合、
```
何年前(例: 2年前(数字のみでも可))>1年前
```
```
何ヶ月前(例: 3ヶ月前(数字のみでも可))>1ヶ月前
```
```
何日前(例: 10日前(数字のみでも可))>1
```
```
何時間前(例: 15時間前(数字のみでも可))>1
```
(2を入れると前が後に変わる)のように出力されるので一つずつ、
1年前のように入力するか、1と数字のみのどちらかを入力する  

3.その後
```
2023年11月26日14時39分日曜日 - ペンの日、いい風呂の日、ビン牛乳の日
```
のように出力される。

 　
