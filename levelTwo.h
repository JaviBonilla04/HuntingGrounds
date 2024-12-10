#ifndef __LEVEL_TWO_H__
#define __LEVEL_TWO_H__

#include "cocos2d.h"
#include "Duck.h"


class levelTwo : public cocos2d::Scene {

public:
	levelTwo();
	~levelTwo();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(levelTwo);

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


#endif // !__MAIN_MENU_H__

