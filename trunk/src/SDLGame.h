#ifndef _SDLGAME
#define _SDLGAME

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "Game.h"
#include "Animation.h"



/*Direction du sprite*/
#define right 		0
#define left 		1
#define attackR		2
#define attackL		3
#define attackFR	4
#define attackFL	5
#define jumpUpR 	6
#define jumpDownR	7

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
	int kCtrlR;
	int kCtrlL;
	int kShift;
}Key;

/*typedef struct
{
	int jump;
}Anim;*/

typedef struct
{
	Game pGame;
	Sprites pSprites;
	Sprites pSpritesObject;
	Sprites *pSpritesEnemy;
	Key pKey;
/*	Anim pAnim;*/
	SDL_Surface *surfaceScreen;
	SDL_Surface *surfaceChar;
	SDL_Surface *surfaceFire;
	SDL_Surface *surfaceFireBall;
	SDL_Surface *surfaceEarth;
	SDL_Surface *surfaceEnemies;
	SDL_Surface *surfaceGrass;
	SDL_Surface *surfaceBG;
	SDL_Surface *surfaceLifeBG;
	SDL_Surface *surfaceLife;
	SDL_Surface *surfaceFilter;
	SDL_Surface *surfaceBall;
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
