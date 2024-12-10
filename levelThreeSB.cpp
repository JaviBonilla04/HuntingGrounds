#include "levelThreeSB.h"
#include "audio/include/AudioEngine.h"
#include "Duck.h"
#include "DuckManager.h"
#include "levelSelection.h"

USING_NS_CC;

levelThreeSB::levelThreeSB(int score, int achieved, int total)
    : score(score), achieved(achieved), total(total) {}

levelThreeSB::~levelThreeSB() {}

levelThreeSB* levelThreeSB::createScene(int score, int achieved, int total)
{
    levelThreeSB* scene = new levelThreeSB(score, achieved, total);
    if (scene && scene->init(score, achieved, total)) {
        scene->autorelease();
        return scene;
    }
    else {
        delete scene;
        return nullptr;
    }
}

bool levelThreeSB::init(int score, int achieved, int total)
{
    if (!Scene::init())
    {
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


    // Fondo color sólido


    auto layerCero = Sprite::create("levelThreeScoreBoard.png");

    layerCero->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    layerCero->setScale(visibleSize.width / layerCero->getContentSize().width, visibleSize.height / layerCero->getContentSize().height);
    this->addChild(layerCero, 0);


    // Mostrar el score en letras grandes
    auto scoreLabel = Label::createWithTTF("Score: " + std::to_string(score), "fonts/Acropolis-HTF-Black.otf", 24);
    scoreLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 3 / 4));
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->enableOutline(Color4B::BLACK, 2);
    this->addChild(scoreLabel);

    // Mostrar el número de patos muertos
    auto targetsLabel = Label::createWithTTF("Targets: " + std::to_string(achieved) + "/" + std::to_string(total), "fonts/Acropolis-HTF-Black.otf", 24);
    targetsLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    targetsLabel->setColor(Color3B::WHITE);
    targetsLabel->enableOutline(Color4B::BLACK, 2);
    this->addChild(targetsLabel);


    auto nextScene = Label::createWithTTF("BACK TO MENU", "fonts/Acropolis-HTF-Black.otf", 12);
    nextScene->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + 50));
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

        AudioEngine::play2d("basicGun.mp3");

        if (nextScene && nextScene->getBoundingBox().containsPoint(mousePos)) {
            log("Back to Menu...");
            Director::getInstance()->replaceScene(TransitionFade::create(2.0f, levelSelection::createScene()));
        }


        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);

    return true;

}

void levelThreeSB::toMenu(Ref* send)
{
    // Cambiar a la escena principal (MainMenu)
    Director::getInstance()->replaceScene(TransitionFade::create(2.0f, levelSelection::createScene()));
}
