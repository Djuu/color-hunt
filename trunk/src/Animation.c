#include <time.h>
#include <math.h>
#include <SDL/SDL_rotozoom.h>
#include <assert.h>
#include <math.h> 

#include "Animation.h"

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
	pSprites->clockPrevious =0.0;

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
	float speedSprite=(1.0/(float)(pSprites->aSprite[id].nbFrame*2));
    pSprites->position = id;
    pSprites->direction = dir;

	if (clockCurrent-pSprites->clockPrevious > speedSprite)
	{ 
			pSprites->frame++; 
			pSprites->clockPrevious=clockCurrent;
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

Uint32 getPixel(SDL_Surface *pSurface, int x, int y)
{
    int nbOctetPerPixel = pSurface->format->BytesPerPixel;
    /*adresse du premier pixel de l'image*/
    Uint8 *p = (Uint8 *)pSurface->pixels + y * pSurface->pitch + x * nbOctetPerPixel;
    /*Gestion selon suivant le nombre d'octets par pixel */
    switch(nbOctetPerPixel)
    {
        case 1:
            return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
            /*Suivant l'architecture de la machine*/
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4:
            return *(Uint32 *)p;
        default:
            return 0; 
    }
}	

void setPixel(SDL_Surface *pSurface, int x, int y, Uint32 pixel)
{
    int nbOctetPerPixel = pSurface->format->BytesPerPixel;
	/*adresse du premier pixel de l'image*/
    Uint8 *p = (Uint8 *)pSurface->pixels + y * pSurface->pitch + x * nbOctetPerPixel;
    /*Gestion selon suivant le nombre d'octets par pixel */
    switch(nbOctetPerPixel)
    {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            /*Suivant l'architecture de la machine*/
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}



void bgBW(SDL_Surface *pSurface, double saturation)
{
	int x, y;
	Uint32 pixel;
	Uint8 red,green,blue;
	Uint8 tmpR,tmpG,tmpB;
	double a,b,c,d,e,f,g,h,i;
	double RW = 0.3086; 
	double RG = 0.6084; 
	double RB = 0.0820; 

	SDL_LockSurface(pSurface);

	for(x=0; x<pSurface->w; x++)
	{
		for(y=0; y<pSurface->h; y++)
		{
				pixel = getPixel(pSurface, x, y);
				SDL_GetRGB(pixel, pSurface->format, &red, &green, &blue);
				a = (1 - saturation) * RW + saturation;
				b = (1 - saturation) * RW;
				c = (1 - saturation) * RW;
				d = (1 - saturation) * RG;
				e = (1 - saturation) * RG + saturation;
				f = (1 - saturation) * RG;
				g = (1 - saturation) * RB;
				h = (1 - saturation) * RB;
				i = (1 - saturation) * RB + saturation;

				tmpR   = a*red + d*green + g*blue;
				tmpG = b*red + e*green + h*blue;
				tmpB  = c*red + f*green + i*blue;
				
				pixel = SDL_MapRGB(pSurface->format, tmpR, tmpG, tmpB);
				
				setPixel(pSurface, x, y, pixel); 
		}
		
	}

   SDL_UnlockSurface(pSurface);
}

void rotationObject(SDL_Surface *pSurface, SDL_Rect positionBall, double *angle, float speed, SDL_Surface *screen)
{	
	
	float clockCurrent =  (float)clock()/(float)CLOCKS_PER_SEC;
	static float clockPrevious = 0.0;
	SDL_Surface *rotationBall;
	SDL_Rect tempRect= {positionBall.x,positionBall.y,0,0};
	float tempY;
	/*if (clockCurrent-clockPrevious > speed)
	{
		(*angle)--;
		
		clockPrevious=clockCurrent;
	}*/
	/*if((*angle) == 360)
		(*angle)=0;*/

/*tempRect.x = 2 *cos(*(angle)) - 2*sin(*(angle));
tempRect.y = 2 *sin(*(angle)) + 2*cos(*(angle));*/
 
//tempRect.x =  sqrt( pow((positionBall.x-tempRect.x),2) + pow((positionBall.y-tempRect.y),2)) * cos((90)) + positionBall.x; 
//tempRect.y =  sqrt( pow((positionBall.x-tempRect.x),2) + pow((positionBall.y-tempRect.y),2)) * sin((90)) + positionBall.y; 


	rotationBall = rotozoomSurface(pSurface, (*angle), 1.0, 0);
	tempRect.x -= (rotationBall->w -  pSurface->w);
	tempRect.y -= (rotationBall->h -  pSurface->h);
	SDL_BlitSurface(rotationBall,NULL, screen, &tempRect);	
	SDL_FreeSurface(rotationBall);
}

void audioBG()
{
	Mix_Music *pMusic;
	pMusic = Mix_LoadMUS("data/audio/bg.mp3");
	Mix_PlayMusic(pMusic, -1);
}

void audioWind()
{
	Mix_Chunk *pSound;
	pSound = Mix_LoadWAV("data/audio/wind.wav");
	Mix_VolumeChunk(pSound, MIX_MAX_VOLUME/10);
	Mix_PlayChannel(1, pSound, 0);
//	Mix_FreeChunk(pSound);   /*!!!!!!!!!!!!!!!!!*/
}

void audioSward()
{
	Mix_Chunk *pSound;
	pSound = Mix_LoadWAV("data/audio/sward.wav");
	Mix_VolumeChunk(pSound, MIX_MAX_VOLUME/3);
	Mix_PlayChannel(2, pSound, 0);
//	Mix_FreeChunk(pSound);   /*!!!!!!!!!!!!!!!!!*/
}

void audioFireBall()
{
	Mix_Chunk *pSound;
	pSound = Mix_LoadWAV("data/audio/fireball.wav");
	Mix_VolumeChunk(pSound, MIX_MAX_VOLUME/3);
	Mix_PlayChannel(3, pSound, 0);
//	Mix_FreeChunk(pSound);   /*!!!!!!!!!!!!!!!!!*/
}
