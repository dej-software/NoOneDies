#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "cocos2d.h"
#include "Edge.h"
#include "Hero.h"
#include "Block.h"

USING_NS_CC;

class GameController : public Ref {
private:
	Layer *_layer;
	float _positionY;
	Size visibleSize;

	Edge *edge;
	Hero *hero;

	int currentFrameIndex;
	int nextFrameCount;

private:
	void resetFrames();
	void addBlock();

public:
    virtual bool init(Layer *layer, float positionY);    
    static GameController* create(Layer *layer, float positionY);

	void onUpdate(float dt);
	bool hitTestPoint(Vec2 point);
	void onUserTouch();
};

#endif // __GAME_CONTROLLER_H__
