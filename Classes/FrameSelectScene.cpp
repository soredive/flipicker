//
//  FrameSelectScene.cpp
//  Flipicker
//
//  Created by BomSok Kim on 2015. 5. 14..
//
//
#include "HelloWorldScene.h"
#include "FrameSelectScene.h"
#include "TypeTextScene.h"

USING_NS_CC;

extern std::vector<struct colorinfo> colorTable;
extern int g_defaultcolor;

Scene* FrameSelect::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = FrameSelect::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool FrameSelect::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init())
    {
        return false;
    }
    
    // size factor
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    r = float(visibleSize.height / 640 > visibleSize.width / 1136 ? visibleSize.width / 1136 : visibleSize.height / 640);
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    auto fontsize = float(80 * r);
    auto label = Label::createWithTTF("SEELCT THE FRAME", "fonts/GROTESKIA.otf", fontsize);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2));
    label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    label->setColor(Color3B(0x64,0x64,0x64));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // add a "close" icon to exit the progress. it's an autorelease object
    if(menuscale * r >= 2.0f){
        path = "res/retina/";
        menuscale = menuscale / 2;
    }
    
    auto file1 = path + "01select_2f_default.png";
    auto file2 = path + colorTable[g_defaultcolor].color2;
    auto frameMenuSelect2 = MenuItemImage::create(
                                       file1,
                                       file2,
                                       CC_CALLBACK_1(FrameSelect::menuFrameSelectTo2, this));
    frameMenuSelect2->setScale(r*menuscale);
  
    auto posMenu2 = Vec2(origin.x + visibleSize.width / 2 ,
                         origin.y + visibleSize.height * 3 / 4);
    frameMenuSelect2->setPosition(posMenu2);
    frameMenuSelect2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

//    frameMenuSelect2->setPosition(posMenu2);
    auto file3 = path + "01select_4f_default.png";
    auto file4 = path + colorTable[g_defaultcolor].color4;
    auto frameMenuSelect4 = MenuItemImage::create(
                                    file3,
                                    file4,
                                    CC_CALLBACK_1(FrameSelect::menuFrameSelectTo4,this));
    frameMenuSelect4->setScale(r*menuscale);
    auto posMenu4 = Vec2(origin.x + visibleSize.width / 2 ,
                         origin.y + visibleSize.height / 4);
    frameMenuSelect4->setPosition(posMenu4);
    frameMenuSelect4->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    // create menu, it's an autorelease object
    auto menuSelect = Menu::create(frameMenuSelect2, frameMenuSelect4, NULL);
    menuSelect->setPosition(Vec2::ZERO);
    menuSelect->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
//    menuSelect->alignItemsVerticallyWithPadding(100);
    this->addChild(menuSelect, 1, 2);
    
    /////////////////////////////
    // 3. add your codes below...
        
    return true;
}

void FrameSelect::menuFrameSelectTo2(Ref* pSender){
    extern int g_frameNumber;
    g_frameNumber = 2;
    
    this->goTypeText();
}

void FrameSelect::menuFrameSelectTo4(Ref* pSender){
    extern int g_frameNumber;
    g_frameNumber = 4;
    
    this->goTypeText();
}

void FrameSelect::goTypeText(){
    auto ttlayer = TypeText::createScene();
    Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, ttlayer));
}


void FrameSelect::menuCloseCallback(Ref* pSender)
{
    auto s = HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionFlipY::create(0.4,s));
}
