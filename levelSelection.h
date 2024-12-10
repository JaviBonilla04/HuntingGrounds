#ifndef __LEVEL_SELECTION_H__
#define __LEVEL_SELECTION_H__

#include "cocos2d.h"

class levelSelection : public cocos2d::Scene {

public:
	levelSelection();
	~levelSelection();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(levelSelection);



};


#endif