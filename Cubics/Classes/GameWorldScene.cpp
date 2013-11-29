#include "GameWorldScene.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

bool GameWorld::init()
{
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

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
		CCMenuItemImage *pGameOver = CCMenuItemImage::create(
			"GameOver.jpg",
			"GameOver.jpg",
			this,
			menu_selector(GameWorld::menuGameOver));


		// Place the menu item bottom-right conner.
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		pTransform->setPosition(ccp(size.width - 190, 210));
		pLeft->setPosition(ccp(size.width - 260, 140));
		pRight->setPosition(ccp(size.width - 120, 140));
		pDown->setPosition(ccp(size.width - 190, 70));
		pGameOver->setPosition(ccp(size.width / 2, size.height / 2));
		pGameOver->setScale(5);
		pGameOver->setVisible(false);
		mMenuGameOver = pGameOver;


		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pTransform, pLeft, pRight, pDown, pGameOver, NULL);
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
		pLabel->setPosition(ccp(size.width - 300, 1100));
		pLabel->setAnchorPoint(ccp(0, 0.5f));
		this->addChild(pLabel);

		pLabel = CCLabelTTF::create("0", "Arial", 56);
		pLabel->setPosition(ccp(size.width - 300, 1000));
		pLabel->setColor(ccc3(255, 192, 0));
		pLabel->setAnchorPoint(ccp(0, 0.5f));
		//pLabel->setHorizontalAlignment(kCCTextAlignmentRight);
		this->addChild(pLabel);
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

	mMenuGameOver->setVisible(mCubeManager.isGameOver());
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

void GameWorld::menuGameOver( CCObject* pSender )
{
	do 
	{
		CCScene* helloScene = HelloWorld::scene();
		CC_BREAK_IF(!helloScene);

		CCDirector::sharedDirector()->replaceScene(helloScene);

	} while (0);
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
