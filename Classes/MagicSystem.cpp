#include "MagicSystem.h"

MagicSystem::MagicSystem()
{

}

MagicSystem::~MagicSystem()
{
	
}

bool MagicSystem::init()
{
	if (!Layer::init())
	{
		return false;
	}

	/*mg1 = Magic::create(MAGIC_10);
	this->setPosition(300, 300);
	this->addChild(mg1);

	mg1->startMagic(12, 1);*/

	return true;
}