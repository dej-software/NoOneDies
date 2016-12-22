#include "Hero.h"
#include "FlashTool.h"

bool Hero::init() {

	if (!Node::init()) {
		return false;
	}

	// ������С Hero.json��鿴
	auto size = Size(44, 52);

	// ʹ��Sprite���ж���
	auto sprite = Sprite::create();	
	sprite->runAction(RepeatForever::create(FlashTool::readJsonSpriteSheet("hero.json", 0.2f)));
	
	addChild(sprite);

	// ���ø����С
	setPhysicsBody(PhysicsBody::createBox(size));
	setContentSize(size); // ���ô�ֵ���ܻᵼ�¸�����Sprite����Ӱ���Ҷ�

	// ���ø��岻��ת
	getPhysicsBody()->setRotationEnable(false);
	// ������ײ��ʶ
	getPhysicsBody()->setContactTestBitmask(1);

	return true;
}
