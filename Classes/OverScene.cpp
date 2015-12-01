#include "OverScene.h"

#include "GameInstance.h"
#include "GameScene.h"

OverScene::OverScene()
{
}



Scene* OverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = OverScene::create();
	scene->addChild(layer);

	GameInstance::getInstance()->isGameOver = false;
	return scene;
}

bool OverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto ui = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("gameover/NewUI4_1.ExportJson");
	this->addChild(ui);

	Button* back = (Button*)Helper::seekWidgetByName(ui,"back");
	Button* fight = (Button*)Helper::seekWidgetByName(ui,"fight");

	if (GameInstance::getInstance()->isWin)
	{
		Sprite* title =Sprite::create("map/stagedetail_raid_title.png");
		title->setPosition(400, 240);
		this->addChild(title);
	}
	else
	{
		Sprite* title = Sprite::create("map/failed_title.png");
		title->setPosition(400, 240);
		this->addChild(title);
	}

	back->addTouchEventListener(this, toucheventselector(OverScene::tbackCallback));
	fight->addTouchEventListener(this, toucheventselector(OverScene::tfightCallback));
	/*Sprite* bg = Sprite::create("map/gameover.png");
	bg->setPosition(400, 240);
	this->addChild(bg);

	if (GameInstance::getInstance()->isWin)
	{
	Sprite* title =Sprite::create("map/stagedetail_raid_title.png");
	title->setPosition(400, 240);
	this->addChild(title);
	}
	else
	{
	Sprite* title = Sprite::create("map/failed_title.png");
	title->setPosition(400, 240);
	this->addChild(title);
	}
	auto back = MenuItemSprite::create(Sprite::create("button/replaybtn.png"), Sprite::create("button/replaybtn-disabled.png"),CC_CALLBACK_1(OverScene::backCallback,this));
	back->setPosition(back->getContentSize().width/2, back->getContentSize().height/2);

	auto fight = MenuItemSprite::create(Sprite::create("button/prepare_go_battle.png"), Sprite::create("button/prepare_go_battle_press.png"),CC_CALLBACK_1(OverScene::fightCallback,this));
	fight->setPosition(800-back->getContentSize().width/2, back->getContentSize().height/2);

	auto menu =Menu::create(back, fight, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);*/
	return true;
}

void OverScene::backCallback(Ref* sender)
{
	Director::getInstance()->end();

}
void OverScene::fightCallback(Ref* sender)
{
	Director::getInstance()->replaceScene(GameScene::createScene());

}

void OverScene::tbackCallback(Ref* sender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		Director::getInstance()->end();
		break;

	}
}
void OverScene::tfightCallback(Ref* sender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		Director::getInstance()->replaceScene(GameScene::createScene());
		break;

	}
}