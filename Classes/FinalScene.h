//
//  FinalScene.h
//  Flipicker
//
//  Created by BomSok Kim on 2015. 5. 27..
//
//

#ifndef __Flipicker__FinalScene__
#define __Flipicker__FinalScene__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class FinalScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
    
    // screen position
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::Vec2 middleVec;
    
    cocos2d::MenuItemImage* btnRefresh;
    cocos2d::MenuItemImage* btnOk;
    cocos2d::Menu* menuInType;
    
    // text placehoder (label) color
    cocos2d::Color3B PlaceholderColor;
    
    // top btns
    cocos2d::MenuItemImage* menuGotoFrameSelect;
    cocos2d::MenuItemImage* menuGotoSetting;
    
    // flipping dim layer
    cocos2d::LayerColor* DimLayer;
    
    // select frame backgroud layer, input, refresh btn, accept btn
    std::vector<cocos2d::Sprite *> sprites;
    std::vector<cocos2d::ui::EditBox *> texts;
    std::vector<cocos2d::MenuItemImage *> refreshs;
    std::vector<cocos2d::MenuItemImage *> accepts;
    std::vector<cocos2d::Label *> labels;
    std::vector<bool> isCompletes={};
    
    // check is keyboard up or down
    bool keyboard_up = false;
    
    // selected string
    int random_number;
    std::string result;
    
    // size factor
    float r;
    float menuscale = 1.7;
    std::string path = "res/basic/";
    float padding = 90.0f;
    float fontBaseSize = 20;
    cocos2d::Rect rect;
    
    // flipping scene
    cocos2d::Layer* FlippingLayer;
    
    // for edit box
    virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
    std::vector<cocos2d::Vec2> anchors;
    std::vector<cocos2d::Vec2> points;
    
    int currentItem;
    
    virtual bool init();
    
    // add refresh
    void AddSpriteBtns(cocos2d::Sprite* pSender, int i);
    
    // to something when accecpt button clicked
    void DoComplete(cocos2d::Ref* pSender, int i);
    
    // to refresh input text
    void DoRefresh(cocos2d::Ref* pSender, int i);
    
    // to accept sub-menu
    void AcceptSubMenu(int i);
    
    // to show sub-menu
    void ShowSubMenu(int i);
    
    // to check all complete
    void CheckAllComplete();
    
    // to go pick item
    void GoPick();
    
    // trans to pick scene
    void TransToPick(float dt);
    
    // adding flipping scene
    void ShowFlippingScene();
    
    // type pannel color
    cocos2d::Color3B GetSpriteColor(int i);
    
    // check string length
    int utf8_strlen(const std::string& str);
    int GetFontSize(int string_length);
    
    // go to frame select
    void goFrameSelect(cocos2d::Ref* pSender);
    
    // go to colorpicker
    void goColorPicker(cocos2d::Ref* pSender);
    
    CREATE_FUNC(FinalScene);
    
};

#endif /* defined(__Flipicker__FinalScene__) */
