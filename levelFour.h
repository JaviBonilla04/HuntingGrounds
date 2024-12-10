#ifndef __LEVEL_FOUR_H__
#define __LEVEL_FOUR_H__

#include "cocos2d.h"
#include "Duck.h"


class levelFour : public cocos2d::Scene {

public:
	levelFour();
	~levelFour();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(levelFour);

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
