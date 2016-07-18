#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__
#include "SimpleAudioEngine.h"

#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(unsigned int m_score);
    virtual bool init();    
    CREATE_FUNC(GameOverScene);

private:
    void GoToMenuScene(cocos2d::Ref *sender);
    void GoToGameScene(cocos2d::Ref *sender);
};

#endif // __GAMEOVER_SCENE_H__
