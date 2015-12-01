#ifndef _BASESPRITE_
#define _BASESPRITE_

#include "cocos2d.h"
#include "Config.h"
using namespace cocos2d;


class BaseSprite : public Sprite
{
public:
	BaseSprite();
	~BaseSprite();
	
	static BaseSprite* create(_stSpriteConfig spConfig);          //��ʼ��
	CC_SYNTHESIZE(_stSpriteConfig, spConf, SpConf);               //��������
	CC_SYNTHESIZE_RETAIN(Action*, m_aIdleAction, IdleAction);     //����״̬����        
	CC_SYNTHESIZE_RETAIN(Action*, m_aRunningAction, RunningAction);
	CC_SYNTHESIZE_RETAIN(Action*, m_aAttackAction, AttackAction);
	CC_SYNTHESIZE_RETAIN(Action*, m_aHurtAction, HurtAction);
	CC_SYNTHESIZE_RETAIN(Action*, m_aDeadAction, DeadAction);
	CC_SYNTHESIZE_RETAIN(Action*, m_aMagicAction, MagicAction);
	
	CC_SYNTHESIZE(BaseSprite*, targetSp, TargetSp);               //����Ŀ��
	CC_SYNTHESIZE(int, m_iCurPower, CurPower);                    //��ǰ����ֵ
	CC_SYNTHESIZE(int, m_iCurLife, CurLife);                      //��ǰħ��ֵ
	CC_SYNTHESIZE(bool, m_bIsMagic, IsMagic);                     //�Ƿ�Ϊ�ͷ�ħ��״̬
	CC_SYNTHESIZE(SpriteState, spriteState, SpriteState);         //��ǰ״̬
	
	void startAction(SpriteState state);                          //�ı�״̬
	void move(MoveType moveTpye,Point endPoint, float duration);  //��Ϸ��ʼʱ�ܶ�
	
private:

	Action* setAction(const char* frameName, int count, int fps, bool repeat, bool restore, int times =1);  //���þ���״̬
	void setAllAction();                                          //��ʼ������״̬����
	void actionCallback();                                        //��ͨ�����ص�                                        
	void moveCallback();                                          //�ƶ������ص�

};

#endif