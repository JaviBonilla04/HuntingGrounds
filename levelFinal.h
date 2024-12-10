#ifndef __LEVEL_FINAL_H__
#define __LEVEL_FINAL_H__

#include "cocos2d.h"
#include "Duck.h"


class levelFinal : public cocos2d::Scene {

public:
	levelFinal();
	~levelFinal();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(levelFinal);

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
