//
//  HelpLayer.cpp
//  Game
//
//  Created by chenjinpeng on 15/5/10.
//
//

#include "HelpLayer.h"
#include "GameLayer.h"

USING_NS_CC;

Scene* HelpLayer::scene()
{
    Scene* pRet = nullptr;
    
    do{
        pRet = Scene::create();
        auto layer = HelpLayer::create();
        pRet->addChild(layer);
        
    }while(0);
    return pRet;
}

bool HelpLayer::init()
{
    bool bRet = false;
    do{
        if(!Layer::init())
        {
            return bRet;
        }
        auto backItem = MenuItemFont::create("Back", CC_CALLBACK_1(HelpLayer::backCallback, this));
        
        auto menu = Menu::create(backItem, NULL);
        menu->setAnchorPoint(Point::ZERO);
        menu->setPosition(Point::ZERO);
        backItem->setPosition(Point(780, 60));
        
        backItem->setAnchorPoint(Point::ZERO);
        backItem->setColor(Color3B::WHITE);
        
        auto hintLabel = Label::create("Hint:", "fonts/arial.ttf", 24);
        hintLabel->setPosition(200, 400);
        hintLabel->setAnchorPoint(Point::ZERO);
        auto msgLabel = Label::create("Greedy Snake is a classical game.", "fonts/arial.ttf", 24);
        msgLabel->setPosition(200, 350);
        msgLabel->setAnchorPoint(Point::ZERO);
        addChild(hintLabel);
        addChild(msgLabel);
        addChild(menu);
        bRet = true;
    }while(0);
    return bRet;
}

void HelpLayer::backCallback(const cocos2d::Ref *pSender)
{
    log("back");
    Director::getInstance()->replaceScene(GameLayer::scene());
}

