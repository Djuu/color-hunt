#include <assert.h>
#include <time.h>
#include "sdlJeu.h"
const int TAILLE_SPRITE=20;

SDL_Surface *SDL_load_image(const char* filename );
void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination, int x, int y );

void sdlInitialisation(sdlJeu *pSdlJeu)
{
	
	Jeu *pJeu;
	
	int dimx, dimy;
	pJeu = &(pSdlJeu->jeu);
	jeuInit(pJeu);
	assert(getDimX(jeuGetMap(pJeu))!=0);
	dimx=getDimX(jeuGetMap(pJeu));
	dimy=getDimY(jeuGetMap(pJeu));
	
	dimx=dimx*TAILLE_SPRITE;
	dimy=dimy*TAILLE_SPRITE;
	
	SDL_Init(SDL_INIT_VIDEO);
	pSdlJeu ->surfaceEcran = SDL_SetVideoMode(dimx,dimy,32, SDL_HWSURFACE|SDL_DOUBLEBUF); /*|SDL_FULLSCREEN*/	
	SDL_WM_SetCaption( "ColorHunt", NULL );
	
	pSdlJeu -> surfaceHero = SDL_load_image("data/mario2.bmp");
	if (pSdlJeu->surfaceHero==NULL)
		pSdlJeu->surfaceHero = SDL_load_image("../data/mario2.bmp");
	assert( pSdlJeu->surfaceHero!=NULL);
	
	pSdlJeu -> surfaceMap = SDL_load_image("data/grasss.bmp");
	if (pSdlJeu->surfaceMap==NULL)	
		pSdlJeu->surfaceMap = SDL_load_image("../data/grasss.bmp");
	assert( pSdlJeu->surfaceMap!=NULL);
}

void sdlAffiche(sdlJeu *pSdlJeu)
{
	int x,y;
	Jeu *pJeu = &(pSdlJeu->jeu);
	hero *pHero= jeuGetHero(pJeu);
	map *pMap=jeuGetMap(pJeu);

	/* Remplir l'écran de blanc */
	SDL_FillRect( pSdlJeu->surfaceEcran, &pSdlJeu->surfaceEcran->clip_rect, SDL_MapRGB( pSdlJeu->surfaceEcran->format, 0xFF, 0xFF, 0xFF ));

	
	assert(getDimX(pMap)!=0);
	for (x=0;x<getDimX(pMap);++x)
		for (y=0;y<getDimY(pMap);++y)
			if (mapGetXY(pMap,x,y)=='#')
				SDL_apply_surface(pSdlJeu-> surfaceMap, pSdlJeu->surfaceEcran, x*TAILLE_SPRITE,  y*TAILLE_SPRITE);
	
	
	
	
		
		/*SDL_BlitSurface(pSdlJeu -> surfaceHero, &(pSdlJeu->rcSprite), pSdlJeu->surfaceEcran, &(pSdlJeu->rcSprite));*/
	SDL_apply_surface(pSdlJeu->surfaceHero, pSdlJeu->surfaceEcran, getPosiX(pHero)*TAILLE_SPRITE,  getPosiY(pHero)*TAILLE_SPRITE);
}

void sdlBoucle(sdlJeu *pSdlJeu)
{
	SDL_Event event;
	int continueBoucle=1;
	int rafraichissement=1;
	
	/* Horloges (en secondes) */
	float horloge_courante, horloge_precedente;

	/* Intervalle de temps (en secondes) entre deux évolutions du jeu */
	/* Changer la valeur pour ralentir ou accélérer le déplacement des fantomes */
	float intervalle_horloge = 0.01f;
	
	/* Récupère l'horloge actuelle et la convertit en secondes */
    /* clock() retourne le nombre de tops horloge depuis le lancement du programme */
    horloge_precedente = (float)clock()/(float)CLOCKS_PER_SEC;
    
    
    
    
    
    
	
	int tempGauche=0;
	int tempDroite=0;
	
	animSpInit(pSdlJeu->rcSprite,128,0, TAILLE_SPRITE,TAILLE_SPRITE);
	
	
	while(continueBoucle==1)
	{
		
		/*pSdlJeu->rcSprite.x=getPosiX(&(pSdlJeu->jeu.perso));
		pSdlJeu->rcSprite.y=getPosiY(&(pSdlJeu->jeu.perso));*/
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
							/*if ( pSdlJeu->rcSprite.x == 192 )
								pSdlJeu->rcSprite.x = 224;
							else
								pSdlJeu->rcSprite.x = 192;
							pSdlJeu->rcSprite.x -= 5;*/
							
							tempGauche=1; 
							break;
						case SDLK_RIGHT:
							tempDroite=1;
							break;	
						case SDLK_UP:
							pSdlJeu->jeu.perso.saut = 1;
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
                gravitation(&(pSdlJeu->jeu.perso), &(pSdlJeu->jeu.gMap));
                rafraichissement = 1;
                horloge_precedente = horloge_courante;
        

		if(tempGauche==1)
		{
			control(&(pSdlJeu->jeu), 'g');
		}
		if(tempDroite==1)
		{
			control(&(pSdlJeu->jeu), 'd');
		}
		if(pSdlJeu->jeu.perso.sol == 1 && pSdlJeu->jeu.perso.saut >=1)  /*ATTENTION : dépendance SDL*/
		{
			control(&(pSdlJeu->jeu), 's');
		}
		
		
	}	
		if (rafraichissement==1)
		{
			
		    /* on affiche le jeu sur le buffer caché */
		    sdlAffiche(pSdlJeu);

		    /* on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle) */
		    SDL_Flip( pSdlJeu->surfaceEcran);
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
