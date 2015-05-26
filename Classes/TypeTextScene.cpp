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
    
    menuGotoFrameSelect = MenuItemImage::create(
                                                    path+"02input_selmenu_blackbg_default.png",
                                                    path+"02input_selmenu_blackbg_touch.png",
                                                     CC_CALLBACK_1(TypeText::goFrameSelect, this));
    menuGotoFrameSelect->setScale(r*menuscale);
    
    menuGotoSetting = MenuItemImage::create(
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
    auto touchSize = Size(textSize.width,textSize.height/2);
    auto rect = Rect(0,0,visibleSize.width/(g_frameNumber==2?1:2),visibleSize.height/2);
    middleVec = Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2);
    
    if(g_frameNumber==2){
        anchors = {
            Vec2(0.5f,0.0f),Vec2(0.5f,1.0f)
//            Vec2::ANCHOR_MIDDLE,Vec2::ANCHOR_MIDDLE
        };
        points = {
            Vec2(visibleSize.width/2,visibleSize.height/4),Vec2(visibleSize.width/2,visibleSize.height/4)
        };
    }else if(g_frameNumber==4){
        anchors = {
          Vec2(1.0f,0.0f),Vec2(0.0f,0.0f),Vec2(1.0f,1.0f),Vec2(0.0f,1.0f)
//            Vec2::ANCHOR_MIDDLE,Vec2::ANCHOR_MIDDLE,Vec2::ANCHOR_MIDDLE,Vec2::ANCHOR_MIDDLE
        };
        points = {
            Vec2(visibleSize.width/4,visibleSize.height/4),Vec2(visibleSize.width/4,visibleSize.height/4),Vec2(visibleSize.width/4,visibleSize.height/4),Vec2(visibleSize.width/4,visibleSize.height/4)
        };
    }
    
    for(auto i = 0; i < g_frameNumber; i++){
//        auto textInputObj = ui::TextField::create("|", "GROTESKIA.otf", 32);
//        textInputObj->setPosition(Vec2::ZERO);
//        textInputObj->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
//        textInputObj->setPlaceHolder("ANOTHER");
//        textInputObj->setAttachWithIME(true); // TRUE
//        textInputObj->ignoreContentAdaptWithSize(false);
//        textInputObj->setContentSize(textSize);
//        textInputObj->setTextHorizontalAlignment(TextHAlignment::CENTER);
//        textInputObj->setTextVerticalAlignment(TextVAlignment::CENTER);
//        textInputObj->setColor(Color3B::BLACK);
//        this->texts.push_back(textInputObj);
        auto textInputObj = ui::EditBox::create(touchSize, "transparent.png");
        textInputObj->setFontName("GROTESKIA");//Marker Felt
//        textInputObj->setFontName("Marker Felt");
//        textInputObj->setPosition(Vec2::ZERO);
        textInputObj->setPosition(points[i]);
        textInputObj->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        textInputObj->setPlaceHolder("ANOTHER");
        textInputObj->setPlaceholderFontName("GROTESKIA");
        textInputObj->setPlaceholderFontSize(int(fontBaseSize*r));
        textInputObj->ignoreContentAdaptWithSize(false);
        textInputObj->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
//        textInputObj->setContentSize(fontSize);
        textInputObj->setColor(Color3B::RED);
        textInputObj->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
        this->texts.push_back(textInputObj);
        
        auto sprite = Sprite::create("white1200x1200.png", rect);
        sprite->setColor(GetSpriteColor(i));
        sprite->setPosition(middleVec);
        sprite->setAnchorPoint(anchors[i]);
        sprite->addChild(textInputObj);
        sprite->setTag(i+100);
        
        AddSpriteBtns(sprite, i);
        
        this->addChild(sprite,2);
        
        textInputObj->setDelegate(this);
        
//        textInputObj->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
//            CCLOG("num is %d %d",i, sprite->getTag());
//            log("editing");
//        });
       

//        break;
    }
    return true;
}

void TypeText::editBoxEditingDidBegin(cocos2d::ui::EditBox *editBox)
{
    // EditBox편집이 시작될 때 발생하는 이벤트
    keyboard_up = true;
    auto sp = editBox->getParent();
    sp->setColor(colorTable[g_defaultcolor].color);
    editBox->setFontColor(Color3B::BLACK);
}
void TypeText::editBoxEditingDidEnd(cocos2d::ui::EditBox *editBox)
{
    // EditBox편집이 끝날 때 발생하는 이벤트
    auto sp = editBox->getParent();
    auto i = sp->getTag() - 100;
    sp->setColor(GetSpriteColor(i));
    editBox->setFontColor(colorTable[g_defaultcolor].color);
    
    auto span = labels[i];
    span->setString(editBox->getText());
    span->setFontSize(GetFontSize(utf8_strlen(editBox->getText())));
    span->setColor(colorTable[g_defaultcolor].color);
    span->setVisible(true);
    
    editBox->setVisible(true);
    editBox->setText("");
    
}
void TypeText::editBoxTextChanged(cocos2d::ui::EditBox *editBox, const std::string &text)
{
    // EditBox내 Text가 변경될 때 발생하는 이벤트
    auto len = utf8_strlen(text.c_str());
    auto fontsize = GetFontSize(len);
    CCLOG("%s %d %d",text.c_str(),len, fontsize);
    editBox->setFontSize(fontsize);
}
void TypeText::editBoxReturn(cocos2d::ui::EditBox *editBox){
    keyboard_up = false;
    // edit box return
}

int TypeText::GetFontSize(int len){
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

void TypeText::goFrameSelect(Ref* pSender){
    auto s = FrameSelect::createScene();
    
    Director::getInstance()->replaceScene(TransitionFlipY::create(0.5, s));
}

cocos2d::Color3B TypeText::GetSpriteColor(int i){
    auto color = i==0||i==3?Color3B(0x19,0x19,0x19):Color3B(0x3,0x3,0x3);
    return color;
}

void TypeText::AddSpriteBtns(Sprite* pSender, int i){
    auto refreshBtn = MenuItemImage::create(
                                            path+"02input_refresh_colorbg_default.png",
                                            path+colorTable[g_defaultcolor].refresh,
                                            path+"02input_refresh_colorbg_default.png",
                                            CC_CALLBACK_1(TypeText::DoRefresh, this, i));
    refreshBtn->setScale(r * menuscale);
    auto acceptBtn = MenuItemImage::create(
                                            path+"02input_ok_colorbg_default.png",
                                            path+colorTable[g_defaultcolor].select,
                                            path+colorTable[g_defaultcolor].select,
                                            CC_CALLBACK_1(TypeText::DoComplete, this, i));
    acceptBtn->setScale(r * menuscale);
    
    auto menu = Menu::create(refreshBtn,acceptBtn,nullptr);
    menu->setAnchorPoint(Vec2(0.5f,0));
    menu->alignItemsHorizontallyWithPadding(100);
    menu->setPosition(Vec2(pSender->getContentSize().width/2, 100));
    pSender->addChild(menu);
    
    auto label = LabelTTF::create();
    label->setColor(colorTable[g_defaultcolor].color);
    label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    label->setPosition(points[i]);
    label->setVisible(false);
    pSender->addChild(label,8);
    
    labels.push_back(label);
    refreshs.push_back(refreshBtn);
    accepts.push_back(acceptBtn);
}

void TypeText::DoRefresh(cocos2d::Ref *pSender, int i){
    // refresh textfield
//    this->texts[i]->setString("");
    this->labels[i]->setString("");
    this->texts[i]->setText("");
    CCLOG("parent tag is %d",i);
  
}

void TypeText::AcceptSubMenu(int i){
    auto temp = accepts[i];
    temp->setEnabled(false);
    auto temp2 = refreshs[i];
    temp2->setEnabled(false);
    texts[i]->setEnabled(false);
}

void TypeText::ShowSubMenu(int i){
    refreshs[i]->setVisible(true);
    accepts[i]->setVisible(true);
}

void TypeText::DoComplete(Ref* pSender, int i){
    // accept textfield
//    CCLOG("parent tag is %d",i);
    std::string str;
    if(keyboard_up == true){
        str = texts[i]->getText();
    }else{
        str = labels[i]->getString();
    }
    auto len = utf8_strlen(str);
    if(len<1){
        MessageBox("내용을 입력하세요", "");
        return;
    }
    
    AcceptSubMenu(i);
    this->isCompletes[i] = true;
    this->CheckAllComplete();
}

int TypeText::utf8_strlen(const std::string& str)
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

void TypeText::CheckAllComplete(){
    bool allclear = true;
    std::for_each(this->isCompletes.begin(), this->isCompletes.end(), [&](bool check){
        if(check==false) allclear = false;
    });
    if (allclear) {
        menuGotoFrameSelect->setEnabled(false);
        menuGotoSetting->setEnabled(false);
        GoPick();
    }
    
}

void TypeText::GoPick(){
    this->random_number = rand() % g_frameNumber;
    auto dimcolor = Color4B::BLACK;
    dimcolor = Color4B(0,0,0,150);

    DimLayer = LayerColor::create(dimcolor, visibleSize.width, visibleSize.height);
    DimLayer->setPosition(Vec2::ZERO);
    DimLayer->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->addChild(DimLayer, 8);
    
//    this->result = this->texts[this->random_number]->getString();
    this->result = this->texts[this->random_number]->getText();
    
    this->
    
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
    this->addChild(FlippingLayer,9);
    
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
