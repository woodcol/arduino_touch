#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2018-10-30 23:17:58
# @Author  : Mage
# @Link    : https://fengmm521.taobao.com
# @Version : $Id$

import os,sys
import serial
import time

def touchOnce():
    dev = '/dev/cu.wchusbserial14140'  #这里请写你电脑正确的串口,windows请写"COM数字"这样的端口
    t = serial.Serial(dev,115200,timeout=0.1) #115200
    # t.open()

    print(t.name)
    print(t.port)
    print(t.baudrate)           #波特率
    print(t.bytesize)           #字节大小
    print(t.parity)             #校验位N－无校验，E－偶校验，O－奇校验
    print(t.stopbits)           #停止位
    print(t.timeout)            #读超时设置
    print(t.writeTimeout)       #写超时
    print(t.xonxoff)            #软件流控
    print(t.rtscts)             #硬件流控
    print(t.dsrdtr)             #硬件流控
    print(t.interCharTimeout)   #字符间隔超时
    print('-'*10)
    # n = t.write('x')
    time.sleep(3)
    s = t.write('5')
    t.flush()
    n = t.inWaiting()
    count = 10
    while n < 1 and count > 0:
        n = t.inWaiting()
        s = t.write('2')
        t.flush()
        print(n)
        time.sleep(0.1)
        count -= 1
    n = t.inWaiting()
    print(n)
    time.sleep(0.5)
    n = t.inWaiting()
    print(n)
    pstr = t.read(n)
    print(pstr)
    t.close()
#测试
if __name__ == '__main__':
    touchOnce()
    
