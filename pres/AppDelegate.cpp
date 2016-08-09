#include "AppDelegate.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"



USING_NS_CC;

void _p(String s)
{
	CCLog("%s", s.getCString());
}

void CCLogError(const char * pszFormat, ...)
{
	char buf[1000]="";

	va_list args;
	va_start(args, pszFormat);
	vsprintf(buf, pszFormat, args);
	va_end(args);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	__android_log_print(ANDROID_LOG_ERROR, "cocos2d-x debug info", buf);
#endif
}
 
AppDelegate::AppDelegate() {

	/*
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	const char* str = TDCCTalkingDataGA::getDeviceId();
	TDCCAccount::setAccount(str);
	#endif
	*/

}



AppDelegate::~AppDelegate()
{
    // end simple audio engine here, or it may crashed on win32
    SimpleAudioEngine::sharedEngine()->end();
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director

    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

	glview->setDesignResolutionSize(720,1280,ResolutionPolicy::EXACT_FIT);

	//director->setContentScaleFactor(16.0/12.0);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object


    auto scene = HelloWorld::createScene();

    // run
	director->runWithScene(scene);



	
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here

	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

}

