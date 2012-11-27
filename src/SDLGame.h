#ifndef _SDLGAME
#define _SDLGAME

#include <assert.h>
#include <time.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include "Game.h"
#include "Animation.h"


/*Direction du sprite*/
#define down 	0
#define left 	1
#define right 	2
#define up 		3




typedef struct
{
	Game pGame;
	Sprite pSprite;
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
Precontition : SdlGame non initialise
Poscondition : SdlGame initialise
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
