#include "CubicsCore.h"

CubeManager::CubeManager()
{
}

CubeManager::~CubeManager()
{
}

bool CubeManager::init( cocos2d::CCLayer* layer )
{
	if (layer == NULL)
		return false;

	mLayer = layer;
	mGameOver = false;
	mFallingActive = false;
	mScore = 0;
	mNextFallingType = -1;
	mNextFallingIndex = -1;
	mNextFallingBaseX = 11;
	mNextFallingBaseY = 16;

	for (int i = 0; i < FALLING_BOARD_WIDTH; ++i)
		for (int j = 0; j < FALLING_BOARD_HEIGHT; ++j)
			mFallingSprites[i][j] = NULL;

	for (int i = 0; i < FALLING_BOARD_WIDTH; ++i)
		for (int j = 0; j < FALLING_BOARD_HEIGHT; ++j)
			mNextFallingSprites[i][j] = NULL;

	for (int i = 0; i < MAIN_BOARD_WIDTH; ++i)
		for (int j = 0; j < MAIN_BOARD_HEIGHT; ++j)
			mMainSprites[i][j] = NULL;

	mBoardTemplateManager.init();

	time_t t;  
	std::srand((unsigned int)time(&t));

	if (!generateFallingBoard())
		return false;

	return true;
}

void CubeManager::step(float dt)
{
	if (isGameOver())
		return;

	if (!isFallingActive())
	{
		if (!generateFallingBoard())
		{
			setGameOver(true);
		}
		return;
	}

	stepDown();
}

void CubeManager::move( ENUM_DIRECTION direction )
{
	if (isGameOver())
		return;

	if (collide(direction))
		return;

	if (direction == ED_LEFT)
		mFallingBaseX -= 1;
	else if (direction == ED_RIGHT)
		mFallingBaseX += 1;
	else if (direction == ED_DOWN)
		mFallingBaseY -= 1;

	for (int i = 0; i < FALLING_BOARD_WIDTH; ++i)
	{
		for (int j = 0; j < FALLING_BOARD_HEIGHT; ++j)
		{
			if (mFallingSprites[i][j])
			{
				mFallingSprites[i][j]->setPosition(
					ccp((mFallingBaseX + i) * CUBE_SIZE, (mFallingBaseY + j) * CUBE_SIZE));
			}
		}
	}
}

void CubeManager::transform()
{
	if (isGameOver())
		return;

	if (!mFallingActive)
		return;

	if (collide(mFallingBaseX, mFallingBaseY, mFallingType, mFallingIndex + 1))
		return;

	const BoardTemplate& curTempl = mBoardTemplateManager.getBoardTemplate(mFallingType, mFallingIndex);
	const BoardTemplate& nextTemp = mBoardTemplateManager.getBoardTemplate(mFallingType, ++mFallingIndex);

	std::vector<cocos2d::CCSprite*> vecTemp;
	for (size_t i = 0; i < curTempl.size(); ++i)
	{
		int x = curTempl[i].x;
		int y = curTempl[i].y;

		CCAssert(mFallingSprites[x][y] != NULL, "mFallingSprites[x][y] != NULL");

		vecTemp.push_back(mFallingSprites[x][y]);
		mFallingSprites[x][y] = NULL;
	}

	for (size_t i = 0; i < nextTemp.size(); ++i)
	{
		int x = nextTemp[i].x;
		int y = nextTemp[i].y;

		mFallingSprites[x][y] = vecTemp[i];
		mFallingSprites[x][y]->setPosition(
			ccp((mFallingBaseX + x)*CUBE_SIZE, (mFallingBaseY + y)*CUBE_SIZE));
	}
}

bool CubeManager::generateFallingBoard()
{
	mFallingActive = true;

	for (int i = 0; i < FALLING_BOARD_WIDTH; ++i)
		for (int j = 0; j < FALLING_BOARD_HEIGHT; ++j)
			mFallingSprites[i][j] = NULL;

	mFallingBaseX = MAIN_BOARD_WIDTH / 2 - FALLING_BOARD_WIDTH / 2;
	mFallingBaseY = MAIN_BOARD_HEIGHT - FALLING_BOARD_HEIGHT;

	bool bFirst = false;
	if (mNextFallingType == -1)
	{
		bFirst = true;
		mNextFallingType = rand() % BOARD_TYPE;
		mNextFallingIndex = rand();
		mFallingType = rand() % BOARD_TYPE;
		mFallingIndex = rand();
	}
	else
	{
		mFallingType = mNextFallingType;
		mFallingIndex = mNextFallingIndex;
		mNextFallingType = rand() % BOARD_TYPE;
		mNextFallingIndex = rand();
	}

	if (bFirst)
	{
		generateBoardSprite(
			mNextFallingSprites, 
			mNextFallingBaseX,
			mNextFallingBaseY, 
			mNextFallingType, 
			mNextFallingIndex);

		generateBoardSprite(
			mFallingSprites,
			mFallingBaseX,
			mFallingBaseY,
			mFallingType,
			mFallingIndex);
	}
	else
	{
		// copy next to current
		for (int i = 0; i < FALLING_BOARD_WIDTH; ++i)
		{
			for (int j = 0; j < FALLING_BOARD_HEIGHT; ++j)
			{
				mFallingSprites[i][j] = mNextFallingSprites[i][j];

				if (mFallingSprites[i][j])
				{
					mFallingSprites[i][j]->setPosition(
						ccp((mFallingBaseX + i)*CUBE_SIZE, (mFallingBaseY + j)*CUBE_SIZE));
				}
			}
		}

		generateBoardSprite(
			mNextFallingSprites, 
			mNextFallingBaseX,
			mNextFallingBaseY, 
			mNextFallingType, 
			mNextFallingIndex);
	}

	return !collide(mFallingBaseX, mFallingBaseY, mFallingType, mFallingIndex);
}

bool CubeManager::collide( ENUM_DIRECTION direction )
{
	int newBaseX = mFallingBaseX;
	int newBaseY = mFallingBaseY;

	if (direction == ED_LEFT)
		--newBaseX;
	else if (direction == ED_RIGHT)
		++newBaseX;
	else if (direction == ED_DOWN)
		--newBaseY;

	return collide(newBaseX, newBaseY, mFallingType, mFallingIndex);
}

bool CubeManager::collide( int fallingBaseX, int fallingBaseY, int boardType, int boardIndex )
{
	const BoardTemplate& templ = mBoardTemplateManager.getBoardTemplate(boardType, boardIndex);
	for (size_t i = 0; i < templ.size(); ++i)
	{
		int newX = fallingBaseX + templ[i].x;
		int newY = fallingBaseY + templ[i].y;
		if (newX < 0 || newX >= MAIN_BOARD_WIDTH
			|| newY < 0 || newY >= MAIN_BOARD_HEIGHT
			|| mMainSprites[newX][newY] != NULL)
		{
			return true;
		}
	}

	return false;
}

void CubeManager::stepDown()
{
	if (mGameOver)
		return;

	if (collide(ED_DOWN))
	{
		mergeFalling();

		if (checkFullLines())
		{
			clearFullLines();
		}
	}
	else
	{
		move(ED_DOWN);
	}
}

void CubeManager::mergeFalling()
{
	for (int i = 0; i < FALLING_BOARD_WIDTH; ++i)
	{
		for (int j = 0; j < FALLING_BOARD_HEIGHT; ++j)
		{
			if (mFallingSprites[i][j] == NULL)
				continue;

			if (mMainSprites[mFallingBaseX + i][mFallingBaseY + j] != NULL)
			{
				CCAssert(0, "CubeManager::mergeFalling()");
				return;
			}

			mMainSprites[mFallingBaseX + i][mFallingBaseY + j] = mFallingSprites[i][j];
			mFallingSprites[i][j] = NULL;
		}
	}

	mFallingActive = false;
}

bool CubeManager::checkFullLines()
{
	bool full = true;
	for (int j = 0; j < MAIN_BOARD_HEIGHT; ++j)
	{
		full = true;
		for (int i = 0; i < MAIN_BOARD_WIDTH; ++i)
		{
			if (mMainSprites[i][j] == NULL)
			{
				full = false;
				break;
			}
		}

		if (full == true)
			return true;
	}
	return false;
}

void CubeManager::clearFullLines()
{
	bool bFull = true;
	int iFullLines = 0;
	for (int j = 0; j < MAIN_BOARD_HEIGHT;)
	{
		bFull = true;
		for (int i = 0; i < MAIN_BOARD_WIDTH; ++i)
		{
			if (mMainSprites[i][j] == NULL)
			{
				bFull = false;
				break;
			}
		}

		if (bFull)
		{
			++iFullLines;
			clearFullLine(j);
			continue;
		}

		++j;
	}

	mScore += iFullLines * iFullLines * 100;
}

void CubeManager::clearFullLine( int line )
{
	for (int i = 0; i < MAIN_BOARD_WIDTH; ++i)
	{
		if (mMainSprites[i][line])
			mLayer->removeChild(mMainSprites[i][line]);
	}

	for (int j = line; j < MAIN_BOARD_HEIGHT; ++j)
	{
		for (int i = 0; i < MAIN_BOARD_WIDTH; ++i)
		{
			if (j + 1 < MAIN_BOARD_HEIGHT)
			{
				mMainSprites[i][j] = mMainSprites[i][j + 1];
			}
			else
			{
				mMainSprites[i][j] = NULL;
			}

			if (mMainSprites[i][j])
			{
				mMainSprites[i][j]->setPosition(
					ccp(i*CUBE_SIZE, j*CUBE_SIZE));
			}
		}
	}
}

void CubeManager::generateBoardSprite( cocos2d::CCSprite* pSprites[][FALLING_BOARD_HEIGHT], 
	int fallingBaseX, int fallingBaseY, int boardType, int boardIndex )
{
	for (int i = 0; i < FALLING_BOARD_WIDTH; ++i)
		for (int j = 0; j < FALLING_BOARD_HEIGHT; ++j)
			pSprites[i][j] = NULL;

	char strSprite[20];
	sprintf_s(strSprite, 20, "%d.png", boardType);

	const BoardTemplate& templ = mBoardTemplateManager.getBoardTemplate(boardType, boardIndex);
	for (size_t i = 0; i < templ.size(); ++i)
	{
		int x = templ[i].x;
		int y = templ[i].y;

		cocos2d::CCSprite* pSprite = cocos2d::CCSprite::create(strSprite);
		pSprite->setAnchorPoint(ccp(0, 0));
		pSprite->setPosition(
			ccp((fallingBaseX + x)*CUBE_SIZE, (fallingBaseY + y)*CUBE_SIZE));

		mLayer->addChild(pSprite);
		pSprites[x][y] = pSprite;
	}

}