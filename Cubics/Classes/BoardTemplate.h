#pragma once
#include "cocos2d.h"

struct CubePosition
{
	int x;
	int y;
};
typedef std::vector<CubePosition> BoardTemplate;
typedef std::vector<BoardTemplate> BoardTemplateVector;
typedef std::vector<BoardTemplateVector> BoardTemplateDataBase;

class BoardTemplateManager
{
public:
	BoardTemplateManager();
	~BoardTemplateManager();

	void init();
	const BoardTemplate& getBoardTemplate(int type, int index);

protected:
	void createDataBase();

protected:
	BoardTemplateDataBase mDataBase;
};