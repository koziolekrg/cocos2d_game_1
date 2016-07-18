#ifndef __BIRD_H__
#define __BIRD_H__
#include "SimpleAudioEngine.h"

#include "cocos2d.h"

class Bird : public cocos2d::Layer
{
public:
    Bird(cocos2d::Layer *layer);
    void Fall(float dt);
    void Fly(float dt);
    void stopFlying(float dt) {isFalling = true;}


private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite *flappyBird;
    bool isFalling;
};

#endif // __BIRD_H__
