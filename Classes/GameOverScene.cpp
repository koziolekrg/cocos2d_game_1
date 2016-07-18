#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"
USING_NS_CC;

unsigned int score;

Scene* GameOverScene::createScene( unsigned int m_score)
{
    score = m_score;

    auto scene = Scene::create();
    auto layer = GameOverScene::create();

    scene->addChild(layer);

    return scene;
}

bool GameOverScene::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    // ---- Code begin ---

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto retryItem = MenuItemImage::create("Retry Button.png", "Retry Button Clicked.png", CC_CALLBACK_1(GameOverScene::GoToGameScene, this));
    retryItem->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/4*3));

    auto mainMenuItem = MenuItemImage::create("Menu Button.png", "Menu Button Clicked.png", CC_CALLBACK_1(GameOverScene::GoToMenuScene, this));
    mainMenuItem->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/4));

    auto menu = Menu::create(retryItem, mainMenuItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    UserDefault *def = UserDefault::getInstance();
    auto highScore = def->getIntegerForKey("HIGHSCORE", 0);
    if(score > highScore){
        highScore=score;
        def->setIntegerForKey("HIGHSCORE", highScore);
    }

    def->flush();

    __String *tempScore = __String::createWithFormat( "%i", score );

    auto scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height*SCORE_FONT_SIZE);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2));

    this->addChild(scoreLabel);
    __String *tempHighScore  = __String::createWithFormat("%i", highScore);
    auto highScoreLabel = Label::createWithTTF(tempHighScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height*SCORE_FONT_SIZE);
    highScoreLabel->setColor(Color3B::YELLOW);
    highScoreLabel->setPosition(Point(visibleSize.width*0.75 + origin.x, visibleSize.height/2+origin.y));

    this->addChild(highScoreLabel);

    return true;

}


void GameOverScene::GoToGameScene(Ref *sender){
    auto scene  = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameOverScene::GoToMenuScene(Ref *sender){
    auto scene  = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));


}
