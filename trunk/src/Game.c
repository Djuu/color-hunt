#include "Game.h"



void left(Game *pGame)
{
	Map *pMap = getGameMap(pGame);
	Character *pChar = getGameChar(pGame);
	if(pMap->tab[(int)(pChar->cPosi.y)][(int)(pChar->cPosi.x)-1]!='#')
		pChar->cPosi.x-=1;
	
	
}

void right(Game *pGame)
{
	Map *pMap = getGameMap(pGame);
	Character *pChar = getGameChar(pGame);
	if(pMap->tab[(int)(pChar->cPosi.y)][(int)(pChar->cPosi.x)+1]!='#')
		pChar->cPosi.x+=1;
	
}

void jump(Game *pGame)
{
	/*	if(perso->saut == 1 && hmap->tab[perso->y-1][perso->x]!= '#')
		{
		
			if(perso->air<sautHauteur)
			{
				perso->y--;
				usleep(300);
				perso->air++;
			}
			else
			{
				perso->sol=0;
				perso->saut=0;
				perso->air=0;
			}	
			
		
		}
		if(hmap->tab[perso->y-1][perso->x]== '#')
		{
			perso->air=0;
			perso->sol=0;
			perso->saut = sautHauteur;
		}
*/
	
}

void controlKey(Game *pGame, const char key)
{ 
	
	switch(key)
	{
		case 'g':
			left (pGame);
			break;
		case 'd':
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
	pGame->gChar.cPosi.v_x = 0.2;
	pGame->gChar.cPosi.v_grav = 0.08;
	pGame->gChar.cPosi.v_saut = -0.01;
	pGame->gChar.cPosi.v_y =pGame->gChar.cPosi.v_saut;
}
