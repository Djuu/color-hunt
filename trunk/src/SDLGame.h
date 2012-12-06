#ifndef _SDLGAME
#define _SDLGAME

// #include <assert.h>
// #include <time.h>
#include <SDL/SDL_image.h>
// #include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include "Game.h"
#include "Animation.h"


/*Direction du sprite*/
#define right 		0
#define left 		1
#define attackR		2
#define attackL		3
#define attackFR	4
#define attackFL	5
#define KOR			12
#define KOL			13
#define fireBallR	0
#define fireBallL	1
#define stayR 		16
#define stayL 		17



typedef struct
{
	int kLeft;
	int kRight;
	int kJump;
	int kUp;
	int kDown;
	int kCtrl;
	int kShift;
}Key;

typedef struct
{
	Game pGame;
	Sprites pSprites;
	Sprites pSpritesObject;
	Key pKey;
	SDL_Surface *surfaceScreen;
	SDL_Surface *surfaceChar;
	SDL_Surface *surfaceFire;
	SDL_Surface *surfaceFireBall;
	SDL_Surface *surfaceEarth;
	SDL_Surface **surfaceEnemies;
	SDL_Surface *surfaceGrass;
	SDL_Surface *surfaceBG;
	SDL_Surface *surfaceLifeBG;
	SDL_Surface *surfaceLife;
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
