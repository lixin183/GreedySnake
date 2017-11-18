//
//  HelpLayer.h
//  Game
//
//  Created by chenjinpeng on 15/5/10.
//
//

#ifndef __Game__HelpLayer__
#define __Game__HelpLayer__

#include "cocos2d.h"

class HelpLayer : public cocos2d::Layer
{
private:
    
public:
    static cocos2d::Scene* scene();
    
    virtual bool init() override;
    
    CREATE_FUNC(HelpLayer);
    
    void backCallback(const cocos2d::Ref* pSender);
};
#endif /* defined(__Game__HelpLayer__) */
