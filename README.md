# arduino_touch

## USB转串口芯片驱动程序下载

这是ch340芯片的官方驱动，有linux，mac，windows等等驱动,选择自已适合自已电脑系统的驱动
http://www.wch.cn/products/CH340.html

## 使用方法

1.在arduino的IDE里打开touchTest目录下的touchtest.ino。
![](https://github.com/woodcol/arduino_touch/raw/master/img/dk.png)

2.设置好arduino的串口,windows下显示com+数字的接口
![](https://github.com/woodcol/arduino_touch/raw/master/img/com.png)

3.设置好arduino的编程器为AVR ISP.
![](https://github.com/woodcol/arduino_touch/raw/master/img/bcq.jpeg)

4.arduino的开发板选择arduino nano
![](https://github.com/woodcol/arduino_touch/raw/master/img/kfb.jpeg)

5.点击上传，等待IDE上传完成就好。
![](https://github.com/woodcol/arduino_touch/raw/master/img/sc.png)

6.注意，在arduino最新版1.8.8中，如果出现烧写错误，要把处理器设置为(OLD ATmega328p),这是新为新版arduino和旧板的芯引导程序bootloader不一样。