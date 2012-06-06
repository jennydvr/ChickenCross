#include "AppDelegate.h"

#include "cocos2d.h"
#include "Controller.h"
#include "CCEGLView.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::initInstance() {
	bool bRet = false;
	do {
		CCEGLView * pMainWnd = new CCEGLView();
		CC_BREAK_IF(! pMainWnd|| ! pMainWnd->Create(1024, 600));
		CCFileUtils::setResourcePath("app/native/Resources");
		bRet = true;
	} while (0);
	return bRet;
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();

	pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

	// enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);

	// turn on display FPS
	pDirector->setDisplayFPS(true);

	// pDirector->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	// Create a scene
    CCScene * pScene = CCScene::node();
    CCLayer * pLayer = new Controller();
    pLayer->autorelease();

    pScene->addChild(pLayer);
	pDirector->runWithScene(pScene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->pause();

	// if you use SimpleAudioEngine, it must be pause
//	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	CCDirector::sharedDirector()->resume();

	// if you use SimpleAudioEngine, it must resume here
//	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
