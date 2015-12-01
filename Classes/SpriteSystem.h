#ifndef _SPRITESYSTEM_
#define _SPRITESYSTEM_

#include "cocos2d.h"
#include "BaseSprite.h"
#include "Config.h"
#include <vector>

USING_NS_CC;

class SpriteSystem : public Layer
{
public:
	SpriteSystem();
	~SpriteSystem();

	virtual bool init();
	
	CREATE_FUNC(SpriteSystem);

	void spAttackSchedule(float dt);

	/*void sp1attackSchedule(float dt);
	void sp2attackSchedule(float dt);
	void sp3attackSchedule(float dt);
	void sp4attackSchedule(float dt);
	void sp5attackSchedule(float dt);
	void sp6attackSchedule(float dt);*/

	void magicMoveCallback(Node* node, BaseSprite* sp);
	void showLife(BaseSprite* sp);
	//float attack(BaseSprite* sp1, BaseSprite* sp2);

private:
	BaseSprite* m_bsSp[6];

	MenuItemSprite* m_itItem[3];

	ProgressTimer* m_ptLife[3];
	ProgressTimer* m_ptPower[3];

	float m_fOldScheTime[6];
	float m_fScheduleTime[6];


	bool m_bIsAttack;
	float m_fElapseTime;
	float m_fOverTime;
	_stSpriteConfig spConf[6];
	_stMagicConfig magConf[11];





	std::vector<bool> heroArray;
	std::vector<bool> enemyArray;

	void initSprite();
	void readJson(_stSpriteConfig (&spConf)[6]);
	void readMagicJson(_stMagicConfig (&magConf)[11]);

	_stSpriteConfig readConfig(SpriteId id);
	_stMagicConfig readMagConfig(MagicId id);
	void magicMove(MagicId id, BaseSprite* attackSprite, BaseSprite* hurtSprite);
	
	void showLifeCallback(Node* node);
	void ergodicSprite(BaseSprite* attack,BaseSprite* tmp1, BaseSprite* tmp2, BaseSprite* tmp3);
	void update(float dt);

	void itemCallback(Ref* pSender, int Num);


	void showBottomLife(BaseSprite* sprite);
	void showPower(BaseSprite* sprite);

	void setMagicPanel();
	void startMagic(BaseSprite* attack,MagicId id, int times= 1);
	void magicHurt(BaseSprite* attack,BaseSprite* sp1, BaseSprite* sp2, BaseSprite* sp3);
};

#endif