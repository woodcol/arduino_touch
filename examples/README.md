##### 示例程序目录说明

在[examples](https://github.com/woodcol/arduino_touch/examples)目录下的[11p](https://github.com/woodcol/arduino_touch/examples/11p)中是目前根据用户需求对11个点击头的主控板编写的所有程序

https://github.com/woodcol/arduino_touch/examples/11p

在[examples](https://github.com/woodcol/arduino_touch/examples)目录下的[nano](https://github.com/woodcol/arduino_touch/examples/nano)中是最早没有做主控pcb电路板时编写的真对arduino nano小板编写的一些简单示例程序,这些程序对有想自已设计主控板的或者不想买11头主控的程序可以参考

https://github.com/woodcol/arduino_touch/examples/nano

##### 示例程序的一些具体说明

下边例出已有的几个比较常用的11p主控程序

###### 1.oppo手机快速顺序按三个键的程序(touch_11p_oppoPhone)

https://github.com/woodcol/arduino_touch/examples/11p/touch_11p_oppoPhone

功能和功能是按一下按键，J1,J2,J3分别以一定间隔时间按顺序点击一次

###### 2. 用与密码解锁0000～9999的示例程序(touch_11p_touchPhone)

https://github.com/woodcol/arduino_touch/examples/11p/touch_11p_touchPhone

功能是上电后，程序按0000,0001,0002...一直到9999的顺序按下相应的按键

###### 3. 所有点击头每秒点20次的程序(touch_11p_20PS)

https://github.com/woodcol/arduino_touch/examples/11p/touch_11p_20PS

这个程序也是发货时主控板默认烧写的程序,上电后所有点击头每秒点20次的速度一直点，按下按键后会停止，再按下按键后就继续

###### 4. 通过电脑控制点击器进行点击动作(touch_11p_comTouch)

https://github.com/woodcol/arduino_touch/examples/11p/touch_11p_comTouch

程序分为[上位机电脑端的程序](https://github.com/woodcol/arduino_touch/examples/11p/touch_11p_comTouch/comTouch/comTouch.ino)和[下位机主控板上要烧写的程序](https://github.com/woodcol/arduino_touch/examples/11p/touch_11p_comTouch/windows-python)两部分，要使用电脑对点击头控制，需要先给主控板烧写上下位机程序.其中电脑端程序使用python编写有界面程序，并有已编译好的windows下的二进制可执行程序。

下位机主控板要烧写程序：

https://github.com/woodcol/arduino_touch/examples/11p/touch_11p_comTouch/comTouch

上位机电脑端程序：

https://github.com/woodcol/arduino_touch/examples/11p/touch_11p_comTouch/windows-python

###### 5. 使用外部开关信号控制点击(touch_11p_keyPlus)

https://github.com/woodcol/arduino_touch/examples/11p/touch_11p_keyPlus

这个程序是应一位用户要求，在一个钓鱼的游戏上使用的，主要功能是主控板使用一个外部的继电器或者其他可以产生电信号的设备来控制点击器点击，当时用户使用的是一个声音检测模块来产生控制信号

###### 6. 不同点击头使用不同点击速度的程序(touch_11p_otherTimes)

https://github.com/woodcol/arduino_touch/examples/11p/touch_11p_otherTimes

###### 7. 点击头随机时间点击程序(touch_11p_1type_random，touch_11p_2typeR)

随机时间范围内点击

https://github.com/woodcol/arduino_touch/examples/11p/touch_11p_1type_random

多个固定时间，随机选择时间点击

https://github.com/woodcol/arduino_touch/examples/11p/touch_11p_2typeR

###### 8. 按键控制常按时间的方式点击(touch_11p_longtime)

https://github.com/woodcol/arduino_touch/examples/11p/touch_11p_longtime

功能是:J1~J10为按一下按键后点住屏，再按一下按键不点,jok为每秒20次点击，按一下按键后变为不点，再按一下又为每秒20次

###### 9. 按键控制点击(touch_11p_button)

https://github.com/woodcol/arduino_touch/examples/11p/touch_11p_button

所有点击头的点击受按钮控制，每按一次按钮，11个点击头都同时发生一次点击事件

###### 10. 其他点击方式

所有按键循环点击：[touch_11p_6p](https://github.com/woodcol/arduino_touch/examples/11p/touch_11p_6p)

三个点击头循环一定次数点击：[touch_11p_123p](https://github.com/woodcol/arduino_touch/examples/11p/touch_11p_123p)

按一定间隔时间循环一定次数：[touch_11p_buttondelay](https://github.com/woodcol/arduino_touch/examples/11p/touch_11p_buttondelay)

