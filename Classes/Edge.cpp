#include "Edge.h"

bool Edge::init() {

	if (!Node::init()) {
		return false;
	}

    auto visibleSize = Director::getInstance()->getVisibleSize();    
    setPhysicsBody(PhysicsBody::createEdgeBox(visibleSize));
    
    return true;
}