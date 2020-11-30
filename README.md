# robosys2020 led

ロボットシステム学で作成したLEDを点灯させるRaspberry Piのデバイスドライバ

# 実装内容

- 1~5のいずれかをデバイスファイルに書き込むと，選択した番号のLEDが点灯する．（LED ON）
- デバイスファイルに0を書き込むと，すべてのLEDが消灯する．（LED OFF）
- 0~5の数字以外が入力された場合，5つのLEDでエラーを表現し，デバイスファイルに"I don't know !!!"を出力させる．

# 実験器具

- Raspberry Pi4 Model B
- ブレッドボード
- ジャンパーワイヤ
- LED(赤)×5, 抵抗(220[Ω])×5

# DEMO

```bash
  git clone https://github.com/GakuKuwano/robosys2020_led.git
  cd robosys2020_led
  make
  sudo insmod myled.ko
  sudo chmod 666 /dev/myled0
```

https://youtu.be/8bBAgfoZG0U
