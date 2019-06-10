#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2018-10-30 23:17:58
# @Author  : Mage
# @Link    : https://fengmm521.taobao.com
# @Version : $Id$

import os,sys
import serial
import time

class STool(object):
    """docstring for STool"""
    #pdev:串口设备名
    #pbtlv:波特率,默认为115200
    def __init__(self, pdev,pbtlv=115200):
        super(STool, self).__init__()
        self.dev = pdev
        self.pbtv = pbtlv
        self.t = None
        self.isOK = False
    #打开串口
    def openSerial(self):
        self.t = serial.Serial(self.dev,self.pbtv,timeout=1)  #初始化串口
        if self.t and self.t.isOpen():
            return True
        else:
            return False

    def closeSerial(self):
        if self.t and self.t.isOpen():
            self.t.close()
        self.t = None


    def isOpen(self):
        if self.t and self.t.isOpen():
            return True
        else:
            return False

    #测试通信是否正常,向设备发送连接测试字符，如果成功返回则说明连接正常
    def checkDevice(self):
        bstr = self.sendCmd('t')
        if bstr == 't':
            self.isOK = True
        else:
            self.isOK = False

    #发设备发送命令字符,pcmd为一个字符
    def sendCmd(self,pcmd):
        if self.isOpen():
            self.t.write(pcmd)
            self.t.flush()
            time.sleep(0.2) #等200毫秒
            n = t.inWaiting()
            if n:
                pstr = t.read(n)
                print(pstr)
                return pstr
            else:
                return ''
        else:
            return ''

stool = None

def initSerial(pPort,pBTV):
    global stool
    stool = STool(pPort,pBTV)

def openSerial():
    isopen = stool.openSerial()
    return isopen

def checkPort():
    stool.checkDevice()
    return stool.isOK

def sendCMD(pcmd):
    back = stool.sendCmd(pcmd)
    return back

def closePort():
    stool.closeSerial()

def touchOnce():
    dev = '/dev/cu.wchusbserial14140'  #这里请写你电脑正确的串口,windows请写"COM数字"这样的端口
    t = serial.Serial(dev,115200,timeout=1) #115200
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
    time.sleep(2)
    s = t.write('5')
    t.flush()
    n = t.inWaiting()
    count = 10
    # while n < 1 and count > 0:
    #     n = t.inWaiting()
    #     # s = t.write('2')
    #     t.flush()
    #     print(n)
    #     time.sleep(0.1)
    #     count -= 1
    n = t.inWaiting()
    print(n)
    time.sleep(0.5)
    n = t.inWaiting()
    print(n)
    pstr = t.read(n)
    print(pstr)
    t.close()
def test():
    print('aaaabbbb')
#测试
if __name__ == '__main__':
    touchOnce()
    
