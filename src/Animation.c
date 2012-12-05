#include "Animation.h"
#include "SDLGame.h"
#include <time.h>
#include <assert.h>


void InitSprite (Sprites *pSprites,int id, int w,int h, int nbFrame, int reFrame)
{
	
	pSprites->nbSprite =id+1; /*nombre de sprite*/
	//pSprites->aSprite = calloc(id+1, sizeof(Sprite));
	pSprites->aSprite[id].width = w;
	pSprites->aSprite[id].height = h;
	pSprites->direction = 0;
	pSprites->aSprite[id].nbFrame = nbFrame;
	pSprites->aSprite[id].reFrame = reFrame;
	pSprites->aSprite[id].end=1;
	pSprites->frame = 0;
	pSprites->position = 16;

}
void displaySprite(Sprites *pSprites, SDL_Rect posi, SDL_Surface *screen)
{
	pSprites->aSprite[pSprites->position].rcSprite.y=pSprites->aSprite[pSprites->position].height*pSprites->position;
	pSprites->aSprite[pSprites->position].rcSprite.x=pSprites->aSprite[pSprites->position].width*pSprites->frame;
	
	pSprites->aSprite[pSprites->position].rcSprite.w=pSprites->aSprite[pSprites->position].width;
	pSprites->aSprite[pSprites->position].rcSprite.h=pSprites->aSprite[pSprites->position].height;
	
	SDL_BlitSurface(pSprites->source, &(pSprites->aSprite[pSprites->position].rcSprite), screen, &posi);
}

void freeSprite(Sprites *pSprites)
{
		assert(pSprites->aSprite!=NULL);
		free(pSprites->aSprite);
}
/*
void DisplaySprite (Sprite* pSprite, SDL_Rect pos, int dir, SDL_Surface *screen)
{
    pSprite->source.x = TAILLE_SPRITE * pSprite->frame;
    pSprite->source.y = 48*dir;
    pSprite->source.w = pSprite->largeur;
    pSprite->source.h = pSprite->hauteur;
    SDL_BlitSurface(pSprite->sprite, &(pSprite->source), screen, &pos);
    SDL_Flip(screen);
}
*/
void animSprite (Sprites* pSprites, int id, int loop, int dir)
{
	float clockCurrent =  (float)clock()/(float)CLOCKS_PER_SEC;
	static float clockPrevious = 0.0;
	float speedSprite=(1.0/(float)(pSprites->aSprite[id].nbFrame+3));
  //  Uint8 *keystate = SDL_GetKeyState(NULL);
    pSprites->position = id;
    pSprites->direction = dir;

	if (clockCurrent-clockPrevious > speedSprite)
		{
				pSprites->frame++; 
				clockPrevious=clockCurrent;
		}

		
		
		if (loop == 0)	
		{
			if(pSprites->frame >= (pSprites->aSprite[id].nbFrame))
			{
				
				pSprites->frame = pSprites->aSprite[id].reFrame;
			}
		}
//		printf("loop = %d\n", loop);
		if(pSprites->aSprite[id].end==0 && loop == 1)
		{
	
			if(pSprites->frame == pSprites->aSprite[id].nbFrame)
			{
				pSprites->aSprite[id].end=1;
		
			}
		}
		
		
}
