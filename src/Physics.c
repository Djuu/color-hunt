#include "Physics.h"

void gravity (Character *pChar, Map *pMap)
{
	if(pMap->tab[(int)(pChar->cPosi.y)+1][(int)(pChar->cPosi.x)]!='#') 
	{
		pChar->cPosi.y += pChar->cPosi.v_y;
		pChar->cPosi.v_y += pChar->cPosi.v_grav;
	}
}
