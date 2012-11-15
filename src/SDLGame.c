#include <assert.h>
#include <time.h>

#include "SDLGame.h"

const int TAILLE_SPRITE=20;

const int SCREEN_WIDTH =800;
const int SCREEN_HEIGHT =720;

SDL_Surface *SDL_load_image(const char* filename );
void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination, int x, int y);

void initSDL(SdlGame *pSdlGame)
{
	
	Game *pGame;

	
	/*Déplacer la map*/
	pSdlGame->scrollX=0;
	pSdlGame->scrollY=0;
	
	pGame = &(pSdlGame -> pGame);
	initGame(pGame);

	pSdlGame->rectScreen.x=0;
	pSdlGame->rectScreen.y=0;
	
	SDL_Init(SDL_INIT_VIDEO);
	pSdlGame -> surfaceScreen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32, SDL_HWSURFACE|SDL_DOUBLEBUF);/*|SDL_FULLSCREEN);*/
	SDL_WM_SetCaption( "ColorHunt", NULL );
	
	pSdlGame -> surfaceChar = SDL_load_image("data/mario2.bmp");
	if (pSdlGame->surfaceChar ==NULL)
		pSdlGame->surfaceChar = SDL_load_image("../data/mario2.bmp");
	assert( pSdlGame->surfaceChar!=NULL);
	
	pSdlGame -> surfaceEarth = SDL_load_image("data/grasss.bmp");
	if (pSdlGame->surfaceEarth==NULL)	
		pSdlGame->surfaceEarth = SDL_load_image("../data/grasss.bmp");
	assert( pSdlGame->surfaceEarth!=NULL);


	
}

void sdlDisplay(SdlGame *pSdlGame)
{
	int i,j;
	Game *pGame = &(pSdlGame->pGame);
	Character *pChar= getGameChar(pGame);
	Map *pMap=getGameMap(pGame);
	SDL_Rect posiChar;

	posiChar.x = getPosiChar(pChar).x*TAILLE_SPRITE - pSdlGame->scrollX;
	posiChar.y = getPosiChar(pChar).y*TAILLE_SPRITE - pSdlGame->scrollY;
	
	/* Remplir l'écran de blanc */
	SDL_FillRect( pSdlGame->surfaceScreen, &pSdlGame->surfaceScreen->clip_rect, SDL_MapRGB( pSdlGame->surfaceScreen->format, 0xFF, 0xFF, 0xFF ));

	SDL_Rect positionTile;
	assert(getDimX(pMap)!=0);
	
	
	int xmin,xmax,ymin,ymax;
	xmin = pSdlGame->scrollX/TAILLE_SPRITE;
	xmax = (pSdlGame->scrollX + SCREEN_WIDTH)/TAILLE_SPRITE;
	ymin = pSdlGame->scrollY/TAILLE_SPRITE;
	ymax = (pSdlGame->scrollY + SCREEN_HEIGHT)/TAILLE_SPRITE;
	

	for (i=xmin;i<xmax;++i)
	{
		for (j=ymin;j<ymax;++j)
		{
			positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
			positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
			
			switch (pSdlGame->pGame.gMap.tab[j][i])
			{
				case '#':
					SDL_BlitSurface(pSdlGame->surfaceEarth,NULL, pSdlGame->surfaceScreen, &positionTile);
				break;
			
			}
		} 
				
	}
	
	
	SDL_BlitSurface(pSdlGame->surfaceChar,NULL, pSdlGame->surfaceScreen, &posiChar);
	
	
}

void loopSDL(SdlGame *pSdlGame)
{
	SDL_Event event;
	int continueLoop=1;
	int refresh=1;
	
	Game *pGame = &(pSdlGame->pGame);
	Character *pChar= getGameChar(pGame);
	Map *pMap=getGameMap(pGame);
	
	/* Horloges (en secondes) */
	float currentClock, previousClock;

	/* Intervalle de temps (en secondes) entre deux évolutions du Game */
	/* Changer la valeur pour ralentir ou accélérer le déplacement des fantomes */
	float clockInterval = 0.01f;
	
	/* Récupère l'horloge actuelle et la convertit en secondes */
    /* clock() retourne le nombre de tops horloge depuis le lancement du programme */
	previousClock = (float)clock()/(float)CLOCKS_PER_SEC;
    
    
    
    
    
    
	
	int tmpLeft=0;
	int tmpRight=0;
	
/*	animSpInit(pSdlGame->rcSprite,128,0, TAILLE_SPRITE,TAILLE_SPRITE);*/
	
	
	while(continueLoop==1)
	{
		
		/*pSdlGame->rcSprite.x=getPosiX(&(pSdlGame->Game.perso));
		pSdlGame->rcSprite.y=getPosiY(&(pSdlGame->Game.perso));*/
		/*Position du sprite*/
		
		
		
		
		
		 /* Récupère l'horloge actuelle et la convertit en secondes */
		currentClock = (float)clock()/(float)CLOCKS_PER_SEC;

       




		
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_LEFT:
							tmpLeft=1; 
							break;
						case SDLK_RIGHT:
							tmpRight=1;
							break;	
						case SDLK_UP:
							controlKey(&(pSdlGame->pGame), 's');
							break;	
						case SDLK_ESCAPE:
							continueLoop = 0;
							break;
						default:
							break;
					}
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym)
					{
						case SDLK_LEFT:
							tmpLeft=0; 
							break;
						case SDLK_RIGHT:
							tmpRight=0;
							break;
						case SDLK_ESCAPE:
							continueLoop = 0;
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
		if (currentClock-previousClock>=clockInterval)
		{
			
	 /*               gravitation(&(pSdlGame->pGame).perso, &(pSdlGame->pGame).gMap);*/
			

			gravity (&(pSdlGame->pGame.gChar));

	 		collision (&(pSdlGame->pGame.gChar), &(pSdlGame->pGame.gMap));
	
	
		        refresh = 1;
		        previousClock = currentClock;
			
			// Limitation de la fenetre de scrolling
			if (pSdlGame->scrollX<0)
				pSdlGame->scrollX=0;
			if (pSdlGame->scrollX+SCREEN_WIDTH>TAILLE_SPRITE*pMap->dimx-1)
				pSdlGame->scrollX=TAILLE_SPRITE*pMap->dimx-SCREEN_WIDTH;
			
			int temp;
			temp = (int)(getPosiChar(pChar).x*TAILLE_SPRITE-pSdlGame->scrollX);
			if(tmpLeft==1)
			{
				controlKey(&(pSdlGame->pGame), 'g');
				if(temp <= SCREEN_WIDTH/4)
					pSdlGame->scrollX+=pChar->cPosi.v_x*TAILLE_SPRITE;

		
			}
			if(tmpRight==1)
			{
				
				controlKey(&(pSdlGame->pGame), 'd');
				if(temp >= SCREEN_WIDTH*3/4)
					pSdlGame->scrollX+=pChar->cPosi.v_x*TAILLE_SPRITE;

			}
			if(tmpLeft==0 && tmpRight==0)
			{
				initSpeed(&(pSdlGame->pGame));
			}
			/*if(pSdlGame->Game.perso.sol == 1 && pSdlGame->Game.perso.saut ==1) 
			{
				controlKey(&(pSdlGame->Game), 's');
			}*/
		
		
		}	
		if (refresh==1)
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


void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination, int x, int y)
{
	/* Make a temporary rectangle to hold the offsets */
	SDL_Rect offset;

	/* Give the offsets to the rectangle */
	offset.x = x;
	offset.y = y;

	/* Blit the surface */
	SDL_BlitSurface( source,NULL, destination, &offset );
}
