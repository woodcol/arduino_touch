#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "pyUtil.hpp"
class UDPClient;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	HelloWorld();
	~HelloWorld();
    
    cocos2d::Layer* _uiLayer;
    cocos2d::ui::Layout* _widget;
    
    cocos2d::ui::Layout* _inputBG;
    
    cocos2d::ui::Text* _logtxt;
    
    cocos2d::ui::TextField* _inputTxt;
    
    std::vector<cocos2d::ui::Button*> _btns;
    

    void btnEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    
    void helpUIEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);

    
    std::string touchMidBeganWithPoint(cocos2d::Point tp);
    
    
    
//电脑键盘事件监听
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
//    ---------------------
//    作者：醉卧南楼
//    来源：CSDN
//    原文：https://blog.csdn.net/wsr270591269/article/details/72758543
//    版权声明：本文为博主原创文章，转载请附上博文链接！
    
//输入框
    bool isOpen = false;
    
//UDP网络
    PyUtil* _pyutil;
    std::string _portName;
    void sendCmd(std::string pcmd);

    
};

#endif // __HELLOWORLD_SCENE_H__
