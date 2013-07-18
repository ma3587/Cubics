#ifndef __GAMEWORLD_SCENE_H__
#define __GAMEWORLD_SCENE_H__

#include "cocos2d.h"
#include "CubicsCore.h"

class GameWorld : public cocos2d::CCLayer
{
public:
	GameWorld();
	~GameWorld();

	virtual bool init();
	virtual void draw();

	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	// Game step
	void stepGo();

	CREATE_FUNC(GameWorld);

protected:
	Cube mCurrentCube;
	Cube mNextCube;
};

#endif