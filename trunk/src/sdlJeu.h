#ifndef _SDLJEU_H
#define _SDLJEU_H

#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include "jeu.h"
#include "anim.h"

typedef struct
{
	Jeu jeu;
	SDL_Surface *surfaceEcran;
	SDL_Surface *surfaceHero;
	SDL_Surface *surfaceMap;
	SDL_Rect rcSprite;
	SDL_Rect rcSpPosi;
}sdlJeu;


/**
Description : Initialisation des surfaces ecran, hero et map
*/
void sdlInitialisation(sdlJeu*);

/**
Description : Boucle principale de SDL
Paramétre : sdlJeu :DR
Variables locales : continueBoucle, rafraichissement,tempGauche,tempDroite : entier
*/
void sdlBoucle(sdlJeu*);

#endif
