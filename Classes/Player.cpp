/*
 * Player.cpp
 *
 *  Created on: 21/05/2012
 *      Author: VGroup
 */

#include "Player.h"

#define FIX_POS(_pos, _min, _max) \
    if (_pos < _min)        \
    _pos = _min;        \
else if (_pos > _max)   \
    _pos = _max;        \

Player::Player() {
	points = 0;
	maxScore = 0;
}

Player::~Player() {
}

void Player::onEnter()
{
    CCAccelerometer::sharedAccelerometer()->setDelegate(this);
	CCSprite::onEnter();
}

void Player::onExit()
{
	CCSprite::onExit();
}

Player* Player::playerWithTexture(CCTexture2D* texture) {
	Player* player = new Player();
	player->initWithTexture(texture);
	player->autorelease();

	return player;
}

void Player::didAccelerate(CCAcceleration* acceleration) {
	// Get window size
    CCDirector* pDir = CCDirector::sharedDirector();
    CCSize winSize   = pDir->getWinSize();
    CCSize size  = getContentSize();

    // Get current position
    CCPoint ptNow  = getPosition();
    CCPoint ptTemp = pDir->convertToUI(ptNow);

    // Calculate acceleration
    ptTemp.x += acceleration->x * 9.81f;
    ptTemp.y -= acceleration->y * 9.81f;

    // Calculate new position. Don't let the sprite go out of the window
    CCPoint ptNext = pDir->convertToGL(ptTemp);
    FIX_POS(ptNext.x, (size.width / 2.0), (winSize.width - size.width / 2.0));
    FIX_POS(ptNext.y, (size.height / 2.0), (winSize.height - size.height / 2.0));
    setPosition(ptNext);
}

bool Player::hitByCar(Car* car) {
	return CCRect::CCRectIntersectsRect(car->rect(), rect());
}

CCRect Player::rect() {
	CCSize s = getTexture()->getContentSize();
	CCRect rect = CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
	rect.origin.x += getPosition().x;
	rect.origin.y += getPosition().y;

	return rect;
}

void Player::spin() {
    CCActionInterval* actionBy = CCRotateBy::actionWithDuration(0.5f, 360);
    CCActionInterval* actionByBack = actionBy->reverse();
    runAction(CCSequence::actions(actionBy, actionByBack, NULL));
}
