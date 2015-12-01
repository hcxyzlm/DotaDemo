#ifndef _MAGIC_
#define _MAGIC_

#include "cocos2d.h"
#include "Config.h"
USING_NS_CC;

class Magic : public Sprite
{
public:
	Magic();
	~Magic();

	CC_SYNTHESIZE_RETAIN(Action*, magicAction, MagicAction);

	static Magic* create(_stMagicConfig magConfig);
	void startMagic(int fps, int Times);
	void move(Point endPoint, int duration, float speed);

	
private:
	int magicFps;
	int magicTimes;
	void setMagic();
	void startMagicCallback();

	CC_SYNTHESIZE(_stMagicConfig, magicConf, magicConf);
};

#endif