#include "UIData.h"

typedef std::map<std::string, Ref*>::iterator UIData_ItorType;

bool UIData::init(Node *node)
{
	this->node = node;
	return true;
}

UIData::UIData()
{

}

void UIData::add(std::string name, Ref *r)
{
	if (r)
	{
		ui[name] = r;
	}
}

std::string UIData::getKey(Ref* r)
{
	for (UIData_ItorType it = ui.begin(); it != ui.end();it++)
	{
		if (r == it->second)
		{
			return it->first;
		}
	}

	std::string ret;
	return ret;
}

Ref* UIData::get(std::string key)
{
	if (!(key.empty()))
	{
		return ui[key];
	}
}

MenuItemImage* UIData::getButton(std::string key)
{
	Ref* ret = get(key);
	return (MenuItemImage*)(ret);
}