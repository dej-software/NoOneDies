#include "GameController.h"

bool GameController::init(Layer * layer, float positionY) {

	_layer = layer;
	_positionY = positionY;

	visibleSize = Director::getInstance()->getVisibleSize();

	//添加Edge
	edge = Edge::create();
	edge->setPosition(visibleSize.width / 2, visibleSize.height / 2 + positionY);
	edge->setContentSize(visibleSize);
	layer->addChild(edge);

	// 添加下边界（地板）
	auto ground = Sprite::create();
	ground->setColor(Color3B(0, 0, 0));
	ground->setTextureRect(Rect(0, 0, visibleSize.width, 3));
	ground->setPosition(visibleSize.width / 2, 1.5 + positionY);
	layer->addChild(ground);

	// 添加人物
	hero = Hero::create();
	hero->setPosition(50, hero->getContentSize().height / 2 + positionY);
	layer->addChild(hero);

	resetFrames();

	return true;
}

GameController * GameController::create(Layer * layer, float positionY) {

	auto _ins = new GameController();
	_ins->init(layer, positionY);
	_ins->autorelease();

	return _ins;
}

/*
 * 重设出现障碍物的帧参数
 */
void GameController::resetFrames() {
	// 当前帧
	currentFrameIndex = 0;
	// 下一次出现障碍物的帧数
	nextFrameCount = rand() % 120 + 100;
}

/*
 * 添加一个障碍物
 */
void GameController::addBlock() {
	CCLOG("addBlock");
	auto block = Block::create();
	block->setPositionY(block->getContentSize().height / 2 + _positionY);
	_layer->addChild(block);
}

/*
 * 不断更新的函数 增加障碍物
 */
void GameController::onUpdate(float dt) {		
	currentFrameIndex++;
	if (currentFrameIndex >= nextFrameCount) {
		resetFrames();
		addBlock();
	}
}

/*
 * 测试触摸点是否在人物边界内
 */
bool GameController::hitTestPoint(Vec2 point) {
	
	// 需要做位置修正
	point.x += visibleSize.width / 2;
	point.y += visibleSize.height / 2;

	//CCLOG("point.x = %f, MinX = %f, MaxX = %f", point.x, edge->getBoundingBox().getMinX(), edge->getBoundingBox().getMaxX());
	//CCLOG("point.y = %f, MinY = %f, MaxY = %f", point.y, edge->getBoundingBox().getMinY(), edge->getBoundingBox().getMaxY());

	return edge->getBoundingBox().containsPoint(point);
}

/*
 * 触摸满足条件时使小人跳起
 */
void GameController::onUserTouch() {
	// 判断hero的速度 为0不在空中时才重新跳起
	if (abs(hero->getPhysicsBody()->getVelocity().y) < 1e-6) {
		hero->getPhysicsBody()->setVelocity(Vec2(0, 400));
	}
}
