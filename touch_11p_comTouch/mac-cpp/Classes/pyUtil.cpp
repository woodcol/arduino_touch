//
//  JimiConfigData.cpp
//  jimipro
//
//  Created by mage on 2019/3/7.
//

#include "pyUtil.hpp"


//C++和python通信
/*
https://blog.csdn.net/tobacco5648/article/details/50890106

C++路径的一些操作
https://www.jianshu.com/p/4ea92d9688d1

Arduino串口通信
https://blog.csdn.net/iracer/article/details/50334041
*/


PyUtil::PyUtil(){
   
    Py_Initialize();
//    PyRun_SimpleString("import sys");
//    PyRun_SimpleString("import os");
//    PyRun_SimpleString("import time");
}

std::string PyUtil::g_getFolderPath(std::string str)
{
    std::string::size_type idx = str.rfind('/', str.length());
    std::string folder = str.substr(0, idx);
    return folder;
}

bool PyUtil::initWithPyFileName(std::string respath,std::string filename)
{
    
    std::string chdir_cmd = std::string("sys.path.append(\"") + respath + "\")";
    const char* cstr_cmd = chdir_cmd.c_str();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(cstr_cmd);
    _lastSendCmd = "";
//    ---------------------
//    作者：liuwons
//    来源：CSDN
//    原文：https://blog.csdn.net/tobacco5648/article/details/50890106
//    版权声明：本文为博主原创文章，转载请附上博文链接！
    
     m_moduleName = PyString_FromString(filename.c_str());
    if(!m_moduleName){
        printf("mode name erro,path=%s,\nfilename=%s\n",respath.c_str(),filename.c_str());
        return false;
    }else{
        printf("load ok,path=%s,\nfilename=%s\n",respath.c_str(),filename.c_str());
    }
     m_pModule = PyImport_Import(m_moduleName);
    if(!m_pModule)
    {
        printf("load py file erro");
        return false;
    }else{
        return initPyFunc();
    }
    return true;
}

bool PyUtil::initPyFunc()
{
    if(m_pModule)
    {
        //初始化串口，需要两个参数，1:串口端口，2:串口波特率
        m_func_InitSerial = PyObject_GetAttrString(m_pModule, "func_initSerial");
        
        //打开串口,无参数，返回是否打开成功，成功为true,失败为false
        m_func_openSerial = PyObject_GetAttrString(m_pModule, "func_openSerial");
        
        //检查串口是否打开,正常返回true, 错误返回false
        m_func_checkPort = PyObject_GetAttrString(m_pModule, "func_isSerialOpen");
        
        //向串口发送数据，一个参数发送的数据为一个字符，,正常会返回发送的字符，否则返回空字符
        m_func_sendCMD = PyObject_GetAttrString(m_pModule, "func_sendCMD");
        
        m_func_readPort = PyObject_GetAttrString(m_pModule, "func_readPort");
        
        //关闭串口，无参数,无返回值
        m_func_closePort = PyObject_GetAttrString(m_pModule, "func_closePort");
        
        
        return true;
        
    }else{
        printf("init py func erro");
        return false;
    }
    
}

void PyUtil::initWithPort(std::string port,int btv)
{
      if(m_func_InitSerial)
      {
          PyObject* args = Py_BuildValue("(si)", port.c_str(), btv);
          PyObject* pRet = PyObject_CallObject(m_func_InitSerial, args);
          if(pRet){
              printf("set port ok\n");
          }
      }else{
          printf("init serial erro...\n");
      }
    Py_Finalize();
}

bool PyUtil::openSerial()
{
    
    if(m_func_openSerial)
    {
        PyObject* args = Py_BuildValue("()");
        PyObject* pRet = PyObject_CallObject(m_func_openSerial, args);
        if (pRet)
        {
            long bHasVul =PyLong_AsLong(pRet);
            printf("openSerial ret:%ld\n",bHasVul);
            if(bHasVul != 0){
                return true;
            }else{
                return false;
            }
        }
    }else{
        printf("init serial erro...\n");
        return false;
    }
    return false;
}


bool PyUtil::sendCMD(std::string pcmd)
{
    printf("send cmd=%s\n",pcmd.c_str());
    if(m_func_sendCMD)
    {
        PyObject* args = Py_BuildValue("(s)",pcmd.c_str());
        PyObject* pRet = PyObject_CallObject(m_func_sendCMD, args);
        if (pRet)
        {
            long bHasVul =PyLong_AsLong(pRet);
            printf("sendCMD ret:%ld\n",bHasVul);
            if(bHasVul != 0){
                _lastSendCmd = pcmd;
                return true;
            }else{
                return false;
            }
        }else{
            printf("send cmd not back\n");
        }
    }else{
        printf("init serial erro...\n");
    }
    return false;
}

std::string PyUtil::readPort()
{
    if(m_func_readPort)
    {
        PyObject* args = Py_BuildValue("()");
        PyObject* pRet = PyObject_CallObject(m_func_readPort, args);
        if (pRet)
        {
            std::string retString =PyString_AsString(pRet);
            if(retString.empty())
            {
                return "";
            }
            printf("readPort ret:%s\n",retString.c_str());
            return retString;
        }
    }else{
//        printf("readPort erro...\n");
    }
    return "";
}


void PyUtil::closeSerial()
{
    if(m_func_closePort)
    {
        PyObject* args = Py_BuildValue("()");
        PyObject* pRet = PyObject_CallObject(m_func_closePort, args);
        if(pRet){
            printf("close port ok\n");
        }
    }else{
        printf("init serial erro...\n");
    }
}

std::vector<std::string> PyUtil::getPorts()
{
    return m_ports;
}
bool PyUtil::isOpen()
{
    if(m_func_checkPort)
    {
        PyObject* args = Py_BuildValue("()");
        PyObject* pRet = PyObject_CallObject(m_func_checkPort, args);
        if(pRet){
            long bHasVul =PyLong_AsLong(pRet);
            printf("isOpen ret:%ld\n",bHasVul);
            if(bHasVul != 0){
                return true;
            }
        }
    }else{
        printf("init serial erro...\n");
    }
    return false;
}

void PyUtil::pyfuncTest()
{
    if(_testStep < 0){
        _testStep = 0;
    }
    switch (_testStep) {
        case 0: //初始化并打开串口
        {
            initWithPort("/dev/cu.wchusbserial14140");
//            if(openSerial())
//            {
//                printf("open serial ok\n");
//            }else{
//                printf("open serial erro\n");
//            }
        }
            break;
        case 1: //打开串口
        {
            if(openSerial())
            {
                printf("openSerial ok\n");
            }else{
                _testStep = 0;
                printf("openSerial erro\n");
            }
        }
            break;
        case 2: //检查串口
        {
            bool isSend = sendCMD("5");
            printf("sendcmd t and back:%d\n",isSend);
        }
            break;
            
        case 3: //发送字符命令
        {
            bool isSend = sendCMD("9");
            printf("sendcmd 9 and back:%d\n",isSend);
        }
            break;
        case 4: //发送字符命令
        {
            bool isSend = sendCMD("3");
            printf("sendcmd 3 and back:%d\n",isSend);
        }
            break;
            
        default:
            _testStep = -99;
            break;
    }
    _testStep++;
    
}

PyUtil::~PyUtil(){
    closeSerial();
    Py_Finalize();
    
}
