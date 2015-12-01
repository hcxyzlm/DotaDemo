#include "LoadScene.h"
#include "GameScene.h"
LoadScene::LoadScene()
{
	numOfRes = 12;
	numOfLoadedRes = 0;
}



Scene* LoadScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadScene::create();
	scene->addChild(layer);

	return scene;
}

bool LoadScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto size = Director::getInstance()->getWinSize();

	labelLoad = Label::createWithTTF("loading...", "fonts/Marker Felt.ttf", 25);
	labelPercent = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 25);

	labelLoad->setPosition(size.width/2, size.height/2 -140);
	labelPercent->setPosition(size.width/2, size.height/2 -100);

	this->addChild(labelLoad);
	this->addChild(labelPercent);

	this->loadRes();
	
	return true;
}

//异步加载
void LoadScene::loadRes()
{
	//加载精灵动画
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/magic.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/magic2.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/magic3.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/magic4.plist");
	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/monster1.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/monster2.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/monster3.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/monster4.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/monster5.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/monster6.plist");

	TextureCache::getInstance()->addImageAsync("plist/magic.png",
		                         CC_CALLBACK_1(LoadScene::loadCallback, this));
	TextureCache::getInstance()->addImageAsync("plist/magic2.png",
		                         CC_CALLBACK_1(LoadScene::loadCallback, this));
	TextureCache::getInstance()->addImageAsync("plist/magic3.png",
		                         CC_CALLBACK_1(LoadScene::loadCallback, this));
	TextureCache::getInstance()->addImageAsync("plist/magic4.png",
		                         CC_CALLBACK_1(LoadScene::loadCallback, this));

	TextureCache::getInstance()->addImageAsync("plist/monster1.png",
		                                      CC_CALLBACK_1(LoadScene::loadCallback, this));
	TextureCache::getInstance()->addImageAsync("plist/monster2.png",
		                                      CC_CALLBACK_1(LoadScene::loadCallback, this));
	TextureCache::getInstance()->addImageAsync("plist/monster3.png",
											  CC_CALLBACK_1(LoadScene::loadCallback, this));
	TextureCache::getInstance()->addImageAsync("plist/monster4.png",
											  CC_CALLBACK_1(LoadScene::loadCallback, this));
	TextureCache::getInstance()->addImageAsync("plist/monster5.png",
		                                      CC_CALLBACK_1(LoadScene::loadCallback, this));
	TextureCache::getInstance()->addImageAsync("plist/monster6.png",
		                                      CC_CALLBACK_1(LoadScene::loadCallback, this));
	//加载地图
	TextureCache::getInstance()->addImageAsync("map/bbg_spring2.png",
											  CC_CALLBACK_1(LoadScene::loadCallback, this));
	//战斗场景组件
	TextureCache::getInstance()->addImageAsync("card/panel.png",
		                                      CC_CALLBACK_1(LoadScene::loadCallback, this));
}
void LoadScene::loadCallback(Texture2D* texture)
{
	numOfLoadedRes++;
	char tmp[10];
	sprintf(tmp, "%d", (int)(((float)numOfLoadedRes/numOfRes) * 100));
	labelPercent->setString(tmp);

	if (numOfLoadedRes == numOfRes)
	{
		//this->removeChild(labelLoad, true);
		//this->removeChild(labelPercent, true);
		this->scheduleOnce(schedule_selector(LoadScene::toStartScene), 1.0f);
	}

}

void LoadScene::toStartScene(float dt)
{
	auto gameScene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, gameScene));
}