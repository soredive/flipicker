//
//  TypeTextScene.cpp
//  Flipicker
//
//  Created by BomSok Kim on 2015. 5. 14..
//
//

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

Scene* TypeText::createScene(){
    auto s = Scene::create();
    
    auto l = TypeText::create();
    
    s->addChild(l);
    
    return s;
}

bool TypeText::init(){
    if (!Layer::init()) {
        return false;
    }
    
    {
        // initing...
        currentItem = 0;
        
        for(auto i = 0; i < g_frameNumber; i++){
            this->isCompletes.push_back(false);
        }
   }
    
    // size factor
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    r = float(visibleSize.height / 640 > visibleSize.width / 1136 ? visibleSize.width / 1136 : visibleSize.height / 640);
    if(menuscale * r >= 2.0f){
        path = "res/retina/";
        menuscale = menuscale / 2;
    }
    
    auto menuGotoFrameSelect = MenuItemImage::create(
                                                    path+"02input_selmenu_blackbg_default.png",
                                                    path+"02input_selmenu_blackbg_touch.png",
                                                     CC_CALLBACK_1(TypeText::goFrameSelect, this));
    menuGotoFrameSelect->setScale(r*menuscale);
    auto menuGotoSetting = MenuItemImage::create(
                                                 path+"02input_setting_blackbg_default.png",
                                                 path+"02input_setting_blackbg_touch.png",
                                                 CC_CALLBACK_1(TypeText::goColorPicker, this));
    menuGotoSetting->setScale(r*menuscale);

    menuGotoFrameSelect->setPosition(Vec2(padding * r,this->getBoundingBox().getMaxY()-padding * r));
    menuGotoFrameSelect->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    
    menuGotoSetting->setPosition(Vec2(this->getBoundingBox().getMaxX()- padding * r,this->getBoundingBox().getMaxY()-padding * r));
    menuGotoSetting->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    
    auto menuTop = Menu::create(menuGotoFrameSelect,menuGotoSetting,NULL);
    menuTop->setPosition(Vec2::ZERO);
    //menuTop->alignItemsHorizontallyWithPadding(100);
    this->addChild(menuTop,3);
    
    //ui::TextField *textInputObj;
    
    auto textSize = Size(visibleSize.width/(g_frameNumber==2?1:2),visibleSize.height/2);
    auto rect = Rect(0,0,visibleSize.width/(g_frameNumber==2?1:2),visibleSize.height/2);
    middleVec = Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2);
    
    
    std::vector<Vec2> anchors;
    if(g_frameNumber==2){
        anchors = {
            Vec2(0.5f,0.0f),Vec2(0.5f,1.0f)
        };
    }else if(g_frameNumber==4){
        anchors = {
          Vec2(1.0f,0.0f),Vec2(0.0f,0.0f),Vec2(1.0f,1.0f),Vec2(0.0f,1.0f)
        };
    }
    
    auto temp = ui::EditBox::create(Size(300, 300), "transparent.png");
    temp->setDelegate((cocos2d::ui::EditBoxDelegate *)this);
    this->addChild(temp,100);
    
    for(auto i = 0; i < g_frameNumber; i++){
        
        auto textInputObj = ui::TextField::create("|", "GROTESKIA.otf", 32);
        textInputObj->setPosition(Vec2::ZERO);
        textInputObj->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
        textInputObj->setPlaceHolder("ANOTHER");
        textInputObj->setAttachWithIME(true); // TRUE
        textInputObj->ignoreContentAdaptWithSize(false);
        textInputObj->setContentSize(textSize);
        textInputObj->setTextHorizontalAlignment(TextHAlignment::CENTER);
        textInputObj->setTextVerticalAlignment(TextVAlignment::CENTER);
        //textInputObj->addEventListener(CC_CALLBACK_1(TypeText::typeHandler, this));
        textInputObj->setColor(Color3B::BLACK);
        //        textInputObj->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        //            log("editing");
        //        });
        //        textInputObj->setDelegate(this);

        this->texts.push_back(textInputObj);
        
       
        auto sprite = Sprite::create("white1200x1200.png", rect);
//        sprite->setColor(colorTable[g_defaultcolor].color);
        sprite->setColor(i==0||i==3?Color3B(0x19,0x19,0x19):Color3B(0x3,0x3,0x3));
        CCLOG("NUM IS %d",g_defaultcolor);
        sprite->setPosition(middleVec);
        sprite->setAnchorPoint(anchors[i]);
        sprite->addChild(textInputObj);
        sprite->setTag(i+100);
        
        AddSpriteBtns(sprite, i);
        
        this->addChild(sprite,2);
//        break;
    }
    
//    ui::EditBox *editbox;
//        editbox = ui::EditBox::create(Size(visibleSize.width, visibleSize.height/2),"HelloWorld.png");
//        editbox->setPosition(Vec2(origin.x+visibleSize.width/2.0f,origin.y+visibleSize.height*1.0f/4.0f));
//        editbox->setPlaceHolder("this is edit box");
//        editbox->setFont("fonts/GROTESKIA OBLIQUE.otf", 25);
//        editbox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
//        this->addChild(editbox);
    //Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
//    }else if(g_frameNumber==4){
    
//    }
    return true;
}

void TypeText::editBoxEditingDidBegin(cocos2d::ui::EditBox *editBox)
{
    // EditBox편집이 시작될 때 발생하는 이벤트
}
void TypeText::editBoxEditingDidEnd(cocos2d::ui::EditBox *editBox)
{
    // EditBox편집이 끝날 때 발생하는 이벤트
}
void TypeText::editBoxTextChanged(cocos2d::ui::EditBox *editBox, const std::string &text)
{
    // EditBox내 Text가 변경될 때 발생하는 이벤트
}
void TypeText::editBoxReturn(cocos2d::ui::EditBox *editBox){
    // edit box return
}

void TypeText::goFrameSelect(Ref* pSender){
    auto s = FrameSelect::createScene();
    
    Director::getInstance()->replaceScene(TransitionFlipY::create(0.5, s));
}

void TypeText::OpenText(Ref* pSender){
    // type 창 열기
}

void TypeText::AddSpriteBtns(Sprite* pSender, int i){
    auto refreshBtn = MenuItemImage::create(
                                            path+"02input_refresh_colorbg_default.png",
                                            path+colorTable[g_defaultcolor].refresh,
                                            CC_CALLBACK_1(TypeText::DoRefresh, this, i));
    refreshBtn->setScale(r * menuscale);
    auto acceptBtn = MenuItemImage::create(
                                            path+"02input_ok_colorbg_default.png",
                                            path+colorTable[g_defaultcolor].select,
                                            CC_CALLBACK_1(TypeText::DoComplete, this, i));
    acceptBtn->setScale(r * menuscale);
    refreshs.push_back(refreshBtn);
    accepts.push_back(acceptBtn);
    
    auto menu = Menu::create(refreshBtn,acceptBtn,nullptr);
    menu->setAnchorPoint(Vec2(0.5f,0));
    menu->alignItemsHorizontallyWithPadding(100);
    menu->setPosition(Vec2(pSender->getContentSize().width/2, 100));
    pSender->addChild(menu);
}

void TypeText::DoRefresh(cocos2d::Ref *pSender, int i){
    // refresh textfield
    this->texts[i]->setString("");
    CCLOG("parent tag is %d",i);
  
}

void TypeText::HideSubMenu(int i){
    refreshs[i]->setVisible(false);
    accepts[i]->setVisible(false);
}

void TypeText::ShowSubMenu(int i){
    refreshs[i]->setVisible(true);
    accepts[i]->setVisible(true);
}

void TypeText::DoComplete(Ref* pSender, int i){
    // accept textfield
    CCLOG("parent tag is %d",i);
    HideSubMenu(i);
    this->isCompletes[i] = true;
    this->CheckAllComplete();
}

void TypeText::CheckAllComplete(){
    bool allclear = true;
    std::for_each(this->isCompletes.begin(), this->isCompletes.end(), [&](bool check){
        if(check==false) allclear = false;
    });
    if (allclear) {
        GoPick();
    }
    
}

void TypeText::GoPick(){
    this->random_number = rand() % g_frameNumber;
    
    this->result = this->texts[this->random_number]->getString();

    ShowFlippingScene();
}

void TypeText::ShowFlippingScene(){
    FlippingLayer = Layer::create();
    
    DrawNode* FlippingCard = DrawNode::create();
    auto w1 = visibleSize.width*0.3;
    auto h1 = visibleSize.height*0.3;
    Vec2 rect[4];
    rect[0] = Vec2(-w1/2,-h1/2);
    rect[1] = Vec2(w1/2,-h1/2);
    rect[2] = Vec2(w1/2,h1/2);
    rect[3] = Vec2(-w1/2,h1/2);
    auto CardColor = Color4F(
                             colorTable[g_defaultcolor].color.r,
                             colorTable[g_defaultcolor].color.b,
                             colorTable[g_defaultcolor].color.g,
        0.3
    );
    FlippingCard->drawPolygon(rect, 4, CardColor, 1, CardColor);
    FlippingCard->setPosition(middleVec);
//    FlippingCard->setOpacity(0.5);
    FlippingCard->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    DrawNode* FlippingCard2 = DrawNode::create();
    auto w2 = w1 * 0.8;
    auto h2 = h1 * 0.8;
    Vec2 rect2[4];
    rect2[0] = Vec2(-w2/2,-h2/2);
    rect2[1] = Vec2(w2/2,-h2/2);
    rect2[2] = Vec2(w2/2,h2/2);
    rect2[3] = Vec2(-w2/2,h2/2);
    auto CardColor2 = Color4F(colorTable[g_defaultcolor].color);
    FlippingCard2->drawPolygon(rect2, 4, CardColor2, 1, CardColor2);
    auto po1 = Vec2(w1/2,h1/2);
//    FlippingCard2->setPosition(po1);
    FlippingCard2->setPosition(Vec2::ZERO);
    FlippingCard2->setOpacity(1);
    FlippingCard2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    FlippingLayer->setPosition(Vec2::ZERO);
    FlippingCard->addChild(FlippingCard2);
    FlippingLayer->addChild(FlippingCard);
    this->addChild(FlippingLayer,5);
    
    auto BaseFontSize = 75;
    
    auto labelwidth = 0.0f;
    
    auto label1 = Label::createWithTTF("FLIP", "fonts/GROTESKIA.otf", BaseFontSize * r);
    label1->setColor(colorTable[g_defaultcolor].color);
    label1->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    labelwidth += label1->getBoundingBox().size.width;
    
    auto label2 = Label::createWithTTF(" THE PHONE", "fonts/GROTESKIA.otf", BaseFontSize * r);
    label2->setColor(Color3B(0x63,0x63,0x63));
    label2->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    labelwidth += label2->getBoundingBox().size.width;
    label1->setPosition(Vec2(visibleSize.width/2-labelwidth/2, 0));
    label2->setPosition(Vec2(visibleSize.width/2+labelwidth/2, 0));
    
    auto labelLayer = Layer::create();
    labelLayer->addChild(label1);
    labelLayer->addChild(label2);
    labelLayer->setPosition(Vec2(0, visibleSize.height/2 - h1 / 2 - h1 * 0.2 * r));
    labelLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    this->addChild(labelLayer, 10);
    
    // b
    
    
    // animation
    auto flipAnimation = RotateBy::create(2, Vec3(0, 360, 0));
    auto forever = RepeatForever::create(Sequence::create(flipAnimation, NULL));
//    FlippingCard->runAction(Sequence::create(flipAnimation,flipAnimation,flipAnimation, NULL));
    FlippingCard->runAction(forever);
 }


void TypeText::goColorPicker(Ref* pSender){
    auto s = ColorPicker::createScene();
    
    Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, s));
}
