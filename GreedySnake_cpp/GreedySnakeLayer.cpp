/**
 * @author Simba
 * @version 1.0
 * @describe 游戏主界面
 */

#include "GreedySnakeLayer.h"
#include "GameLayer.h"
#include "SnakeBody.h"

USING_NS_CC;

GreedySnakeLayer::GreedySnakeLayer() : food(nullptr), score(0), head(nullptr), bodys(Vector<SnakeBody*>()), label(nullptr)
{
    
}

GreedySnakeLayer::~GreedySnakeLayer()
{
    head->release();
    food->release();
    label->release();
    log("GreedySnakeLayer destructor");
}

Scene* GreedySnakeLayer::scene()
{
    Scene* pRet = nullptr;
    
    do{
        pRet = Scene::create();
        auto layer = GreedySnakeLayer::create();
        pRet->addChild(layer);
        
    }while(0);
    return pRet;
}

bool GreedySnakeLayer::init()
{
    bool bRet = false;
    do{
        if(!Layer::init())
        {
            return bRet;
        }
        const Size& size = Director::getInstance()->getWinSize();
        auto backItem = MenuItemFont::create("Back", CC_CALLBACK_1(GreedySnakeLayer::backCallback, this));
        
        auto menu = Menu::create(backItem, NULL);
        menu->setAnchorPoint(Point::ZERO);
        menu->setPosition(Point::ZERO);
        backItem->setPosition(Point(780, 60));
        
        backItem->setAnchorPoint(Point::ZERO);
        backItem->setColor(Color3B::WHITE);
        
        auto drawNode = DrawNode::create();
        
        for(int i=0; i<11; ++i)
        {
            drawNode->drawSegment(Point(20, 20 + i * 50), Point(520, 20 + i * 50), 0.5, Color4F(1,1,1,1));
            drawNode->drawSegment(Point(20 + i * 50, 20), Point(20 + i * 50, 520), 0.5, Color4F(1,1,1,1));
        }
        
        
        auto label = Label::create("Score: 0", "fonts/arial.ttf", 22);
        label->setAnchorPoint(Point::ZERO);
        label->setPosition(Point(size.width - 200, size.height- 70));
        label->enableGlow(Color4B::GREEN);
        setLabel(label);
        addChild(drawNode);
        addChild(menu);
        addChild(label);
        
        //初始化逻辑
        auto tempHead = SnakeBody::create();
        tempHead->setDirection(Direction::RIGHT);
        tempHead->setType(Type::HEAD);
        tempHead->set(0, 0);
        setHead(tempHead);
        
        auto tempFood = SnakeBody::create();
        tempFood->setDirection(Direction::NONE);
        //随机设定食物的x,y
        int x =  CCRANDOM_0_1() * 9;
        int y = CCRANDOM_0_1() * 9;
        tempFood->setType(Type::FOOD);
        tempFood->set(x, y);
        setFood(tempFood);
        
        //刷新并设定真正的坐标值
        tempFood->calculate();
        tempHead->calculate();
        
        addChild(food);
        addChild(head);
        
        //调度
        schedule(schedule_selector(GreedySnakeLayer::gameLogic), 0.5, -1, 0);
        
        //触摸事件
        auto listener = EventListenerTouchOneByOne::create();//创建一个触摸监听
        listener->setSwallowTouches(false);//设置是否想下传递触摸
        listener->onTouchBegan = CC_CALLBACK_2(GreedySnakeLayer::onTouch, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        bRet = true;
    }while(0);
    return bRet;
}

//触摸事件
bool GreedySnakeLayer::onTouch(cocos2d::Touch *touch, cocos2d::Event *event)
{
    const Point& location = touch->getLocation();
    int headX = 20 + getHead()->getX() * 50;
    int headY = 20 + getHead()->getY() * 50;
    
    float deltaX = location.x - headX;
    float deltaY = location.y - headY;
    
    if(abs(deltaX) >= abs(deltaY))
    {
        if(deltaX < 0)
        {
            getHead()->setDirection(Direction::LEFT);
        }else{
            getHead()->setDirection(Direction::RIGHT);
        }
    }else{
        if(deltaY < 0)
        {
            getHead()->setDirection(Direction::DOWN);
        }else{
            getHead()->setDirection(Direction::UP);
        }
    }
    //其他触摸事件不必继续
    return false;
}

void GreedySnakeLayer::gameover()
{
    
}

void GreedySnakeLayer::gameLogic(float time)
{
    log("game logic");
    move();
    
    if(collideBorder() || collideSelf())
    {
        gameover();
    }
    
    if(collide())
    {
        //刷新分数
        updateScore();
        //添加身体节点
        addNewBody();
        //刷新食物
        int x =  CCRANDOM_0_1() * 9;
        int y = CCRANDOM_0_1() * 9;
        getFood()->set(x, y);
        getFood()->calculate();
    }
}

void GreedySnakeLayer::addNewBody()
{
    auto body = SnakeBody::create();
    body->setType(Type::BODY);
    //或的前一个节点的x,y  如果bodys==0,则通过head获取，否则通过bodys.at(bodys.size() - 1)获取
    int x = -1;
    int y = -1;
    if(bodys.size() == 0)
    {
        x = getHead()->getX();
        y = getHead()->getY();
        body->setDirection(getHead()->getDirection());
    }else{
        x = getBodys().at(getBodys().size() - 1)->getX();
        y = getBodys().at(getBodys().size() - 1)->getY();
        body->setDirection(getBodys().at(getBodys().size() - 1)->getDirection());
    }
    
    switch(body->getDirection())
    {
        case Direction::UP:
        {
            body->set(x , y-1);
            break;
        }
        case Direction::DOWN:
        {
            body->set(x, y+1);
            break;
        }
        case Direction::LEFT:
        {
            body->set(x+1, y);
            break;
        }
        case Direction::RIGHT:
        {
            body->set(x-1, y);
            break;
        }
    }
    body->calculate();
    getBodys().pushBack(body);
    addChild(body);
}

void GreedySnakeLayer::move()
{
    log("move head");
    
    //头部移动
    switch(getHead()->getDirection())
    {
        
        case Direction::UP:
        {
            getHead()->set(getHead()->getX(), getHead()->getY() + 1);
            getHead()->calculate();
            break;
        }
        case Direction::DOWN:
        {
            getHead()->set(getHead()->getX(), getHead()->getY() - 1);
            getHead()->calculate();
            break;
        }
        case Direction::LEFT:
        {
            getHead()->set(getHead()->getX() - 1, getHead()->getY());
            getHead()->calculate();
            break;
        }
        case Direction::RIGHT:
        {
            getHead()->set(getHead()->getX() + 1, getHead()->getY());
            getHead()->calculate();
            break;
        }
        default:
        {
            //do nothing
        }
    }
    log("body size %d", getBodys().size());
    //身体移动
    for(SnakeBody* body : getBodys())
    {
        //log("move body");
        switch(body->getDirection())
        {
            case Direction::UP:
            {
                body->set(body->getX(), body->getY() + 1);
                body->calculate();
            
                break;
            }
            case Direction::DOWN:
            {
                body->set(body->getX(), body->getY() - 1);
                body->calculate();
                break;
            }
            case Direction::LEFT:
            {
                body->set(body->getX() - 1, body->getY());
                body->calculate();
                break;
            }
            case Direction::RIGHT:
            {
                body->set(body->getX() + 1, body->getY());
                body->calculate();
                break;
            }
            default:
            {
                //do nothing
            }
        }
        
    }
    
    //变换方向
    if(getBodys().size() > 0)
    {
        for(int i=getBodys().size()-1; i > 0; --i)
        {
            SnakeBody* b = getBodys().at(i);
            b->setDirection((getBodys().at(i-1))->getDirection());
        }
        
        getBodys().at(0)->setDirection(getHead()->getDirection());
    }
    
}

bool GreedySnakeLayer::collideBorder()
{
    return false;
}

bool GreedySnakeLayer::collideSelf()
{
    return false;
}

bool GreedySnakeLayer::collide()
{
    if(getHead()->getX() == getFood()->getX() && getHead()->getY() == getFood()->getY())
    {
        log("collide");
        return true;
    }
    return false;
}


void GreedySnakeLayer::backCallback(const cocos2d::Ref *pSender)
{
    log("back");
    Director::getInstance()->replaceScene(GameLayer::scene());
}
