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

class PyUtil
{
public:
    PyUtil();
    ~PyUtil();
    
    std::vector<std::string> m_ports;
    
    void initWithPort(std::string port);
    bool isOpen();
    bool sendCmd(std::string pcmd);
    std::vector<std::string> getPorts();
};


#endif /* JimiConfigData_hpp */
