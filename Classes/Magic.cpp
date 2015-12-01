#include "Magic.h"
#include "sqlite3.h"
#include "GameInstance.h"
Magic::Magic():
	magicAction(nullptr)
{

}

Magic::~Magic()
{
	//CC_SAFE_RELEASE_NULL(magicAction);
}

Magic* Magic::create(_stMagicConfig magConfig)
{
	Magic*  sprite = new Magic();

	sprite->magicConf = magConfig;

	std::string spriteName = GameInstance::getInstance()->getMagicName(sprite->magicConf.id);

	spriteName += "_001.png";

	auto spriteFrame = SpriteFrameCache::getInstance()->spriteFrameByName(spriteName);

	if (spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
	{
		sprite->autorelease();
		return sprite;
	}
	else
	{
		delete sprite;
		sprite = NULL;
		return NULL;
	}
	return NULL;
}

void Magic::setMagic()
{
	std::string str;
	str = this->magicConf.name;
	str += "_%03d.png";
	this->magicAction = GameInstance::getInstance()->setAnimate(str.c_str(), this->magicConf.count, this->magicFps, false, this->magicTimes);
}
void Magic::startMagic(int fps, int times)
{
	this->magicFps = fps;
	this->magicTimes = times;
	this->setMagic();
	Animate* tmp = (Animate*)this->magicAction;
	auto callfunc = CallFunc::create(CC_CALLBACK_0(Magic::startMagicCallback, this));

	auto sequence = Sequence::create(tmp, callfunc, NULL);

	this->runAction(sequence);
}

void Magic::startMagicCallback()
{
	this->setVisible(false);
}

void Magic::move(Point endPoint, int duration, float speed)
{
	float s= ccpDistance(this->getPosition(), endPoint);

	auto move = MoveTo::create(s/speed,endPoint);
	this->runAction(move);
}