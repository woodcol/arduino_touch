# 一机多头可编程点击器

## 程序功能

所有点击头按设置的间隔时间最小值和最大值之间随机点击，间隔时间单位为ms，最大随机时间不要超过60秒，最小时间不要小于30ms.可以是双击也可以是单击，点击几次在程序的touchTimes变量那里设置就好

## 说明：

这个代码的功能是,所有点击头的随机时间都可以在代码里通过设置两个间隔时间数组完成。

``` C++
//要点击的引脚和排号对应关系
const int pinkeys[11] = {J1,J2,J3,J4,J5,J6,J7,J8,J9,J10,Jok};

//所有引脚的下次点击延时时间
unsigned long pinRD[11] = {0,0,0,0,0,0,0,0,0,0,0};
                               //J1,J2 ,J3 ,J4 ,J5  J6  J7     J8    J9   J10 Jok
//随机间隔点击时间最小值，单位ms
unsigned long delay_Mins[11] = {300,300,300,500,500,500,20000,20000,20000,100,100};
 //随机间隔点击时间最大值，单位ms
unsigned long delay_Maxs[11] = {700,700,700,800,800,800,22000,22000,22000,101,101};
```

上边的最小时间是每随机间隔的最小时间，最大时间是指随机间隔的最大时间

开机后，默认1－3接头0.3－0.7秒随机点一次:4－6接头0.5－0.8秒随机点一次；7－9接头20－22秒随机点一次,其他J10和Jok为每0.1秒点一次.

当按一次按键后，程序为所有点击头每秒点18次左右，再按一次又会是随机点.



## 注意

这个代码使用了一个第三方的多线程SCoop库，这个库使用简单，使用这个库的主要原因是为了把按键实时检测和点击头延时停顿分开，以做到点击头点击的同时不影响程序对按键的检测（因为没有使用arduino的外部中断来处理按键）

使用的时候要把lib目录下的文件夹复制到arduio的库目录下。这个目录一般是在arduino的libraries目录下，这里放了所有的第三方arduino库.

## 点击头购买地址:

https://fengmm521.taobao.com

## SCoop多线程库地址：

https://github.com/fabriceo/SCoop

在这里查看SCoop库的使用方法，作者有放一个pdf教程在项目目录下

实际请使用下边路径下的库

https://github.com/woodcol/arduino_touch/tree/master/lib



