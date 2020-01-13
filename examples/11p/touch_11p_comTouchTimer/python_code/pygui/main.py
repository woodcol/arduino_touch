#!/usr/bin/env python
# -*- coding: utf-8 -*-
# author:洪卫
 

import pyutil
import time
import threading
import json
import timetool

class WorkerThread(threading.Thread):
    """
    This just simulates some long-running task that periodically sends
    a message to the GUI thread.
    """
    def __init__(self, puitool):
        threading.Thread.__init__(self)
        self.uitool = puitool

    def stop(self):
        pass
    def run(self):

        # downtool.downLoadWithStrList(self.liststr, self.countCallBack,self.savePth)
        try:
            while True:
                time.sleep(0.1)
                dat = pyutil.func_readPort()
                if dat != '' and self.uitool:
                    print('back data=' + dat)
                    self.uitool.callback(dat)
        except Exception as e:
            if self.uitool:
                self.uitool.showLog('读取串口数据错误')
                print('读取串口数据错误')
                print(e)
            else:
                print('读取串口数据错误')


class COMTool(object):
    """docstring for COMTool"""
    def __init__(self):
        #
        self.isOpen = False
        self.isCheckOK = False
        self.isOpeningCOM = False
        self.portName = ''
        self.lastReadData = None
        self.callbackTh = None

        self.isTestCom = False

        self.initCallBack()

        self.comPort = None


        if pyutil.func_isSerialOpen():
            self.showLog('正在打开之前设置的串口')
            self.isOpeningCOM = True
            self.isTestCom = True
            self.comPort = pyutil.stool.dev[3:]
            self.showLog('serial port:' + str(self.comPort))
    def showLog(self,pmsg):
        print(pmsg)
    #服务器返回的数据
    def initCallBack(self):
        self.callbackTh = WorkerThread(self)
        self.callbackTh.setDaemon(True)
        self.callbackTh.start()
    def callback(self,dat):
        if str(dat) == 't':
            self.isTestCom = False
            self.isCheckOK = True
            self.isOpen = True
            self.isOpeningCOM = False
            self.showLog("串口已连接")
        else:
            self.showLog(str(dat))
    def touch1(self): # 在鼠标焦点处插入输入内容
        # t.insert('insert', var)
        pyutil.func_sendCMD('1')
        self.showLog('touch J1')
    def touch2(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('2')
        self.showLog('touch J2')
    def touch3(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('3')
        self.showLog('touch J3')
    def touch4(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('4')
        self.showLog('touch J4')
    def touch5(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('5')
        self.showLog('touch J5')
    def touch6(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('6')
        self.showLog('touch J6')
    def touch7(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('7')
        self.showLog('touch J7')
    def touch8(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('8')
        self.showLog('touch J8')
    def touch9(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('9')
        self.showLog('touch J9')
    def touch10(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('a')
        self.showLog('touch J10')
    def touchOK(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('b')
        self.showLog('touch Jok')
    def touchConnect(self):   # 在文本框内容最后接着插入输入内容

        self.comPort = self.e.get()
        if self.isOpen and self.isOpeningCOM:
            pyutil.func_closePort()
            self.showLog("关闭串口成功")
        else:
            print(self.comPort)
            if self.comPort and self.comPort != '' and int(self.comPort) >= 0 and int(self.comPort) < 20: 
                self.showLog("正在打开串口:com%s,请等串口初始化完成"%(self.comPort))
                time.sleep(0.5)
                if not self.isOpeningCOM:
                    print('xdd')
                    if self.isOpen:
                        pyutil.func_closePort()
                        self.isOpen = False
                        self.showLog("串口已关闭")
                    else:
                        tmport = 'com' + self.comPort
                        self.initSeial(tmport)
                        time.sleep(0.5)
                        if pyutil.func_openSerial():
                            print('open ok')
                            self.isCheckOK = False
                        else:
                            print('open erro')
                        time.sleep(0.5)
                        if not self.isCheckOK and pyutil.func_isSerialOpen():
                            self.isOpeningCOM = True
                            self.isTestCom = True
    def initSeial(self,pPort,btv=115200):
        pyutil.func_initSerial(pPort,btv)

class TimeObj(object):
    """docstring for TimeObj"""
    def __init__(self):
        super(TimeObj, self).__init__()
        self.timedict = {}
        self.times = []
        self.initTimer()
    def initTimer(self):
        f = open('timer.json','r')
        dat = f.read()
        configs = json.loads(dat)
        f.close()
        for i,v in enumerate(configs):
            tmptime = int(timetool.conventTimeFromStrConfig(v['time'])*1000)
            self.timedict[tmptime] = v['number']
            self.times.append(tmptime)
        self.times.sort()

def serialThread(pUtool):
    time.sleep(1)
    if pyutil.func_isSerialOpen():
        pUtool.showLog('尝试打开之前设置的串口')
    else:
        pUtool.showLog('未设置串口号，或串口被占用，\n串口号可在设备管理器中查看')
    time.sleep(2.0)
    pyutil.func_sendCMD('t')
    taskobj = TimeObj()
    times = taskobj.times
    while True:
        time.sleep(0.005)
        nowtime = int(time.time()*1000)
        if len(times) > 0 and times[0] <= nowtime:
            if nowtime - times[0] > 60: #一分钟前已点击，这里直接认为时间为无效
                ptime = times.pop(0)
                taskobj.timedict.pop(ptime)
                print('time is passed:%s'%(timetool.getNowDate(ptime/1000)))
            else:
                touchdat = taskobj.timedict.pop(times.pop(0))
                key = touchdat['key']
                tmpcount = touchdat['times']
                delay = touchdat['delay']
                while tmpcount > 0:
                    pyutil.func_sendCMD(key)
                    if delay > 0:
                        time.sleep(delay/1000.0)
                    else:
                        time.sleep(0.005)
                    tmpcount -= 1
        elif len(times) < 1:
            taskobj.initTimer()
            times = taskobj.times
            time.sleep(1.0)
            print('init times again')

def main():
    comtool = COMTool()
    serth = threading.Thread(target=serialThread,args=(comtool,))
    serth.setDaemon(True)
    serth.start()
    while True:
        time.sleep(1)

if __name__ == '__main__':
    main()