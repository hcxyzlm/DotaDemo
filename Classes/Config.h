#ifndef _CONFIG_
#define _CONFIG_

USING_NS_CC;
//精灵初始位置
const Point PointS_1 = Point(355, 317) - Point(380, 0);
const Point PointS_2 = Point(190, 290)- Point(380, 0);
const Point PointS_3 = Point(80, 300)- Point(380, 0);
const Point PointS_4 = Point(445, 300)+ Point(380, 0);
const Point PointS_5 = Point(550, 313)+ Point(380, 0);
const Point PointS_6 = Point(720, 355)+ Point(380, 0);

const Point PointE_1 = Point(355, 317);
const Point PointE_2 = Point(190, 290);
const Point PointE_3 = Point(80, 300);
const Point PointE_4 = Point(445, 300);
const Point PointE_5 = Point(550, 313);
const Point PointE_6 = Point(720, 355);

//精灵的唯一标示
enum SpriteId
{
	SPRITEID_1 = 1,
	SPRITEID_2,
	SPRITEID_3,
	SPRITEID_4,
	SPRITEID_5,
	SPRITEID_6

};

//每个技能的唯一标示
enum MagicId
{
	MAGIC_1 = 1,
	MAGIC_2,
	MAGIC_3,
	MAGIC_4,
	MAGIC_5,
	MAGIC_6,
	MAGIC_7,
	MAGIC_8,
	MAGIC_9,
	MAGIC_10,
	MAGIC_11,
};
//精灵状态
enum SpriteState
{
	SPRITESTATE_IDLE,
	SPRITESTATE_RUN,
	SPRITESTATE_ATTACK,
	SPRITESTATE_MAGIC,
	SPRITESTATE_HURT,
	SPRITESTATE_DEAD
};
//精灵类型 前排、中排、后排
enum  SpriteType
{
	SPRITETYPE_FRONT = 1,    //前排
	SPRITETYPE_MIDDLE,   //中排
	SPRITETYPE_BACK      //后排
};

enum MoveType
{
	MoveType_To,
	MoveType_By
};

//精灵每个状态的动画数量
struct StateNum
{
	int idleNum;    //空闲
	int runNum;     //跑动
	int attackNum;  //攻击
	int hurtNum;    //受伤
	int deadNum;    //死亡
};

//精灵属性

struct MagicGroup
{
	MagicId magic1;
	MagicId magic2;
};

struct _stSpriteConfig
{
	SpriteId id;             //精灵ID,唯一识别
	std::string name;        //名字
	SpriteType type;         //类型，前排、中排、后排
	int life;                //生命值
	int attack;              //攻击力
	double attackSpeed;      //攻击速度
	int power;               //魔法值
	MagicGroup magicGroup;   //魔法类别，远距离、直接攻击
	StateNum stateNum;       //各动画帧数
};



//技能属性
struct _stMagicConfig
{
	MagicId id;
	std::string name;
	int count;

};


struct AttackId
{
	bool s1;
	bool s2;
	bool s3;
};
#endif