#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenuScene::create();

    scene->addChild(layer);

    return scene;
}

bool MainMenuScene::init()
{

    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("Background.png");
    backgroundSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2+origin.y));

    this->addChild(backgroundSprite);

    auto titleSprite = Sprite::create("Title.png");
    titleSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height - titleSprite->getContentSize().height));
    this->addChild(titleSprite);

    auto playItem = MenuItemImage::create("Play Button.png", "Play Button Clicked.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
    playItem->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);

    return true;

}

void MainMenuScene::GoToGameScene(cocos2d::Ref *sender){

    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}
