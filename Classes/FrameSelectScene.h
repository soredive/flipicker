//
//  FrameSelectScene.h
//  Flipicker
//
//  Created by BomSok Kim on 2015. 5. 14..
//
//

#ifndef __Flipicker__FrameSelectScene__
#define __Flipicker__FrameSelectScene__

#include "cocos2d.h"

class FrameSelect : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // size factor
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    float r;
    float menuscale = 1.7;
    std::string path = "res/basic/";
   
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // select frame number
    void menuFrameSelectTo2(cocos2d::Ref* pSender);
    
    // select frame number
    void menuFrameSelectTo4(cocos2d::Ref* pSender);
    
    void goTypeText();
    
    // implement the "static create()" method manually
    CREATE_FUNC(FrameSelect);
};

#endif /* defined(__Flipicker__FrameSelectScene__) */
