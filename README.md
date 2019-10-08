# arduino_touch

##请认准商品真实购买地址

    最近发现淘宝有其他商家复制我的点击头商品页面后，再加一定价格再出售，请购买时认准本点击器的真实地址：

本点击器的淘宝店铺唯一地址：

https://fengmm521.taobao.com

请认准本店商品页面地址：

https://item.taobao.com/item.htm?id=592983523791

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

## 第三方库的安装

用到的所有第三方库都放在lib（https://github.com/woodcol/arduino_touch/tree/master/lib） 目录下了，用的时候需要把这个目录下的所有文件夹复制到Arduino的库目录下来使用，方法如下：

在Arduino开发工具的菜单栏里先，"文件"->"首选项"，在设置界面里会看到有一个"项目文件夹位置"的路径

在这个路径下有一个libraries目录，请将这里的MsTimer2和SCoop两个库的文件夹整个复制进去。这样这两个三方库就安装到Arduino的开发环境下了

