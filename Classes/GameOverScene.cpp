#include "GameOverScene.h"
#include "StartGameScene.h"
#include "PlayGameScene.h"

Scene * GameOver::createScene(int heroCount, double score) {

	auto scene = Scene::create();
	auto layer = GameOver::create(heroCount, score);
	scene->addChild(layer);

	return scene;
}

GameOver * GameOver::create(int heroCount, double score)
{
	auto layer = new GameOver();
	layer->init(heroCount, score);
	layer->autorelease();

	return layer;
}

bool GameOver::init(int heroCount, double score) {

	if (!LayerColor::initWithColor(Color4B::WHITE))	{
		return false;
	}

	_currentHeroCnt = heroCount;
	_score = score;

	visibleSize = Director::getInstance()->getVisibleSize();
	localStrings = CCDictionary::createWithContentsOfFile("string.xml");

	auto overLabel = Label::create(GET_LOCAL_STRING("gameOver"), "Courier", 40);
	overLabel->setColor(Color3B::BLACK);
	overLabel->setPosition(visibleSize.width / 2, visibleSize.height - overLabel->getContentSize().height / 2 - 40);
	addChild(overLabel);

	char str[10];
	sprintf(str, "%.3fs", _score);
	auto scoreLabel = Label::create(str, "Courier", 40);
	scoreLabel->setColor(Color3B::BLACK);
	scoreLabel->setPosition(visibleSize.width / 2, visibleSize.height - scoreLabel->getContentSize().height / 2 - 100);
	addChild(scoreLabel);

	addBtnLabel();
	addBtnListener();

	return true;
}

void GameOver::addBtnLabel() {

	btnReplay = Label::create(GET_LOCAL_STRING("btnReplay"), "Courier", 32);
	btnReplay->setColor(Color3B::BLACK);
	btnReplay->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 50);
	addChild(btnReplay);

	btnBackHome = Label::create(GET_LOCAL_STRING("btnBackHome"), "Courier", 32);
	btnBackHome->setColor(Color3B::BLACK);
	btnBackHome->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 50);
	addChild(btnBackHome);
}

void GameOver::addBtnListener() {

	auto director = Director::getInstance();
	touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = [this, director](Touch *touch, Event *event) {

		if (this->btnReplay->getBoundingBox().containsPoint(touch->getLocation())) {
			director->getEventDispatcher()->removeEventListener(touchListener);
			CCLOG("_currentHeroCnt %d", _currentHeroCnt);
			director->replaceScene(PlayGame::createScene(_currentHeroCnt));
		} else if (this->btnBackHome->getBoundingBox().containsPoint(touch->getLocation())) {
			director->getEventDispatcher()->removeEventListener(touchListener);			
			director->replaceScene(StartGame::createScene());
		}		

		return false;
	};

	// 按键监听
	auto listener = EventListenerKeyboard::create();
	// 触摸开始事件
	listener->onKeyReleased = [this, director](EventKeyboard::KeyCode code, Event *event) {
		CCLOG("onKeyReleased - KeyCode: %d", code); // KeyCode: 6 后退键 KeyCode: 18 菜单键
		switch (code) {
		case EventKeyboard::KeyCode::KEY_BACK:
			director->end(); // 关闭程序
			break;
		case EventKeyboard::KeyCode::KEY_MENU:
			CCLOG("onKeyReleased - KEY_MENU");
			break;
		}
	};

	// 设置监听
	director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}
