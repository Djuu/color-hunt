#include "Character.h"

void initChar (Character *pChar)
{
	pChar->cPosi.v_x = 0;/*0.2*/
	pChar->cPosi.v_y=0;
	pChar->cPosi.v_grav = 0.08;/*0.02*/
	pChar-> floor = 0;
	pChar->cPosi.air = 0;
	setLife(pChar, 100);
	setMana(pChar, 0);
	pChar-> attack = 0;
	pChar-> superAttack = 0;
}

Position getPosiChar (const Character *pChar)
{
	assert(pChar != NULL);
	return pChar -> cPosi;
}

void setPosiChar (Character *pChar, const float x, const float y, const float z)
{
	assert(pChar != NULL);
	pChar -> cPosi.x = x;
	pChar -> cPosi.y = y;
	pChar -> cPosi.z = z;
}

int getLife (const Character *pChar)
{
	assert(pChar -> life >= 0 || pChar -> life <= 100);
	return pChar -> life;
}

void setLife (Character *pChar, int nbLife)
{
	assert(nbLife >= 0 || nbLife <= 0);
	pChar -> life = nbLife;
}

int getMana (const Character *pChar)
{
	assert(pChar -> mana >= 0 || pChar -> mana <= 100);
	return pChar -> mana;
}

void setMana (Character *pChar, int nbMana)
{
	assert(nbMana >= 0 || nbMana <= 0);
	pChar -> mana = nbMana;
}

