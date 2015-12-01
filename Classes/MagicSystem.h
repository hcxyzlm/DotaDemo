#ifndef _MAGICSYSTEM_
#define _MAGICSYSTEM_

#include "cocos2d.h"
#include "Magic.h"
#include "Config.h"
USING_NS_CC;

class MagicSystem : public Layer
{
public:
	MagicSystem();
	~MagicSystem();

	virtual bool init();
	void initSprite();
	CREATE_FUNC(MagicSystem);

	//CC_SYNTHESIZE(Vector<BaseSprite*>, heroArray, HeroArray);
	//CC_SYNTHESIZE(Vector<BaseSprite*>, enemyArray, EnemyArray);

	

private:
	Magic* mg1;


};

#endif