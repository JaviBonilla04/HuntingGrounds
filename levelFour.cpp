#include "levelFour.h"
#include "audio/include/AudioEngine.h"
#include "levelFourSB.h"
USING_NS_CC;

levelFour::levelFour() {}
levelFour::~levelFour() {}

Scene* levelFour::createScene() {

    return levelFour::create();

}

bool levelFour::init() {

    if (!Scene::init()) {

        return false;

    }
    // variables utiles
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //background
    auto background = Sprite::create("levelFour.png");

    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
    this->addChild(background);

    total = 20;
    int random;
    std::vector<int> pattern;
    for (int i = 0; i < total; i++) {

        auto duck = Duck::create();
        duck->setScale(2.0f);
        
        random = std::rand() % 6;
        if (random == 0 || random == 4 || random == 5) {
            duck->setMinSpeed(100.0f);
            duck->setMaxSpeed(150.0f);
            duck->setDirectionProb(0.1f);
            duck->setType(2);
            duck->setScoreValue(-5);
        }
        else if(random == 1){
            duck->setMinSpeed(100.0f);
            duck->setMaxSpeed(150.0f);
            duck->setDirectionProb(0.1f);
            duck->setType(1);
            duck->setScoreValue(10);
        } else if(random == 2 || random == 3){
            duck->setMinSpeed(200.0f);
            duck->setMaxSpeed(210.0f);
            duck->setDirectionProb(0.3f);
            duck->setType(3);
            duck->setScoreValue(20);

        }
        ducks.pushBack(duck);

    }

    //countDown

    auto countdownLabel = Label::createWithTTF("3", "fonts/Acropolis-HTF-Black.otf", 24);
    countdownLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 3 / 4));
    countdownLabel->setColor(Color3B::WHITE);
    countdownLabel->enableOutline(Color4B::BLACK, 2);
    this->addChild(countdownLabel);

    this->scheduleOnce([this, countdownLabel](float dt) {
        AudioEngine::play2d("beep.mp3");
        countdownLabel->setString("3");
        countdownLabel->setVisible(true);
        }, 1.0f, "schedule3");

    this->scheduleOnce([this, countdownLabel](float dt) {
        AudioEngine::play2d("beep.mp3");
        countdownLabel->setString("2");
        countdownLabel->setVisible(true);
        }, 2.0f, "schedule2");

    this->scheduleOnce([this, countdownLabel](float dt) {
        AudioEngine::play2d("beep.mp3");
        countdownLabel->setString("1");
        countdownLabel->setVisible(true);
        }, 3.0f, "schedule1");

    this->scheduleOnce([this, countdownLabel](float dt) {
        AudioEngine::play2d("beep.mp3");
        countdownLabel->setString("GOOD LUCK");
        countdownLabel->setVisible(true);
        }, 4.0f, "schedule0");

    this->scheduleOnce([this, countdownLabel](float dt) {
        auto backMusic = "levelOneBackgroundMusic.mp3";
        int musicId = AudioEngine::play2d(backMusic, true);
        AudioEngine::setVolume(musicId, 0.1f);
        countdownLabel->setVisible(false);
        }, 5.0f, "hide_countdown");

    this->scheduleOnce([this](float dt) {
        // Crear el primer pato
        if (!ducks.empty()) {
            for (int i = 0; i < 5; i++) {
                this->addChild(ducks.at(i));
            }
            AudioEngine::play2d("bebek.mp3");
        }
        }, 5.0f, "add_first_duck");

    //cross
    auto cross = Sprite::create("crosshair.png");

    Director::getInstance()->getOpenGLView()->setCursorVisible(false);

    if (cross == nullptr) {
        CCLOG("Crosshair not found");
        return false;
    }

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

    //bullet numbers
    numBullets = 12;
    bulletCount = Label::createWithTTF(std::to_string(numBullets), "fonts/Acropolis-HTF-Black.otf", 12);
    bulletCount->setPosition(Vec2(origin.x + 115, origin.y + 26));
    bulletCount->enableOutline(Color4B::BLACK, 2);
    this->addChild(bulletCount, 1);

    auto listener2 = EventListenerMouse::create();
    listener2->onMouseDown = [this](Event* event) {

        EventMouse* mouseEvent = (EventMouse*)event;
        Vec2 mousePos = mouseEvent->getLocation();
        mousePos.y = Director::getInstance()->getVisibleSize().height - mousePos.y;

        if (numBullets > 0) {
            numBullets--;
            bulletCount->setString(std::to_string(numBullets));

            AudioEngine::play2d("basicGun.mp3");

            for (ssize_t i = 0; i < ducks.size(); ++i) {
                Duck* duck = ducks.at(i);
                if (duck->getParent() == this && duck->getBoundingBox().containsPoint(mousePos)) {

                    duck->removeFromParent();


                    if (i < indicators.size()) {
                        indicators[i]->setColor(Color3B(169, 169, 169));
                    }


                    score += duck->getScoreValue();
                    scoreLabel->setString(std::to_string(score));
                    achieved++;
                    //if (i < 16) {
                        ssize_t nextDuckIndex = i + 5;
                        if (nextDuckIndex < ducks.size()) {
                            Duck* nextDuck = ducks.at(nextDuckIndex);
                            this->addChild(nextDuck);
                            AudioEngine::play2d("bebek.mp3");
                        }
                        else {
                            CCLOG("No more ducks to add");
                        }

                        break;
                    //}
                }
            }

        }

        if (numBullets == 0) {
            // cuando uno se queda sin balas
            CCLOG("Out of bullets, next scene...");
            auto scoreScene = levelFourSB::createScene(score, achieved, total);

            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scoreScene));
        }

        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);


    this->schedule([this](float dt) {
        // Buscar el pato actual en la escena
        Duck* currentDuck = nullptr;
        ssize_t currentDuckIndex = -1;

        for (ssize_t i = 0; i < ducks.size(); ++i) {
            if (ducks.at(i)->getParent() == this) {
                currentDuck = ducks.at(i);
                currentDuckIndex = i;
                break;
            }
        }

        if (currentDuck == nullptr || !currentDuck->vclickedNext()) {
            return;
        }

        // Remover el pato actual

        if (ducks.at(currentDuckIndex)->getNextDuck()) {
            currentDuck->removeFromParent();
            if (currentDuckIndex >= 0 && currentDuckIndex < indicators.size()) {

                indicators[currentDuckIndex]->setColor(Color3B(169, 169, 169));

            }

        }

        // Buscar y a�adir el siguiente pato
        ssize_t nextDuckIndex = currentDuckIndex + 5;
        if (nextDuckIndex < ducks.size()) {
            Duck* nextDuck = ducks.at(nextDuckIndex);
            this->addChild(nextDuck);
            AudioEngine::play2d("bebek.mp3");
            CCLOG("Adding next duck at index %zd", nextDuckIndex);
        }
        else {
            // No hay m�s patos
            this->unschedule("check_next_duck");
            CCLOG("No more ducks to add");
            auto scoreScene = levelFourSB::createScene(score, achieved, ducks.size());
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scoreScene));
            return;
        }

        bool allDucks = true;
        for (auto& duck : ducks) {
            if (duck->getParent() == this) {
                allDucks = false;
                break;
            }
        }

        if (allDucks) {

            CCLOG("All ducks, next scene...");
            this->unschedule("check_next_duck");
            auto scoreScene = levelFourSB::createScene(score, achieved, total);
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scoreScene));

            return;
        }

        }, 0.1f, "check_next_duck");

    this->schedule([this](float dt) {

        if (achieved == ducks.size()) {
            CCLOG("All ducks eliminated. Changing to score scene...");

            this->unschedule("check_achieved");

            auto scoreScene = levelFourSB::createScene(score, achieved, ducks.size());
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scoreScene));
        }

        }, 0.1f, "check_achieved");



    float indWidth = 2.5f;
    float indHeight = 5.0f;
    float spacing = 3.0f;

    float totalWidth = (indWidth + spacing) * ducks.size() - spacing;
    float centerX = origin.x + (visibleSize.width - totalWidth) / 2;

    for (int i = 0; i < ducks.size(); i++) {

        auto indicator = Sprite::create();
        indicator->setTextureRect(Rect(0, 0, indWidth, indHeight));
        indicator->setColor(Color3B::WHITE);
        indicator->setPosition(Vec2(centerX + (indWidth + spacing) * i, origin.y + 26));
        this->addChild(indicator, 2);
        indicators.push_back(indicator);
    }

    scoreLabel = Label::createWithTTF("0", "fonts/Acropolis-HTF-Black.otf", 12);
    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width - 115, origin.y + 26));
    scoreLabel->enableOutline(Color4B::BLACK, 2);
    this->addChild(scoreLabel, 1);





    return true;

}

