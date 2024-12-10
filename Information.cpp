#include "Information.h"
#include "levelSelection.h"
#include "audio/include/AudioEngine.h"


USING_NS_CC;

Information::Information() {}

Information::~Information() {}

Scene* Information::createScene() {

	return Information::create();

}

bool Information::init() {

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

	auto layerCero = Sprite::create("Information.png");

	layerCero->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	layerCero->setScale(visibleSize.width / layerCero->getContentSize().width, visibleSize.height / layerCero->getContentSize().height);
	this->addChild(layerCero, 0);

	auto nextScene = Label::createWithTTF("BACK", "fonts/Acropolis-HTF-Black.otf", 12);
	nextScene->setPosition(Vec2(origin.x + 25, origin.y + 25));
	nextScene->setTextColor(Color4B::WHITE);
	nextScene->enableOutline(Color4B::BLACK, 2);
	this->addChild(nextScene);

	auto up = MoveBy::create(0.5f, Vec2(0, 10));
	auto down = up->reverse();
	auto se = Sequence::create(up, down, nullptr);
	nextScene->runAction(RepeatForever::create(se));


	auto listener2 = EventListenerMouse::create();
	listener2->onMouseDown = [this, nextScene](Event* event) {

		EventMouse* mouseEvent = (EventMouse*)event;
		Vec2 mousePos = mouseEvent->getLocation();
		mousePos.y = Director::getInstance()->getVisibleSize().height - mousePos.y;

		if (nextScene && nextScene->getBoundingBox().containsPoint(mousePos)) {
			log("Next Scene...");
			
			Director::getInstance()->replaceScene(TransitionFade::create(2.0f, levelSelection::createScene()));
		}


		};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);

	return true;
}