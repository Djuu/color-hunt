#ifndef _SDLGAME
#define _SDLGAME

#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include "Game.h"


typedef struct
{
	Game pGame;
	SDL_Surface *surfaceScreen;
	SDL_Surface *surfaceChar;
	SDL_Surface *surfaceEarth;
	SDL_Surface *surfaceEnemy;
	SDL_Rect rcSprite;
	SDL_Rect rcSpPosi;
	SDL_Rect rectScreen;
	float scrollX;
	float scrollY;
}SdlGame;


/**
Description : Initialisation des surfaces ecran, hero et map
*/
void initSDL(SdlGame*);

/**
Description : Boucle principale de SDL
Paramétre : sdlJeu :DR
Variables locales : continueBoucle, rafraichissement,tempGauche,tempDroite : entier
*/
void loopSDL(SdlGame*);

#endif
