#include "jeu.h"


void control(Jeu *jeu, const char touche)
{ 
	switch(touche)
	{
		case 'g':
			gauche (&(jeu->perso), &(jeu->gMap));
			break;
		case 'd':
			droite (&(jeu->perso), &(jeu->gMap));
			break;
		case 's':
			sautPerso(&(jeu->perso));
			break;
	}
}

map *jeuGetMap(Jeu *pJeu)
{
	return &(pJeu->gMap);
}

hero *jeuGetHero(Jeu *pJeu)
{
	return &(pJeu->perso);
}

void jeuInit(Jeu * pJeu)
{
	heroInit(&(pJeu->perso));
	mapInit(&(pJeu->gMap));
	
	
}
