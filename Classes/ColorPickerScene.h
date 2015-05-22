//
//  ColorPickerScene.h
//  Flipicker
//
//  Created by BomSok Kim on 2015. 5. 15..
//
//

#ifndef __Flipicker__ColorPickerScene__
#define __Flipicker__ColorPickerScene__

#include "cocos2d.h"

class ColorPicker : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    std::vector<cocos2d::Sprite *> colorList;
    
    virtual bool init();
    
    // size factor
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    float r;
    float menuscale = 1.7;
    std::string path = "res/basic/";
    float padding = 90.0f;
    
    cocos2d::MenuItemImage* backBtn;
    
    void goBack(cocos2d::Ref* pSender);
    
    void selectColor(cocos2d::Touch* touch, cocos2d::Event* event);
    
    CREATE_FUNC(ColorPicker);
};
#endif /* defined(__Flipicker__ColorPickerScene__) */
