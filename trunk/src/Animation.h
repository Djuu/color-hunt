#ifndef _ANIMATION
#define _ANIMATION
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <assert.h>
#include <time.h>


typedef struct
{
	int width;
	int height;
	int nbFrame; /*nombre de frame*/
	int reFrame; /*le frame a partir duquel on recommence*/
	SDL_Rect rcSprite;
	int end;
	
}Sprite;

typedef struct
{
	Sprite aSprite[20];
	SDL_Surface *source;
	int nbSprite;
	int direction;
	int frame; /*le frame du debut*/
	int position;
	
}Sprites;

/**
Precondition : SDL_Surface implemente

*/
void InitSprite (Sprites *pSprites,int id, int w,int h, int nbFrame, int reFrame);
void animSprite (Sprites* pSprites, int id, int loop);
void displaySprite(Sprites *pSprites, int id);
void freeSprite(Sprites *pSprites);
#endif
