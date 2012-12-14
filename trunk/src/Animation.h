#ifndef _ANIMATION
#define _ANIMATION
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
 


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
	float clockPrevious;
	
}Sprites;

/**
Precondition : SDL_Surface implemente

*/
void InitSprite (Sprites *pSprites,int id, int w,int h, int nbFrame, int reFrame);
void animSprite (Sprites* pSprites, int id, int loop, int dir);
void displaySprite(Sprites *pSprites, SDL_Rect posi, SDL_Surface *screen);
void freeSprite(Sprites *pSprites);
void displayGauge(SDL_Surface *pSurfaceBG, SDL_Surface *pSurfaceLife , SDL_Surface * pSurfaceMana , SDL_Surface *screen, int life , int mana);
void bgBW(SDL_Surface *pSurface, double saturation);
void rotationObject(SDL_Surface *pSurface, SDL_Rect positionBall, double *angle, float speed,  SDL_Surface *screen);
void audioBG();
void audioSward();
void audioFireBall();
void audioWind();
#endif
