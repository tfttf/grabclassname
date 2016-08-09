#include "UIFactory.h"

UIFactory::UIFactory(UIData* d)
{
	data = d;
}

bool UIFactory::init()
{
	return true;
}

Node * UIFactory::name(const std::string& name, Node * node)
{
	node->setName(name);
	return node;
}

Layer * UIFactory::createLayer()
{
	return Layer::create();
}

Layer * UIFactory::createLayer(const std::string& name, int zorder)
{
	Layer* ret = Layer::create();
	UIFactory::name(name, ret);
	ret->setZOrder(zorder);
	return ret;
}

Sprite* UIFactory::createSprite(const std::string& name, const std::string& filename, int zorder)
{
	Sprite *ret = Sprite::create(filename);
	UIFactory::name(name, ret);
	data->add(name, ret);
	ret->setZOrder(zorder);
	return ret;
}

Sprite* UIFactory::createSprite(const std::string& filename)
{
	return Sprite::create(filename);
}

Sprite* UIFactory::createSpriteWithSpriteFrameName(const std::string& name, const std::string& spriteFrameName, int zorder)
{
	auto ret = Sprite::createWithSpriteFrameName(spriteFrameName);
	UIFactory::name(name, ret);
	data->add(name, ret);
	ret->setZOrder(zorder);
	return ret;
}

Sprite* UIFactory::createSpriteWithSpriteFrameName(const std::string& spriteFrameName)
{
	return Sprite::createWithSpriteFrameName(spriteFrameName);
}


MenuItemImage* UIFactory::createButton(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, int zorder)
{
	MenuItemImage* ret = MenuItemImage::create(normalImage, selectedImage, "", callback);
	ret->setZOrder(zorder);
	return ret;
}

MenuItemImage* UIFactory::createButton(const std::string& name, const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback,int zorder)
{
	MenuItemImage * ret = MenuItemImage::create(normalImage, selectedImage, "", callback);
	UIFactory::name( name, ret);
	data->add(name, ret);
	ret->setZOrder(zorder);
	return ret;
}

Menu * UIFactory::createMenu(const std::string& name, int zorder, MenuItem* item, ...)
{
	va_list args;
	va_start(args, item);

	Menu *ret = Menu::createWithItems(item, args);
	//初始化成功之后，设置所有MenuItem为新的行为模式
	ret->setTouchMoveEnable(false);
	va_end(args);

	UIFactory::name(name, ret);
	data->add(name, ret);
	ret->setZOrder(zorder);
	return ret;
}

Menu * UIFactory::createMenu(int zorder, MenuItem* item, ...)
{
	va_list args;
	va_start(args, item);

	Menu *ret = Menu::createWithItems(item, args);
	//初始化成功之后，设置所有MenuItem为新的行为模式
	ret->setTouchMoveEnable(false);
	va_end(args);
	ret->setZOrder(zorder);

	return ret;
}


MenuItemImage* UIFactory::enableButton(const std::string& name)
{
	MenuItemImage * ret = data->getButton(name);
	ret->setEnabled(true);
	return ret;
}

MenuItemImage* UIFactory::enableButton(MenuItem* node)
{
	node->setEnabled(true);
	return (MenuItemImage*)(node);
}

MenuItemImage* UIFactory::disableButton(const std::string& name)
{
	MenuItemImage * ret = data->getButton(name);
	ret->setEnabled(false);
	return ret;
}

MenuItemImage* UIFactory::disableButton(MenuItem* node)
{
	node->setEnabled(false);
	return (MenuItemImage*)(node);
}



Node * UIFactory::alignCenter(Node* node, Node * parent)
{
	node->ignoreAnchorPointForPosition(true);
	if (parent)
	{
		Rect r = parent->getBoundingBox();
		node->setAnchorPoint(ccp(0.5, 0.5));
		node->setPosition(ccp(r.size.width / 2, r.size.height / 2));
	}
	else
	{
		Size r = Director::getInstance()->getVisibleSize();
		node->setAnchorPoint(ccp(0.5, 0.5));
		node->setPosition(ccp(r.width / 2, r.height / 2));
	}
	return node;
}

Node* UIFactory::alignCorner(Node* node, float mode, Vec2 size, float offsetPercentX, float offsetPercentY){
	if (mode == 0){
		size.x = 0;
		size.y *= 0.5;
	}
	else if (mode == 1.5){
		size.x *= 0.5;
		size.y *= 0.5;
	}
	else if (mode == 3){
		size.x *= 0.5;
		size.y = 0;
	}
	else if (mode == 4.5){
		size.x *= -0.5;
		size.y = 0.5;
	}
	else if (mode == 6){
		size.x = 0;
		size.y *= -0.5;
	}
	else if (mode == 7.5){
		size.x *= -0.5;
		size.y *= -0.5;
	}
	else if (mode == 9){
		size.x *= -0.5;
		size.y *= 0;
	}
	else if (mode == 10.5){
		size.x *= -0.5;
		size.y *= 0.5;
	}
	else if (mode == -1){
		size.x = 0;
		size.y = 0;
	}

	node->setPosition(size);
	Vec2 box = node->getBoundingBox().size;
	int w = box.x;
	int h = box.y;
	node->offset(w*offsetPercentX, h*offsetPercentY);
	return node;
}


Node * UIFactory::offset(Node* node, int x, int y)
{
	Vec2 p = node->getPosition();
	p.x += x;
	p.y += y;
	node->setPosition(p);
	return node;
}


void UIFactory::setUIData(UIData* d)
{
	data = d;
}

UIData* UIFactory::getUIData()
{
	return data;
}

Node  * UIFactory::show(Node* node)
{
	node->setVisible(true);
	return node;
}

Node  * UIFactory::hide(Node* node)
{
	node->setVisible(false);
	return node;
}

void UIFactory::show(Node * item, ...){
	va_list args;
	va_start(args, item);
	item->setVisible(true);
	if (item)
	{
		Node *i = va_arg(args, Node*);
		item->setVisible(true);
		while (i)
		{
			i->setVisible(true);
			i = va_arg(args, Node*);
		}
	}
	va_end(args);
}

void UIFactory::hide(Node * item, ...){
	va_list args;
	va_start(args, item);
	if (item)
	{
		Node *i = va_arg(args, Node*);
		item->setVisible(false);
		while (i)
		{
			i->setVisible(false);
			i = va_arg(args, Node*);
		}
	}
	va_end(args);
}

Node* UIFactory::printPos(Node* node)
{
	Vec2 pos = node->getPosition();
	CCLog("%s:%f,%f", node->getName().c_str(), pos.x, pos.y);
	return node;
}
