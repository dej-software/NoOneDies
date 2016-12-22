#ifndef __STARTGAME_SCENE_H__
#define __STARTGAME_SCENE_H__

#include "cocos2d.h"

#define GET_LOCAL_STRING(name) (((CCString*)localStrings->objectForKey(name))->getCString())

USING_NS_CC;

class StartGame : public cocos2d::LayerColor {

private:
	Size visibleSize;
	__Dictionary* localStrings;

	Label *btnTwo, *btnThree, *btnFour, *btnFive;
	EventListenerTouchOneByOne *touchListener;

public:
    static Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(StartGame);

private:
	void addBtnLabel();
	void addBtnListener();
};

#endif // __STARTGAME_SCENE_H__
