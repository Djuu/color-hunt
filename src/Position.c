#include "Position.h"


float getPosiX (const Position *pPosi)
{
	assert(pPosi != NULL);
	return pPosi->x;
}


float getPosiY (const Position *pPosi)
{
	assert(pPosi != NULL);
	return pPosi->y;
}

float getPosiZ (const Position *pPosi)
{
	assert(pPosi != NULL);
	return pPosi->z;
}

void setPosi (Position *pPosi, const float x, const float y, const float z)
{
	assert(pPosi != NULL); 
	pPosi -> x = x;
	pPosi -> y = y;
	pPosi -> z = z;
}

int getPosiXint(const Position *pPosi)
{
	return (int)(pPosi->x);
}

int getPosiYint(const Position *pPosi)
{
	return (int)(pPosi->y);
}

int getPosiZint(const Position *pPosi)
{
	return (int)(pPosi->z);
}

void refreshDirection(Position *pPosi)
{
		if (pPosi -> v_x>0)
		{
			pPosi -> direction = 0;
		}
		if (pPosi -> v_x<0)
		{
			pPosi -> direction = 1;
		}
}
