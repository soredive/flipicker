//
//  ColorPickerScene.cpp
//  Flipicker
//
//  Created by BomSok Kim on 2015. 5. 15..
//
//
#include "HelloWorldScene.h"
#include "ColorPickerScene.h"
#include "TypeTextScene.h"

USING_NS_CC;

extern int g_defaultcolor;
extern std::vector<struct colorinfo> colorTable;

Scene* ColorPicker::createScene(){
    auto scene = Scene::create();
    
    auto layer = ColorPicker::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool ColorPicker::init(){
    if(!Layer::init()){
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
    
    backBtn = MenuItemImage::create(path+"88popup_close_default.png", path+"88popup_close_touch.png", CC_CALLBACK_1(ColorPicker::goBack, this));
    
    backBtn->setPosition(Vec2(visibleSize.width - padding * r,0));
    backBtn->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    backBtn->setScale(r * menuscale);
    
    auto topmenu = Menu::create(backBtn, nullptr);
    topmenu->setPosition(Vec2(0,visibleSize.height - padding * r));
    topmenu->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    
    this->addChild(topmenu,2);
    
    auto colorRect = Rect(0, 0, visibleSize.width/2,visibleSize.height/4);
    auto colorPosition = Vec2(0,0);
    auto center = Vec2(visibleSize.width/2,visibleSize.height/2);
    
    std::vector<int> nums = {0,1,2,3,4,5,6,7};
    
    Texture2D *texture = TextureCache::getInstance()->addImage("white1200x1200.png");
    SpriteBatchNode* batch = SpriteBatchNode::createWithTexture(texture);
    this->addChild(batch);
    
    std::for_each(nums.begin(), nums.end(), [&](int i){
        Vec2 anchor;
//        auto tempItem = Sprite::create("white1200x1200.png",colorRect);
        Sprite* tempItem = Sprite::createWithTexture(texture, colorRect);
        
        tempItem->setColor(colorTable[i].color);
        switch (i) {
            case 0:anchor = Vec2(1,-1);break;
            case 1:anchor = Vec2(0,-1);break;
            case 2:anchor = Vec2(1,0);break;
            case 3:anchor = Vec2(0,0);break;
            case 4:anchor = Vec2(1,1);break;
            case 5:anchor = Vec2(0,1);break;
            case 6:anchor = Vec2(1,2);break;
            case 7:anchor = Vec2(0,2);break;
        }
        tempItem->setAnchorPoint(anchor);
        tempItem->setPosition(center);
        
        tempItem->setTag(10+i); // 10, 11, ... 17 color
        this->addChild(tempItem,1);
        colorList.push_back(tempItem);
        
        auto touch_callback = EventListenerTouchOneByOne::create();
        touch_callback->onTouchBegan = [=](Touch* touch, Event* event)
        {
            Vec2 p = touch->getLocation();
            Rect rect = tempItem->getBoundingBox();
            
            if(rect.containsPoint(p))
            {
                ColorPicker::selectColor(touch, event);
                return true; // to indicate that we have consumed it.
            }
            
            return false; // we did not consume this event, pass thru.
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touch_callback, tempItem);
    });
    
    return true;
}

void ColorPicker::goBack(Ref* pSender){
    auto s = TypeText::createScene();
    
    Director::getInstance()->replaceScene(TransitionFlipX::create(0.5f, s));
}

void ColorPicker::selectColor(Touch* touch, Event* event){
    auto target = static_cast<Sprite *>(event->getCurrentTarget());
    auto tag = target->getTag();
    g_defaultcolor = tag - 10;
    auto scene = TypeText::createScene();
    Director::getInstance()->replaceScene(TransitionSplitCols::create(0.5f, scene));
}