#include "Game.h"



void initGame (Game *pGame)
{
	int i,j;
	initChar(&(pGame -> gChar));
	initEnemy(&(pGame -> gEnemies), 5);
	
	mapInit(&(pGame -> gMap),"Map/Map1.txt");
	for (j=0;j<pGame->gMap.dimy;j++)
		for(i=0;i<pGame->gMap.dimx;i++)
			switch(pGame->gMap.tab[j][i])
			{
				case 'C':
					pGame->gChar.cPosi.x = i;
					pGame->gChar.cPosi.y = j;
				break;
				case 'E':
					pGame->gEnemies.eEnemy[1].eChar.cPosi.x = i;
					pGame->gEnemies.eEnemy[1].eChar.cPosi.y = j;
				break;
			}	

}

void initSpeed(Game *pGame)
{
	Character *pChar = getGameChar(pGame);
	pChar->cPosi.v_x=0;

}

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

Enemy *getGameEnemies(Game *pGame, int id)
{
	return &(pGame -> gEnemies.eEnemy[id].eChar);
}

