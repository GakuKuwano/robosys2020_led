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

Raspberry Pi GPIO pin : {25, 8, 7, 12, 16}　(左から順にLED1, LED2, LED3, LED4, LED5を割り当てる)

<img src="https://github.com/GakuKuwano/robosys2020_led/blob/main/images/robosys_circuit_diagram_led.png" width="320px">

![Figure_Experimental_image](https://github.com/GakuKuwano/robosys2020_led/blob/main/images/IMG_1169.PNG "Figure_Experimental_image")

# DEMO

https://youtu.be/8bBAgfoZG0U

## プログラムの実行方法
- システムの起動
```bash
  git clone https://github.com/GakuKuwano/robosys2020_led.git
  cd robosys2020_led
  make
  sudo insmod myled.ko
  sudo chmod 666 /dev/myled0
  ```
  
- LED1を点灯
```bash
  echo 1 > /dev/myled0
  ```
- LED2を点灯
```bash
  echo 2 > /dev/myled0
  ```
- LED3を点灯
```bash
  echo 3 > /dev/myled0
  ```
- LED4を点灯
```bash
  echo 4 > /dev/myled0
  ```
- LED5を点灯
```bash
  echo 5 > /dev/myled0
  ```
- すべてのLEDを消灯
```bash
  echo 0 > /dev/myled0
  ```
- 0~5以外を入力するとLEDによるエラー表現（点滅）
  ex) デバイスファイルに6を書き込む
```bash
  echo 6 > /dev/myled0
  ```
  
- システムの停止
```bash
  sudo rmmod myled
  ```
  
  
