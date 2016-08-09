#include "StartScene.h"
#include <iostream>
#include <map>
#include <list>
using namespace std;
#include "UIFactory.h"
#include "StatusHelper.h"


CCScene * StartScene::scene()
{
	CCScene * ret = CCScene::create();
	StartScene* l = StartScene::create();
	ret->addChild(l);
	return ret;
}

bool StartScene::init()
{
	bool initSuccess = false;
	do{
		Layer::init();
		uidata.init(this);
		presentor.init(this);
		behavior.init(this);

		UIFactory uif(&uidata);
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto bg			 = uif.createSprite("ss_img_bg",		"ss_img_bg.jpg")->addTo(this);
		auto btnPlay     = uif.createButton("ss_btn_play",		"ss_btn_play.png",		"ss_btn_play.png",		BTN_CALLBACK(StartScene::Presentor::onBtnPlay));
		auto btnMusicOn  = uif.createButton("ss_btn_music_on",	"ss_btn_music_on.png",	"ss_btn_music_on.png",	BTN_CALLBACK(StartScene::Presentor::onBtnMusicOn));
		auto btnMusicOff = uif.createButton("ss_btn_music_off", "ss_btn_music_off.png", "ss_btn_music_off.png", BTN_CALLBACK(StartScene::Presentor::onBtnMusicOff));
		auto btnSoundOn  = uif.createButton("ss_btn_sound_on",	"ss_btn_sound_on.png",	"ss_btn_sound_on.png",	BTN_CALLBACK(StartScene::Presentor::onBtnSoundOn));
		auto btnSoundOff = uif.createButton("ss_btn_sound_off", "ss_btn_sound_off.png", "ss_btn_sound_off.png", BTN_CALLBACK(StartScene::Presentor::onBtnSoundOff));
		auto btnHelp     = uif.createButton("ss_btn_help",		"ss_btn_help.png",		"ss_btn_help.png",		BTN_CALLBACK(StartScene::Presentor::onBtnHelp));

		uif.createMenu(1, btnPlay, btnMusicOn, btnMusicOff, btnSoundOn, btnSoundOff, btnHelp, NULL)->addTo(this);
		uif.alignCenter(bg,this);

		bg			->alignCorner( -1, visibleSize,  0, 0);
		btnPlay		->alignCorner( -1, visibleSize,  0, -0.75);
		btnMusicOn  ->alignCorner(7.5, visibleSize,  1, 1);
		btnMusicOff	->alignCorner(7.5, visibleSize,  1, 1);
		btnSoundOn	->alignCorner(	6, visibleSize,  0, 1);
		btnSoundOff	->alignCorner(	6, visibleSize,  0, 1);
		btnHelp		->alignCorner(4.5, visibleSize, -1, 1);

		uif.hide(btnMusicOff, btnSoundOff, NULL);

	} while (0);

	return true;
}

StartScene::Behavior* StartScene::getBehavior()
{
	return &behavior;
}

StartScene::Presentor* StartScene::getPresentor()
{
	return &presentor;
}

void StartScene::Presentor::init(StartScene * scene)
{
	this->scene = scene;
}

StartScene * StartScene::Presentor::getScene()
{
	return this->scene;
}

StartScene::Behavior * StartScene::Presentor::getBehavior()
{
	return this->scene->getBehavior();
}

void StartScene::Presentor::checkStatus()
{

}

void StartScene::Presentor::onBtnPlay()
{

}

void StartScene::Presentor::onBtnMusicOn()
{
	getBehavior()->showMusicOff();
	StatusHelper::writeBool("GAME_STATUS_MUSIC_ISPLAYING", true);
}

void StartScene::Presentor::onBtnMusicOff()
{
	getBehavior()->showMusicOn();
}

void StartScene::Presentor::onBtnSoundOn()
{
	getBehavior()->showSoundOff();
}

void StartScene::Presentor::onBtnSoundOff()
{
	getBehavior()->showSoundOn();
}

void StartScene::Presentor::onBtnHelp()
{
	
}

void StartScene::Behavior::init(StartScene * scene)
{
	this->scene = scene;
}


void StartScene::Behavior::showReset()
{
	showMusicOn();
	showSoundOn();
}

/*
auto bg			 = uif.createSprite("ss_img_bg",		"ss_img_bg.jpg")->addTo(this);
auto btnPlay     = uif.createButton("ss_btn_play",		"ss_btn_play.png",		"ss_btn_play.png",		BTN_CALLBACK(StartScene::btnPlay ));
auto btnMusicOn  = uif.createButton("ss_btn_music_on",	"ss_btn_music_on.png",	"ss_btn_music_on.png",	BTN_CALLBACK(StartScene::btnMusic));
auto btnMusicOff = uif.createButton("ss_btn_music_off", "ss_btn_music_off.png", "ss_btn_music_off.png", BTN_CALLBACK(StartScene::btnMusic));
auto btnSoundOn  = uif.createButton("ss_btn_sound_on",	"ss_btn_sound_on.png",	"ss_btn_sound_on.png",	BTN_CALLBACK(StartScene::btnSound));
auto btnSoundOff = uif.createButton("ss_btn_sound_off", "ss_btn_sound_off.png", "ss_btn_sound_off.png", BTN_CALLBACK(StartScene::btnSound));
auto btnHelp     = uif.createButton("ss_btn_help",		"ss_btn_help.png",		"ss_btn_help.png",		BTN_CALLBACK(StartScene::btnHelp ));
*/
void StartScene::Behavior::showMusicOn()
{
	this->scene->uidata.getButton("ss_btn_music_on")->show();
	this->scene->uidata.getButton("ss_btn_music_off")->hide();
}

void StartScene::Behavior::showMusicOff()
{
	this->scene->uidata.getButton("ss_btn_music_on")->hide();
	this->scene->uidata.getButton("ss_btn_music_off")->show();
}

void StartScene::Behavior::showSoundOn()
{
	this->scene->uidata.getButton("ss_btn_sound_on")->show();
	this->scene->uidata.getButton("ss_btn_sound_off")->hide();
}

void StartScene::Behavior::showSoundOff()
{
	this->scene->uidata.getButton("ss_btn_sound_on")->hide();
	this->scene->uidata.getButton("ss_btn_sound_off")->show();
}