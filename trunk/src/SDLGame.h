#ifndef _SDLGAME
#define _SDLGAME
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

#include "Game.h"
#include "Animation.h"
#include "Dialogue.h"


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
	int kReturn;
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
	Sprites pSpritesWorldMap;
	Key pKey;
	Tree pTree;
	int choiceMenu;
	int confirmMenu;
	int choiceDialogue;
	int confirmDialogue;
	int dialogue;
	float choiceSpeech;

/*Menu*/
	SDL_Surface *surfaceStart;
	SDL_Surface *surfaceExit;
	SDL_Surface *surfaceMenuBG;
	
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
	SDL_Surface *surfaceBall2;
	SDL_Surface *surfaceMana;
	
	SDL_Surface *surfaceKing;

/*Dialogue*/
	SDL_Surface *surfaceText1;/*ligne 1*/
	SDL_Surface *surfaceText2;/*ligne 2*/
	SDL_Surface *surfaceText3;/*ligne 3*/
	SDL_Surface *surfaceDial;
	SDL_Surface *surfaceDialYes;
	SDL_Surface *surfaceDialNo;
	TTF_Font *font;
	
	SDL_Surface *surfaceMapBG;
	SDL_Surface *surfaceCharMap;
	SDL_Surface *surfaceBorder;
	SDL_Surface *surfaceMapEarth1;
	SDL_Surface *surfaceMapEarth2;
	SDL_Surface *surfaceMapGrass1;
	SDL_Surface *surfaceMapGrass2;
	SDL_Surface *surfaceMapGED;
	SDL_Surface *surfaceMapGEDL;
	SDL_Surface *surfaceMapGEDR;
	SDL_Surface *surfaceMapGEL;
	SDL_Surface *surfaceMapGER;
	SDL_Surface *surfaceMapGEU;
	SDL_Surface *surfaceMapGEUL;
	SDL_Surface *surfaceMapGEUR;
	
	SDL_Surface *surfaceMapWater;
	SDL_Surface *surfaceMapWaterD;
	SDL_Surface *surfaceMapWaterL;
	SDL_Surface *surfaceMapWaterR;
	SDL_Surface *surfaceMapWaterU;
	SDL_Surface *surfaceMapWaterCDL;
	SDL_Surface *surfaceMapWaterCUL;
	SDL_Surface *surfaceMapWaterCDR;
	SDL_Surface *surfaceMapWaterCUR;
	SDL_Surface *surfaceMapCDL;
	SDL_Surface *surfaceMapCDR;
	SDL_Surface *surfaceMapCUL;
	SDL_Surface *surfaceMapCUR;
	SDL_Surface *surfaceMapTree;
	SDL_Surface *surfaceMapCastle;
	
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
