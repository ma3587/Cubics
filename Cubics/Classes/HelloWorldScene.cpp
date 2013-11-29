#include "HelloWorldScene.h"
#include "GameWorldScene.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
	CCScene* tempScene = NULL;
	CCScene* retScene = NULL;
	do 
	{
		tempScene = CCScene::create();
		CC_BREAK_IF(!tempScene);

		HelloWorld *layer = HelloWorld::create();
		CC_BREAK_IF(! layer);

		tempScene->addChild(layer);

		// 'scene' is an autorelease object
		retScene = CCTransitionFade::create(0.5f, tempScene);
		CC_BREAK_IF(!retScene);

	} while (0);

	return retScene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		/////////////////////////////////////////////////////////////////////////

		setTouchEnabled(true);

		// Create a label and initialize with string "Hello World".
		CCLabelTTF* pLabel = CCLabelTTF::create("Tetris", "Arial", 56);
		CC_BREAK_IF(! pLabel);

		// Get window size and place the label upper. 
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		pLabel->setPosition(ccp(size.width / 2, size.height - 400));

		// Add the label to HelloWorld layer as a child layer.
		this->addChild(pLabel, 1);

		pLabel = CCLabelTTF::create("Cocos2d-X Powered", "Arial", 44);
		CC_BREAK_IF(! pLabel);
		pLabel->setPosition(ccp(size.width / 2, 200));
		pLabel->setColor(ccc3(255, 192, 0));
		this->addChild(pLabel, 1);
		pLabel = CCLabelTTF::create("Weibo:@DweepGold", "Arial", 44);
		CC_BREAK_IF(! pLabel);
		pLabel->setPosition(ccp(size.width / 2, 100));
		pLabel->setColor(ccc3(255, 192, 0));
		this->addChild(pLabel, 1);


		// 3. Add add a splash screen, show the cocos2d splash image.
		CCSprite* pSprite = CCSprite::create("HelloWorld.png");
		CC_BREAK_IF(! pSprite);

		// Place the sprite on the center of the screen
		pSprite->setPosition(ccp(size.width/2, size.height/2));

		// Add the sprite to HelloWorld layer as a child layer.
		this->addChild(pSprite, 0);

		bRet = true;
	} while (0);

	return bRet;
}

void HelloWorld::ccTouchesEnded( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{
	CCScene* gameScene = NULL;
	CCScene* transScene = NULL;
	do 
	{
		gameScene = GameWorld::scene();
		CC_BREAK_IF(!gameScene);

		transScene = CCTransitionFade::create(0.5f, gameScene);
		CC_BREAK_IF(!transScene);

		CCDirector::sharedDirector()->replaceScene(transScene);

	} while (0);
}


