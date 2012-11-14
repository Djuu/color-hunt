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
	initChar(&(pGame -> gChar));
	mapInit(&(pGame -> gMap));	
	pGame->gChar.cPosi.v_x = 0;/*0.2*/
	pGame->gChar.cPosi.v_y=0;
	pGame->gChar.cPosi.v_grav = 0.08;/*0.02*/
	pGame->gChar.cPosi.v_saut = 0;/*0.01*/
	pGame->gChar.cPosi.v_y =pGame->gChar.cPosi.v_saut;
}

void initSpeed(Game *pGame)
{
	Character *pChar = getGameChar(pGame);
	pChar->cPosi.v_x=0;

}
