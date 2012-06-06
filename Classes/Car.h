/*
 * Car.h
 *
 *  Created on: 22/05/2012
 *      Author: VGames
 */

#ifndef CAR_H_
#define CAR_H_

#include "cocos2d.h"

using namespace cocos2d;

class Car : public CCSprite {
public:
	Car();
	virtual ~Car();

	static Car* carWithTexture(CCTexture2D* texture);
	void setRandomPosition();
	CCFiniteTimeAction* setRandomSpeed();
	CCRect rect();
};

#endif /* CAR_H_ */
