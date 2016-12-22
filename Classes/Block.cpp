#include "Block.h"

bool Block::init() {

	if (!Node::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	// ��������ϰ����С ��5-25 ��10-40
	auto size = Size(rand() % 20 + 5, rand() % 30 + 10);
	
	// ʹ��Sprite����һ��Block
	auto sprite = Sprite::create();
	sprite->setTextureRect(Rect(0, 0, size.width, size.height));
	sprite->setColor(Color3B(0, 0, 0));
	
	addChild(sprite);

	// ���ø����С
	setPhysicsBody(PhysicsBody::createBox(size));		
	setContentSize(size);

	// �ŵ����Ҷ�
	setPositionX(visibleSize.width);	
	scheduleUpdate();

	// ���÷Ƕ�̬
	getPhysicsBody()->setDynamic(false);
	// ������ײ��ʶ
	getPhysicsBody()->setContactTestBitmask(1);

	return true;
}

void Block::update(float dt) {
	// �����ƶ� �ɸ���λ�ƴ�С�ı��ٶ�
	this->setPositionX(getPositionX() - 4);
	// �Ƴ�
	if (getPositionX() < 0) {		
		unscheduleUpdate();
		removeFromParent();
	}
}
