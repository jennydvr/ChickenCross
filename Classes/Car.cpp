/*
 * Car.cpp
 *
 *  Created on: 22/05/2012
 *      Author: VGames
 */

#include "Car.h"

Car::Car() {
}

Car::~Car() {
}

Car* Car::carWithTexture(CCTexture2D* texture) {
	Car* car = new Car();
	car->initWithTexture(texture);
	car->autorelease();

	return car;
}

void Car::setRandomPosition() {
    // Determine where to spawn the target along the X axis
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    int minX = getContentSize().width / 2;
    int maxX = winSize.width - getContentSize().width / 2;
    int rangeX = maxX - minX;
    int actualX = (rand() % rangeX) + minX;

    // Create the target slightly off-screen along the right edge
    setPosition(ccp(actualX, winSize.height + (getContentSize().height / 2)));
}

CCFiniteTimeAction* Car::setRandomSpeed() {
    // Determine a random speed
    int minDuration = (int)1.5;
    int maxDuration = (int)4.0;
    int rangeDuration = maxDuration - minDuration;
    int actualDuration = (rand() % rangeDuration) + minDuration;

    return CCMoveTo::actionWithDuration((ccTime)actualDuration, ccp(getPositionX(), 0 - getContentSize().height / 2));
}

CCRect Car::rect()
{
	CCSize s = getTexture()->getContentSize();
	CCRect rect = CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
	rect.origin.x += getPosition().x;
	rect.origin.y += getPosition().y;

	return rect;
}
