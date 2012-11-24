#include "Game.h"



void initGame (Game *pGame, const char* Map)
{
	int i,j,e;
	initChar(&(pGame -> gChar));
	initEnemy(&(pGame -> gEnemies), 5);
	
	pGame->level = 1;
	e=0;
	mapInit(&(pGame -> gMap),Map);
	for (j=0;j<pGame->gMap.dimy;j++)
		for(i=0;i<pGame->gMap.dimx;i++)
			switch(pGame->gMap.tab[j][i])
			{
				case 'C':
					pGame->gChar.cPosi.x = i;
					pGame->gChar.cPosi.y = j;
				break;
				case 'E':
					pGame->gEnemies.eEnemy[e].eChar.cPosi.x = i;
					pGame->gEnemies.eEnemy[e].eChar.cPosi.y = j;
					e++;
				break;
			}	

}

void warpMap (Game *pGame)
{
	Map *pMap=getGameMap(pGame);
	Character *pChar= getGameChar(pGame);
	int i,j;
	for (j=0;j<pMap->dimy;j++)
		for(i=0;i<pMap->dimx;i++)
			switch(getMapXY(pMap, (int)(pChar->cPosi.x-0.5), (int)(pChar->cPosi.y-0.5)))
			{
				case'2' : 
					initGame(pGame,"Map/Map2.txt");
					pGame->level = 2;
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
			if (pGame -> gChar.cPosi.air != 1)
			left (pGame);
			break;
		case 'd':
			if (pGame -> gChar.cPosi.air != 2)
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


Enemies *getGameEnemies(Game *pGame)
{
	return &(pGame -> gEnemies);
}

void collisionMap (Game *pGame)
{
	int j;
	Position *posiChar;
	Enemies *pEnemies;
	Map *pMap;
	Character * pChar;

	pChar = getGameChar(pGame);
	pMap = getGameMap(pGame);
	posiChar = &(pGame -> gChar.cPosi);
	pEnemies = &(pGame -> gEnemies);

// Collision Ennemies / Map
	for(j=0;j<pEnemies->number; j++)
	{
		pEnemies->eEnemy[j].eChar.cPosi.v_x *=pathMap(&(pEnemies->eEnemy[j].eChar.cPosi),pMap);
		pEnemies->eEnemy[j].eChar.cPosi.v_y *=pathMap(&(pEnemies->eEnemy[j].eChar.cPosi),pMap);

		pEnemies->eEnemy[j].eChar.cPosi.y+=pEnemies->eEnemy[j].eChar.cPosi.v_y;
		pEnemies->eEnemy[j].eChar.cPosi.x+=pEnemies->eEnemy[j].eChar.cPosi.v_x;

		if (getMapXY(pMap, (int)(pEnemies->eEnemy[j].eChar.cPosi.x), (int)(pEnemies->eEnemy[j].eChar.cPosi.y+1.5))=='#' || 
		getMapXY(pMap, (int)(pEnemies->eEnemy[j].eChar.cPosi.x+1), (int)(pEnemies->eEnemy[j].eChar.cPosi.y+1.5))=='#')
		{
			pEnemies->eEnemy[j].eChar.floor = 1;
		} 
		else
		{
			pEnemies->eEnemy[j].eChar.floor = 0;
		
		}
	}

//Collision Hero / Map
	posiChar->v_y*=pathMap (posiChar, pMap);
	posiChar->v_x*=pathMap (posiChar, pMap);
	
	posiChar->y+=posiChar->v_y;
	posiChar->x+=posiChar->v_x;
	
	if (getMapXY(pMap, (int)(posiChar->x), (int)(posiChar->y+1.5))=='#' || 
	    getMapXY(pMap, (int)(posiChar->x+1), (int)(posiChar->y+1.5))=='#')
	{
		pChar->floor = 1;
	} 
	else
	{
		pChar->floor = 0;
		
	}
	
}

void collision(Game *pGame)
{
	int j;
	Position *posiChar;
	Enemies *pEnemies;
	posiChar = &(pGame -> gChar.cPosi);
	pEnemies = &(pGame -> gEnemies);

//Collision Hero/Ennemies , Ennemies/Hero
	for(j=0;j<pEnemies->number; j++)
	{
		
		posiChar->v_x *=path(posiChar, &(pEnemies->eEnemy[j].eChar.cPosi));
		posiChar->v_y *=path(posiChar, &(pEnemies->eEnemy[j].eChar.cPosi));
		pEnemies->eEnemy[j].eChar.cPosi.v_x *=path(posiChar, &(pEnemies->eEnemy[j].eChar.cPosi));
		pEnemies->eEnemy[j].eChar.cPosi.v_y *=path(posiChar, &(pEnemies->eEnemy[j].eChar.cPosi));

	}
	
}


