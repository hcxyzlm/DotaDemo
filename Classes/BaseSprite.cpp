#include "BaseSprite.h"
#include "GameInstance.h"
#include "SpriteSystem.h"

BaseSprite::BaseSprite()
{
	/*spConf->name = "";
	spConf->type= SPRITETYPE_1;
	spConf->attack = NULL;
	spConf->attackSpeed = NULL;
	spConf->power = NULL;*/
}

BaseSprite::~BaseSprite()
{
	CC_SAFE_RELEASE_NULL(m_aIdleAction);
	CC_SAFE_RELEASE_NULL(m_aRunningAction);
	CC_SAFE_RELEASE_NULL(m_aAttackAction);
	CC_SAFE_RELEASE_NULL(m_aHurtAction);
	CC_SAFE_RELEASE_NULL(m_aDeadAction);
	CC_SAFE_RELEASE_NULL(m_aMagicAction);

}

BaseSprite* BaseSprite::create(_stSpriteConfig spConfig)
{
	BaseSprite*  sprite = new BaseSprite();

	sprite->setAnchorPoint(Point(0.5, 0.5));
	sprite->spConf = spConfig;

	sprite->m_iCurLife = sprite->spConf.life;
	sprite->m_iCurPower = 0;
	sprite->m_bIsMagic = false;
	
	sprite->setAllAction();

	std::string spriteName = GameInstance::getInstance()->getSpriteName(sprite->spConf.id);
	spriteName += "_run_001.png";
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
}

void BaseSprite::setAllAction()
{
	std::string str;
	str = GameInstance::getInstance()->getStateName(this->spConf.id, SPRITESTATE_IDLE);
	m_aIdleAction = this->setAction(str.c_str(), spConf.stateNum.idleNum, 12, true, true);

	str = GameInstance::getInstance()->getStateName(this->spConf.id, SPRITESTATE_RUN);
	m_aRunningAction = this->setAction(str.c_str(), spConf.stateNum.runNum, 12, true, true);

	str = GameInstance::getInstance()->getStateName(this->spConf.id, SPRITESTATE_ATTACK);
	m_aAttackAction = this->setAction(str.c_str(), spConf.stateNum.attackNum, 12, false, true);

	m_aMagicAction = this->setAction(str.c_str(), spConf.stateNum.attackNum, 12, false, true);

	str = GameInstance::getInstance()->getStateName(this->spConf.id, SPRITESTATE_HURT);
	m_aHurtAction = this->setAction(str.c_str(), spConf.stateNum.hurtNum, 12, false, true);

	str = GameInstance::getInstance()->getStateName(this->spConf.id, SPRITESTATE_DEAD);
	m_aDeadAction = this->setAction(str.c_str(), spConf.stateNum.deadNum, 12, false, false);
}

Action* BaseSprite::setAction(const char* name, int count, int fps, bool repeat, bool restore, int times)
{
	//¿ÕÏÐ¡¢ÅÜ¶¯
	if (repeat)
	{
		auto tempAnimate = GameInstance::getInstance()->setAnimate(name, count, fps, restore);
		auto repeat = RepeatForever::create(tempAnimate);
		CC_SAFE_RETAIN(repeat);
		return repeat;
	}
	//
	else
	{
		auto tempAnimate = GameInstance::getInstance()->setAnimate(name, count, fps, restore);
		auto callfunc = CallFunc::create(CC_CALLBACK_0(BaseSprite::actionCallback, this));
		
		auto sequence = Sequence::create(tempAnimate, callfunc, NULL);
		CC_SAFE_RETAIN(sequence);
		return sequence;

	}
	
}



void BaseSprite::startAction(SpriteState state)
{
	this->stopAllActions();
	this->spriteState = state;

	switch (this->spriteState)
	{
	case SPRITESTATE_IDLE:
		this->runAction(m_aIdleAction);
		break;

	case SPRITESTATE_RUN:
		this->runAction(m_aRunningAction);
		break;

	case SPRITESTATE_ATTACK:
		this->runAction(m_aAttackAction);
		break;

	case SPRITESTATE_MAGIC:
		this->setScale(1.5f);
		this->runAction(m_aMagicAction);
		this->m_bIsMagic = true;		
		break;

	case SPRITESTATE_HURT:
		this->runAction(m_aHurtAction);
		break;

	case SPRITESTATE_DEAD:
		this->runAction(m_aDeadAction);
		break;

	default:
		break;
	}
	
}

void BaseSprite::actionCallback()
{
	
	SpriteState state = this->spriteState;

	switch (state)
	{
	case SPRITESTATE_IDLE:
		break;
	case SPRITESTATE_RUN:
		break;
	case SPRITESTATE_ATTACK:
		
		this->startAction(SPRITESTATE_IDLE);
		break;

	case SPRITESTATE_MAGIC:
		 this->setScale( this->spConf.id == SPRITEID_1 ? 0.8f : 1.0f );
		 this->m_bIsMagic = false;

		this->startAction(SPRITESTATE_IDLE);
		break;

	case SPRITESTATE_HURT:
		break;

	case SPRITESTATE_DEAD:
		{
			auto fadeout = FadeOut::create(2.0f);
			this->runAction(fadeout);
			
			break;
		}
	default:
		break;

	}
}
/*
void BaseSprite::attack(BaseSprite* targetSp)
{
	targetSp->m_iCurLife -= this->getSpConf().attack;
}*/


void BaseSprite::move(MoveType moveTpye,Point endPoint, float duration)
{
	
	this->startAction(SPRITESTATE_RUN);
	auto callfunc = CallFunc::create(CC_CALLBACK_0(BaseSprite::moveCallback, this));

	if (moveTpye == MoveType_To)
	{
		auto moveAction = MoveTo::create(duration, endPoint);
		this->runAction(Sequence::create(moveAction, callfunc, NULL));
		//CCLOG("moveto");
	}
	else
	{
		auto moveAction = MoveBy::create(duration, endPoint);
		this->runAction(Sequence::create(moveAction, callfunc, NULL));
	}
	
}

void BaseSprite::moveCallback()
{
	this->startAction(SPRITESTATE_IDLE);
	//CCLOG("mcovetocall");
}

/*
void BaseSprite::attackSchedule(float delay)
{
	this->schedule(schedule_selector(BaseSprite::attack), this->getSpConf().attackSpeed, kRepeatForever, delay);
}


void BaseSprite::attack(float dt)
{
	this->startAction(SPRITESTATE_ATTACK);
}


int BaseSprite::hurted(int attack)
{
	this->spConf.life = this->spConf.life - attack;
	if(this->spConf.life <= 0)
	{
		this->startAction(SPRITESTATE_DEAD);
	}
	return this->spConf.life;
}
*/


