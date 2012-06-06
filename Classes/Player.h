/*
 * Player.h
 *
 *  Created on: 21/05/2012
 *      Author: VGroup
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "cocos2d.h"
#include "Car.h"

using namespace cocos2d;

class Player : public CCSprite, public CCAccelerometerDelegate {
public:
	int points;
	int maxScore;

	Player();
	virtual ~Player();

	virtual void onEnter();
	virtual void onExit();

	static Player* playerWithTexture(CCTexture2D* texture);
    virtual void didAccelerate(CCAcceleration* acceleration);
    CCRect rect();
    bool hitByCar(Car* car);
    void spin();
};

#endif /* PLAYER_H_ */
