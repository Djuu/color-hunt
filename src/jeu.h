#ifndef _JEU
#define _JEU

#include "hero.h"

typedef struct
{
	hero perso;
	map gMap;
}Jeu;

void control(Jeu *jeu, const char touche);
map *jeuGetMap(Jeu *);
hero *jeuGetHero(Jeu *);
void jeuInit(Jeu *);


#endif
