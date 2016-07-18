#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SplashScene::create();

    scene->addChild(layer);

    return scene;
}

bool SplashScene::init()
{

    if ( !Layer::init() )
    {
        return false;
    }

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/fly.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/hit.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/point.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/punch.mp3");


    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    this->scheduleOnce(schedule_selector(SplashScene::GoToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);

    auto backgroundSprite = Sprite::create("Splash Screen.png");
    backgroundSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(backgroundSprite);


    return true;

}

void SplashScene::GoToMainMenuScene(float dt){
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
