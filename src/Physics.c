#include "Physics.h"

void gravity (Character *pChar)
{
	

	pChar->cPosi.x += pChar->cPosi.v_x;
	pChar->cPosi.y += pChar->cPosi.v_y;
	pChar->cPosi.v_y += pChar->cPosi.v_grav;

}
