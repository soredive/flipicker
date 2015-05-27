//
//  FinalScene.cpp
//  Flipicker
//
//  Created by BomSok Kim on 2015. 5. 27..
//
//

#include "FinalScene.h"
#include "TypeTextScene.h"
#include "HelloWorldScene.h"
#include "FrameSelectScene.h"
#include "ColorPickerScene.h"

#include "ui/CocosGUI.h"

#define COCOS2D_DEBUG 1

USING_NS_CC;

extern int g_frameNumber;
extern int g_defaultcolor;
extern std::vector<struct colorinfo> colorTable;
extern std::string select_result;

Scene* FinalScene::createScene(){
    auto s = Scene::create();
    
    auto l = TypeText::create();
    
    s->addChild(l);
    
    return s;
}

bool FinalScene::init(){
    auto color3 = colorTable[g_defaultcolor].color;
    auto InitColor = Color4B(color3.r,color3.g,color3.b,0xff);
    if (!LayerColor::initWithColor(InitColor)) {
        return false;
    }
    
    // size factor
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    r = float(visibleSize.height / 640 > visibleSize.width / 1136 ? visibleSize.width / 1136 : visibleSize.height / 640);
    if(menuscale * r >= 2.0f){
        path = "res/retina/";
        menuscale = menuscale / 2;
    }
   
    menuGotoFrameSelect = MenuItemImage::create(
                                                path+"02input_selmenu_blackbg_default.png",
                                                path+"02input_selmenu_blackbg_touch.png",
                                                CC_CALLBACK_1(FinalScene::goFrameSelect, this));
    menuGotoFrameSelect->setScale(r*menuscale);
    
    menuGotoSetting = MenuItemImage::create(
                                            path+"02input_setting_blackbg_default.png",
                                            path+"02input_setting_blackbg_touch.png",
                                            CC_CALLBACK_1(FinalScene::goColorPicker, this));
    menuGotoSetting->setScale(r*menuscale);
    
    menuGotoFrameSelect->setPosition(Vec2(padding * r,this->getBoundingBox().getMaxY()-padding * r));
    menuGotoFrameSelect->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    
    menuGotoSetting->setPosition(Vec2(this->getBoundingBox().getMaxX()- padding * r,this->getBoundingBox().getMaxY()-padding * r));
    menuGotoSetting->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    
    auto menuTop = Menu::create(menuGotoFrameSelect,menuGotoSetting,NULL);
    menuTop->setPosition(Vec2::ZERO);
    this->addChild(menuTop,3);
    
    
    {
        // display result
        auto str = select_result;
        auto len = utf8_strlen(str.c_str());
        auto fontsize = (int)(GetFontSize(len) * r);
        
        auto SizeLabel = Size(visibleSize.width * 0.8, visibleSize.height * 0.8);
        auto label = Label::createWithTTF(str.c_str(), "fonts/GROTESKIA.otf", fontsize, SizeLabel);
        
//        label->setColor(colorTable[g_defaultcolor].color);
        label->setColor(Color3B::BLACK);
        label->setHorizontalAlignment(TextHAlignment::CENTER);
        label->setVerticalAlignment(TextVAlignment::CENTER);
        label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        label->setPosition(visibleSize.width/2, visibleSize.height/2);
        label->setVisible(true);
        this->addChild(label);
        
        
    }
    
    return true;
}

int FinalScene::GetFontSize(int len){
    float size = 1.0f;
    size *= fontBaseSize;
    if(len >= 15){
        size *= 8.0f;
    }else if(len >= 10){
        size *= 10.0f;
    }else if(size >= 5){
        size *= 12.0f;
    }else if(size >= 3){
        size *= 12.0f;
    }else {
        size *= 12.0f;
    }
    size *= r;
    size = (int)size;
    return size;
}

void FinalScene::goFrameSelect(Ref* pSender){
    auto s = FrameSelect::createScene();
    
    Director::getInstance()->replaceScene(TransitionFlipY::create(0.5, s));
}

cocos2d::Color3B FinalScene::GetSpriteColor(int i){
    auto color = i==0||i==3?Color3B(0x19,0x19,0x19):Color3B(0x3,0x3,0x3);
    return color;
}

int FinalScene::utf8_strlen(const std::string& str)
{
    int c,i,ix,q;
    int len = int(str.length());
    for (q=0, i=0, ix=len; i < ix; i++, q++)
    {
        c = (unsigned char) str[i];
        if      (c>=0   && c<=127) i+=0;
        else if ((c & 0xE0) == 0xC0) i+=1;
        else if ((c & 0xF0) == 0xE0) i+=2;
        else if ((c & 0xF8) == 0xF0) i+=3;
        //else if (($c & 0xFC) == 0xF8) i+=4; // 111110bb //byte 5, unnecessary in 4 byte UTF-8
        //else if (($c & 0xFE) == 0xFC) i+=5; // 1111110b //byte 6, unnecessary in 4 byte UTF-8
        else return 0;//invalid utf8
    }
    return q;
}

void FinalScene::goColorPicker(Ref* pSender){
    auto s = ColorPicker::createScene();
    
    Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, s));
}

