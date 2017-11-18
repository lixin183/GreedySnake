/**
 * created by simba.
 * 2015-05-09
 */

#include "GameLayer.h"
#include "GreedySnakeLayer.h"
#include "HelpLayer.h"

USING_NS_CC;

/**
 * 使用do-while(0)是为了消除goto指令
 */
Scene* GameLayer::scene()
{
    Scene* pRet = nullptr;
    do{
        pRet = Scene::create();
        auto layer = GameLayer::create();
        pRet->addChild(layer);
    }while(0);
    return pRet;
}


bool GameLayer::init()
{
    bool bRet = false;
    
    do{
        if(!Layer::init())
        {
            return bRet;
        }
        const Size& size = Director::getInstance()->getWinSize();
        log("size %f * %f", size.width, size.height);
        auto bg = Sprite::create("bg.jpg");
        //log("test");
        bg->setPosition(Point(size.width / 2, size.height / 2));
        addChild(bg);
        
        MenuItemFont::setFontName("fonts/arial.ttf");
        MenuItemFont::setFontSize(30);
        auto helpItem = MenuItemFont::create("Help", CC_CALLBACK_1(GameLayer::helpCallback, this));
        auto startItem = MenuItemFont::create("Start", CC_CALLBACK_1(GameLayer::startCallback,this));
        auto quitItem = MenuItemFont::create("Quit", CC_CALLBACK_1(GameLayer::quitCallback, this));
       
        auto menu = Menu::create(helpItem, startItem, quitItem, NULL);
        menu->setAnchorPoint(Point::ZERO);
        menu->setPosition(Point::ZERO);
        helpItem->setPosition(Point(700, 120));
        startItem->setPosition(Point(700, 160));
        quitItem->setPosition(Point(700, 80));
        helpItem->setAnchorPoint(Point::ZERO);
        startItem->setAnchorPoint(Point::ZERO);
        quitItem->setAnchorPoint(Point::ZERO);
        helpItem->setColor(Color3B::WHITE);
        startItem->setColor(Color3B::WHITE);
        quitItem->setColor(Color3B::WHITE);
        log("menu size %f * %f", menu->getContentSize().width, menu->getContentSize().height);
        auto label = Label::create("Greedy Snake", "fonts/arial.ttf", 48);
        label->setPosition(Point(size.width / 2, 480));
        label->setAnchorPoint(Point(0.5, 0.5));
        label->enableGlow(Color4B::MAGENTA);
        addChild(label);
        addChild(menu);
    
        bRet = true;
    }while(0);
    return bRet;
}

void GameLayer::helpCallback(const cocos2d::Ref *pSender)
{
    Director::getInstance()->replaceScene(HelpLayer::scene());
}

void GameLayer::startCallback(const cocos2d::Ref *pSender)
{
    Director::getInstance()->replaceScene(GreedySnakeLayer::scene());
}


void GameLayer::quitCallback(const cocos2d::Ref *pSender)
{
    log("quit");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
