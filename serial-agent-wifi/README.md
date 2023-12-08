# RS232C agent with WiFi connection
LAN 内のホストから、RS232C ポートを備えたデバイスに接続するための代理サーバを ESP32 で実現するためのプログラム。

## Framework
PlatformIO IDE は、Arduino IDE を置き換える開発環境である。VSCode の拡張機能としてインストールされる。

## Instoration
1. [Visual Studio Code (VSCode)](https://code.visualstudio.com/) をインストールする
2. VSCode の拡張機能サイトにある[Platform IO IDE のページ](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)の指示に従って、Platform IDE 拡張機能をインストールする
3. 別の方法として、VSCode の拡張機能ペインから「platformio」で検索し、「OkatformIO IDE」を選択してインストールすることもできる
4. esp32-tools を git でクローンし、serial-agent-wifi サブプロジェクトのフォルダに移動し、VSCode を起動する
```bash
$ git clone https://github.com/cnloni/esp32-tools.git
$ cd esp32/serial-agent-wifi
$ code .
```
5. VSCode を立ち上げる

## Features
1. ESP32 は、あらかじめ設定した WiFi ルータに接続して、クライアントホストからの接続要求を待ち受ける
2. クライアントからの接続が開かれると、デバイスからの入力とクライアントからの入力をノンブロッキングで待ち受ける
3. クライアントから入力があると、その入力を（ほぼ）そのままの形で、デバイスへ出力する
4. デバイスから入力があると、その入力を（ほぼ）そのままの形で、クライアントへ出力する
