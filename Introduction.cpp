#include "Introduction.h"
#include "MainMenu.h"
#include "levelSelection.h"
#include "audio/include/AudioEngine.h"
#include <cstdlib>

USING_NS_CC;

Introduction::Introduction() {}

Introduction::~Introduction() {}

Scene* Introduction::createScene() {

	return Introduction::create();

}

bool Introduction::init() {

	if (!Scene::init()) {

		return false;

	}
	
	Director::getInstance()->getOpenGLView()->setCursorVisible(false);

	auto cross = Sprite::create("crosshair.png");

	if (cross == nullptr) {
		CCLOG("Crosshair not found");
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	cross->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	cross->setScale(0.1f);
	this->addChild(cross, 1);

	auto listener = EventListenerMouse::create();
	listener->onMouseMove = [cross, visibleSize](Event* event) {
	
		EventMouse* mouseEvent = (EventMouse*)event;
		Vec2 mousePos = mouseEvent->getLocation();
		mousePos.y = visibleSize.height - mousePos.y;
		cross->setPosition(mousePos);

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto layerCero = Sprite::create("Introduction.png");

	layerCero->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	layerCero->setScale(visibleSize.width / layerCero->getContentSize().width, visibleSize.height / layerCero->getContentSize().height);
	this->addChild(layerCero, 0);

	int backgroundId = AudioEngine::play2d("introNature.mp3", true);


	auto nextScene = Label::createWithTTF("CLICK TO CONTINUE...", "fonts/Acropolis-HTF-Black.otf", 12);
	nextScene->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + 50));
	nextScene->setTextColor(Color4B::WHITE);
	nextScene->enableOutline(Color4B::BLACK, 2);
	this->addChild(nextScene);

	auto up = MoveBy::create(0.5f, Vec2(0, 10));
	auto down = up->reverse();
	auto se = Sequence::create(up, down, nullptr);
	nextScene->runAction(RepeatForever::create(se));

	/*
	auto touch = EventListenerTouchOneByOne::create();
	touch->setSwallowTouches(true);
	touch->onTouchBegan = [nextScene, this](Touch* touch, Event* event) {

		if (nextScene->getBoundingBox().containsPoint(touch->getLocation())) {
			log("Next Scene...");
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MainMenu::createScene()));
			return true;
		}

		return false;
		
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch, this);
	*/

	auto listener2 = EventListenerMouse::create();
	listener2->onMouseDown = [this, nextScene, backgroundId](Event* event) {
		
		EventMouse* mouseEvent = (EventMouse*)event;
		Vec2 mousePos = mouseEvent->getLocation();
		mousePos.y = Director::getInstance()->getVisibleSize().height - mousePos.y;
		
		AudioEngine::pause(backgroundId);
		
		AudioEngine::play2d("basicGun.mp3");

		this->runAction(Sequence::create(
			DelayTime::create(2.5f), 
			CallFunc::create([backgroundId]() {
					
				AudioEngine::resume(backgroundId);

			}), nullptr));

		if (nextScene && nextScene->getBoundingBox().containsPoint(mousePos)) {
			log("Next Scene...");
			AudioEngine::stop(backgroundId);
			Director::getInstance()->replaceScene(TransitionFade::create(2.0f, levelSelection::createScene()));
		}


	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
	
	return true;

}

