//
//  SnakeBody.h
//  Game
//
//  Created by chenjinpeng on 15/5/10.
//
//

#ifndef __Game__SnakeBody__
#define __Game__SnakeBody__

#include "cocos2d.h"
enum class Type {
    FOOD, BODY, HEAD
};

enum class Direction{
    UP, DOWN, LEFT, RIGHT, NONE
};

class SnakeBody : public cocos2d::DrawNode
{
private:
    Type type;
    int x, y; //x,y的取值是[0, 9]
    Direction direction;
    
public:
    CREATE_FUNC(SnakeBody);
    
    SnakeBody();
    
    ~SnakeBody();
    
    inline void setDirection(const Direction& direction)
    {
        this->direction = direction;
    }
    
    void calculate();
    
    inline const Type& getType()
    {
        return type;
    }
    
    inline void setType(const Type& type)
    {
        this->type = type;
    }
    
    inline const Direction& getDirection()
    {
        return direction;
    }
    
    inline void set(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    
    inline const int& getX()
    {
        return x;
    }
    
    inline const int& getY()
    {
        return y;
    }
    
    
};

#endif /* defined(__Game__SnakeBody__) */
