#include "GameWorldScene.h"

using namespace cocos2d;

GameWorld::GameWorld()
{
	mBoard = new CubicsBoard;
	mBoard->init();
}

GameWorld::~GameWorld()
{
	delete mBoard;
}

bool GameWorld::init()
{
	do 
	{
	// Add a menu item with "X" image, which is clicked to quit the program.
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(GameWorld::menuCloseCallback));
	CC_BREAK_IF(! pCloseItem);

	// Place the menu item bottom-right conner.
	pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

	// Create a menu with the "close" menu item, it's an auto release object.
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	CC_BREAK_IF(! pMenu);

	// Add the menu to HelloWorld layer as a child layer.
	this->addChild(pMenu, 1);

	} while(0);

	return true;
}

void GameWorld::draw()
{
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


void GameWorld::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}

void GameWorld::stepGo()
{

}
