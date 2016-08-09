#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "UIFactory.h"


USING_NS_CC;

class StartScene : public cocos2d::Layer
{
public:

	static CCScene * scene();
	bool init();
	CREATE_FUNC(StartScene);


	class Behavior : public Ref
	{
	public:
		void init(StartScene * scene);
		StartScene * scene;
		void showReset();
		void showMusicOn();
		void showMusicOff();
		void showSoundOn();
		void showSoundOff();
	};


	class Presentor : public Ref
	{
	public:
		void init(StartScene * scene);
		StartScene * scene;
		StartScene * getScene();
		StartScene::Behavior * getBehavior();

		void checkStatus();
		void onBtnPlay();
		void onBtnMusicOn();
		void onBtnMusicOff();
		void onBtnSoundOn();
		void onBtnSoundOff();
		void onBtnHelp();
	};



public:
	UIData uidata;
	StartScene::Presentor presentor;
	StartScene::Behavior behavior;
	
	StartScene::Behavior* getBehavior();
	StartScene::Presentor* getPresentor();


private:


};


#endif // !__START_SCENE_H__
