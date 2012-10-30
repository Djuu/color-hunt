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
