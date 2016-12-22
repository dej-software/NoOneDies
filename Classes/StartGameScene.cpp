#include "StartGameScene.h"
#include "PlayGameScene.h"

Scene * StartGame::createScene() {

	auto scene = Scene::create();
	auto layer = StartGame::create();
	scene->addChild(layer);

	return scene;
}

bool StartGame::init() {

	if (!LayerColor::initWithColor(Color4B::WHITE))	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	localStrings = CCDictionary::createWithContentsOfFile("string.xml");

	addBtnLabel();
	addBtnListener();

	auto titleLabel = Label::create(GET_LOCAL_STRING("title"), "Courier", 40);
	titleLabel->setColor(Color3B::BLACK);
	titleLabel->setPosition(visibleSize.width / 2, visibleSize.height - titleLabel->getContentSize().height / 2 - 40);
	addChild(titleLabel);
	
	return true;
}

/*
 * 在界面添加用作按钮的Label
 */
void StartGame::addBtnLabel() {
	
	btnTwo = Label::create(GET_LOCAL_STRING("btnTwo"), "Courier", 32);
	btnTwo->setColor(Color3B::BLACK);
	btnTwo->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 150);
	addChild(btnTwo);

	btnThree = Label::create(GET_LOCAL_STRING("btnThree"), "Courier", 32);
	btnThree->setColor(Color3B::BLACK);
	btnThree->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 50);
	addChild(btnThree);

	btnFour = Label::create(GET_LOCAL_STRING("btnFour"), "Courier", 32);
	btnFour->setColor(Color3B::BLACK);
	btnFour->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 50);
	addChild(btnFour);

	btnFive = Label::create(GET_LOCAL_STRING("btnFive"), "Courier", 32);
	btnFive->setColor(Color3B::BLACK);
	btnFive->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 150);
	addChild(btnFive);
}

void StartGame::addBtnListener() {

	auto director = Director::getInstance();
	touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = [this, director](Touch *touch, Event *event) {
		
		if (this->btnTwo->getBoundingBox().containsPoint(touch->getLocation())) {
			director->getEventDispatcher()->removeEventListener(touchListener);
			director->replaceScene(PlayGame::createScene(2));
		} else if (this->btnThree->getBoundingBox().containsPoint(touch->getLocation())) {
			director->getEventDispatcher()->removeEventListener(touchListener);
			director->replaceScene(PlayGame::createScene(3));
		}
		else if (this->btnFour->getBoundingBox().containsPoint(touch->getLocation())) {
			director->getEventDispatcher()->removeEventListener(touchListener);
			director->replaceScene(PlayGame::createScene(4));
		}
		else if (this->btnFive->getBoundingBox().containsPoint(touch->getLocation())) {
			director->getEventDispatcher()->removeEventListener(touchListener);
			director->replaceScene(PlayGame::createScene(5));
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
