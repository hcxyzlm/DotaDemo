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
	
	static BaseSprite* create(_stSpriteConfig spConfig);          //初始化
	CC_SYNTHESIZE(_stSpriteConfig, spConf, SpConf);               //精灵属性
	CC_SYNTHESIZE_RETAIN(Action*, m_aIdleAction, IdleAction);     //保存状态动画        
	CC_SYNTHESIZE_RETAIN(Action*, m_aRunningAction, RunningAction);
	CC_SYNTHESIZE_RETAIN(Action*, m_aAttackAction, AttackAction);
	CC_SYNTHESIZE_RETAIN(Action*, m_aHurtAction, HurtAction);
	CC_SYNTHESIZE_RETAIN(Action*, m_aDeadAction, DeadAction);
	CC_SYNTHESIZE_RETAIN(Action*, m_aMagicAction, MagicAction);
	
	CC_SYNTHESIZE(BaseSprite*, targetSp, TargetSp);               //攻击目标
	CC_SYNTHESIZE(int, m_iCurPower, CurPower);                    //当前生命值
	CC_SYNTHESIZE(int, m_iCurLife, CurLife);                      //当前魔法值
	CC_SYNTHESIZE(bool, m_bIsMagic, IsMagic);                     //是否为释放魔法状态
	CC_SYNTHESIZE(SpriteState, spriteState, SpriteState);         //当前状态
	
	void startAction(SpriteState state);                          //改变状态
	void move(MoveType moveTpye,Point endPoint, float duration);  //游戏开始时跑动
	
private:

	Action* setAction(const char* frameName, int count, int fps, bool repeat, bool restore, int times =1);  //设置精灵状态
	void setAllAction();                                          //初始化所有状态动画
	void actionCallback();                                        //普通攻击回调                                        
	void moveCallback();                                          //移动结束回调

};

#endif