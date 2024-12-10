#include "Duck.h"
#include <cstdlib>
#include <cmath>
#include "audio/include/AudioEngine.h"
//#include <cstdlib>
//#include <ctime>

USING_NS_CC;

Duck::Duck() {


    speed = 50.0f;
    angle = (rand() % 360) * (M_PI / (180.0f));
    dir.x = cos(angle);
    dir.y = sin(angle);
    dir.normalize();
    isEscaping = false;
    timeAlive = 0.0f;
    escapeThreshold = (rand() % 11) + 10.0f;
}

bool Duck::init() {
    if (!Sprite::init()) {
        return false;
    }

    stop = false;
    nextDuck = false;
    mouseListener();
    this->scheduleUpdate();

    
    initializeEntry();
    
    return true;
}

void Duck::setMaxSpeed(float maxSpeed) {
    this->maxSpeed = maxSpeed;
}

void Duck::setMinSpeed(float minSpeed) {
    this->minSpeed = minSpeed;
}

void Duck::setScoreValue(int value) {
    this->scoreValue = value;
}

int Duck::getScoreValue() const {
    return this->scoreValue;
}

void Duck::setDirectionProb(float directionProb) {
    this->changeDirectionProb = directionProb;
}

void Duck::setType(int type) {
    this->type = type;
}

void Duck::initializeEntry() {

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    float entrySpeed = 200.0f;
    float normalSpeed = 50.0f;
    float randomY = origin.y + visibleSize.height / 2;

    int direction = rand() % 2;
    Vec2 entryVector;
    
    switch (direction) {
    
    case 0: {
    
        this->setPosition(origin.x - 50, randomY);
        entryVector = Vec2(1, (rand() % 200 - 100) / 100.0f);
        break;

    }
    case 1: {
    
        this->setPosition(visibleSize.width + 50, randomY);
        entryVector = Vec2(-1, (rand() % 200 - 100) / 100.0f); 
        break;
    
    }

    }

    entryVector.normalize();

    //AudioEngine::play2d("bebek.mp3");
    

    this->schedule([this, visibleSize, entryVector, entrySpeed, normalSpeed](float dt) {
        static float currentSpeed = 0.0f;
        
        currentSpeed += (entrySpeed - currentSpeed) * 0.1f;

        Vec2 currentPos = this->getPosition();
        Vec2 movement = entryVector * entrySpeed * dt;

        this->setPosition(currentPos + movement);

        if (currentPos.x >= 0 && currentPos.x <= visibleSize.width &&
            currentPos.y >= 0 && currentPos.y <= visibleSize.height) {

            this->speed = normalSpeed;
            randomizeDirection();

            this->unschedule("entry_transition");

            this->schedule([this](float dt) {
                Vec2 currentPos = this->getPosition();
                Vec2 movement = dir * this->speed * dt;

                this->setPosition(currentPos + movement);
                }, 0.01f, "normal_movement");
        }
    }, 0.01f, "entry_transition");



}

void Duck::randomizeDirection() {
    angle = (rand() % 360) * (M_PI / 180.0f);
    dir.x = cos(angle);
    dir.y = sin(angle);
    dir.normalize();

    updateSpriteDirection();

}

void Duck::clicked() {
    if (!stop) {
        stop = true;
        speed = 0;
        nextDuck = true;
        this->setVisible(false);
        CCLOG("Duck clicked and marked for next");
    }
}

bool Duck::vclickedNext() const {
    return nextDuck;
}

void Duck::update(float deltaTime) {
    timeAlive += deltaTime;
    
    float targetSpeed = (rand() % int(maxSpeed - minSpeed + 1)) + minSpeed;
    speed += (targetSpeed - speed) * 0.1f;
    
    if (!isEscaping && timeAlive >= escapeThreshold) {
        startEscaping();
    }

    updatePosition(deltaTime);
}

void Duck::startEscaping() {
    isEscaping = true;
    Size visibleSize = Director::getInstance()->getVisibleSize();

    int edge = rand() % 2;
    if (edge == 0) {
        escapeDirection = Vec2(-1, 0);
    }
    else {
        escapeDirection = Vec2(1, 0);
    }

    speed *= 2.0f;


    updateSpriteDirection();
}

void Duck::updateSpriteDirection() {
    
    if (this->type == 1) {

        if (dir.x > 0) {
            this->setTexture("b_east.png");
            this->setFlippedX(false);
        }
        else {
            this->setTexture("b_west.png");
            this->setFlippedX(false);
        }
    }
    else if (this->type == 2) {
        
        if (dir.x > 0) {
            this->setTexture("r_east.png");
            this->setFlippedX(false);
        }
        else {
            this->setTexture("r_west.png");
            this->setFlippedX(false);
        }
    
    }
    else if (this->type == 3) {

        if (dir.x > 0) {
            this->setTexture("blue_east.png");
            this->setFlippedX(false);
        }
        else {
            this->setTexture("blue_west.png");
            this->setFlippedX(false);
        }
    
    }
}


void Duck::updatePosition(float deltaTime) {
    if (stop) {
        return;
    }

    
    if (speed == 50.0f && rand() % 100 < changeDirectionProb) {
        randomizeDirection();
    }

    Vec2 current = this->getPosition();
    
    
    Vec2 targetDirection;
    if (isEscaping) {
        targetDirection = escapeDirection;
    }
    else {
        targetDirection = dir;
    }
    Vec2 smooth = dir.lerp(targetDirection, 0.1f);
    Vec2 toMove = smooth.getNormalized();
    
    float nX = current.x + (toMove.x * speed * deltaTime);
    float nY = current.y + (toMove.y * speed * deltaTime);

    Size visibleSize = Director::getInstance()->getVisibleSize();

    
    if (!isEscaping) {
        if (nX < 0 || nX > visibleSize.width) {
            dir.x *= -1;
            updateSpriteDirection();
            nX = current.x + (dir.x * speed * deltaTime);
        }
        if (nY < (visibleSize.height / 3.0f) || nY > visibleSize.height - 3.0f) {
            dir.y *= -1;
            nY = current.y + (dir.y * speed * deltaTime);
        }
    }

    
    if (isEscaping) {
        if (nX < -100 || nX > visibleSize.width + 100 || nY < -100 || nY > visibleSize.height + 100) {
            nextDuck = true;
            
            return;
        }
    }

    this->setPosition(nX, nY);
}

void Duck::mouseListener() {
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        if (mouseEvent) {
            Vec2 clickPos = mouseEvent->getLocationInView();

            
            if (this->getBoundingBox().containsPoint(clickPos)) {
                CCLOG("Duck clicked! Position: (%.2f, %.2f)", clickPos.x, clickPos.y);
                this->clicked();
            }
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}