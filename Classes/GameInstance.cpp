#include "GameInstance.h"
#include "Resource.h"
static GameInstance *s_SharedGameInstance = nullptr;

GameInstance::GameInstance()
{
	for (unsigned int i = 0; i <6; i++)
	{
		spSel[i] = false;
	}
	isGameOver = false;
	isWin = false;
}

GameInstance::~GameInstance()
{
	
}

GameInstance* GameInstance::getInstance()
{
	if (!s_SharedGameInstance)
	{
		s_SharedGameInstance = new GameInstance();
		//s_SharedGameInstance->init();
	}

	return s_SharedGameInstance;
}

Animate* GameInstance::setAnimate(const char* frameName, int frameCount, int fps, bool restore,int times)
{
	using namespace cocos2d;
	Vector<SpriteFrame*> frames;

	for (int i = 1; i <= frameCount; i++)
	{
		const char* imgName = String::createWithFormat(frameName, i)->getCString();
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
		frames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(frames, 1.0f/fps, times);
	animation->setRestoreOriginalFrame(restore);
	auto animate = Animate::create(animation);
	return animate;
}






//MagicConfig GameInstance::readDataBase(MagicId id)
//{
//	MagicConfig magicConf;
//	sqlite3* pdb;
//	std::string path = "database/magic.db3";
//	int result;
//	char** re;
//	int row;
//	int col;
//
//	result = sqlite3_open(path.c_str(), &pdb);
//
//	sqlite3_get_table(pdb, "select * from magicConfig", &re, &row,&col, NULL);
//
//	magicConf.id = (MagicId)atoi(re[2*col+0]);
//	magicConf.name = re[id*col+1];
//	magicConf.count = atoi(re[id*col+2]);
//
//	sqlite3_close(pdb);
//
//	return magicConf;
//}

std::string GameInstance::getMagicName(MagicId id)
{
	_stMagicConfig mgConf;
	rapidjson::Document doc;
	std::string str = FileUtils::getInstance()->getStringFromFile(s_spMagJson);
	doc.Parse<rapidjson::kParseDefaultFlags>(str.c_str());

	rapidjson::Value &val =doc[(rapidjson::SizeType)(id-1)];

	std::string name = val["name"].GetString();

	return name;

}

int GameInstance::getMagicNum(MagicId id)
{
	_stMagicConfig mgConf;
	rapidjson::Document doc;
	std::string str = FileUtils::getInstance()->getStringFromFile(s_spMagJson);
	doc.Parse<rapidjson::kParseDefaultFlags>(str.c_str());

	rapidjson::Value &val =doc[(rapidjson::SizeType)(id-1)];

	int count = val["count"].GetInt();

	return count;
}

std::string GameInstance::getSpriteName(SpriteId id)
{
	std::string name;
	_stSpriteConfig spConf;
	rapidjson::Document doc;
	std::string str = FileUtils::getInstance()->getStringFromFile(s_spConfJson);
	doc.Parse<rapidjson::kParseDefaultFlags>(str.c_str());

	rapidjson::Value &val =doc[(rapidjson::SizeType)(id-1)];

	if (val.HasMember("name"))
	{
		name = val["name"].GetString();
	}

	return name;
}

std::string GameInstance::getStateName(SpriteId id,SpriteState state)
{
	std::string str = GameInstance::getInstance()->getSpriteName(id);

	switch (state)
	{
	case SPRITESTATE_IDLE:
		str += "_run_%03d.png";
		break;
	case SPRITESTATE_RUN:
		str += "_run_%03d.png";
		break;
	case SPRITESTATE_ATTACK:
		str += "_attack_%03d.png";
		break;
	case SPRITESTATE_HURT:
		str += "_run_%03d.png";
		break;
	case SPRITESTATE_DEAD:
		str += "_dead_%03d.png";
		break;
	default:
		break;
	}
	return str;
}


