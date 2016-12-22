#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameOver : public cocos2d::LayerColor {

private:
	Size visibleSize;
	__Dictionary* localStrings;
	int _currentHeroCnt;
	double _score;
	Label *btnReplay, *btnBackHome;
	EventListenerTouchOneByOne *touchListener;

public:
    static Scene* createScene(int heroCount, double score);
	static GameOver* create(int heroCount, double score);
    virtual bool init(int heroCount, double score);

private:
	void addBtnLabel();
	void addBtnListener();
};

#endif // __GAMEOVER_SCENE_H__
