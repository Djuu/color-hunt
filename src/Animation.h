#ifndef _ANIMATION
#define _ANIMATION
#include <SDL/SDL.h>

 


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
	int frame; 
	int position;
	
}Sprites;

/**
Precondition : SDL_Surface implemente

*/
void InitSprite (Sprites *pSprites,int id, int w,int h, int nbFrame, int reFrame);
void animSprite (Sprites* pSprites, int id, int loop, int dir);
void displaySprite(Sprites *pSprites, SDL_Rect posi, SDL_Surface *screen);
void freeSprite(Sprites *pSprites);
void fire(SDL_Surface *pSurface);
void displayGauge(SDL_Surface *pSurfaceBG, SDL_Surface *pSurface , SDL_Surface *screen, int value);

#endif
