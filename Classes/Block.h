#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"

USING_NS_CC;

class Block : public Node {
public:
    virtual bool init();
	virtual void update(float dt);
    
    CREATE_FUNC(Block);
};

#endif // __BLOCK_H__
