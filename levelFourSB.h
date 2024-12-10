#ifndef __LEVEL_FOUR_SB_H__
#define __LEVEL_FOUR_SB_H__
#include "cocos2d.h"

class levelFourSB : public cocos2d::Scene {

public:
	levelFourSB(int score, int achieved, int total);
	~levelFourSB();

	static levelFourSB* createScene(int score, int achieved, int total);

	bool init(int score, int achieved, int total);

	void toMenu(cocos2d::Ref* send);

private:
	int score;
	int achieved;
	int total;


};

#endif // !__LEVEL_FOUR_SB_H__