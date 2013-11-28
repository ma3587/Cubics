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
		pTransform->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 190, 210));
		pLeft->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 260, 140));
		pRight->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 120, 140));
		pDown->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 190, 70));

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

		CCLabelTTF* pLabel = CCLabelTTF::create("Score:", "Arial", 56);
		pLabel->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 300, 1100));
		pLabel->setAnchorPoint(ccp(0, 0.5f));
		this->addChild(pLabel, 1);

		pLabel = CCLabelTTF::create("0", "Arial", 56);
		pLabel->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 300, 1000));
		pLabel->setColor(ccc3(255, 192, 0));
		pLabel->setAnchorPoint(ccp(0, 0.5f));
		//pLabel->setHorizontalAlignment(kCCTextAlignmentRight);
		this->addChild(pLabel, 1);
		mLabelScore = pLabel;


		if (!mCubeManager.init(this))
			return false;

		schedule(schedule_selector(GameWorld::stepGo), 0.5f);
		schedule(schedule_selector(GameWorld::checkKeyInput));
		schedule(schedule_selector(GameWorld::onKeyInput), 0.05f);

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

	char strScore[20];
	sprintf_s(strScore, 20, "%d", mCubeManager.getScore());
	mLabelScore->setString(strScore);
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
	mCubeManager.stepDown();
}

void GameWorld::checkKeyInput( float dt )
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (mInputKey != VK_UP)
		{
			mInputKey = VK_UP;
			mCubeManager.transform();
		}
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (mInputKey != VK_LEFT)
		{
			mInputKey = VK_LEFT;
			mCubeManager.move(CubeManager::ED_LEFT);
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (mInputKey != VK_RIGHT)
		{
			mInputKey = VK_RIGHT;
			mCubeManager.move(CubeManager::ED_RIGHT);
		}
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (mInputKey != VK_DOWN)
		{
			mInputKey = VK_DOWN;
			mCubeManager.stepDown();
		}
	}
	else
	{
		mInputKey = 0;
	}
}

void GameWorld::onKeyInput( float dt )
{
	if (mInputKey == VK_DOWN)
	{
		mCubeManager.stepDown();
	}
}
