#include "PlayGameScene.h"
#include "GameOverScene.h"

/*
 * 创建场景
 */
Scene* PlayGame::createScene(int heroCount)
{    
	// 创建一个物理世界场景
	auto scene = Scene::createWithPhysics();
	// 打开调试框
	// scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	// 设置重力
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1000));
    

    auto layer = PlayGame::create(heroCount);
    scene->addChild(layer);

    return scene;
}

/*
 * 创建PlayGame层
 */
PlayGame * PlayGame::create(int heroCount) {

	auto layer = new PlayGame();
	layer->init(heroCount);
	layer->autorelease();

	return layer;
}

/*
 * PlayGame层初始化
 */
bool PlayGame::init(int heroCount)
{
    // 父类init
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) ) {
        return false;
    }
    
	_heroCount = heroCount;
	_time = 0;

	setGameControllers(heroCount);
	setContactListener();
	setUserTouchListener();

	scheduleUpdate();
	schedule(schedule_selector(PlayGame::onTimer), 1.0f / 1000);

    return true;
}

void PlayGame::update(float dt) {
	// 控制器更新
	for (auto it = gameCtrs.begin(); it != gameCtrs.end(); it++) {
		(*it)->onUpdate(dt);
	}
}

/*
 * 定时器 1/1000s 执行一次
 */
void PlayGame::onTimer(float dt) {
	_time += dt;
	CCLOG("Time dt : %f", dt);
	CCLOG("Time : %f", _time);
}

void PlayGame::setContactListener() {
	// 碰撞监听
	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [this](PhysicsContact& contact) {
		CCLOG("Contact GameOver");
		this->unscheduleUpdate();

		auto director = Director::getInstance();
		director->getEventDispatcher()->removeEventListener(contactListener);
		director->getEventDispatcher()->removeEventListener(touchListener);
		director->replaceScene(GameOver::createScene(_heroCount, _time));

		return true;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(contactListener, this);
}

void PlayGame::setUserTouchListener() {
	// 触摸监听
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [this](Touch* touch, Event* event) {

		CCLOG("onTouchBegan");

		// 遍历每个人物所处的游戏控制器 从最上方开始
		for (auto it = gameCtrs.begin(); it != gameCtrs.end(); it++) {
			if ((*it)->hitTestPoint(touch->getLocation())) {
				// 触摸满足最上面的一个后跳出遍历 后面的不参与此次触摸
				(*it)->onUserTouch();
				break;
			}
		}

		return false;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(touchListener, this);
}

/*
 * 每个人物使用一个游戏控制器创建
 */
void PlayGame::setGameControllers(int heroCount) {

	auto size = Director::getInstance()->getVisibleSize();
	float startY = 30; //第一个人物所在Y位置
	float gap = (size.height - startY) / heroCount; // 每个人物间距

	for (int i = 0; i < heroCount; i++) {
		// 使用insert把最新的人放到最上面
		gameCtrs.insert(0, GameController::create(this, startY + gap * i));
	}
}
