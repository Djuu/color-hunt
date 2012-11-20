#include "Game.h"



void left(Game *pGame)
{

	Character *pChar = getGameChar(pGame);

	pChar->cPosi.v_x=-0.5;
	
}

void right(Game *pGame)
{

	Character *pChar = getGameChar(pGame);
	pChar->cPosi.v_x=0.5;
	
}

void jump(Game *pGame)
{
	if(pGame->gChar.floor == 1)
	pGame->gChar.cPosi.v_y = -1;
	
}

void controlKey(Game *pGame, const char key)
{ 
	
	switch(key)
	{
		case 'g':
			if (pGame -> gChar.air != 1)
			left (pGame);
			break;
		case 'd':
			if (pGame -> gChar.air != 2)
			right (pGame);
			break;
		case 's':
			jump (pGame);
			break;		
	}
}

Map *getGameMap(Game *pGame)
{
	return &(pGame -> gMap);
}

Character *getGameChar(Game *pGame)
{
	return &(pGame -> gChar);
}

void initGame (Game *pGame)
{
	int i,j;
	initChar(&(pGame -> gChar));
	mapInit(&(pGame -> gMap),"Map/Map2.txt");	
	for(j=0;j<pGame -> gMap.dimy;++j)
		for(i=0;i<pGame -> gMap.dimx;++i)
			switch(pGame -> gMap.tab[j][i])
			{
				case 'C':
					pGame -> gChar.cPosi.x = i;
					pGame -> gChar .cPosi.y = j;
				break;
			}
	
	pGame->gChar.cPosi.v_grav = 0.08;/*0.02*/
}

void initSpeed(Game *pGame)
{
	Character *pChar = getGameChar(pGame);
	pChar->cPosi.v_x=0;

}
