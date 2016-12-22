#ifndef __PLAYGAME_SCENE_H__
#define __PLAYGAME_SCENE_H__

#include "cocos2d.h"
#include "GameController.h"

USING_NS_CC;

class PlayGame : public cocos2d::LayerColor
{
private:
	Vector<GameController*> gameCtrs;	
	int _heroCount;
	float _time;
	EventListenerPhysicsContact * contactListener;
	EventListenerTouchOneByOne * touchListener;

public:
    static Scene* createScene(int heroCount);
	static PlayGame* create(int heroCount);
    virtual bool init(int heroCount);
	virtual void update(float dt);
	virtual void onTimer(float dt);

private:
	void setContactListener();
	void setUserTouchListener();
	void setGameControllers(int heroCount);
};

#endif // __PLAYGAME_SCENE_H__
