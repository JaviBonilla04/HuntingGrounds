#ifndef __DUCK_H__
#define __DUCK_H__

#include "cocos2d.h"

USING_NS_CC;

class Duck : public cocos2d::Sprite {
public:

	CREATE_FUNC(Duck);

	Duck();
	virtual bool init() override;

	void update(float deltaTime) override;

	void clicked();

	bool vclickedNext() const;

	bool getNextDuck() const { return nextDuck; }

	void setScoreValue(int value);

	int getScoreValue() const;

	//void setSpeed(float speed);

	void setMaxSpeed(float maxSpeed);

	void setMinSpeed(float minSpeed);

	void setDirectionProb(float directionProb);

	void setType(int type);



private:

	float speed;

	float maxSpeed;
	float minSpeed;

	float angle;
	cocos2d::Vec2 dir;

	bool stop;
	bool nextDuck;

	void updatePosition(float deltaTime);
	void mouseListener();
	void startEscaping();
	void initializeEntry();
	void randomizeDirection();

	void updateSpriteDirection();

	float timeAlive;
	float escapeThreshold;
	bool isEscaping;
	cocos2d::Vec2 escapeDirection;

	int scoreValue;

	float changeDirectionProb;
	
	int type;
};

#endif
