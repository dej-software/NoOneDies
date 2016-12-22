#include "Hero.h"
#include "FlashTool.h"

bool Hero::init() {

	if (!Node::init()) {
		return false;
	}

	// 人物块大小 Hero.json里查看
	auto size = Size(44, 52);

	// 使用Sprite运行动画
	auto sprite = Sprite::create();	
	sprite->runAction(RepeatForever::create(FlashTool::readJsonSpriteSheet("hero.json", 0.2f)));
	
	addChild(sprite);

	// 设置刚体大小
	setPhysicsBody(PhysicsBody::createBox(size));
	setContentSize(size); // 设置此值可能会导致刚体受Sprite动画影响乱动

	// 设置刚体不旋转
	getPhysicsBody()->setRotationEnable(false);
	// 设置碰撞标识
	getPhysicsBody()->setContactTestBitmask(1);

	return true;
}
