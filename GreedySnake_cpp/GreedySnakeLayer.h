//
//  GreedySnakeLayer.h
//  Game
//
//  Created by chenjinpeng on 15/5/9.
//
//

#ifndef __Game__GreedySnakeLayer__
#define __Game__GreedySnakeLayer__

#include "cocos2d.h"
#include "SnakeBody.h"

class GreedySnakeLayer : public cocos2d::Layer
{
private:
    int score;
    SnakeBody* head;
    SnakeBody* food;
    
    cocos2d::Label* label;
    cocos2d::Vector<SnakeBody*> bodys;
    
    void move();
    
    void gameLogic(float time);
    
    bool collide();
    
    bool collideBorder();
    
    bool collideSelf();
    
public:
    GreedySnakeLayer();
    
    ~GreedySnakeLayer();
    
    static cocos2d::Scene* scene();
    
    virtual bool init() override;
    
    CREATE_FUNC(GreedySnakeLayer);
    
    void backCallback(const cocos2d::Ref* pSender);
    
    inline void updateScore()
    {
        score += 100;
        std::stringstream ss;
        ss << "Score: " << score << std::endl;
        label->setString(ss.str());
    }
    
    inline void setHead(SnakeBody* head)
    {
        this->head = head;
        head->retain();
    }
    
    inline void setFood(SnakeBody* food)
    {
        this->food = food;
        food->retain();
    }
    
    inline void setLabel(cocos2d::Label* label)
    {
        this->label = label;
        label->retain();
    }
    
    inline cocos2d::Label* getLabel()
    {
        return label;
    }
    
    inline SnakeBody* getHead()
    {
        return head;
    }
    
    inline SnakeBody* getFood()
    {
        return food;
    }
    
    inline cocos2d::Vector<SnakeBody*>& getBodys()
    {
        return bodys;
    }
    
    void addNewBody();
    
    void gameover();
    
    bool onTouch(cocos2d::Touch* touch, cocos2d::Event* event);
    
};
#endif /* defined(__Game__GreedySnakeLayer__) */
