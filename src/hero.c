#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include "hero.h"
const int sautHauteur = 5;

void heroInit(hero *perso)
{
	perso->x=1;
	perso->y=1;
	perso->sol=0;
	perso->saut=0;
}
void gauche (hero *perso,  map *hmap)
{
	perso->x--;
	
}
void droite (hero *perso,  map *hmap)
{
	perso->x++;
	
}
int getPosiX (const hero *perso)
{
	return perso->x;
}
int getPosiY (const hero *perso)
{
	return perso->y;
}
void gravitation(hero *perso, map *hmap)
{
	if (perso->sol!=1)
	{
		if(perso->saut!=1)
		{
			if(hmap->tab[perso->y+1][perso->x]!='#')
			{
				perso->y++;
			
				/*hmap->tab[perso->y-1][perso->x]=' ';

				mapAffiche(hmap);
				sleep(1);
				system("clear");*/
				usleep(30000);
			
			}
			else
			{
				perso->sol=1;
			}
		}
		/*mapAffiche(hmap);*/
	}
}

void positionHero(hero *perso, map *hmap)
{
	
	
}

void sautPerso(hero *perso)
{

	if(perso->saut >= 1)
	{
		
		if(perso->saut<sautHauteur)
		{
			perso->y--;
			usleep(30000);
			perso->saut++;
		}
		else
		{
			perso->saut = 0;
			perso->sol=0;
		}	
		
		
	}
	
}





















