#ifndef __LEVEL_THREE_SB_H__
#define __LEVEL_THREE_SB_H__
#include "cocos2d.h"

class levelThreeSB : public cocos2d::Scene {

public:
	levelThreeSB(int score, int achieved, int total);
	~levelThreeSB();

	static levelThreeSB* createScene(int score, int achieved, int total);

	bool init(int score, int achieved, int total);

	void toMenu(cocos2d::Ref* send);

private:
	int score;
	int achieved;
	int total;


};

#endif // !__LEVEL_TWO_SB_H__