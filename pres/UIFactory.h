#ifndef __UI_FACTORY_H__
#define __UI_FACTORY_H__

#include "cocos2d.h"
#include "UIData.h"


USING_NS_CC;
#define BTN_CALLBACK(FUN) CC_CALLBACK_0(FUN,&presentor)

class UIFactory : public Ref
{
public:
	bool init();
	UIFactory(UIData* d);
	void setUIData(UIData* d);
	UIData* getUIData();

	UIData* data;
	Node * name(const std::string& name, Node * node);
	MenuItemImage* createButton(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, int zorder = 1);
	MenuItemImage* createButton(const std::string& name, const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, int zorder = 1);
	Menu * createMenu(const std::string &name, int zorder, MenuItem* item, ...);
	Menu * createMenu(int zorder, MenuItem* item, ...);
	Sprite* createSprite(const std::string& name, const std::string& filename, int zorder = 1);
	Sprite* createSprite(const std::string& filename);
	Sprite* createSpriteWithSpriteFrameName(const std::string& name, const std::string& spriteFrameName, int zorder = 1);
	Sprite* createSpriteWithSpriteFrameName(const std::string& spriteFrameName);



	Layer * createLayer();
	Layer * createLayer(const std::string& name, int zorder = 1);

	MenuItemImage* enableButton(const std::string& name);
	MenuItemImage* enableButton(MenuItem* node);
	MenuItemImage* disableButton(const std::string& name);
	MenuItemImage* disableButton(MenuItem* node);



	Node  * offset(Node* node, int x, int y = 0);
	Node  * alignCenter(Node* node, Node * parent = NULL);
	Node  * alignCorner(Node* node, float mode, Vec2 size, float offsetPercentX, float offsetPercentY);

	Node  * show(Node* node);
	Node  * hide(Node* node);

	void show(Node * item, ...);
	void hide(Node * item, ...);

	Node  * printPos(Node* node);

};






#endif // !__UI_FACTORY_H__
