#ifndef __STATUS_HELPER_H__
#define __STATUS_HELPER_H__

#include "cocos2d.h"

USING_NS_CC;

class StatusHelper
{
public:
	StatusHelper();
	static void writeBool(std::string key, bool value);
	static bool readBool(std::string key, bool b);
};


#endif // !__STATUS_HELPR_H__
