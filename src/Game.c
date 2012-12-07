#include "Game.h"
#include <math.h>


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
			if(pGame->gChar.attack == 0)
			{
				if (pGame -> gChar.air != 2)
				right (pGame);
			}
			break;
		case 's':
			jump (pGame);
			break;		
		case 'a':
			pGame->gChar.attack = 1;
			break;
		case'A':
			pGame->gChar.superAttack = 1;
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
int distanceEnemies(Game *pGame)
{
		float distance=1000;
		float diff;
		float diffY;
		int id=-1;
		int i;
		for (i=0; i<pGame->gEnemies.number; i++)
		{
			diff = fabs(pGame->gEnemies.eEnemy[i].eChar.cPosi.x - pGame->gChar.cPosi.x);
			diffY = fabs(pGame->gEnemies.eEnemy[i].eChar.cPosi.y - pGame->gChar.cPosi.y);
			if (distance > diff && diffY <2)
			{
				id=i;
			}
		
			distance=diff;
		}
		
		
		return id;
		
}
void collisionMap (Character *pChar, Map *pMap)
{
	
	pChar->cPosi.v_y*=pathMap (pChar, pMap);
	pChar->cPosi.v_x*=pathMap (pChar, pMap);
	
	pChar->cPosi.y+=pChar->cPosi.v_y;
	pChar->cPosi.x+=pChar->cPosi.v_x;
	
	if (getMapXY(pMap, (int)(pChar->cPosi.x), (int)(pChar->cPosi.y+pChar->cPosi.spriteSizeH+0.5))=='#' || 
	    getMapXY(pMap, (int)(pChar->cPosi.x+pChar->cPosi.spriteSizeW), (int)(pChar->cPosi.y+pChar->cPosi.spriteSizeH+0.5))=='#')
	{
		pChar->floor = 1;
	} 
	else
	{
		pChar->floor = 0;
		
	}
	
}

void projectionChar(Game *pGame, float power)
{
	int idE = distanceEnemies(pGame);
	if (pGame->gChar.attack != 1 && pGame->gChar.superAttack != 1)
	{
		if(pGame->gEnemies.eEnemy[idE].eChar.attack == 1)
		{
			pGame->gChar.cPosi.v_x+=power/5;
			pGame->gChar.cPosi.v_y=-0.2;
		}
	}
}

void attack(Game *pGame)
{
	int i;
	Character *pChar = getGameChar(pGame);
	if (pGame->gChar.attack == 0)
	{			
		pGame->gChar.domage = 1;
	}
	
	for(i=0;i<pGame->gEnemies.number;i++)
	{
		
		if(collision(&(pChar->cPosi),&(pGame->gEnemies.eEnemy[i].eChar.cPosi))==2 && pGame->gChar.attack == 1)
		{
			
			if (pGame->gChar.domage != 0)
			{

				pGame->gEnemies.eEnemy[i].eChar.life -=30;
				deadEnemy(&(pGame->gEnemies),i);
				pGame->gChar.domage = 0;
			}

		}
		

	}
	
}


void superAttack(Game *pGame)
{
	Character *pChar = getGameChar(pGame);
	Objects *pObjects = getGameObjects(pGame);

	if (pChar -> cPosi.direction == 0)
	{
		if(pObjects -> oObject[1].oPosi.x <0 && pObjects -> oObject[1].oPosi.y <0)
		{
			pObjects -> oObject[1].oPosi.x = pChar->cPosi.x;
			pObjects -> oObject[1].oPosi.y =pChar->cPosi.y;
			pObjects -> oObject[1].xS = pChar->cPosi.x;
			pObjects -> oObject[1].yS =pChar->cPosi.y;
			moveObjectR(&(pObjects -> oObject[1]));
		}
	}
	else if (pChar -> cPosi.direction == 1)
	{
		if(pObjects -> oObject[1].oPosi.x <0 && pObjects -> oObject[1].oPosi.y <0)
		{
			pObjects -> oObject[1].oPosi.x = pChar->cPosi.x;
			pObjects -> oObject[1].oPosi.y =pChar->cPosi.y;
			pObjects -> oObject[1].xS = pChar->cPosi.x;
			pObjects -> oObject[1].yS =pChar->cPosi.y;
			moveObjectL(&(pObjects -> oObject[1]));
			
		}
	}
}

void superAttackDmg(Game *pGame)
{
	int i,j;
	Objects *pObjects = getGameObjects(pGame);
	if (pGame->gChar.superAttack == 0)
	{			
		pGame->gChar.superDomage = 1;

	}
	for (i=0;i<pObjects->number;i++)
	{
		for(j=0;j<pGame->gEnemies.number;j++)
		{
			if(collision(&(pObjects -> oObject[i].oPosi),&(pGame->gEnemies.eEnemy[j].eChar.cPosi)) != 0 && pGame->gChar.superAttack == 0)
			{
				if (pGame->gChar.superDomage != 0)
				{
					pGame->gEnemies.eEnemy[j].eChar.life -=60;
					deadEnemy(&(pGame->gEnemies),j);
					pObjects -> oObject[i].oPosi.x = -42;
					pObjects -> oObject[i].oPosi.y = -42;
					pObjects -> oObject[i].oPosi.v_y =0;
					pObjects -> oObject[i].oPosi.v_x =0;
					pGame->gChar.superDomage = 0;
				}				
			}
		}
	}
}

void helpEnemy(Game *pGame)
{
	int i,j;
	
		for (i=0; i< pGame->gEnemies.number; i++)
		{
			if (pGame->gEnemies.eEnemy[i].panic==1)
			{
				for(j=0; j< pGame->gEnemies.number ; j++)
				{
					if (i!=j)
					{
						if(collision(&(pGame->gEnemies.eEnemy[i].eChar.cPosi),&(pGame->gEnemies.eEnemy[j].eChar.cPosi)) != 0)
						{
							pGame->gEnemies.eEnemy[i].panic=-1;
							pGame->gEnemies.eEnemy[i].idHelp = j;
						}
					}
				}
			}
		}
	
	
}

/*S'applique lorsque qu'un énemie est en mode "rebel"*/
int rebel (Game *pGame)
{	
	int i;
	Character *pChar = getGameChar(pGame);
	for (i=0; i< pGame->gEnemies.number; i++)
	{
			if (pGame->gEnemies.eEnemy[i].panic == -1 && pGame->gEnemies.eEnemy[i].eChar.life>0)
			{
				if ((pGame->gEnemies.eEnemy[i].eChar.cPosi.x - pChar->cPosi.x) >0)
				{
					moveEnemyLeft(&(pGame->gEnemies), i);
					moveEnemyLeft(&(pGame->gEnemies), pGame->gEnemies.eEnemy[i].idHelp);
					return i;
				}
				else if ((pGame->gEnemies.eEnemy[i].eChar.cPosi.x - pChar->cPosi.x)<0)
				{
					moveEnemyRight(&(pGame->gEnemies), i);
					moveEnemyRight(&(pGame->gEnemies), pGame->gEnemies.eEnemy[i].idHelp);
					return i;
				}
				
			}
	}
	return -1;
}

void detect(Game *pGame)
{	
	Character *pChar = getGameChar(pGame);
	/*int nearestE = distanceEnemies(pGame);*/ /*l'enemie le plus proche*/
	int nearestE;
	int idPanic = rebel(pGame);
	helpEnemy(pGame);
	for(nearestE = 0; nearestE < pGame->gEnemies.number; nearestE++)
	{
		if (nearestE!=idPanic)
		{
			if ((pGame->gEnemies.eEnemy[nearestE].eChar.cPosi.x - pChar->cPosi.x) <= 10 && (pGame->gEnemies.eEnemy[nearestE].eChar.cPosi.x - pChar->cPosi.x) >0) 
			{
				
				if (pGame->gEnemies.eEnemy[nearestE].eChar.life>30)
				{
					moveEnemyLeft(&(pGame->gEnemies), nearestE);
				}
				else
				{
					pGame->gEnemies.eEnemy[nearestE].panic=1;
					moveEnemyRight(&(pGame->gEnemies), nearestE);
				}
			}
			else if ((pGame->gEnemies.eEnemy[nearestE].eChar.cPosi.x - pChar->cPosi.x) >= -10  && (pGame->gEnemies.eEnemy[nearestE].eChar.cPosi.x - pChar->cPosi.x)<0)
			{
				if (pGame->gEnemies.eEnemy[nearestE].eChar.life>30)
				{
					moveEnemyRight(&(pGame->gEnemies), nearestE);
				}
				else
				{
					moveEnemyLeft(&(pGame->gEnemies), nearestE);
				}
			}
		}
	}
	
}









