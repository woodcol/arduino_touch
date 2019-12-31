#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2018-10-30 23:17:58
# @Author  : Mage
# @Link    : https://fengmm521.taobao.com
# @Version : $Id$

import os,sys
import serial
import time
import json

def func_getSerial():
    print(os.system('pwd'))
    try:
        if os.path.exists('config.json'):
            f = open('config.json','r')
            dictmp = json.loads(f.read())
            f.close()
            return dictmp['port'],dictmp['btv']
    except Exception as e:
        print('load config.josn erro...')
    return None,None

class STool(object):
    """docstring for STool"""
    #pdev:串口设备名
    #pbtlv:波特率,默认为115200
    def __init__(self):
        super(STool, self).__init__()
        self.dev,self.pbtv = func_getSerial()
        print(self.dev,self.pbtv)
        self.t = None
        if self.dev and self.pbtv:
            try:
                self.t = serial.Serial(self.dev,self.pbtv,timeout=0.5)
            except Exception as e:
                print('pyuitl init serial erro...')
        self.isOK = False
    # def setPort(self,pdev,pbtlv=115200):
    #     self.dev = pdev
    #     self.pbtv = pbtlv
    #     # tmp = copy()
    #     try:
    #         print(self.dev,self.pbtv)
    #         self.t = serial.Serial("/dev/cu.wchusbserial14140",115200,timeout=0.5)
    #     except Exception as e:
    #         print("pyutil设置串口错误...")
    #         self.t = None
    #打开串口
    def openSerial(self):
        print(self.dev)
        print(self.pbtv)
        # self.t = serial.Serial(str(self.dev),int(self.pbtv),timeout=1)  #初始化串口
        if self.t:
            if not self.t.isOpen():
                print('serial not open')
                self.t.open()
            if self.t.isOpen():
                return True
        else:
            print('not heave serial')
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
    #发设备发送命令字符,pcmd为一个字符
    def sendCmd(self,pcmd):
        print('per send cmd:%s'%(pcmd))
        if self.isOpen():
            print('is open sendcmd')
            self.t.write(pcmd)
            print('write end')
            self.t.flush()
            print('send start,%s'%(pcmd))
            return True
        else:
            print('serial not open')
            return False
    def readPort(self):
        if self.isOpen():
            n = self.t.inWaiting()
            # print(n)
            if n > 0:
                pstr = self.t.read(n)
                return pstr
            return ''
        else:
            return ''


stool = STool()


def func_initSerial(pPort,pBTV):
    print('save serial:%s,%d'%(pPort,pBTV))
    dictmp = {'port':str(pPort),'btv':int(pBTV)}
    out = json.dumps(dictmp)
    print(out)
    print(dictmp)
    f = open('config.json','w')
    f.write(out)
    f.close()

    return True


# def func_initSerial(pPort,pBTV):
#     print('initSerial')
#     stool.setPort('/dev/cu.wchusbserial14140',115200)
#     print('initSerial end')

def func_isSerialOpen():
    if stool:
        return stool.isOpen()
    return False

def func_openSerial():
    if stool:
        print('stool is heave')
    isopen = stool.openSerial()
    return isopen

def func_sendCMD(pcmd):
    back = stool.sendCmd(pcmd)
    print('send cmd python back:%d'%(back))
    return back

def func_readPort():
    back = stool.readPort()
    return back

def func_closePort():
    stool.closeSerial()

def func_touchOnce():
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
    func_initSerial('/dev/cu.wchusbserial14140', 115200)
    # time.sleep(2)
    # if(func_openSerial()):
    #     print('open ok')
    # else:
    #     print('open erro')
    # time.sleep(5)
    # func_sendCMD('t')
    # count = 10
    # while count > 0:
    #     count -= 1
    #     data = func_readPort()
    #     if data == '':
    #         time.sleep(0.1)
    #     else:
    #         print('get port data=%s'%(data))
    #         break
    # time.sleep(1)
    # func_closePort()
    time.sleep(1)
    dat = func_isSerialOpen()
    print(dat)

#测试
if __name__ == '__main__':
    test()
    
