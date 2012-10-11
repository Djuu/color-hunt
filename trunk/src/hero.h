#ifndef _HERO
#define _HERO

#include "map.h"

typedef struct
{
	int x,y;
	int sol;
	int saut,air;
}hero;


/*Déplacement gauche-droite*/
void gauche (hero *perso, map *hmap);
void droite (hero *perso, map *hmap);
int getPosiX (const hero *perso);
int getPosiY (const hero *perso);
void gravitation(hero *perso, map *hmap);
void positionHero(hero *perso, map *hmap);
void sautPerso(hero *perso, map *hmap);
void heroInit(hero *perso);
#endif
