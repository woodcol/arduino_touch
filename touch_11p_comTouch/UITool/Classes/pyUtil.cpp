//
//  JimiConfigData.cpp
//  jimipro
//
//  Created by mage on 2019/3/7.
//

#include "pyUtil.hpp"


PyUtil::PyUtil(){
   

}

void PyUtil::initWithPort(std::string port)
{
    
}
std::vector<std::string> PyUtil::getPorts()
{
    return m_ports;
}
bool PyUtil::isOpen()
{
    return false;
}

bool PyUtil::sendCmd(std::string pcmd)
{
    return false;
}


PyUtil::~PyUtil(){
    
}
