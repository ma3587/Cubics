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

	static cocos2d::CCScene* scene();

	// a selector callback
	void menuTransformCallback(CCObject* pSender);
	void menuLeftCallback(CCObject* pSender);
	void menuRightCallback(CCObject* pSender);
	void menuDownCallback(CCObject* pSender);

	// Game step
	void stepGo(float dt);

	CREATE_FUNC(GameWorld);

protected:

	CubeManager mCubeManager;
};

#endif