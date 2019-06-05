#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

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
    auto btn_connect =dynamic_cast<Button*>(Helper::seekWidgetByName(_widget, "btn_connect"));
    btn_connect->addTouchEventListener(CC_CALLBACK_2(HelloWorld::btnEvent, this));
    
    _logtxt = dynamic_cast<Text*>(Helper::seekWidgetByName(_widget, "lab_log"));
    
    _inputTxt =dynamic_cast<TextField*>(Helper::seekWidgetByName(_widget, "tf_input"));
    
    _inputBG =dynamic_cast<Layout*>(Helper::seekWidgetByName(_widget, "panle_bg"));
    _inputBG->setVisible(false);
    
    
    return true;
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
            keytype = "10";
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
            
    //S,向下
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
            
    //A,向左
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
    
    //D，向右
        case EventKeyboard::KeyCode::KEY_9: //向右键
        {
            CCLOG("9");
            keytype = "9";
        }
            break;
    
    //播放/暂停
        case EventKeyboard::KeyCode::KEY_SPACE: //空格键
        {
            CCLOG("ok");
            keytype = "ok";
        }
            break;
        case EventKeyboard::KeyCode::KEY_P://回车键
        {
            CCLOG("ok");
            keytype = "ok";
        }
            break;
        default:
            break;
    }
    if(isOpen)
    {
        sendCmd(keytype);
    }
    
}



void HelloWorld::sendCmd(std::string pcmd)
{
    
    if(pcmd.empty()){
        return;
    }else{
        
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
                if(!comport.empty())
                {
                    int tmpint = atoi(comport.c_str());
                    if(comport.compare("0") != 0 && tmpint == 0)
                    {
                        CCLOG("erro comport number %s",comport.c_str());
                    }else{
                        CCLOG("btn_connect %s",comport.c_str());
                    }
                }
                
            }else{
                std::vector<std::string> tmps = split(btnName,'_');
                std::string endCode = tmps.back();
                CCLOG(endCode.c_str());
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
