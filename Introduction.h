#ifndef __INTRODUCTION_H__
#define __INTRODUCTION_H__

#include "cocos2d.h"

class Introduction : public cocos2d::Scene {

public:
	Introduction();
	~Introduction();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Introduction);




};


#endif
