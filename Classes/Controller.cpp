/*
 * Controller.cpp
 *
 *  Created on: 21/05/2012
 *      Author: VGroup
 */

#include "Controller.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Controller::Controller() {
	dotty = new Player();
}

Controller::~Controller() {
	dotty->~Player();
	paper->release();
	SimpleAudioEngine::sharedEngine()->end();
}

std::string Controller::setMaxScore() {
	stringstream ss;
    ss << "Max Score = ";
    ss << dotty->maxScore;
    return ss.str();
}

std::string Controller::setScore() {
	stringstream ss;
    ss << "Score = ";
    ss << dotty->points;
    return ss.str();
}

void Controller::loadBackground() {
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	// Load texture
    paper = CCSprite::spriteWithFile("paper.png");
    paper->setPosition(ccp(s.width / 2, s.height / 2));

    // Add to layer
    addChild(paper);
    paper->retain();
}

void Controller::onEnter() {
	CCLayer::onEnter();

	CCSize s = CCDirector::sharedDirector()->getWinSize();

	// Place the score
	score = CCLabelTTF::labelWithString(setScore().c_str(), "Arial", 32);
	score->setPosition(CCPointMake(s.width / 2, s.height - 50));
	score->setColor(ccc3(0,0,0));
	addChild(score, 1);

	// Place the max score
	maxScore = CCLabelTTF::labelWithString(setMaxScore().c_str(), "Arial", 32);
	maxScore->setPosition(CCPointMake(125, s.height - 50));
	maxScore->setColor(ccc3(0,0,0));
	addChild(maxScore, 1);

	// Add background
	loadBackground();

	// Add character
	CCTexture2D* playerTexture = CCTextureCache::sharedTextureCache()->addImage("Dotty1.png");

	dotty = Player::playerWithTexture(playerTexture);
	dotty->setPosition(CCPointMake(s.width / 2, s.height / 2));
	addChild(dotty);
	dotty->retain();

	// Add cars
	cars = new CCMutableArray<CCObject *>();

	schedule(schedule_selector(Controller::addCar), 0.5f);
	schedule(schedule_selector(Controller::gameLogic));
	schedule(schedule_selector(Controller::addPoints), 1);

	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic( CCFileUtils::fullPathFromRelativePath("song.ogg") );
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(std::string(CCFileUtils::fullPathFromRelativePath("song.ogg")).c_str(), true);
}

void Controller::gameLogic(ccTime delta) {
	bool hit = false;

	Car* car;
    CCMutableArray<CCObject *>::CCMutableArrayIterator it;

	for (it = cars->begin(); it != cars->end(); it++) {
		car = (Car*)(*it);

		if (!car)
			break;

		if (dotty->hitByCar(car)) {
			hit = true;
			break;
		}
	}

	if (hit) {
	    dotty->points -= 1;

	    if (dotty->points <= 0) {
			CCSize s = CCDirector::sharedDirector()->getWinSize();
			dotty->setPosition(CCPointMake(s.width / 2, s.height / 2));
			dotty->points = 0;
	    }

		// Make dotty spin
	    dotty->spin();
	}

	score->setString(setScore().c_str());
	maxScore->setString(setMaxScore().c_str());
}

void Controller::addCar(ccTime delta) {
	// Create a new car
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("obstacle.png");
	Car* target = Car::carWithTexture(texture);

	// Set for it a random position
	target->setRandomPosition();
    addChild(target);

    // Create the actions
    CCFiniteTimeAction* actionMove = target->setRandomSpeed();
    CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Controller::spriteMoveFinished));
    target->runAction(CCSequence::actions(actionMove, actionMoveDone, NULL));

    // Add to cars list
    cars->addObject(target);
}

void Controller::addPoints(ccTime delta) {
	dotty->points += 5;

	if (dotty->points > dotty->maxScore)
		dotty->maxScore = dotty->points;
}

void Controller::spriteMoveFinished(CCNode* sender) {
	this->removeChild(sender, true);
	cars->removeObject(sender, true);
}
