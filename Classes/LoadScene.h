#ifndef _LOADSCENE_
#define _LOADSCENE_

#include "cocos2d.h"

using namespace cocos2d;

class LoadScene : public Layer
{
public:
	LoadScene();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LoadScene);

private:
	int numOfRes;
	int numOfLoadedRes;
	Label* labelLoad;
	Label* labelPercent;
	
	void loadRes();
	void loadCallback(Texture2D* texture);
	void toStartScene(float dt);

};
#endif