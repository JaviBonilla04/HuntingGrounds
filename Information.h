#ifndef __INFORMATION_H__
#define __INFORMATION_H__

#include "cocos2d.h"

class Information : public cocos2d::Scene {

public:
	Information();
	~Information();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Information);




};


#endif
