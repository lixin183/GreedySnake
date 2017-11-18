//
//  GameLayer.h
//  Game
//
//  Created by chenjinpeng on 15/5/9.
//
//

#ifndef __Game__GameLayer__
#define __Game__GameLayer__

#include "cocos2d.h"

class GameLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(GameLayer);
    
    static cocos2d::Scene* scene();
    
    virtual bool init();
    
    void helpCallback(const cocos2d::Ref* pSender);
    
    void startCallback(const cocos2d::Ref* pSender);
    
    void quitCallback(const cocos2d::Ref* pSender);
};

#endif /* defined(__Game__GameLayer__) */
