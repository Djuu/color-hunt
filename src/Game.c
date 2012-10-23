#include "Game.h"


void controlKey(Game *pGame, const char key)
{ 
	
	switch(key)
	{
		case 'g':
			left (getGameChar(pGame), getGameMap(pGame));
			break;
		case 'd':
			right (getGameChar(pGame), getGameMap(pGame));
			break;
		case 's':
			jump (getGameChar(pGame), getGameMap(pGame));
			break;		
	}
}

void left(Game *pGame)
{
	Map *pMap = getGameMap(pGame);
	Character *pChar = getGameChar(pGame);
	if(pMap->tab[pChar->y][pChar->x-1]!='#')
		pChar->x--;
}

void right(Game *pGame)
{
	Map *pMap = getGameMap(pGame);
	Character *pChar = getGameChar(pGame);
	if(pMap->tab[pChar->y][pChar->x+1]!='#')
		pChar->x++;
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


Map *getGameMap(Game *pGame)
{
	return &(pGame -> pMap);
}

Character *getGameChar(Game *pGame)
{
	return &(pGame -> pChar);
}

void initGame (Game *pGame)
{
	heroInit(&(pGame -> pChar));
	mapInit(&(pGame -> pMap));	
}
