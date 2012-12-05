#include "Game.h"



void initGame (Game *pGame, const char* Map)
{
	int i,j, k;
	initChar(&(pGame -> gChar));
	initEnemy(&(pGame -> gEnemies), 5);
	initObjects(&(pGame ->gObjects),10,1);
	k=0;
	pGame->level = 1;
	
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
					pGame->gEnemies.eEnemy[k].eChar.cPosi.x = i;
					pGame->gEnemies.eEnemy[k].eChar.cPosi.y = j;
					k++;
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
					initGame(pGame,"Map/Map1.txt");
					pGame->level = 2;
				break;
			}
}
void initSpeedX(Game *pGame)
{
	Character *pChar = getGameChar(pGame);
	pChar->cPosi.v_x=0;

}

void initSpeedY(Game *pGame)
{
	Character *pChar = getGameChar(pGame);
	pChar->cPosi.v_y=0;
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

void up(Game *pGame)
{

	Character *pChar = getGameChar(pGame);
	pChar->cPosi.v_y=-0.5;
	
}

void down(Game *pGame)
{

	Character *pChar = getGameChar(pGame);
	pChar->cPosi.v_y=0.5;
	
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
			if(pGame->gChar.attack ==0 )
			{
				if (pGame -> gChar.air != 1)
				left (pGame);
			}
			break;
		case 'd':
			if(pGame->gChar.attack ==0 )
			{
				if (pGame -> gChar.air != 2)
				right (pGame);
			}
			break;
		case 's':
			jump (pGame);
			break;		
		case 'a':
			attack(pGame);
			break;
		case'A':
			superAttack(pGame);
			break;
	}
}

void controlKey2(Game *pGame, const char key)
{ 
	
	switch(key)
	{
		case 'g':
			left (pGame);
			break;
		case 'd':
			right (pGame);
			break;
		case 'h':
			up (pGame);
			break;	
		case 'b':
			down (pGame);
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

Objects *getGameObjects(Game *pGame)
{
	return &(pGame -> gObjects);
}


Enemies *getGameEnemies(Game *pGame)
{
	return &(pGame -> gEnemies);
}

void collisionMap (Character *pChar, Map *pMap)
{
	
	pChar->cPosi.v_y*=pathMap (pChar, pMap);
	pChar->cPosi.v_x*=pathMap (pChar, pMap);
	
	pChar->cPosi.y+=pChar->cPosi.v_y;
	pChar->cPosi.x+=pChar->cPosi.v_x;
	
	if (getMapXY(pMap, (int)(pChar->cPosi.x), (int)(pChar->cPosi.y+pChar->cPosi.spriteSizeH+1))=='#' || 
	    getMapXY(pMap, (int)(pChar->cPosi.x+pChar->cPosi.spriteSizeW), (int)(pChar->cPosi.y+pChar->cPosi.spriteSizeH+1))=='#')
	{
		pChar->floor = 1;
	} 
	else
	{
		pChar->floor = 0;
		
	}
	
}

void action(Game *pGame, float power)
{
	if (pGame->gChar.attack != 1 && pGame->gChar.superAttack != 1)
	{
		pGame->gChar.cPosi.v_x+=power/5;
		pGame->gChar.cPosi.v_y=-0.2;
	}
}

void attack(Game *pGame)
{
	int i;
	int e=0;
	Character *pChar = getGameChar(pGame);
	for(i=0;i<pGame->gEnemies.number;i++)
	{
		//printf("ATTACk  =  %d ",collision(&(pChar->cPosi),&(pGame->gEnemies.eEnemy[i].eChar.cPosi)));
		if(collision(&(pChar->cPosi),&(pGame->gEnemies.eEnemy[i].eChar.cPosi))==2 )
		{
			if (e==0)
			{
				pGame->gEnemies.eEnemy[i].eChar.life -=30;
				printf("Enemy %d HP ====== %d \n",i,pGame->gEnemies.eEnemy[i].eChar.life);
				
				//printf("SIZE = %f \n",pChar->cPosi.spriteSizeW);
				e=1;

			}
			
			
		}
		printf("SIZE = %f \n",pChar->cPosi.spriteSizeW);
	}
	
}

void superAttack(Game *pGame)
{
	Character *pChar = getGameChar(pGame);
	Objects *pObjects = getGameObjects(pGame);

	pObjects -> oObject[1].oPosi.x = pChar->cPosi.x;
	pObjects -> oObject[1].oPosi.y =pChar->cPosi.y;
	moveObjectR(&(pObjects -> oObject[1]));
	
	

}

