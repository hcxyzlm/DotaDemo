#include "GameScene.h"
#include "json/document.h"
#include "GameInstance.h"

GameScene::GameScene()
{
}
GameScene::~GameScene()
{
}

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->initMap();

	spriteSystem = SpriteSystem::create();
	this->addChild(spriteSystem, 1);

	/*magicSystem = MagicSystem::create();
	this->addChild(magicSystem, 2);*/

	
	return true;
}

void GameScene::initMap()
{
	auto size = Director::getInstance()->getVisibleSize();

	auto texMap1 = TextureCache::getInstance()->getTextureForKey("map/bbg_spring2.png");
	auto map1 = Sprite::createWithTexture(texMap1);
	map1->setPosition(size.width/2, size.height/2);
	this->addChild(map1);
}




