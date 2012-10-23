#include "Character.h"

void initChar (Character *pChar)
{
	pChar -> pPosi.x = 0;
	pChar -> pPosi.y = 0;
	pChar -> pPosi.z = 0;
	pChar-> floor = 0;
	pChar-> air = 0;
	setLife(pChar-> life, 100);
	setMana(pChar-> mana, 0);
	pChar-> attack = 0;
	pChar-> superAttack = 0;
}

Position *getPosiChar (const Character *pChar)
{
	assert(pChar != NULL);
	return pChar -> pPosi;
}

void setPosiChar (Character *pChar, const float x, const float y, const float z)
{
	assert(pChar != NULL);
	pChar -> pPosi.x = x;
	pChar -> pPosi.y = y;
	pChar -> pPosi.z = z;
}

int getLife (const Character *pChar)
{
	assert(pChar -> life >= 0 || pChar -> life <= 100);
	return pChar -> life;
}

void setLife (Character pChar, int nbLife)
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
	assert(nbLife >= 0 || nbLife <= 0);
	pChar -> mana = nbMana;
}

