#ifndef __UI_COMMANDER_H__
#define __UI_COMMANDER_H__

#include "cocos2d.h"

USING_NS_CC;
#define BTN_CALLBACK CC_CALLBACK_0


class UICommander
{
public:
	UICommander();
	Node* node;
	bool init(Node * node);
};


#endif // !__UI_COMMANDER_H__
