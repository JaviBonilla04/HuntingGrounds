#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__	

#include "cocos2d.h"
#include "Duck.h"
#include <vector>


class MainMenu : public cocos2d::Scene {

public:
	MainMenu();
	~MainMenu();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainMenu);

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

#endif#pragma once
