//
//  SnakeBody.cpp
//  Game
//
//  Created by chenjinpeng on 15/5/10.
//
//

#include "SnakeBody.h"

USING_NS_CC;

SnakeBody::SnakeBody() : x(0), y(0), direction(Direction::NONE), type(Type::FOOD)
{
    
}

SnakeBody::~SnakeBody()
{
    
}

void SnakeBody::calculate()
{
    {
        clear();
        switch(type)
        {
            case Type::BODY :
            {
                drawSolidRect(cocos2d::Point(20+50*x, 20+50*y), cocos2d::Point(20+50*(x + 1), 20 +50*(y + 1)), cocos2d::Color4F::GREEN);
                break;
            }
            case Type::FOOD:
            {
                drawSolidRect(cocos2d::Point(20+50*x, 20+50*y), cocos2d::Point(20+50*(x + 1), 20 +50*(y + 1)), cocos2d::Color4F::ORANGE);
                break;
            }
            case Type::HEAD:
            {
                drawSolidRect(cocos2d::Point(20+50*x, 20+50*y), cocos2d::Point(20+50*(x + 1), 20 +50*(y + 1)), cocos2d::Color4F::BLUE);
                break;
            }
        }
        
    }
}

