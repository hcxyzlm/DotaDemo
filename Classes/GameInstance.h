#ifndef _GAMEINSTANCE_
#define _GAMEINSTANCE_
#include "cocos2d.h"
#include "json/document.h"
#include "sqlite3.h"
#include <vector>
#include <string>
using namespace cocos2d;
#include "Config.h"

class GameInstance
{
public:
	GameInstance();
	~GameInstance();
	static GameInstance* getInstance();
	Animate* setAnimate(const char* frameName, int frameCount, int fps, bool restore = true,int times =1);

	//void readJson(_stSpriteConfig (&spConf)[6]);
	//用于技能
	std::string getMagicName(MagicId id);
	int getMagicNum(MagicId id);
	//用于精灵
	std::string getSpriteName(SpriteId id);
	std::string getStateName(SpriteId id, SpriteState state);
	std::string getAttackName(MagicId magicId);

	int heroNum;
	int enemyNum;
	bool spSel[6];
	bool isWin;
	bool isGameOver;
};


#endif 
