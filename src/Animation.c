#include "Animation.h"



void InitSprite (Sprite *pSprite,SDL_Surface *nom, int w,int h)
{
	
        pSprite->width = w;
        pSprite->height = h;
        pSprite->direction = 1;
        pSprite->frame = 0;
        pSprite->delay = 100;
	pSprite->source = nom;
        if (pSprite->source == NULL)
        {
            fprintf(stderr,"Erreur, le chargement de l'image n'a pas etais fait \n");
            exit(EXIT_FAILURE);
        }
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
    int previousTime = 0, currentTime = 0;


        currentTime = SDL_GetTicks();
      //  printf(" =====> %f <======\n",usleep(1000));
        if (currentTime - previousTime > pSprite->delay)
        {
		pSprite->frame++; 
		previousTime = currentTime; 
        }
        else
        {
            SDL_Delay(pSprite->delay - (currentTime - previousTime));
        }
        if(pSprite->frame > 3)
        {
            pSprite->frame = 0;
        }
    
}
