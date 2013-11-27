#include "GameWorldScene.h"

using namespace cocos2d;

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
}

bool GameWorld::init()
{
	do 
	{
		CCMenuItemImage *pTransform = CCMenuItemImage::create(
			"6.png",
			"6.png",
			this,
			menu_selector(GameWorld::menuTransformCallback));
		CCMenuItemImage *pLeft = CCMenuItemImage::create(
			"6.png",
			"6.png",
			this,
			menu_selector(GameWorld::menuLeftCallback));
		CCMenuItemImage *pRight = CCMenuItemImage::create(
			"6.png",
			"6.png",
			this,
			menu_selector(GameWorld::menuRightCallback));
		CCMenuItemImage *pDown = CCMenuItemImage::create(
			"6.png",
			"6.png",
			this,
			menu_selector(GameWorld::menuDownCallback));


		// Place the menu item bottom-right conner.
		pTransform->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 100, 160));
		pLeft->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 160, 100));
		pRight->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 40, 100));
		pDown->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 100, 40));

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pTransform, pLeft, pRight, pDown, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		addChild(pMenu, 1);

		CCDrawNode *pDrawNode = CCDrawNode::create();
		addChild(pDrawNode);
		CCPoint points[] = { 
			CCPoint(0,0), 
			CCPoint((CubeManager::MAIN_BOARD_WIDTH)* CubeManager::CUBE_SIZE, 0),
			CCPoint((CubeManager::MAIN_BOARD_WIDTH)* CubeManager::CUBE_SIZE, (CubeManager::MAIN_BOARD_HEIGHT + 1)* CubeManager::CUBE_SIZE),
			CCPoint(0, (CubeManager::MAIN_BOARD_HEIGHT + 1)* CubeManager::CUBE_SIZE)
		};
		pDrawNode->drawPolygon(points, sizeof(points)/sizeof(points[0]), ccc4f(0,0,0.3f,0.5f), 4, ccc4f(0,0,1,1));


		if (!mCubeManager.init(this))
			return false;

		schedule(schedule_selector(GameWorld::stepGo), 0.5f);

	} while(0);

	return true;
}

cocos2d::CCScene* GameWorld::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		GameWorld *layer = GameWorld::create();
		CC_BREAK_IF(!layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

void GameWorld::stepGo(float dt)
{
	mCubeManager.step(dt);
}

void GameWorld::menuTransformCallback( CCObject* pSender )
{
	mCubeManager.transform();
}

void GameWorld::menuLeftCallback( CCObject* pSender )
{
	mCubeManager.move(CubeManager::ED_LEFT);
}

void GameWorld::menuRightCallback( CCObject* pSender )
{
	mCubeManager.move(CubeManager::ED_RIGHT);
}

void GameWorld::menuDownCallback( CCObject* pSender )
{
	mCubeManager.move(CubeManager::ED_DOWN);
}
