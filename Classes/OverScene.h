#ifndef _OVERSCENE_
#define _OVERSCENE_

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocostudio;
using namespace cocos2d::ui;

class OverScene : public Layer
{
public:
	OverScene();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(OverScene);

private:
	void backCallback(Ref* sender);
	void fightCallback(Ref* sender);

	void tbackCallback(Ref* sender, TouchEventType type);
	void tfightCallback(Ref* sender, TouchEventType type);

};
#endif