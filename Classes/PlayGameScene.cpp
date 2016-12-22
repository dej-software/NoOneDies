#include "PlayGameScene.h"
#include "GameOverScene.h"

/*
 * ��������
 */
Scene* PlayGame::createScene(int heroCount)
{    
	// ����һ���������糡��
	auto scene = Scene::createWithPhysics();
	// �򿪵��Կ�
	// scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	// ��������
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1000));
    

    auto layer = PlayGame::create(heroCount);
    scene->addChild(layer);

    return scene;
}

/*
 * ����PlayGame��
 */
PlayGame * PlayGame::create(int heroCount) {

	auto layer = new PlayGame();
	layer->init(heroCount);
	layer->autorelease();

	return layer;
}

/*
 * PlayGame���ʼ��
 */
bool PlayGame::init(int heroCount)
{
    // ����init
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
	// ����������
	for (auto it = gameCtrs.begin(); it != gameCtrs.end(); it++) {
		(*it)->onUpdate(dt);
	}
}

/*
 * ��ʱ�� 1/1000s ִ��һ��
 */
void PlayGame::onTimer(float dt) {
	_time += dt;
	CCLOG("Time dt : %f", dt);
	CCLOG("Time : %f", _time);
}

void PlayGame::setContactListener() {
	// ��ײ����
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
	// ��������
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [this](Touch* touch, Event* event) {

		CCLOG("onTouchBegan");

		// ����ÿ��������������Ϸ������ �����Ϸ���ʼ
		for (auto it = gameCtrs.begin(); it != gameCtrs.end(); it++) {
			if ((*it)->hitTestPoint(touch->getLocation())) {
				// ���������������һ������������ ����Ĳ�����˴δ���
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
 * ÿ������ʹ��һ����Ϸ����������
 */
void PlayGame::setGameControllers(int heroCount) {

	auto size = Director::getInstance()->getVisibleSize();
	float startY = 30; //��һ����������Yλ��
	float gap = (size.height - startY) / heroCount; // ÿ��������

	for (int i = 0; i < heroCount; i++) {
		// ʹ��insert�����µ��˷ŵ�������
		gameCtrs.insert(0, GameController::create(this, startY + gap * i));
	}
}
