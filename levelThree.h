#ifndef __LEVEL_THREE_H__
#define __LEVEL_THREE_H__

#include "cocos2d.h"
#include "Duck.h"


class levelThree : public cocos2d::Scene {

public:
	levelThree();
	~levelThree();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(levelThree);

private:
	Duck* duck;
	int currentDuckIndex;
	cocos2d::Vector<Duck*> ducks;
	int numBullets;
	std::vector<Sprite*> indicators;
	Label* bulletCount;
	Label* scoreLabel;
	int score = 0;
	int achieved = 0;
	int total;


};


#endif // !__LEVEL_THREE_H__
