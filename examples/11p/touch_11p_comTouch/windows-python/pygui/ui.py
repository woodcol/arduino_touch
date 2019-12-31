#!/usr/bin/env python
# -*- coding: utf-8 -*-
# author:洪卫
 
import tkinter as tk  # 使用Tkinter前需要先导入
 
from tkinter import StringVar, IntVar

import pyutil
import time
import threading

# import Queue

# class MsgObj():
#     def __init__(self,msg,ptype = 'msg'):
#         self.ptype = ptype
#         self.data = msg

# class showMsgTool(object):
#     """docstring for ClassName"""
#     def __init__(self):
#         self.uitool = None
        
#     def setUIObj(self,uiobj):
#         self.uitool = uiobj
#     def showMsgTOUI(self,msg):
#         if self.uitool:
#             msgobj = MsgObj(msg)
#             self.uitool.queue.put(msgobj)
#             # self.uitool.showMsg(msg)
#     def sendCmd(self,cmd):
#         if self.uitool:
#             msgobj = MsgObj(cmd,'cmd')
#             self.uitool.queue.put(msgobj)

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
        # self.queue = Queue.Queue()
        #
        self.window = tk.Tk()
        self.window.title('青苹果屏幕点击器')
        self.window.geometry('500x360')  # 这里的乘是小x
        self.log = StringVar()
        self.log.set('正在初始化。。。')
        self.status = IntVar()
        self.comPort = None
        self.conBtnTxt = StringVar()
        self.conBtnTxt.set('打开串口')

        self.eTxt = StringVar()

        self.lbcom = tk.Label(self.window,text = 'com')
        self.lbcom.place(x=25,y=255,anchor='nw')

        self.e = tk.Entry(self.window,textvariable=self.eTxt, width=5,show = None)#显示成明文形式
        # e.pack()
        self.e.place(x=65,y=255,anchor='nw')

        self.lbinputlog = tk.Label(self.window,text = '在下边输入串口编号，串口号在设备管理器查看')
        self.lbinputlog.place(x=5,y=220,anchor='nw')

        
        # 第6步，创建并放置两个按钮分别触发两种情况
        self.b1 = tk.Button(self.window, text='1', width=5,
                       height=2, command=self.touch1)
        # b1.pack()
        self.b1.place(x=305,y=5,anchor='nw')

        self.b2 = tk.Button(self.window, text='2', width=5,
                       height=2, command=self.touch2)
        # b2.pack()
        self.b2.place(x=355,y=5,anchor='nw')

        self.b3 = tk.Button(self.window, text='3', width=5,
                       height=2, command=self.touch3)
        self.b3.place(x=405,y=5,anchor='nw')


        self.b4 = tk.Button(self.window, text='4', width=5,
                       height=2, command=self.touch4)
        self.b4.place(x=305,y=55,anchor='nw')
        self.b5 = tk.Button(self.window, text='5', width=5,
                       height=2, command=self.touch5)
        self.b5.place(x=355,y=55,anchor='nw')
        self.b6 = tk.Button(self.window, text='6', width=5,
                       height=2, command=self.touch6)
        self.b6.place(x=405,y=55,anchor='nw')


        self.b7 = tk.Button(self.window, text='7', width=5,
                       height=2, command=self.touch7)
        self.b7.place(x=305,y=105,anchor='nw')
        self.b8 = tk.Button(self.window, text='8', width=5,
                       height=2, command=self.touch8)
        self.b8.place(x=355,y=105,anchor='nw')
        self.b9 = tk.Button(self.window, text='9', width=5,
                       height=2, command=self.touch9)
        self.b9.place(x=405,y=105,anchor='nw')

        self.b10 = tk.Button(self.window, text='10', width=5,
                       height=2, command=self.touch10)
        self.b10.place(x=305,y=155,anchor='nw')
        self.bok = tk.Button(self.window, text='ok', width=5,
                       height=2, command=self.touchOK)
        self.bok.place(x=405,y=155,anchor='nw')
         

        self.bcon = tk.Button(self.window,textvariable=self.conBtnTxt, width=10,
                       height=2, command=self.touchConnect)
        self.bcon.place(x=335,y=255,anchor='nw')

        self.lb = tk.Label(self.window,width=40,height=10,textvariable = self.log)
        self.lb.place(x=5,y=5,anchor='nw')

        if pyutil.func_isSerialOpen():
            self.showLog('正在打开之前设置的串口')
            self.isOpeningCOM = True
            self.isTestCom = True
            self.comPort = pyutil.stool.dev[3:]
            self.eTxt.set(self.comPort)

    def uiLoop(self):
        # 第8步，主窗口循环显示
        self.window.mainloop()
    def showLog(self,pmsg):
        self.log.set(str(pmsg))
    #服务器返回的数据
    def initCallBack(self):
        self.callbackTh = WorkerThread(self)
        self.callbackTh.setDaemon(True)
        self.callbackTh.start()
    def callback(self,dat):
        print(dat)
        if dat == 't':
            self.isTestCom = False
            self.isCheckOK = True
            self.isOpen = True
            self.isOpeningCOM = False
            self.showLog("串口已连接")
            self.conBtnTxt.set('关闭串口')
        else:
            self.log.set(dat)
    def touch1(self): # 在鼠标焦点处插入输入内容
        # t.insert('insert', var)
        pyutil.func_sendCMD('1')
        self.log.set("正在发送1")
    def touch2(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('2')
        self.log.set("正在发送2")
    def touch3(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('3')
        self.log.set("正在发送3")
    def touch4(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('4')
        self.log.set("正在发送4")
    def touch5(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('5')
        self.log.set("正在发送5")
    def touch6(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('6')
        self.log.set("正在发送6")
    def touch7(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('7')
        self.log.set("正在发送7")
    def touch8(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('8')
        self.log.set("正在发送8")
    def touch9(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('9')
        self.log.set("正在发送9")
    def touch10(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('a')
        self.log.set("正在发送10")
    def touchOK(self):   # 在文本框内容最后接着插入输入内容
        pyutil.func_sendCMD('b')
        self.log.set("正在发送ok")
    def touchConnect(self):   # 在文本框内容最后接着插入输入内容

        self.comPort = self.e.get()
        if self.isOpen and self.isOpeningCOM:
            pyutil.func_closePort()
            self.log.set("关闭串口成功")
        else:
            print(self.comPort)
            if self.comPort and self.comPort != '' and int(self.comPort) >= 0 and int(self.comPort) < 20: 
                self.log.set("正在打开串口:com%s,请等串口初始化完成"%(self.comPort))
                time.sleep(0.5)
                if not self.isOpeningCOM:
                    print('xdd')
                    if self.isOpen:
                        pyutil.func_closePort()
                        self.isOpen = False
                        self.log.set("串口已关闭")
                        self.conBtnTxt.set('打开串口')
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


def serialThread(pUtool):
    time.sleep(1)
    if pyutil.func_isSerialOpen():
        pUtool.showLog('尝试打开之前设置的串口')
    else:
        pUtool.showLog('未设置串口号，或串口被占用，\n串口号可在设备管理器中查看')
    while True:
        time.sleep(1.0)
        if pUtool.isTestCom:
            pyutil.func_sendCMD('t')

def main():
    comtool = COMTool()
    serth = threading.Thread(target=serialThread,args=(comtool,))
    serth.setDaemon(True)
    serth.start()
    comtool.uiLoop()

if __name__ == '__main__':
    main()