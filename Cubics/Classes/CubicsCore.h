#pragma once
#include "cocos2d.h"
#include "BoardTemplate.h"

class CubeManager
{
public:
	enum ENUM_DIRECTION
	{
		ED_LEFT = 0,
		ED_RIGHT,
		ED_DOWN,
	};

	enum
	{
		CUBE_SIZE = 80,
		FALLING_BOARD_WIDTH = 4,
		FALLING_BOARD_HEIGHT = 4,
		MAIN_BOARD_WIDTH = 10,
		MAIN_BOARD_HEIGHT = 22,
		BOARD_TYPE = 6,
	};

public:
	CubeManager();
	~CubeManager();

	bool init(cocos2d::CCLayer* layer);
	void step(float dt);
	void stepDown();
	void move(ENUM_DIRECTION direction);
	void transform();

	int getScore() const { return mScore; }
	bool isFallingActive() const { return mFallingActive; }
	bool isGameOver() const { return mGameOver; }
	void setGameOver(bool gameOver) { mGameOver = gameOver; }

protected:
	bool generateFallingBoard();
	bool collide(ENUM_DIRECTION direction);
	bool collide(int fallingBaseX, int fallingBaseY, int boardType, int boardIndex);

	void mergeFalling();
	bool checkFullLines();
	void clearFullLines();
	void clearFullLine(int line);

private:
	void generateBoardSprite( cocos2d::CCSprite* pSprites[][FALLING_BOARD_HEIGHT], 
		int fallingBaseX, int fallingBaseY, int boardType, int boardIndex );

protected:

	cocos2d::CCSprite* mFallingSprites[FALLING_BOARD_WIDTH][FALLING_BOARD_HEIGHT];
	cocos2d::CCSprite* mNextFallingSprites[FALLING_BOARD_WIDTH][FALLING_BOARD_HEIGHT];
	cocos2d::CCSprite* mMainSprites[MAIN_BOARD_WIDTH][MAIN_BOARD_HEIGHT];
	cocos2d::CCLayer* mLayer;

	int mScore;
	bool mGameOver;

	bool mFallingActive;
	int mFallingBaseX;
	int mFallingBaseY;
	int mFallingType;
	int mFallingIndex;

	int mNextFallingBaseX;
	int mNextFallingBaseY;
	int mNextFallingType;
	int mNextFallingIndex;

	BoardTemplateManager mBoardTemplateManager;
};


