#include <assert.h>
#include <time.h>

#include "SDLGame.h"

const int TAILLE_SPRITE=20;

SDL_Surface *SDL_load_image(const char* filename );
void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination, int x, int y );

void initSDL(SdlGame *pSdlGame)
{
	
	Game *pGame;
	int dimx, dimy;
	
	pGame = &(pSdlGame -> pGame);
	initGame(pGame);
	assert(getDimX(getGameMap(pGame))!=0);
	dimx=getDimX(getGameMap(pGame));
	dimy=getDimY(getGameMap(pGame));
	
	dimx=dimx*TAILLE_SPRITE;
	dimy=dimy*TAILLE_SPRITE;
	
	SDL_Init(SDL_INIT_VIDEO);
	pSdlGame -> surfaceScreen = SDL_SetVideoMode(dimx,dimy,32, SDL_HWSURFACE|SDL_DOUBLEBUF); /*|SDL_FULLSCREEN*/	
	SDL_WM_SetCaption( "ColorHunt", NULL );
	
	pSdlGame -> surfaceChar = SDL_load_image("data/mario2.bmp");
	if (pSdlGame->surfaceChar ==NULL)
		pSdlGame->surfaceChar = SDL_load_image("../data/mario2.bmp");
	assert( pSdlGame->surfaceChar!=NULL);
	
	pSdlGame -> surfaceMap = SDL_load_image("data/grasss.bmp");
	if (pSdlGame->surfaceMap==NULL)	
		pSdlGame->surfaceMap = SDL_load_image("../data/grasss.bmp");
	assert( pSdlGame->surfaceMap!=NULL);
}

void sdlDisplay(SdlGame *pSdlGame)
{
	int x,y;
	Game *pGame = &(pSdlGame->pGame);
	Character *pChar= getGameChar(pGame);
	Map *pMap=getGameMap(pGame);

	/* Remplir l'écran de blanc */
	SDL_FillRect( pSdlGame->surfaceScreen, &pSdlGame->surfaceScreen->clip_rect, SDL_MapRGB( pSdlGame->surfaceScreen->format, 0xFF, 0xFF, 0xFF ));

	
	assert(getDimX(pMap)!=0);
	for (x=0;x<getDimX(pMap);++x)
		for (y=0;y<getDimY(pMap);++y)
			if (getMapXY(pMap,x,y)=='#')
				SDL_apply_surface(pSdlGame-> surfaceMap, pSdlGame->surfaceScreen, x*TAILLE_SPRITE,  y*TAILLE_SPRITE);
	
	
	
	
		
		/*SDL_BlitSurface(pSdlGame -> surfaceChar, &(pSdlGame->rcSprite), pSdlGame->surfaceEcran, &(pSdlGame->rcSprite));*/
	SDL_apply_surface(pSdlGame->surfaceChar, pSdlGame->surfaceScreen, getPosiChar(pChar).x*TAILLE_SPRITE,  getPosiChar(pChar).y*TAILLE_SPRITE);
}

void loopSDL(SdlGame *pSdlGame)
{
	SDL_Event event;
	int continueBoucle=1;
	int rafraichissement=1;
	
	/* Horloges (en secondes) */
	float horloge_courante, horloge_precedente;

	/* Intervalle de temps (en secondes) entre deux évolutions du Game */
	/* Changer la valeur pour ralentir ou accélérer le déplacement des fantomes */
	float intervalle_horloge = 0.01f;
	
	/* Récupère l'horloge actuelle et la convertit en secondes */
    /* clock() retourne le nombre de tops horloge depuis le lancement du programme */
	horloge_precedente = (float)clock()/(float)CLOCKS_PER_SEC;
    
    
    
    
    
    
	
	int tempGauche=0;
	int tempDroite=0;
	
/*	animSpInit(pSdlGame->rcSprite,128,0, TAILLE_SPRITE,TAILLE_SPRITE);*/
	
	
	while(continueBoucle==1)
	{
		
		/*pSdlGame->rcSprite.x=getPosiX(&(pSdlGame->Game.perso));
		pSdlGame->rcSprite.y=getPosiY(&(pSdlGame->Game.perso));*/
		/*Position du sprite*/
		
		
		
		
		
		 /* Récupère l'horloge actuelle et la convertit en secondes */
		horloge_courante = (float)clock()/(float)CLOCKS_PER_SEC;

       




		
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_LEFT:
							tempGauche=1; 
							break;
						case SDLK_RIGHT:
							tempDroite=1;
							break;	
						case SDLK_UP:
							/*fonction saut : vitesse et paf */
							break;	
						case SDLK_ESCAPE:
							continueBoucle = 0;
							break;
						default:
							break;
					}
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym)
					{
						case SDLK_LEFT:
							tempGauche=0; 
							break;
						case SDLK_RIGHT:
							tempDroite=0;
							break;
						case SDLK_ESCAPE:
							continueBoucle = 0;
							break;
						default:
							break;
					}
					break;
				default:
							break;
			}
			
		}
		 /* Si suffisamment de temps s'est écoulé depuis la dernière prise d'horloge */
		if (horloge_courante-horloge_precedente>=intervalle_horloge)
		{
			
	 /*               gravitation(&(pSdlGame->pGame).perso, &(pSdlGame->pGame).gMap);*/
	if( collision (&(pSdlGame->pGame.gChar), &(pSdlGame->pGame.gMap))==0)
	{
		gravity (&(pSdlGame->pGame.gChar));
	}
	 
	
	
		        rafraichissement = 1;
		        horloge_precedente = horloge_courante;
		

			if(tempGauche==1)
			{
				controlKey(&(pSdlGame->pGame), 'g');
			}
			if(tempDroite==1)
			{
				controlKey(&(pSdlGame->pGame), 'd');
				
			}
			/*if(pSdlGame->Game.perso.sol == 1 && pSdlGame->Game.perso.saut ==1) 
			{
				controlKey(&(pSdlGame->Game), 's');
			}*/
		
		
		}	
		if (rafraichissement==1)
		{
			
		    /* on affiche le Game sur le buffer caché */
		    sdlDisplay(pSdlGame);

		    /* on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle) */
		    SDL_Flip( pSdlGame->surfaceScreen);
		}
		
	}
}

SDL_Surface *SDL_load_image(const char* filename )
{
	/* Temporary storage for the image that's loaded */
	SDL_Surface* loadedImage = NULL;

	/* The optimized image that will be used */
	SDL_Surface* optimizedImage = NULL;

	/* Load the image */
	loadedImage = SDL_LoadBMP( filename );

	/* If nothing went wrong in loading the image */
	if ( loadedImage != NULL )
	{
		/* Create an optimized image */
		optimizedImage = SDL_DisplayFormat( loadedImage );

		/* Free the old image */
		SDL_FreeSurface( loadedImage );
	}

	/* Return the optimized image */
	return optimizedImage;
}


void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination, int x, int y )
{
	/* Make a temporary rectangle to hold the offsets */
	SDL_Rect offset;

	/* Give the offsets to the rectangle */
	offset.x = x;
	offset.y = y;

	/* Blit the surface */
	SDL_BlitSurface( source, NULL, destination, &offset );
}
