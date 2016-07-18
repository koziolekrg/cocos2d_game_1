#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include "GameOverScene.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    auto layer = GameScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);

    return scene;
}

bool GameScene::init()
{

    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    backgroundSprite = Sprite::create("Background.png");
    backgroundSprite2 = Sprite::create("Background.png");

    backgroundSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2+origin.y));
    backgroundSprite2->setPosition(Point(visibleSize.width/2 + backgroundSprite2->getBoundingBox().size.width +0 + origin.x, visibleSize.height/2+origin.y));

    this->addChild(backgroundSprite);
    this->addChild(backgroundSprite2);

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    edgeBody->setContactTestBitmask(true);


    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2+origin.y));

    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);

    this->schedule(schedule_selector(GameScene::SpawnPipe), PIPE_SPAWN_FREQUENCY*visibleSize.width);

    bird = new Bird(this);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    score =0;

    __String *tempScore = __String::createWithFormat("%i", score);

    scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height*SCORE_FONT_SIZE);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height*0.75 + origin.y));

    this->addChild(scoreLabel, 10000);

    this->scheduleUpdate();

    return true;

}

void GameScene::SpawnPipe(float dt){
    pipe.SpawnPipe(this);
}

bool GameScene::onContactBegin( cocos2d::PhysicsContact &contact )
{
    PhysicsBody *a = contact.getShapeA( )->getBody();
    PhysicsBody *b = contact.getShapeB( )->getBody();

    if ( ( BIRD_COLLISION_BITMASK == a->getCollisionBitmask( ) && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( BIRD_COLLISION_BITMASK == b->getCollisionBitmask( ) && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask() ) )
    {
        auto scene = GameOverScene::createScene(  score );
        Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/punch.mp3");

        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/hit.mp3");

    }
    else if ( ( BIRD_COLLISION_BITMASK == a->getCollisionBitmask( ) && POINT_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( BIRD_COLLISION_BITMASK == b->getCollisionBitmask( ) && POINT_COLLISION_BITMASK == a->getCollisionBitmask() ) )
    {
        score++;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/point.mp3");

        __String *tempScore = __String::createWithFormat( "%i", score );

        scoreLabel->setString( tempScore->getCString( ) );
    }

    return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    bird->Fly(1);

    this->scheduleOnce(schedule_selector(GameScene::StopFlying), BIRD_FLY_DURATION);
    return true;
}

void GameScene::StopFlying(float dt){
    bird->stopFlying(1);
}

void GameScene::update(float dt){
    bird->Fall(1);

    auto position = backgroundSprite->getPosition();
    auto position2 = backgroundSprite2->getPosition();

    position.x -= 350 * dt;
    position2.x -= 350 * dt;
    if (position.x  <  0 - (backgroundSprite->getBoundingBox().size.width / 2)){
        position.x = this->getBoundingBox().getMaxX() + backgroundSprite->getBoundingBox().size.width/2;
    }
    if (position2.x  <  0 - (backgroundSprite2->getBoundingBox().size.width / 2)){
        position2.x = this->getBoundingBox().getMaxX() + backgroundSprite2->getBoundingBox().size.width/2;
    }


    backgroundSprite->setPosition(position);
    backgroundSprite2->setPosition(position2);


}

