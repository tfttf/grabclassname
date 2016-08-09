#include "StatusHelper.h"

void StatusHelper::writeBool(std::string key, bool b)
{
	UserDefault::sharedUserDefault()->setBoolForKey(key.c_str(), b);
}

bool StatusHelper::readBool(std::string key, bool b)
{
	return UserDefault::sharedUserDefault()->getBoolForKey(key.c_str());
}
