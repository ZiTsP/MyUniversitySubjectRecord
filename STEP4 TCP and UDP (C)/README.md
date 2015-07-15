#STEP
このプログラムは、2014年4月から7月にかけて段階的に作成した、TCP通信に関するC言語プログラムの最終課題です。

***
##目的
###TCP/UDP通信とブロードキャスト

TCPおよびUDP通信を用いて簡易チャットプログラムを作る。

***
##動作説明
###起動時
起動時に引数として、「ユーザ名(英文字15文字以内)」・「待ち受けポート番号(デフォルトは50001)」を指定する  
コマンドラインオプション

* -U ユーザ名 : ユーザ名を設定
* -P : ポート番号を指定
* -T : (後述の)「HELO」パケットに対する返答待ち時間を指定

起動すると、まず、「HELO」という内容のパケットを 待ち受けポートに対してブロードキャストする。  サーバから一定時間返事がなければ、同じパケットを3回再送する。これに対し、

* 返事がなければ、自身がサーバになる。
* UDPで「HERE」パケットを受信したら、以後クライアントとして動作する。 (「HERE」パケットからサーバのIPアドレスを入手)

###サーバ時
10個まで同時にやりとりできる。

UDPポート(待ち受けポート)を監視し、「HELO」パケットが送られてきたら 送ってきた相手に「HERE」パケット(UDP)を送り返す。

TCPポート(待ち受けポート)を監視し、クライアントからの接続を待ち受ける。  
接続したクライアントから「JOIN ユーザ名」という内容のメッセージを受信したら、そのユーザ名を接続しているソケット番号(個別でTCP)と関連づけて記録することでログイン完了とする。ユーザの追加を全クライアントに通知する。

ログイン完了しているクライアントから、「POST 発言メッセージ」の形式のメッセージを受信したら、発言メッセージの先頭部分に発言者のユーザ名を付加して「MESG ユーザ名$発言メッセージ」の形式のメッセージを(発信者含む)全クライアントに対して送信する。
このとき、自身の画面には「発言メッセージ」を表示する。

ログイン完了しているクライアントから、「QUIT」メッセージを受信したら、 そのクライアントをログアウトとする。
この時、(実質は他の)全クライアントに対して「MESG ユーザ名$Log out」と、メッセージを送信する。

自身のキーボードからの入力を監視し、入力されたテキストを「MESG 発言メッセージ」の形式で全クライアントに対して送信する。

###クライアント時
起動時に判明したサーバのIPアドレスのTCPポートに接続を要求する。  
サーバに接続したら、「JOIN ユーザ名」メッセージを送信する。

サーバと接続している(TCP)ソケットを監視し、「MESG 発言メッセージ」形式のメッセージを受信したら、「発言メッセージ」を画面に表示する。

自身のキーボードからの入力を監視し、

* 入力されたテキストが「QUIT」でなければそれを発言メッセージ(488バイト以内であること)として、「POST 発言メッセージ」の形式でサーバに送信する。
* 「QUIT」ならば、「QUIT」メッセージをサーバに送信し、サーバとの接続を閉じ、プログラムを終了する。

<!---
###各種メッセージについて
* 「HELO」
* 「HERE」
* 「JOIN ユーザ名」
* 「POST 発言メッセージ」
* 「MESG 発言メッセージ」
* 「QUIT」
--->

###注意
各メッセージの送受信について、1回のsend関数で送信したメッセージは(recv関数の受信バッファが不足しない限り)1回のrecv関数で受信できるものと仮定する。

***
##コーディング目標や再利用できる項目
* selectによるソケットの監視

##コーディング後の反省点
* 後で接続したクライアントは、他のクライアント情報が分からなくなっている。そのこともあってか、サーバーが手入力メッセージを送信することを想定していなかった。また、サーバーが落ちた場合も想定できていない。
* 作成日時や動作環境を記載していなかった。
* 当時、自分で作成したヘッダファイルの活用法がよくわかっていなかった(課題説明時は意味不明な保存先を指定されていた)ので作成していなかった。そのため、強引に関数や変数を渡しているので改善が必要。
* 命名の不規則さや、コードの重複、例外処理の不足も見当たった。