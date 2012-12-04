#include "Animation.h"



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
void displaySprite(Sprites *pSprites, int id)
{
	pSprites->aSprite[id].rcSprite.x=pSprites->aSprite[id].width*pSprites->frame;
	pSprites->aSprite[id].rcSprite.y=pSprites->aSprite[id].height*pSprites->position;
	
	pSprites->aSprite[id].rcSprite.w=pSprites->aSprite[id].width;
	pSprites->aSprite[id].rcSprite.h=pSprites->aSprite[id].height;
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
void animSprite (Sprites* pSprites, int id, int loop)
{
	float clockCurrent =  (float)clock()/(float)CLOCKS_PER_SEC;
	static float clockPrevious = 0.0;
	float speedSprite=(1.0/(float)(pSprites->aSprite[id].nbFrame+3));
    Uint8 *keystate = SDL_GetKeyState(NULL);
    pSprites->position = id;
    if (id == 0)
    {
		pSprites->direction=0;
	}
	else if(id==1)
	{
		pSprites->direction=1;
	
	}
	

	printf("temp = %f\n",speedSprite);
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
		if(pSprites->aSprite[id].end==0 && loop == 1)
		{
			if(pSprites->frame == pSprites->aSprite[id].nbFrame+1)
			{
				pSprites->aSprite[id].end=1;
				pSprites->frame=0;			
			}
		}
	

}
