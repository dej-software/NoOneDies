#include "Block.h"

bool Block::init() {

	if (!Node::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	// 随机生成障碍物大小 宽5-25 高10-40
	auto size = Size(rand() % 20 + 5, rand() % 30 + 10);
	
	// 使用Sprite制作一个Block
	auto sprite = Sprite::create();
	sprite->setTextureRect(Rect(0, 0, size.width, size.height));
	sprite->setColor(Color3B(0, 0, 0));
	
	addChild(sprite);

	// 设置刚体大小
	setPhysicsBody(PhysicsBody::createBox(size));		
	setContentSize(size);

	// 放到最右端
	setPositionX(visibleSize.width);	
	scheduleUpdate();

	// 设置非动态
	getPhysicsBody()->setDynamic(false);
	// 设置碰撞标识
	getPhysicsBody()->setContactTestBitmask(1);

	return true;
}

void Block::update(float dt) {
	// 向左移动 可更改位移大小改变速度
	this->setPositionX(getPositionX() - 4);
	// 移除
	if (getPositionX() < 0) {		
		unscheduleUpdate();
		removeFromParent();
	}
}
