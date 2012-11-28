#ifndef _ANIMATION
#define _ANIMATION
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <assert.h>




typedef struct
{
	  int previousTime;
	  int currentTime;
	  int delay;
}timeSprite;


typedef struct
{
	timeSprite pTimeSprite;
	SDL_Surface *source;
	SDL_Rect dest;
	int width;
	int height;
	int direction;

	int frame;

}Sprite;




void InitSprite (Sprite *pSprite,SDL_Surface *nom, int w,int h);
void DestructionSprite (Sprite *pSprite);
void MoveSprite (Sprite* pSprite, int anim);

#endif
