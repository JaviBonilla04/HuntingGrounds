#ifndef __LEVEL_TWO_SB_H__
#define __LEVEL_TWO_SB_H__
#include "cocos2d.h"

class levelTwoSB : public cocos2d::Scene {

public:
	levelTwoSB(int score, int achieved, int total);
	~levelTwoSB();

	static levelTwoSB* createScene(int score, int achieve, int total);

	bool init(int score, int achieved, int total);

	void toMenu(cocos2d::Ref* send);

private:
	int score;
	int achieved;
	int total;


};

#endif // !__LEVEL_TWO_SB_H__
