#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include "hero.h"
const int sautHauteur = 5;

void heroInit(hero *perso)
{
	perso->x=1;
	perso->y=25;
	perso->sol=0;
	perso->saut=0;
}
void gauche (hero *perso,  map *hmap)
{
	if(hmap->tab[perso->y][perso->x-1]!='#')
		perso->x--;
	
}
void droite (hero *perso,  map *hmap)
{
if(hmap->tab[perso->y][perso->x+1]!='#')
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
		if(hmap->tab[perso->y+1][perso->x]!='#' && perso -> sol == 0)
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
		
		/*mapAffiche(hmap);*/
	
}

void positionHero(hero *perso, map *hmap)
{
	
	
}

void sautPerso(hero *perso, map *hmap)
{
		if(perso->saut >= 1 && hmap->tab[perso->y-1][perso->x]!= '#')
		{
		
			if(perso->saut<sautHauteur)
			{
				perso->y--;
				usleep(300);
				perso->saut++;
			}
			else
			{
				perso->sol=0;
			}	
			
		
		}
		if(hmap->tab[perso->y-1][perso->x]== '#')
		{
			perso->sol=0;
			perso->saut = sautHauteur;
		}
	
}





















