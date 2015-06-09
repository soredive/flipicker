#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "sqlite3.h"

// color info
struct colorinfo {
    cocos2d::Color3B color;
    std::string colorname;
    std::string color2;
    std::string color4;
    std::string select;
    std::string refresh;
};

class HelloWorld : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // size factor
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::Vec2 middleVec;
    float r;
    float menuscale = 1.7;
    std::string path = "res/basic/";
    float padding = 90.0f;
    
    void goFrameSelect(float t);
        
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

sqlite3* OpenDatabase();

#endif // __HELLOWORLD_SCENE_H__
