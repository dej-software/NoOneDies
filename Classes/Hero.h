#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"

USING_NS_CC;

class Hero : public Node {
public:
    virtual bool init();
    
    CREATE_FUNC(Hero);
};

#endif // __HERO_H__
