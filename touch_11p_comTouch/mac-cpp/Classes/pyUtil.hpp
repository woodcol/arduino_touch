//
//  JimiConfigData.hpp
//  jimipro
//
//  Created by mage on 2019/3/7.
//

#ifndef JimiConfigData_hpp
#define JimiConfigData_hpp

#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include <Python.h>
#include <iostream>


// 取文件夹名字 无后缀


class PyUtil
{
public:
    PyUtil();
    ~PyUtil();
    
    //其他工具, 从文件路径中获取文件所在目录路径
    static std::string g_getFolderPath(std::string str);
    
    std::vector<std::string> m_ports;
    
    PyObject* m_moduleName; //模块名
    PyObject* m_pModule;    //模块
    
    PyObject* m_func_InitSerial;         //初始化串口的python函数
    PyObject* m_func_openSerial;         //打开串口的python函数
    PyObject* m_func_checkPort;          //检查串口通信的python函数
    PyObject* m_func_sendCMD;            //串口发送命令的python函数
    PyObject* m_func_readPort;            //串口发送命令的python函数
    PyObject* m_func_closePort;          //关闭串口的python函数
    
    
    bool initWithPyFileName(std::string respath,std::string filename = "pyutil");
    bool initPyFunc(); //初始化python函数
    
    //使用串口端口号和波特率设置串口
    void initWithPort(std::string port,int btv = 115200);
    //打开串口
    bool openSerial();
    //串口发送字符命令
    bool sendCMD(std::string pcmd);
    //串口读取字符命令
    std::string readPort();
    //关闭串口
    void closeSerial();
    
    bool isOpen();
    
    std::vector<std::string> getPorts();
    
    //test
    void pyfuncTest();
    int _testStep = -1;
    
    std::string _lastSendCmd;
    
};


#endif /* JimiConfigData_hpp */
