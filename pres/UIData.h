#ifndef __UI_DATA_H__
#define __UI_DATA_H__

#include "cocos2d.h"

USING_NS_CC;
#define BTN_CALLBACK CC_CALLBACK_0

class UIData
{
public:
	UIData();
	Node* node;
	bool init(Node * node);

	void add(std::string name, Ref *r);
	Ref* get(std::string key);
	MenuItemImage* getButton(std::string key);
	std::string getKey(Ref* r);
	std::map<std::string, Ref*> ui;
};


#endif // !__UI_DATA_H__
