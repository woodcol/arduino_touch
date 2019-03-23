# 通过电脑控制点击

## 代码功能说明

通过电脑上的串口(COM口)给arduino发送数据控制点击,当通过串口给板子发送字符'1'或者'2'时，会触发点击器点击动作一次。点击时间为30ms.

## USB转串口芯片驱动程序下载

这是ch340芯片的官方驱动，有linux，mac，windows等等驱动,选择自已适合自已电脑系统的驱动
http://www.wch.cn/products/CH340.html


## python中的串口
电脑上的串口工具，或者使用这里提供的Python串口模块也可以给板子发送字符'1'或者'2',python串口的例子是发送字符'1'

```python
import os,sys
import serial

def touchOnce():
    dev = '/dev/cu.wchusbserial14140'  #这里请写你电脑正确的串口,windows请写"COM数字"这样的端口
    t = serial.Serial(dev,115200,timeout=0.5)
    n = t.write('1')
    n = t.inWaiting()
    print n
    str = t.read(n)
    print str
#测试
if __name__ == '__main__':
    touchOnce()
```

python串口模块pyserial可以使用pip工具进行安装
```shell
pip install pyserial
```

关于python串口更多相关知识，请参考:

https://blog.csdn.net/huayucong/article/details/48729907

https://blog.csdn.net/xhao014/article/details/7640568

## 其他

如果从本店购买了多个点击头，想用串口控制多个点击头，可以参考arduino中程序的switch中的case部分增加相应的点击头控制引脚。

点击头购买地址:

https://fengmm521.taobao.com