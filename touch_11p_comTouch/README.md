# 通过电脑控制点击

## 代码功能说明

通过电脑上的串口(COM口)给arduino发送数据控制点击,当通过串口给板子发送字符'1'或者'2'时，会触发点击器点击动作一次。点击时间为30ms.

##### 电脑上位机说明

在UTool目录下为电脑端有界面的上位机程序源码，程序界面使用cocos2d-x游戏引擎开发。串口部分使用python的pyserial串口模块，整个上位机界面部分使用C++编写，串口部分使用python编写，所以项目中用到了C++调用Python混合编程。

本上位机使用的是cocos2d-x 3.15版本

cocos2d-x项目地址：
https://github.com/cocos2d/cocos2d-x


##### Arduino程序说明
comTouch目录为arduino上开发板程序源码，这里使用到了SCoop的Arduino的多线程库。这个库在项目上层的lib目录下

## USB转串口芯片驱动程序下载

这是ch340芯片的官方驱动，有linux，mac，windows等等驱动,选择自已适合自已电脑系统的驱动
http://www.wch.cn/products/CH340.html


## 串口工具使用说明

串口控制上位机程序界面在设置好串口号后，点打开串口按钮等待串口连接成功，一般会在5秒内连接成功。

串连接成功后，把点击头放到手机上，然后在电脑的程序上点击相应的数字编号即可触发相头插孔的点击头发生点击动作。



点击头购买地址:

https://fengmm521.taobao.com

本代码尚未完成