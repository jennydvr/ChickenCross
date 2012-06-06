/*
 * Controller.h
 *
 *  Created on: 21/05/2012
 *      Author: VGroup
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "cocos2d.h"
#include "Player.h"
#include "Car.h"
#include <sstream>

using namespace cocos2d;

class Controller : public CCLayer {
protected:
	CCLabelTTF* score;
	CCLabelTTF* maxScore;
    CCSprite *paper;
    Player *dotty;
	CCMutableArray<CCObject *> *cars;

    double m_fLastTime;

    void loadBackground();
	void spriteMoveFinished(CCNode* sender);
	std::string setMaxScore();
	std::string setScore();

public:
	Controller();
	virtual ~Controller();

	virtual void onEnter();

	void gameLogic(ccTime delta);
	void addCar(ccTime delta);
	void addPoints(ccTime delta);
};

#endif /* CONTROLLER_H_ */
