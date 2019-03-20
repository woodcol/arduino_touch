#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2018-10-30 23:17:58
# @Author  : Mage
# @Link    : https://fengmm521.taobao.com
# @Version : $Id$

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
    
