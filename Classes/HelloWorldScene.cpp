#include "HelloWorldScene.h"
#include "FrameSelectScene.h"
#include <string.h>
#include <stdio.h>
USING_NS_CC;


// global variables
// base frame number global
int g_frameNumber = 2;
int g_defaultcolor = 1;
std::string select_result;

std::vector<struct colorinfo> colorTable = {
    {Color3B(255,205,0),"#ffcd00","01select_2f_touch_1yellow.png","01select_4f_touch_1yellow.png","02input_ok_blackbg_selected_1yellow.png","02input_refresh_blackbg_touch_1yellow.png"},
    {Color3B(106,208,17),"#6ad011","01select_2f_touch.png","01select_4f_touch.png","02input_ok_blackbg_selected.png","02input_refresh_blackbg_touch.png"}, // default green color
    {Color3B(245,90,0),"#f55a00","01select_2f_touch_3orange.png","01select_4f_touch_3orange.png","02input_ok_blackbg_selected_3orange.png","02input_refresh_blackbg_touch_3orange.png"},
    {Color3B(0,144,192),"#0090c0","01select_2f_touch_4blue.png","01select_4f_touch_4blue.png","02input_ok_blackbg_selected_4blue.png","02input_refresh_blackbg_touch_4blue.png"},
    {Color3B(245,0,0),"#f50000","01select_2f_touch_5red.png","01select_4f_touch_5red.png","02input_ok_blackbg_selected_5red.png","02input_refresh_blackbg_touch_5red.png"},
    {Color3B(143,45,255),"#8f2dff","01select_2f_touch_6violet.png","01select_4f_touch_6violet.png","02input_ok_blackbg_selected_6violet.png","02input_refresh_blackbg_touch_6violet.png"},
    {Color3B(255,27,162),"#ff1ba2","01select_2f_touch_7pink.png","01select_4f_touch_7pink.png","02input_ok_blackbg_selected_7pink.png","02input_refresh_blackbg_touch_7pink.png"},
    
    {Color3B(178,45,255),"#b22dff","01select_2f_touch_8purple.png","01select_4f_touch_8purple.png","02input_ok_blackbg_selected_8purple.png","02input_refresh_blackbg_touch_8purple.png"}
};
// /global variables

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(106,208,17,255)))
    {
        return false;
    }
 
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
//    auto closeItem = MenuItemImage::create(
//                                           "CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
//    
//	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
//                                origin.y + closeItem->getContentSize().height/2));

//    auto nextscene = MenuItemFont::create("NEXT", CC_CALLBACK_1(HelloWorld::goFrameSelect,this));
//    nextscene->setPosition(Vec2(100,100));
    
    // create menu, it's an autorelease object
//    auto menu = Menu::create(nextscene, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
//    auto label = Label::createWithTTF("FLIPICKER", "fonts/GROTESKIA OBLIQUE.otf", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//    
//    // add the label as a child to this layer
//    this->addChild(label, 1);
    
    // size factor
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    r = float(visibleSize.height / 640 > visibleSize.width / 1136 ? visibleSize.width / 1136 : visibleSize.height / 640);
    if(menuscale * r >= 2.0f){
        path = "res/retina/";
        menuscale = menuscale / 2;
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create(path+"00splash_logo.png");
    
    auto baseScale = 1.5;
    sprite->setScale(r * baseScale, r * baseScale);

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*55/100 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    auto job = CC_SCHEDULE_SELECTOR(HelloWorld::goFrameSelect);
    this->scheduleOnce(job, 1.0f);
    
    return true;
}

void HelloWorld::goFrameSelect(float t){
    auto frameSelectSceneLayer = FrameSelect::createScene();
    Director::getInstance()->replaceScene(TransitionFadeBL::create(1.0f, frameSelectSceneLayer));
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
