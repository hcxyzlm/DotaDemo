#ifndef _CONFIG_
#define _CONFIG_

USING_NS_CC;
//�����ʼλ��
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

//�����Ψһ��ʾ
enum SpriteId
{
	SPRITEID_1 = 1,
	SPRITEID_2,
	SPRITEID_3,
	SPRITEID_4,
	SPRITEID_5,
	SPRITEID_6

};

//ÿ�����ܵ�Ψһ��ʾ
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
//����״̬
enum SpriteState
{
	SPRITESTATE_IDLE,
	SPRITESTATE_RUN,
	SPRITESTATE_ATTACK,
	SPRITESTATE_MAGIC,
	SPRITESTATE_HURT,
	SPRITESTATE_DEAD
};
//�������� ǰ�š����š�����
enum  SpriteType
{
	SPRITETYPE_FRONT = 1,    //ǰ��
	SPRITETYPE_MIDDLE,   //����
	SPRITETYPE_BACK      //����
};

enum MoveType
{
	MoveType_To,
	MoveType_By
};

//����ÿ��״̬�Ķ�������
struct StateNum
{
	int idleNum;    //����
	int runNum;     //�ܶ�
	int attackNum;  //����
	int hurtNum;    //����
	int deadNum;    //����
};

//��������

struct MagicGroup
{
	MagicId magic1;
	MagicId magic2;
};

struct _stSpriteConfig
{
	SpriteId id;             //����ID,Ψһʶ��
	std::string name;        //����
	SpriteType type;         //���ͣ�ǰ�š����š�����
	int life;                //����ֵ
	int attack;              //������
	double attackSpeed;      //�����ٶ�
	int power;               //ħ��ֵ
	MagicGroup magicGroup;   //ħ�����Զ���롢ֱ�ӹ���
	StateNum stateNum;       //������֡��
};



//��������
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