#include "SpriteSystem.h"
#include "GameInstance.h"
#include "Magic.h"
#include "OverScene.h"
#include "Resource.h"

SpriteSystem::SpriteSystem()
{
	m_bIsAttack = false;
	m_fElapseTime = 0;
}

SpriteSystem::~SpriteSystem()
{
	
}

bool SpriteSystem::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_bIsAttack = false;
	m_fElapseTime = 0;
	 m_fOverTime = 0;

	bool spSel[6] = {true, true, true, true, true, true};

	for (unsigned int i = 0; i < 6; i++)
	{
		GameInstance::getInstance()->spSel[i] = spSel[i];
		m_fOldScheTime[i] = 0;
		m_fScheduleTime[i] = 0;
	}


	GameInstance::getInstance()->heroNum = 3;
	GameInstance::getInstance()->enemyNum = 3;

	this->readJson(spConf);
	this->readMagicJson(magConf);
	this->initSprite();
	this->setMagicPanel();

	

	return true;
}

_stSpriteConfig SpriteSystem::readConfig(SpriteId id)
{
	_stSpriteConfig tmp;

	tmp = spConf[id-1];
	return tmp;
}

void SpriteSystem::readJson(_stSpriteConfig (&spConf)[6])
{
	//_stSpriteConfig spConf[6];
	rapidjson::Document doc;
	std::string str = FileUtils::getInstance()->getStringFromFile(s_spConfJson);
	doc.Parse<rapidjson::kParseDefaultFlags>(str.c_str());

	for(unsigned int i = 0; i < 6; i++)
	{
		rapidjson::Value &val =doc[(rapidjson::SizeType)(i)];

		if (val.HasMember("id")&&val.HasMember("name")&&val.HasMember("type")&&val.HasMember("life")&&
			val.HasMember("attack")&&val.HasMember("attackSpeed")&&val.HasMember("power")&& val.HasMember("magicGroup"))
		{
			spConf[i].id = (SpriteId)val["id"].GetInt();
			spConf[i].name = val["name"].GetString();
			spConf[i].type = (SpriteType)val["type"].GetInt();
			spConf[i].life = val["life"].GetInt();
			spConf[i].attack = val["attack"].GetInt(); 
			spConf[i].attackSpeed = val["attackSpeed"].GetDouble(); 
			spConf[i].power = val["power"].GetInt();
		}

		rapidjson::Value& num = val["stateNum"][(rapidjson::SizeType)0];
		spConf[i].stateNum.idleNum = num["idleNum"].GetInt();
		spConf[i].stateNum.runNum = num["runNum"].GetInt();
		spConf[i].stateNum.attackNum = num["attackNum"].GetInt();
		spConf[i].stateNum.hurtNum = num["hurtNum"].GetInt();
		spConf[i].stateNum.deadNum = num["deadNum"].GetInt();

		rapidjson::Value& group = val["magicGroup"][(rapidjson::SizeType)0];
		spConf[i].magicGroup.magic1 = (MagicId)group["magic1"].GetInt();
		spConf[i].magicGroup.magic2 = (MagicId)group["magic2"].GetInt();
	}



	//return spConf;

}

_stMagicConfig SpriteSystem::readMagConfig(MagicId id)
{
	_stMagicConfig tmp;

	tmp = magConf[id-1];
	return tmp;
}

void SpriteSystem::readMagicJson(_stMagicConfig (&magConf)[11])
{
	rapidjson::Document doc;
	std::string str = FileUtils::getInstance()->getStringFromFile(s_spMagJson);
	doc.Parse<rapidjson::kParseDefaultFlags>(str.c_str());

	for (unsigned int i = 0; i < 11; i++)
	{
		rapidjson::Value &val =doc[(rapidjson::SizeType)(i)];

		if (val.HasMember("id")&&val.HasMember("name")&&val.HasMember("count"))
		{
			magConf[i].id = (MagicId)val["id"].GetInt();
			magConf[i].name = val["name"].GetString();
			magConf[i].count = val["count"].GetInt();
		}

	}
}


void SpriteSystem::update(float dt)
{
	float fOldTime = m_fElapseTime;
	m_fElapseTime  = m_fElapseTime + (dt*1000);

	if(fOldTime < 5000.0f && m_fElapseTime >= 5000.0f && GameInstance::getInstance()->isGameOver == false)
	{
		m_bIsAttack = true;
	}

	if (GameInstance::getInstance()->isGameOver == false && m_bIsAttack == true)
	{
		this->spAttackSchedule(dt);
	}
	
	for (unsigned int i = 0; i < 6; i++)
	{
		if (m_bsSp[i]->getCurLife() < 0 && m_bsSp[i]->getSpriteState() != SPRITESTATE_DEAD)
		{
			m_bsSp[i]->startAction(SPRITESTATE_DEAD);
			if (i < 3)
			{
				m_itItem[i]->setEnabled(false);
				m_ptLife[i]->setPercentage(0);
				m_ptPower[i]->setPercentage(0);
				//CCLOG("Set false%d", m_ptPower[i]->getPercentage());
			}
			if (m_bsSp[i]->getSpConf().id == SPRITEID_1 ||m_bsSp[i]->getSpConf().id == SPRITEID_2 || m_bsSp[i]->getSpConf().id == SPRITEID_3)
			{
				GameInstance::getInstance()->heroNum--;
			}
			else
			{
				GameInstance::getInstance()->enemyNum--;
			}
		}

		
	}

	if (GameInstance::getInstance()->isGameOver == false)
	{
		if (GameInstance::getInstance()->heroNum == 0)
		{
			GameInstance::getInstance()->isWin = false;
			GameInstance::getInstance()->isGameOver = true;
			m_fOverTime = m_fElapseTime;
		}
		if (GameInstance::getInstance()->enemyNum == 0)
		{
			GameInstance::getInstance()->isWin = true;
			GameInstance::getInstance()->isGameOver = true;
			m_fOverTime = m_fElapseTime;
		} 
	}

	

	if (GameInstance::getInstance()->isGameOver == true)
	{
		if (m_fElapseTime >= m_fOverTime + 2000.0f)
		{
			unscheduleUpdate();
			Director::getInstance()->replaceScene(TransitionCrossFade::create(1.5f, OverScene::createScene()));
			
		}
		
	}


	for (unsigned int i = 0; i < 6; i++)
	{
		if (m_bsSp[i]->getSpriteState() != SPRITESTATE_DEAD)
		{
			if (i < 3)
			{
				this->ergodicSprite(m_bsSp[i], m_bsSp[3], m_bsSp[4], m_bsSp[5]);
			}
			else
			{
				this->ergodicSprite(m_bsSp[i], m_bsSp[0], m_bsSp[1], m_bsSp[2]);
			}
		}
		else if(i < 3)
		{
			m_itItem[i]->setEnabled(false);

		}
	}

	for (unsigned int i = 0; i < 3; i++)
	{
		if (m_bsSp[i]->getSpriteState() != SPRITESTATE_DEAD)
		{
			this->showBottomLife(m_bsSp[i]);	
			this->showPower(m_bsSp[i]);
		}
		
	}

}

void SpriteSystem::initSprite()
{
	struct _stSpConf
	{
		float spScale[6];
		Point spPosStart[6];
		Point spPosEnd[6];
		bool  spFlip[6];

		_stSpConf()
		{
			spScale[0] = 0.8f; spScale[1] = 1.0f; spScale[2] = 1.0f; 
			spScale[3] = 1.0f; spScale[4] = 1.0f; spScale[5] = 1.0f;

			spFlip[0] = true; spFlip[1] = true; spFlip[2] = true;
			spFlip[3] = false; spFlip[4] = false; spFlip[5] = false;

			spPosStart[0] = PointS_1; spPosStart[1] = PointS_2; spPosStart[2] = PointS_3;
			spPosStart[3] = PointS_4; spPosStart[4] = PointS_5; spPosStart[5] = PointS_6;

			spPosEnd[0] = PointE_1; spPosEnd[1] = PointE_2; spPosEnd[2] = PointE_3;
			spPosEnd[3] = PointE_4; spPosEnd[4] = PointE_5; spPosEnd[5] = PointE_6;

		
		}

	}_stSpConf;


	for (unsigned int i = 0; i < 6; i++)
	{
		if (GameInstance::getInstance()->spSel[i])
		{
			m_bsSp[i] = BaseSprite::create(spConf[i]);
			m_bsSp[i]->setScale(_stSpConf.spScale[i]);
			m_bsSp[i]->setPosition(_stSpConf.spPosStart[i]);
			m_bsSp[i]->setFlippedX(_stSpConf.spFlip[i]);
			m_bsSp[i]->startAction(SPRITESTATE_IDLE);
			m_bsSp[i]->move(MoveType_To, _stSpConf.spPosEnd[i], 4.5f);
			//m_fScheduleTime[i] = m_bsSp[i]->getSpConf().attackSpeed;
			i < 3 ? m_bsSp[i]->setTargetSp(m_bsSp[3]) : m_bsSp[i]->setTargetSp(m_bsSp[0]);
			this->addChild(m_bsSp[i], 1);
		}
	}


	scheduleUpdate();
	
}



void SpriteSystem::spAttackSchedule(float dt)
{
	for (unsigned int i = 0; i <6; i++)
	{
		//释放魔法状态，将定时器时间设为0
		if (m_bsSp[i]->getIsMagic() == true)
		{
			m_fScheduleTime[i] = 0;
		}
		//普通攻击状态
		if (m_bsSp[i]->getSpriteState() != SPRITESTATE_DEAD && m_bsSp[i]->getIsMagic() == false)
		{
			m_fOldScheTime[i]  = m_fScheduleTime[i];
			m_fScheduleTime[i] += dt;
			
			if (m_fOldScheTime[i] < m_bsSp[i]->getSpConf().attackSpeed && m_fScheduleTime[i] >= m_bsSp[i]->getSpConf().attackSpeed)
			{
				m_bsSp[i]->startAction(SPRITESTATE_ATTACK);
				//远距离攻击
				if (m_bsSp[i]->getSpConf().type != SPRITETYPE_FRONT)
				{
					this->magicMove(m_bsSp[i]->getSpConf().magicGroup.magic1, m_bsSp[i], m_bsSp[i]->getTargetSp());
				}
				//直接攻击
				else
				{
					m_bsSp[i]->getTargetSp()->setCurLife(m_bsSp[i]->getTargetSp()->getCurLife() - m_bsSp[i]->getSpConf().attack);
					this->showLife(m_bsSp[i]->getTargetSp());

					if (m_bsSp[i]->getCurPower() <= m_bsSp[i]->getSpConf().power)
					{
						m_bsSp[i]->setCurPower(m_bsSp[i]->getCurPower() + m_bsSp[i]->getSpConf().attack*2);
					}
					

				}
				m_fOldScheTime[i] = 0;
				m_fScheduleTime[i] = 0;
			}
			
		}
		
	}	
}


void SpriteSystem::magicMove(MagicId id, BaseSprite* attackSprite, BaseSprite* hurtSprite)
{
	auto attackPos = attackSprite->getPosition();
	auto hurtPos = hurtSprite->getPosition();
	auto size = Director::getInstance()->getVisibleSize().width;

	std::string name = GameInstance::getInstance()->getMagicName(id);
	name += "_001.png";
    Sprite* magic = CCSprite::createWithSpriteFrameName(name.c_str());
	
	magic->setScale(0.6f);
	if (id == MAGIC_9)
	{
		magic->setRotation(-90);
	}
	magic->setPosition(attackPos);
	this->addChild(magic, 2);
	float s = ccpDistance(attackPos, hurtPos);
	float v = 300.0f;

	auto move = MoveTo::create(s/v, hurtPos);
	auto callfunc = CallFunc::create(std::bind(&SpriteSystem::magicMoveCallback, this, magic,attackSprite));
	magic->runAction(Sequence::create(move, callfunc, NULL));

}

void SpriteSystem::magicMoveCallback(Node* node, BaseSprite* sp)
{
	node->setVisible(false);
	this->removeChild(node);
	if (sp)
	{
		sp->getTargetSp()->setCurLife(sp->getTargetSp()->getCurLife() - sp->getSpConf().attack);
		this->showLife(sp->getTargetSp());

		if (sp->getCurPower() <= sp->getSpConf().power)
		{
			sp->setCurPower(sp->getCurPower() + sp->getSpConf().attack*2);
		}
	}
	
}

void SpriteSystem::showLife(BaseSprite* sp)
{
	auto startPos = Point(sp->getPositionX(), sp->getPositionY() + sp->getContentSize().height/2 + 5);
	auto endPos = Point(sp->getPositionX(),sp->getPositionY() + sp->getContentSize().height/2 + 20);
	//资源尺寸不一导致
	if (sp->getSpConf().id == 1)
	{
		startPos = Point(sp->getPositionX() - 30, sp->getPositionY() + sp->getContentSize().height/2 + 5 - 90);
		endPos = Point(sp->getPositionX() - 30,sp->getPositionY() +sp->getContentSize().height/2 + 20 - 90);
	}
	if (sp->getSpConf().id == 6)
	{
		startPos = Point(sp->getPositionX(), sp->getPositionY() + sp->getContentSize().height/2 - 30);
		endPos = Point(sp->getPositionX(),sp->getPositionY() +sp->getContentSize().height/2  -15);
	}

	float per = float(sp->getCurLife() )/ (float)sp->getSpConf().life;

	Node* node = Node::create();
	Sprite* lifebg = Sprite::create(s_ptBg);	
	ProgressTimer* life = ProgressTimer::create(Sprite::create(sp->getSpConf().id<3 ? s_ptLife : s_ptLife2));
	life->setType(ProgressTimer::Type::BAR);
	life->setMidpoint(Point::ANCHOR_MIDDLE_LEFT);
	life->setBarChangeRate(Point::ANCHOR_MIDDLE_RIGHT);
	life->setPercentage(per*100);
	
	node->setPosition(startPos);
	node->addChild(lifebg, 0);
	node->addChild(life, 1);

	this->addChild(node, 2);

	auto moveUp = MoveTo::create(0.5f, endPos);
	auto fadeout = FadeOut::create(0.5f);
	auto spawn = Spawn::create(moveUp, fadeout, NULL);

	auto callfunc = CallFunc::create(std::bind(&SpriteSystem::showLifeCallback, this, node));

	node->runAction(Sequence::create(spawn, callfunc, NULL));


}

void SpriteSystem::showLifeCallback(Node* node)
{
	node->setVisible(false);
	this->removeChild(node);
}

void SpriteSystem::ergodicSprite(BaseSprite* attack,BaseSprite* tmp1, BaseSprite* tmp2, BaseSprite* tmp3)
{
	BaseSprite* tmps[3] = {tmp1, tmp2, tmp3};
	for (unsigned int i = 0; i < 3; i++)
	{
		if (attack && tmps[i] && tmps[i]->getSpriteState() != SPRITESTATE_DEAD)
		{
			attack->setTargetSp(tmps[i]);
			break;
		}
	}
}

void SpriteSystem::setMagicPanel()
{
	Sprite* panel = Sprite::create(s_magPan);
	panel->setPosition(400, 90);

	struct _stMagPan
	{
		float scale[3];
		Point spPos[3];
		bool  enable[3];
		Point ptPos[6];

		_stMagPan()
		{
			scale[0] = 0.8f; scale[1] = 0.8f; scale[2] = 0.8f;
			spPos[0] = Point(534, 90); spPos[1] = Point(318, 90); spPos[2] = Point(106, 90);
			enable[0] = false; enable[1] = false; enable[2] = false;
			ptPos[0] = Point(106, 30); ptPos[1] = Point(318, 30); ptPos[2] = Point(534, 30); 
			ptPos[3] = Point(106, 10); ptPos[4] = Point(318, 10); ptPos[5] = Point(534, 10);
		}
	}_stMagPan;


	Sprite* spNor[3];
	Sprite* spDis[3];
	Sprite* life[3];
	Sprite* power[3];
	Sprite* ptBg[6];

	for (unsigned int i = 0; i < 3; i++)
	{
		//英雄头像设为按钮
		spNor[i] = Sprite::create(s_panSpNor[i]);
		spDis[i] = Sprite::create(s_panSpDis[i]);

		m_itItem[i] = MenuItemSprite::create(spNor[i], spNor[i], spDis[i], std::bind(&SpriteSystem::itemCallback, this, std::placeholders::_1,i));
		m_itItem[i]->setScale(_stMagPan.scale[i]);
		m_itItem[i]->setPosition(_stMagPan.spPos[i]);
		m_itItem[i]->setEnabled(_stMagPan.enable[i]);

		//生命值，魔法值
		m_ptLife[i] =  ProgressTimer::create(Sprite::create(s_ptLife));
		m_ptLife[i]->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		m_ptLife[i]->setType(ProgressTimer::Type::BAR);
		m_ptLife[i]->setMidpoint(Point::ANCHOR_MIDDLE_LEFT);
		m_ptLife[i]->setBarChangeRate(Point::ANCHOR_MIDDLE_RIGHT);
		m_ptLife[i]->setPercentage(100);

		m_ptPower[i] = ProgressTimer::create(Sprite::create(s_ptPower));
		m_ptPower[i]->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		m_ptPower[i]->setType(ProgressTimer::Type::BAR);
		m_ptPower[i]->setMidpoint(Point::ANCHOR_MIDDLE_LEFT);
		m_ptPower[i]->setBarChangeRate(Point::ANCHOR_MIDDLE_RIGHT);
		m_ptPower[i]->setPercentage(0);

	}

	auto menu = Menu::create(m_itItem[0], m_itItem[1], m_itItem[2], NULL);
	menu->setPosition(Point::ZERO);

	panel->addChild(menu,1);

	for (unsigned int i = 0; i < 6; i++)
	{
		ptBg[i] = Sprite::create(s_ptBg);
		ptBg[i]->setPosition(_stMagPan.ptPos[i]);
		panel->addChild(ptBg[i]);

	}
	
	ptBg[0]->addChild(m_ptLife[0],2);
	ptBg[1]->addChild(m_ptLife[1],2);
	ptBg[2]->addChild(m_ptLife[2],2);
	ptBg[3]->addChild(m_ptPower[0],2);
	ptBg[4]->addChild(m_ptPower[1],2);
	ptBg[5]->addChild(m_ptPower[2],2);

	this->addChild(panel, 1);


}

void SpriteSystem::itemCallback(Ref* pSender,int Num)
{
	m_itItem[Num]->setEnabled(false);
	CCLOG("Num%d", Num);
	m_bsSp[Num]->setCurPower(0);
	m_bsSp[Num]->startAction(SPRITESTATE_MAGIC);

	this->startMagic(m_bsSp[Num], m_bsSp[Num]->getSpConf().magicGroup.magic2, 3);
	
}

void SpriteSystem::showBottomLife(BaseSprite* sprite)
{
	float per = (((float)sprite->getCurLife()/sprite->getSpConf().life)*100);
	SpriteId id = sprite->getSpConf().id;
	switch (id)
	{
	case SPRITEID_1:
		m_ptLife[2]->setPercentage(per);
		break;
	case SPRITEID_2:
		m_ptLife[1]->setPercentage(per);
		break;
	case SPRITEID_3:
		m_ptLife[0]->setPercentage(per);
		break;
	case SPRITEID_4:
		break;
	case SPRITEID_5:
		break;
	case SPRITEID_6:
		break;
	default:
		break;
	}
}
void SpriteSystem::showPower(BaseSprite* sprite)
{
	float per = (((float)sprite->getCurPower()/sprite->getSpConf().power)*100);
	SpriteId id = sprite->getSpConf().id;
	switch (id)
	{
	case SPRITEID_1:
		m_ptPower[2]->setPercentage(per);
		if (per >= 100)
		{
			m_itItem[0]->setEnabled(true);
		}
		break;
	case SPRITEID_2:
		m_ptPower[1]->setPercentage(per);
		if (per >= 100)
		{
			m_itItem[1]->setEnabled(true);
		}
		break;
	case SPRITEID_3:
		m_ptPower[0]->setPercentage(per);
		if (per >= 100)
		{
			m_itItem[2]->setEnabled(true);
		}
		break;
	case SPRITEID_4:
		break;
	case SPRITEID_5:
		break;
	case SPRITEID_6:
		break;
	default:
		break;
	}
}

void SpriteSystem::startMagic(BaseSprite* tmp,MagicId id, int times)
{
	Magic* magic = Magic::create(magConf[tmp->getSpConf().magicGroup.magic2-1]);
	magic->setPosition(600, 300);
	this->addChild(magic, 1);

	magic->startMagic(12, times);
	this->magicHurt(tmp, m_bsSp[3], m_bsSp[4], m_bsSp[5]);


}

void SpriteSystem::magicHurt(BaseSprite* attack,BaseSprite* tmp1, BaseSprite* tmp2, BaseSprite* tmp3)
{
	BaseSprite* tmps[3] = {tmp1, tmp2, tmp3};
	for (unsigned int i = 0; i < 3; i++)
	{
		if (tmps[i] && tmps[i]->getSpriteState() != SPRITESTATE_DEAD)
		{
			tmps[i]->setCurLife(tmps[i]->getCurLife() - attack->getSpConf().attack);
			CCLOG("showlifes");
			this->showLife(tmps[i]);
		}
	}
}