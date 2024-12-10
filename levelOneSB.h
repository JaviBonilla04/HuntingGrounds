#ifndef __LEVEL_ONE_SB_H__
#define __LEVEL_ONE_SB_H__
#include "cocos2d.h"

class levelOneSB : public cocos2d::Scene {

public:
	levelOneSB(int score, int achieved, int total);
	~levelOneSB();

	static levelOneSB* createScene(int score, int achieved, int total);

	bool init(int score, int achieved, int total);

	void toMenu(cocos2d::Ref* send);

private:
	int score;
	int achieved;
	int total;


};

#endif // !__LEVEL_ONE_SB_H__
