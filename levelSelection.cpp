#include "levelSelection.h"
#include "audio/include/AudioEngine.h"
#include "ui/CocosGUI.h"
#include "MainMenu.h"
#include "levelTwo.h"
#include "levelThree.h"
#include "levelFour.h"
#include "levelFinal.h"
#include "Information.h"
USING_NS_CC;

levelSelection::levelSelection() {}

levelSelection::~levelSelection() {}

Scene* levelSelection::createScene() {

	return levelSelection::create();

}

bool levelSelection::init() {

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

	int backgroundId = AudioEngine::play2d("introNature.mp3", true);

	auto background = Sprite::create("levelSel.png");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
	this->addChild(background, 0);

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

	auto levelOne = Label::createWithTTF("LEVEL 1", "fonts/Acropolis-HTF-Black.otf", 10);
	if (levelOne == nullptr) {
		
		CCLOG("Level One label not found");
		return false;

	}

	levelOne->setPosition(Vec2(visibleSize.width / 3 + origin.x - 75, visibleSize.height / 2 + origin.y + 80));
	levelOne->setTextColor(Color4B::WHITE);
	levelOne->enableOutline(Color4B::BLACK, 2);
	this->addChild(levelOne, 0);

	auto levelTwo = Label::createWithTTF("LEVEL 2", "fonts/Acropolis-HTF-Black.otf", 10);
	if (levelTwo == nullptr) {

		CCLOG("Level Two label not found");
		return false;

	}
	levelTwo->setPosition(Vec2(visibleSize.width / 3 + origin.x - 75 + 315, visibleSize.height / 2 + origin.y + 80));
	levelTwo->setTextColor(Color4B::WHITE);
	levelTwo->enableOutline(Color4B::BLACK, 2);
	this->addChild(levelTwo, 0);

	auto levelThree = Label::createWithTTF("LEVEL 3", "fonts/Acropolis-HTF-Black.otf", 10);
	if (levelThree == nullptr) {

		CCLOG("Level Two label not found");
		return false;

	}
	levelThree->setPosition(Vec2(visibleSize.width / 3 + origin.x - 75, (visibleSize.height / 2) + origin.y - 40));
	levelThree->setTextColor(Color4B::WHITE);
	levelThree->enableOutline(Color4B::BLACK, 2);
	this->addChild(levelThree, 0);

	auto levelFour = Label::createWithTTF("LEVEL 4", "fonts/Acropolis-HTF-Black.otf", 10);
	if (levelThree == nullptr) {

		CCLOG("Level Four label not found");
		return false;

	}
	levelFour->setPosition(Vec2(visibleSize.width / 3 + origin.x - 75 + 315, (visibleSize.height / 2) + origin.y - 40));
	levelFour->setTextColor(Color4B::WHITE);
	levelFour->enableOutline(Color4B::BLACK, 2);
	this->addChild(levelFour, 0);

	auto levelFinal = Label::createWithTTF("FINAL LEVEL", "fonts/Acropolis-HTF-Black.otf", 8);
	if (levelFinal == nullptr) {

		CCLOG("Final level label not found");
		return false;

	}
	levelFinal->setPosition(Vec2(visibleSize.width / 2 + origin.x + 5, (visibleSize.height / 2) + origin.y - 85));
	levelFinal->setTextColor(Color4B::WHITE);
	levelFinal->enableOutline(Color4B::BLACK, 2);
	this->addChild(levelFinal, 0);

	auto info = Label::createWithTTF("Info", "fonts/Acropolis-HTF-Black.otf", 8);
	if (levelFinal == nullptr) {

		CCLOG("info label not found");
		return false;

	}
	info->setPosition(Vec2(visibleSize.width + origin.x - 15, origin.y + 15));
	info->setTextColor(Color4B::WHITE);
	info->enableOutline(Color4B::BLACK, 2);
	this->addChild(info, 0);


	auto listener2 = EventListenerMouse::create();
	listener2->onMouseDown = [this, levelOne, levelTwo, levelThree, levelFour, levelFinal, backgroundId, info](Event* event) {

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

		

		if (levelOne && levelOne->getBoundingBox().containsPoint(mousePos)) {
			log("Level 1 Selected");
			AudioEngine::stop(backgroundId);
			Director::getInstance()->replaceScene(TransitionFade::create(2.0f, MainMenu::createScene()));

		}	

		if (levelTwo && levelTwo->getBoundingBox().containsPoint(mousePos)) {
			log("Level 2 Selected");
			AudioEngine::stop(backgroundId);
			Director::getInstance()->replaceScene(TransitionFade::create(2.0f, levelTwo::createScene()));

		}

		if (levelThree && levelThree->getBoundingBox().containsPoint(mousePos)) {
			log("Level 3 Selected");
			AudioEngine::stop(backgroundId);
			Director::getInstance()->replaceScene(TransitionFade::create(2.0f, levelThree::createScene()));

		}

		if (levelFour && levelFour->getBoundingBox().containsPoint(mousePos)) {
			log("Level 4 Selected");
			AudioEngine::stop(backgroundId);
			Director::getInstance()->replaceScene(TransitionFade::create(2.0f, levelFour::createScene()));

		}

		if (levelFinal && levelFinal->getBoundingBox().containsPoint(mousePos)) {
			log("Level 4 Selected");
			AudioEngine::stop(backgroundId);
			Director::getInstance()->replaceScene(TransitionFade::create(2.0f, levelFinal::createScene()));

		}

		if (info && info->getBoundingBox().containsPoint(mousePos)) {
			log("info Selected");
			AudioEngine::stop(backgroundId);
			Director::getInstance()->replaceScene(TransitionFade::create(2.0f, Information::createScene()));

		}


	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);

	





}
