//
//  JimiConfigData.cpp
//  jimipro
//
//  Created by mage on 2019/3/7.
//

#include "pyUtil.hpp"





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
        m_func_InitSerial = PyObject_GetAttrString(m_pModule, "initSerial");
        
        //打开串口,无参数，返回是否打开成功，成功为true,失败为false
        m_func_openSerial = PyObject_GetAttrString(m_pModule, "openSerial");
        
        //检查通信是否正确,正常返回true, 错误返回false
        m_func_checkPort = PyObject_GetAttrString(m_pModule, "checkPort");
        
        //向串口发送数据，一个参数发送的数据为一个字符，,正常会返回发送的字符，否则返回空字符
        m_func_sendCMD = PyObject_GetAttrString(m_pModule, "sendCmd");
        
        //关闭串口，无参数,无返回值
        m_func_closePort = PyObject_GetAttrString(m_pModule, "closePort");
        
        
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
              printf("set port ok");
          }
      }else{
          printf("init serial erro...");
      }
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
            printf("ret:%l",bHasVul);
            if(bHasVul != 0){
                return true;
            }else{
                return false;
            }
        }
    }else{
        printf("init serial erro...");
        return false;
    }
    return false;
}

bool PyUtil::checkSerial()
{
    if(m_func_checkPort)
    {
        PyObject* args = Py_BuildValue("()");
        PyObject* pRet = PyObject_CallObject(m_func_checkPort, args);
        if (pRet)
        {
            long bHasVul =PyLong_AsLong(pRet);
            printf("ret:%ld",bHasVul);
            if(bHasVul != 0){
                return true;
            }else{
                return false;
            }
        }
    }else{
        printf("init serial erro...");
        return false;
    }
    return false;
}

std::string PyUtil::sendCMD(std::string pcmd)
{
    if(m_func_sendCMD)
    {
        PyObject* args = Py_BuildValue("(s)",pcmd.c_str());
        PyObject* pRet = PyObject_CallObject(m_func_sendCMD, args);
        if (pRet)
        {
            std::string retString =PyString_AsString(pRet);
            printf("ret:%s",retString.c_str());
            return retString;
        }
    }else{
        printf("init serial erro...");
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
            printf("close port ok");
        }
    }else{
        printf("init serial erro...");
    }
}

std::vector<std::string> PyUtil::getPorts()
{
    return m_ports;
}
bool PyUtil::isOpen()
{
    return checkSerial();
}

bool PyUtil::sendCmd(std::string pcmd)
{
    return false;
}

void PyUtil::pyfuncTest()
{


}

PyUtil::~PyUtil(){
    Py_Finalize();
}
