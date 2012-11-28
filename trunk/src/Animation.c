#include "Animation.h"



void InitSprite (Sprite *pSprite,SDL_Surface *nom, int w,int h)
{
	InitTimeSprite(&(pSprite->pTimeSprite));
    pSprite->width = w;
    pSprite->height = h;
        pSprite->direction = 1;
        pSprite->frame = 0;

	pSprite->source = nom;
        if (pSprite->source == NULL)
        {
            fprintf(stderr,"Erreur, le chargement de l'image n'a pas etais fait \n");
            exit(EXIT_FAILURE);
        }
}

void InitTimeSprite(timeSprite *pTimeSprite)
{
	pTimeSprite ->previousTime=0;
	pTimeSprite ->currentTime=0;
	pTimeSprite ->delay=30;
}

void DestructionSprite (Sprite *pSprite)
{
    SDL_FreeSurface(pSprite->source);
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
void MoveSprite (Sprite* pSprite, int dir)
{
    Uint8 *keystate = SDL_GetKeyState(NULL);
	pSprite->direction = dir;



        pSprite ->pTimeSprite.currentTime = SDL_GetTicks();
        printf(" =====> %d <======\n", pSprite ->pTimeSprite.currentTime -  pSprite ->pTimeSprite.previousTime);
        if ( pSprite ->pTimeSprite.currentTime -  pSprite ->pTimeSprite.previousTime >  pSprite ->pTimeSprite.delay)
        {
			pSprite->frame++; 
			 pSprite ->pTimeSprite.previousTime= pSprite ->pTimeSprite.currentTime; 
        }
        else
        {
            SDL_Delay( pSprite ->pTimeSprite.delay - ( pSprite ->pTimeSprite.currentTime -  pSprite ->pTimeSprite.previousTime));
        }
        if(pSprite->frame > 30)
        {
            pSprite->frame = 15;
        }
    
}
