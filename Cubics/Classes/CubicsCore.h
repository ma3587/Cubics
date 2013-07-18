#pragma once

#include "cocos2d.h"

using namespace cocos2d;

// Cube class, represent single square
class Cube
{
public:
	Cube()
		: mTypeIndex(0)
		, mPosX(0)
		, mPosY(0)
		, mSprite(NULL)
	{}

public:
	int mTypeIndex;
	int mPosX;
	int mPosY;
	CCSprite* mSprite;
};


//	class Board, contains lots of cubes
class Board
{
public:
	Board(CCLayer* parent);
	virtual ~Board();

	int getPosX() { return mPosX; }
	int setPosX(int x);
	int getPosY() { return mPosY; }
	int setPosY(int y);

	CCLayer* getLayer() { return mLayer; }
	const std::vector<Cube*>& getCubes() { return mCubes; }

	virtual bool collide(const Board& board) {}
	virtual void changeShape() {}
	virtual void merge(const Board& board) {}
	CCLayer* GetLayer() { return mLayer; }


protected:
	CCLayer* mLayer;
	std::vector<Cube*> mCubes;
	int mPosX;
	int mPosY;
};
