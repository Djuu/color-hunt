#include "Animation.h"
#include <time.h>
#include <assert.h>


void InitSprite (Sprites *pSprites,int id, int w,int h, int nbFrame, int reFrame)
{
	
	pSprites->nbSprite =id+1; /*nombre de sprite*/
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
	float speedSprite=(1.0/(float)(pSprites->aSprite[id].nbFrame*2));
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
		if(pSprites->aSprite[id].end==0 && loop == 1)
		{
	
			if(pSprites->frame == pSprites->aSprite[id].nbFrame)
			{
				pSprites->aSprite[id].end=1;
		
			}
		}
		
		
}


void fillRandomPixels(SDL_Surface *pSurface,SDL_Rect *r)
{
   int x, y;
   unsigned int ofs;
   unsigned char *buf;

   SDL_LockSurface(pSurface);

   buf = (unsigned char *)pSurface->pixels;
   for(y = 0; y < r->h; y++) {
      ofs = (y + r->y) * pSurface->pitch;
      for(x = 0; x < r->w; x++, ofs++) {
         buf[ofs + r->x] = rand() & 0xFF; /* permet de faire clignoter les lignes*/
      }
   }

   SDL_UnlockSurface(pSurface);
}

void fireInterpolate(SDL_Surface *pSurface)
{
   int x, y;
   unsigned int pixel, ofs;
   unsigned char *buf;

   SDL_LockSurface(pSurface); /* pour pouvoir lire les pixels de SDL_Surfac*/

   buf = (unsigned char *)pSurface->pixels;  /* on point vers les pixel de la surface*/

   for(y = 1; y < pSurface->h - 2; y++) {
      ofs = y * pSurface->pitch;
      for(x = 1; x < pSurface->w - 1; x++) {
      	ofs++;
         pixel = (
            buf[ofs - 1] +
            buf[ofs] +
            buf[ofs + 1] +
            buf[ofs + pSurface->pitch - 1] +
            buf[ofs + pSurface->pitch + 1] +
            buf[ofs + pSurface->pitch*2 - 1] +
            buf[ofs + pSurface->pitch*2] +
            buf[ofs + pSurface->pitch*2 + 1]
         ) >> 3;
         buf[ofs] = pixel;
      }
   }

   SDL_UnlockSurface(pSurface);
}

void fire(SDL_Surface *pSurface)
{
		
	int i;
	
	int firePoints = 50;
	int fireSize = 8;
	SDL_Color palette[256];
	
	unsigned char *buffer;
	SDL_Rect r;
	short fire[firePoints];
	
	
	
	for(i = 0; i < 64; i++)
	{
      /* noir au rouge */
      palette[i].r = i * 4;
      palette[i].g = 0;
      palette[i].b = 0;

      /* rouge au jaune */
      palette[i + 64].r = 255;
      palette[i + 64].g = i * 4;
      palette[i + 64].b = 0;

      /* jaune au blanc */
      palette[i + 128].r = 255;
      palette[i + 128].g = 255;
      palette[i + 128].b = i * 4;

      /* on remplie avec le blanc */
      palette[i + 192].r = 255;
      palette[i + 192].g = 255;
      palette[i + 192].b = 255;
   }
   
   
	SDL_SetColors(pSurface,palette,0,256);
	for(i = 0; i < firePoints; i++) 
	{
		fire[i] = pSurface->w;
	}
	
	SDL_LockSurface(pSurface);
	buffer = pSurface -> pixels; /*on pointe les pixels de la surface*/
	
	r.x = 0;
	r.y = pSurface->h - 4;
	r.w = pSurface->w;
	r.h = 3;
	SDL_FillRect(pSurface,&r,0);
	
	
	for(i = 0; i < firePoints; i++)
	{
	
		if(rand() & 1){
            fire[i] += rand() % 7;
            if(fire[i] >= pSurface->w - fireSize)
               fire[i] = (rand() % (pSurface->w - (fireSize << 1))) + fireSize;
         } else {
            fire[i] -= rand() % 7;
            if(fire[i] <= fireSize)
               fire[i] = (rand() % (pSurface->w - (fireSize << 1))) + fireSize;
         }
         
		r.x = fire[i] - (fireSize/2);
		r.y = pSurface->w - 3;
		r.w = fireSize;
		r.h = 3;
		fillRandomPixels(pSurface,&r);
	}
	fireInterpolate(pSurface);
	SDL_UnlockSurface(pSurface);

	SDL_UpdateRect(pSurface,0,0,0,0);
		 
}


void displayGauge(SDL_Surface *pSurfaceBG, SDL_Surface *pSurface , SDL_Surface *screen, int value)
{
		SDL_Rect posiBG, posi, posiM;
		posiBG.x = screen->w/30;
		posiBG.y = screen->h/20;
		posi.x = posiBG.x+5;
		posi.y = posiBG.y+10;
		posiM.x = pSurface->w - ((float)(pSurface->w)/100.0)*value;
		posiM.y=0;
		SDL_BlitSurface(pSurfaceBG,NULL, screen, &posiBG);
		SDL_BlitSurface(pSurface,&posiM, screen, &posi);
	
}
