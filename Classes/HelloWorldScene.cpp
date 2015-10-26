#include "HelloWorldScene.h"

USING_NS_CC;
#define MOTION_STREAK_TAG 1

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
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 3. add a label shows "Hello World"
    // create and initialize a label
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
    // blade and touch effect
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    if (blade != NULL)
        blade->removeFromParent();
    blade = cocos2d::MotionStreak::create(1, 2, 10, Color3B(255, 255, 0), "streak.png");
    this->addChild(blade);
    return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {
    blade->setPosition(touch->getLocation().x, touch->getLocation().y);
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {
}

void HelloWorld::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event) {
}

void HelloWorld::resetMotionStreak() {
    this->removeChildByTag(MOTION_STREAK_TAG, true);
    MotionStreak* streak = MotionStreak::create(0.5f, 1, 10, Color3B(255, 255, 0), "streak.png");
    this->addChild(streak, 5, MOTION_STREAK_TAG);
}

void HelloWorld::addMotionStreakPoint(cocos2d::Point point) {
    MotionStreak* streak = (MotionStreak*)this->getChildByTag(MOTION_STREAK_TAG);
    streak->setPosition(point);
    
    if (++m_iCount>100) {
        int r = rand()%256;
        int b = rand()%265;
        int g = rand()%256;
        streak->setColor(Color3B(r, b, g));
        m_iCount = 0;
    }
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
