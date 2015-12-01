#ifndef _GAMESCENE_
#define _GAMESCENE_

#include "cocos2d.h"
#include "SpriteSystem.h"
#include "MagicSystem.h"


using namespace cocos2d;

class GameScene : public Layer
{
public:
	GameScene();
	~GameScene();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

	
private:
	SpriteSystem* spriteSystem;
	MagicSystem* magicSystem;

	void initMap();

};

#endif