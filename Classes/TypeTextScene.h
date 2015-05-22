//
//  TypeTextScene.h
//  Flipicker
//
//  Created by BomSok Kim on 2015. 5. 14..
//
//

#ifndef __Flipicker__TypeTextScene__
#define __Flipicker__TypeTextScene__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class TypeText : public cocos2d::Layer
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
   
    // select frame backgroud layer, input, refresh btn, accept btn
    std::vector<cocos2d::Sprite *> sprites;
    std::vector<cocos2d::ui::TextField *> texts;
    std::vector<cocos2d::MenuItemImage *> refreshs;
    std::vector<cocos2d::MenuItemImage *> accepts;
    std::vector<bool> isCompletes={};
    
    // selected string
    int random_number;
    std::string result;
    
    // size factor
    float r;
    float menuscale = 1.7;
    std::string path = "res/basic/";
    float padding = 90.0f;
    
    // flipping scene
    cocos2d::Layer* FlippingLayer;
    
    // for edit box
    virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
    
    int currentItem;
    
    virtual bool init();
    
    // add refresh
    void AddSpriteBtns(cocos2d::Sprite* pSender, int i);
    
    // to something when accecpt button clicked
    void DoComplete(cocos2d::Ref* pSender, int i);
    
    // to refresh input text
    void DoRefresh(cocos2d::Ref* pSender, int i);
    
    // to hide sub-menu
    void HideSubMenu(int i);
    
    // to show sub-menu
    void ShowSubMenu(int i);
    
    // to check all complete
    void CheckAllComplete();
    
    // to go pick item
    void GoPick();
    
    // adding flipping scene
    void ShowFlippingScene();

    void AddMenuInFrame(cocos2d::Ref* pSender);
    
    void OpenText(cocos2d::Ref* pSender);
    
    void goFrameSelect(cocos2d::Ref* pSender);
    
    void goColorPicker(cocos2d::Ref* pSender);

    CREATE_FUNC(TypeText);
};

#endif /* defined(__Flipicker__TypeTextScene__) */
