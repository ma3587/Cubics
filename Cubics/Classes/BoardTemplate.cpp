#include "BoardTemplate.h"

#define BEGIN_INSERT()\
{\
	templ.clear(); \
} while(0)

#define END_INSERT()\
{\
	vecTemplate.push_back(templ); \
} while(0)

#define BEGIN_TEMPLATE()\
{\
	vecTemplate.clear();\
} while(0)

#define END_TEMPLATE()\
{\
	mDataBase.push_back(vecTemplate);\
} while(0)

#define INSERT_POS(_X_, _Y_) \
{\
	pos.x = _X_;\
	pos.y = _Y_;\
	templ.push_back(pos);\
} while(0)

BoardTemplateManager::BoardTemplateManager()
{

}

BoardTemplateManager::~BoardTemplateManager()
{

}

void BoardTemplateManager::init()
{
	createDataBase();
}

void BoardTemplateManager::createDataBase()
{
	mDataBase.clear();
	BoardTemplateVector vecTemplate;
	BoardTemplate templ;
	CubePosition pos;

	// I
	BEGIN_TEMPLATE();
	BEGIN_INSERT();
	INSERT_POS(0, 1);
	INSERT_POS(1, 1);
	INSERT_POS(2, 1);
	INSERT_POS(3, 1);
	END_INSERT();
	
	BEGIN_INSERT();
	INSERT_POS(1, 0);
	INSERT_POS(1, 1);
	INSERT_POS(1, 2);
	INSERT_POS(1, 3);
	END_INSERT();
	END_TEMPLATE();

	// O
	BEGIN_TEMPLATE();
	BEGIN_INSERT();
	INSERT_POS(1, 1);
	INSERT_POS(1, 2);
	INSERT_POS(2, 1);
	INSERT_POS(2, 2);
	END_INSERT();
	END_TEMPLATE();

	// L
	BEGIN_TEMPLATE();
	BEGIN_INSERT();
	INSERT_POS(1, 1);
	INSERT_POS(1, 2);
	INSERT_POS(1, 3);
	INSERT_POS(2, 1);
	END_INSERT();

	BEGIN_INSERT();
	INSERT_POS(1, 1);
	INSERT_POS(1, 2);
	INSERT_POS(2, 2);
	INSERT_POS(3, 2);
	END_INSERT();

	BEGIN_INSERT();
	INSERT_POS(1, 2);
	INSERT_POS(2, 2);
	INSERT_POS(2, 1);
	INSERT_POS(2, 0);
	END_INSERT();

	BEGIN_INSERT();
	INSERT_POS(0, 1);
	INSERT_POS(1, 1);
	INSERT_POS(2, 1);
	INSERT_POS(2, 2);
	END_INSERT();
	END_TEMPLATE();

	// J
	BEGIN_TEMPLATE();
	BEGIN_INSERT();
	INSERT_POS(1, 1);
	INSERT_POS(2, 1);
	INSERT_POS(2, 2);
	INSERT_POS(2, 3);
	END_INSERT();

	BEGIN_INSERT();
	INSERT_POS(1, 2);
	INSERT_POS(1, 1);
	INSERT_POS(2, 1);
	INSERT_POS(3, 1);
	END_INSERT();

	BEGIN_INSERT();
	INSERT_POS(2, 2);
	INSERT_POS(1, 2);
	INSERT_POS(1, 1);
	INSERT_POS(1, 0);
	END_INSERT();

	BEGIN_INSERT();
	INSERT_POS(0, 2);
	INSERT_POS(1, 2);
	INSERT_POS(2, 2);
	INSERT_POS(2, 1);
	END_INSERT();
	END_TEMPLATE();

	// Z
	BEGIN_TEMPLATE();
	BEGIN_INSERT();
	INSERT_POS(0, 2);
	INSERT_POS(1, 2);
	INSERT_POS(1, 1);
	INSERT_POS(2, 1);
	END_INSERT();

	BEGIN_INSERT();
	INSERT_POS(1, 1);
	INSERT_POS(1, 2);
	INSERT_POS(2, 2);
	INSERT_POS(2, 3);
	END_INSERT();
	END_TEMPLATE();

	// S
	BEGIN_TEMPLATE();
	BEGIN_INSERT();
	INSERT_POS(0, 1);
	INSERT_POS(1, 1);
	INSERT_POS(1, 2);
	INSERT_POS(2, 2);
	END_INSERT();

	BEGIN_INSERT();
	INSERT_POS(1, 3);
	INSERT_POS(1, 2);
	INSERT_POS(2, 2);
	INSERT_POS(2, 1);
	END_INSERT();
	END_TEMPLATE();
}

const BoardTemplate& BoardTemplateManager::getBoardTemplate( int type, int index )
{
	int iRealType = type % mDataBase.size();
	int iRealIndex = index % mDataBase[iRealType].size();
	return mDataBase[type][iRealIndex];
}