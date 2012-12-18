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

/*** Initialise le sprite entré en paramètre */
void InitSprite (Sprites *pSprites,int id, int w,int h, int nbFrame, int reFrame);
/** Effectue l'annimation du sprite en paramètre */
void animSprite (Sprites* pSprites, int id, int loop, int dir);
/** Fait les blit nécessaires pour afficher l'animation */
void displaySprite(Sprites *pSprites, SDL_Rect posi, SDL_Surface *screen);
/** Libère la mémoire du sprite */
void freeSprite(Sprites *pSprites);
/** Affiche la gauge de vie et de mana */
void displayGauge(SDL_Surface *pSurfaceBG, SDL_Surface *pSurfaceLife , SDL_Surface * pSurfaceMana , SDL_Surface *screen, int life , int mana);
/** Permet de saturer l'image */
void bgBW(SDL_Surface *pSurface, double saturation);
/** Permet grace a la bibliothèque rotozoom d'effectuer une rotation sur un objet */ 
void rotationObject(SDL_Surface *pSurface, SDL_Rect positionBall, double *angle, float speed,  SDL_Surface *screen);
/** Initialisation des sons du jeu */
void audioBG();
void audioSward();
void audioFireBall();
void audioWind();
#endif
