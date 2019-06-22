#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "external/json/document.h"

#include <cstdio>
#include <exception>
#include <vector>
#include <string>

USING_NS_CC;
using namespace cocos2d::ui;

std::vector<std::string> split(std::string strtem,char a)
{
    std::vector<std::string> strvec;
    
    std::string::size_type pos1, pos2;
    pos2 = strtem.find(a);
    pos1 = 0;
    while (std::string::npos != pos2)
    {
        strvec.push_back(strtem.substr(pos1, pos2 - pos1));
        
        pos1 = pos2 + 1;
        pos2 = strtem.find(a, pos1);
    }
    strvec.push_back(strtem.substr(pos1));
    return strvec;
}


Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    
    _pyutil = new PyUtil();
//    std::string respath = FileUtils::getInstance()->fullPathForFilename("res/script/pyutil.py");
//    std::string scriptpath = PyUtil::g_getFolderPath(respath);
//    _pyutil->initWithPyFileName(scriptpath);
//    _pyutil->_testStep = -1;
    this->resetSerial();
    
    _portName = "";
    _uiLayer = Layer::create();
    addChild(_uiLayer);
    
    
    auto *dispatcher = Director::getInstance()->getEventDispatcher();
    auto* keyListener = EventListenerKeyboard::create();
    //创建一个事件监听器监听键盘事件
    keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    //键盘被按下时响应
    keyListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    //键盘按键被弹回时响应
    dispatcher->addEventListenerWithSceneGraphPriority(keyListener,this);


    
    _widget = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("res/NewUi_1.json"));
    _uiLayer->addChild(_widget);
    
    Size screenSize = Director::getInstance()->getWinSize();
    Size rootSize = _widget->getContentSize();
    _uiLayer->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                               (screenSize.height - rootSize.height) / 2));
    
    for(int i=1;i<10;i++)
    {
        std::string tmpstr = "btn_" + std::to_string(i);
        auto btn_tmp=  dynamic_cast<Button*>(Helper::seekWidgetByName(_widget, tmpstr));
    btn_tmp->addTouchEventListener(CC_CALLBACK_2(HelloWorld::btnEvent, this));
        _btns.push_back(btn_tmp);
    }
    
    // 10按键
    auto btn_ok =dynamic_cast<Button*>(Helper::seekWidgetByName(_widget, "btn_a"));
    btn_ok->addTouchEventListener(CC_CALLBACK_2(HelloWorld::btnEvent, this));
    
    // ok按键
    auto btn_b =dynamic_cast<Button*>(Helper::seekWidgetByName(_widget, "btn_b"));
    btn_b->addTouchEventListener(CC_CALLBACK_2(HelloWorld::btnEvent, this));
    
    //打开串口
    _btnconnect =dynamic_cast<Button*>(Helper::seekWidgetByName(_widget, "btn_connect"));
    _btnconnect->addTouchEventListener(CC_CALLBACK_2(HelloWorld::btnEvent, this));
    _btnconnect->setTitleText("打开串口");
    
    _logtxt = dynamic_cast<Text*>(Helper::seekWidgetByName(_widget, "lab_log"));
    
    _inputTxt =dynamic_cast<TextField*>(Helper::seekWidgetByName(_widget, "tf_input"));
    
    _inputBG =dynamic_cast<Layout*>(Helper::seekWidgetByName(_widget, "panle_bg"));
    _inputBG->setVisible(false);
    
    this->schedule(schedule_selector(HelloWorld::readPort),0.05f);
    
    if(_pyutil->openSerial()){
        _btnconnect->setTitleText("关闭串口");
        this->showlog("尝试打开之前设置的串口");
        this->isOpeningCOM = true;
        this->scheduleOnce([&](float dt){
            this->isCheckOK = false;
            this->sendCmd("t");
            _logtxt->setString("正在打开串口...");
        },2.0f,"checkSerial");
    }else{
        this->showlog("需要设置串口端口号,并手动打开串口.");
    }
    
    return true;
}

void HelloWorld::showlog(std::string plog)
{
    _logtxt->setString(plog);
}

//初始化串口和波特率
void HelloWorld::initPytool(std::string pport,int btv)
{
    cocos2d::FileUtils* fu = FileUtils::getInstance();
//    std::string path = fu->getWritablePath();
//    //c++字符串转c字符串
//    CCLOG("writable path is %s\n", path.c_str());
    //写入文件
    std::string path = fu->fullPathForFilename("config.json");
//    std::string txtFilePath = fu->fullPathFromRelativeFile("config.json", path);
//    CCLOG("file path is %s\n", txtFilePath.c_str());
    FILE * file = fopen(path.c_str(), "w");
    std::string fileContent = "{\"port\":\""+ pport + "\",\"btv\":" + std::to_string(btv) + "}";
    fwrite(fileContent.c_str(), 1, fileContent.size(), file);
    fclose(file);

}

void HelloWorld::CallBackForSend(std::string callback)
{
    if(_pyutil->_lastSendCmd.compare(callback.c_str()) == 0)
    {
        
        if(callback.compare("t") == 0){
            this->isCheckOK = true;
            this->isOpen = true;
            this->isOpeningCOM = false;
            this->unschedule("checkSerial");
            _logtxt->setString("串口已连接");
            _btnconnect->setTitleText("关闭串口");
            
            //串口打开后，每0.5秒检测一次串口是否还是打开的
//            this->schedule([&](float dt){
//                if(!_pyutil->isOpen()){
//                    this->unschedule("checkconnect");
//                    this->showlog("串口已断开连接");
//                    this->isOpen =false;
//                    this->isCheckOK = false;
//                    _pyutil->closeSerial();
//                    _btnconnect->setTitleText("打开串口");
//                    
//                }
//            }, 1.0f,"checkconnect");
            
        }else{
            _logtxt->setString(callback);
        }
    }
}

void HelloWorld::readPort(float dt){
    std::string readval= _pyutil->readPort();
    if(readval.empty()){
        return;
    }else{
        _lastReadData = readval;
        CCLOG("read data=%s",readval.c_str());
        CallBackForSend(_lastReadData);
    }
}
HelloWorld::HelloWorld()
{
#ifdef _WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif
}

HelloWorld::~HelloWorld()
{
#ifdef _WIN32
	WSACleanup();
#endif
}
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event)
{
    
}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event)
{
    std::string keytype = "";
    switch (keycode) {
        
    //W,向上
        case EventKeyboard::KeyCode::KEY_0: //0
        {
            CCLOG("10");
            keytype = "a";
        }
            break;
        case EventKeyboard::KeyCode::KEY_1: //1
        {
			CCLOG("1");
            keytype = "1";
        }
            break;
        case EventKeyboard::KeyCode::KEY_2: //W
        {
            CCLOG("2");
            keytype = "2";
        }
            break;
            
        case EventKeyboard::KeyCode::KEY_3: //向下键
        {
            CCLOG("3");
            keytype = "3";
        }
            break;
        case EventKeyboard::KeyCode::KEY_4: //大写S
        {
            CCLOG("4");
            keytype = "4";
        }
            break;
        case EventKeyboard::KeyCode::KEY_5: //W
        {
            CCLOG("5");
            keytype = "5";
        }
            break;
            
        case EventKeyboard::KeyCode::KEY_6: //向左键
        {
            CCLOG("6");
            keytype = "6";
        }
            break;
        case EventKeyboard::KeyCode::KEY_7: //大写A
        {
            CCLOG("7");
            keytype = "7";
        }
            break;
        case EventKeyboard::KeyCode::KEY_8: //A
        {
            CCLOG("8");
            keytype = "8";
        }
            break;
    
        case EventKeyboard::KeyCode::KEY_9: //向右键
        {
            CCLOG("9");
            keytype = "9";
        }
            break;
    
    //ok
        case EventKeyboard::KeyCode::KEY_SPACE: //空格键
        {
            CCLOG("ok");
            keytype = "b";
        }
            break;
        case EventKeyboard::KeyCode::KEY_P://回车键
        {
            CCLOG("ok");
            keytype = "b";
        }
            break;
        default:
            break;
    }
    if(this->isOpen && this->isCheckOK)
    {
        sendCmd(keytype);
    }else{
//        if(_portName.empty()){
//            _logtxt->setString("串口未打开，或串口未连接\n请设置串口端口后，打开串口");
//        }else{
//        _logtxt->setString("串口未打开，或串口未连接\n请确保串口未被其他程序占用.\n程序将再次尝试打开串口:"+_portName);
//            this->openSerial(_portName);
//        }
    }
    
}

void HelloWorld::delayFunc(float dt)
{
    
    delete _pyutil;
    
    _pyutil = new PyUtil();
    
    this->resetSerial();
    
    if(!this->isOpeningCOM){
        if(this->isOpen){
            _pyutil->closeSerial();
            this->isOpen =false;
            this->isCheckOK = false;
            _logtxt->setString("串口已关闭");
            _btnconnect->setTitleText("打开串口");
            
        }else{
            this->scheduleOnce([&](float dt){
                CCLOG("打开串口。。。。");
                if(_pyutil->openSerial()){
                    CCLOG("UI打开串口成功");
                }else{
                    CCLOG("UI打开串口失败");
                }
                
            },0.5f,"openSerial");
            
            
//            this->schedule([&](float dt){
//                 this->isCheckOK = false;
//                 this->sendCmd("t");
//                 CCLOG("发送t测试。。。。");
//             },0.5,8,1.0f,"checkSerial")
            _openTimes = 8;
            this->schedule([&](float dt){
                 this->isCheckOK = false;
                 this->sendCmd("t");
                 CCLOG("发送t测试。。。。");
                _openTimes--;
                if(_openTimes < 1)
                {
                    this->unschedule("checkSerial");
                    this->showlog("打开串口失败");
                    this->isOpen =false;
                    this->isCheckOK = false;
                    _pyutil->closeSerial();
                    _btnconnect->setTitleText("打开串口");
                    _btnconnect->setTitleText("打开串口");
                }
            }, 0.5f,"checkSerial");
            
//            this->scheduleOnce([&](float dt){
//                this->isCheckOK = false;
//                this->sendCmd("t");
//                CCLOG("发送t测试。。。。");
//            },3.0f,"checkSerial");
            _logtxt->setString("正在打开串口...");
            this->isOpeningCOM = true;
        }
    }
}

void HelloWorld::openSerial(std::string comport)
{
#ifdef _WIN32
//    _pyutil->initWithPort(comport);
    //{"btv": 115200, "port": "/dev/cu.wchusbserial14140"}
    this->initPytool(comport);
#else
//    _pyutil->initWithPort("/dev/cu.wchusbserial14140");
    this->initPytool("/dev/cu.wchusbserial14140");
    //                        this->scheduleOnce(schedule_selector() selector, 0.5f);
#endif
    
    this->scheduleOnce(schedule_selector(HelloWorld::delayFunc),0.3f);
}

void HelloWorld::resetSerial()
{
    std::string respath = FileUtils::getInstance()->fullPathForFilename("res/script/pyutil.py");
    std::string scriptpath = PyUtil::g_getFolderPath(respath);
    _pyutil->initWithPyFileName(scriptpath);
    _pyutil->_testStep = -1;
}
void HelloWorld::sendCmd(std::string pcmd)
{
    
    if(pcmd.empty()){
        return;
    }else{
        _pyutil->sendCMD(pcmd);
    }
}

void HelloWorld::btnEvent(Ref *pSender, Widget::TouchEventType type)
{
    auto tmpbtn =dynamic_cast<Widget*>(pSender);
    
    auto btnName = tmpbtn->getName();
    
    
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
        {
            auto tpoint = tmpbtn->getTouchBeganPosition();
            
            CCLOG("touch began---%s",btnName.c_str());
            CCLOG("touch point:%.2f,%.2f",tpoint.x,tpoint.y);
            
        }
            break;
            
        case Widget::TouchEventType::MOVED:
        {
             CCLOG("touch moveed---");
        }
            break;
        
        case Widget::TouchEventType::ENDED:
        {
             CCLOG("touch ended---");
            auto tpoint = tmpbtn->getTouchBeganPosition();
            if(btnName.compare("btn_connect") == 0){
                //打开串口被按下
                CCLOG("btn_connect");
                std::string comport = _inputTxt->getString();
                if(this->isOpen &&  (!this->isOpeningCOM))
                {
                    _pyutil->closeSerial();
                    this->isOpen =false;
                    this->isCheckOK = false;
                    _logtxt->setString("串口已关闭");
                    _btnconnect->setTitleText("打开串口");
                }else{
                    if(!comport.empty())
                    {
                        int tmpint = atoi(comport.c_str());
                        if(comport.compare("0") != 0 && tmpint == 0)
                        {
                            //                        CCLOG("erro comport number %s",comport.c_str());
                            if(comport.compare("test") == 0){
                                CCLOG("connect test");
                                _pyutil->pyfuncTest();
                                
                                Button* btncon = dynamic_cast<Button*>(tmpbtn);
                                btncon->setTitleText("关闭串口");
                                
                            }
                        }else{
                            
                            CCLOG("btn_connect %s",comport.c_str());
                            _portName = "COM" + comport;
                            this->openSerial(_portName);
                            
                        }
                    }
                }
                
                
            }else{
                std::vector<std::string> tmps = split(btnName,'_');
                std::string endCode = tmps.back();
                CCLOG("%s",endCode.c_str());
                if(this->isOpen && this->isCheckOK){
                   _pyutil->sendCMD(endCode);
                }
            }
            

           
        }
            break;
            
        case Widget::TouchEventType::CANCELED:
        {
            CCLOG("touch CANCELED---");
        }
            break;
            
        default:
            break;
    }
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}
