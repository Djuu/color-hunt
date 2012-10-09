
#include <assert.h>
#include <time.h>
#include "sdlJeu.h"
/*
const int TAILLE_SPRITE=32;

SDL_Surface *SDL_load_image(const char* filename );
void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination, int x, int y );



void sdljeuInit(sdlJeu *pSdlJeu)
{
	Jeu *pJeu;
	int dimx, dimy;

	pJeu = &(pSdlJeu->jeu);
	jeuInit(pJeu);

	assert(   
	SDL_Init( SDL_INIT_EVERYTHING )!= -1 );

	dimx = getDimX( jeuGetConstTerrainPtr(pJeu) );
	dimy = getDimY( jeuGetConstTerrainPtr(pJeu) );
	dimx = dimx * TAILLE_SPRITE;
	dimy = dimy * TAILLE_SPRITE;
		zzzTTF_Init();aaa
	pSdlJeu->surface_ecran = SDL_SetVideoMode(   dimx, dimy, 32, SDL_SWSURFACE );
	assert( pSdlJeu->surface_ecran!=NULL);
	SDL_WM_SetCaption( "Pacman v0.1", NULL );

	pSdlJeu->surface_pacman = SDL_load_image("data/pacman.bmp");
	if (pSdlJeu->surface_pacman==NULL)
		pSdlJeu->surface_pacman = SDL_load_image("../data/pacman.bmp");
	assert( pSdlJeu->surface_pacman!=NULL);

	pSdlJeu->surface_mur = SDL_load_image("data/mur.bmp");
	if (pSdlJeu->surface_mur==NULL)
		pSdlJeu->surface_mur = SDL_load_image("../data/mur.bmp");
	assert( pSdlJeu->surface_mur!=NULL);

	pSdlJeu->surface_fantome = SDL_load_image("data/fantome.bmp");
	if (pSdlJeu->surface_fantome==NULL)
		pSdlJeu->surface_fantome = SDL_load_image("../data/fantome.bmp");
	assert( pSdlJeu->surface_fantome!=NULL);
}



void sdljeuAff(sdlJeu *pSdlJeu)
{
	int x,y,i_fant;
    const Jeu *pJeu = &(pSdlJeu->jeu);
	const Terrain *pTer = jeuGetConstTerrainPtr(pJeu);
	const Pacman *pPac = jeuGetConstPacmanPtr(pJeu);
	


	zzz Remplir l'écran de blanc aaa
	SDL_FillRect( pSdlJeu->surface_ecran, &pSdlJeu->surface_ecran->clip_rect, SDL_MapRGB( pSdlJeu->surface_ecran->format, 0xFF, 0xFF, 0xFF ) );

	for (x=0;x<getDimX(pTer);++x)
		for (y=0;y<getDimY(pTer);++y)
			if (terGetXY(pTer,x,y)=='#')
				SDL_apply_surface(  pSdlJeu->surface_mur, pSdlJeu->surface_ecran, x*TAILLE_SPRITE, y*TAILLE_SPRITE);

    for (i_fant=0; i_fant<pJeu->nb_fantomes; i_fant++)
        SDL_apply_surface(  pSdlJeu->surface_fantome, pSdlJeu->surface_ecran, (pJeu->tab_fantomes[i_fant].x)*TAILLE_SPRITE, (pJeu->tab_fantomes[i_fant].y)*TAILLE_SPRITE);

	zzz Copier le sprite de Pacman sur l'écran aaa
	SDL_apply_surface(  pSdlJeu->surface_pacman, pSdlJeu->surface_ecran, pacGetX(pPac)*TAILLE_SPRITE,  pacGetY(pPac)*TAILLE_SPRITE );
	zzzTTF_Font *police;
		police = TTF_OpenFont( "CaslonBold.ttf", 65 );
    		SDL_Color couleurNoire= {255, 0, 0};
    		pSdlJeu -> texte = TTF_RenderText_Blended(police, "Pacman !", couleurNoire);
	SDL_apply_surface( pSdlJeu->texte,pSdlJeu->surface_ecran ,0, 0); aaa
	
}



void sdljeuBoucle(sdlJeu *pSdlJeu)
{
	SDL_Event event;
	int continue_boucle = 1;

    zzz Horloges (en secondes) aaa
    float horloge_courante, horloge_precedente;

    zzz Intervalle de temps (en secondes) entre deux évolutions du jeu aaa
    zzz Changer la valeur pour ralentir ou accélérer le déplacement des fantomes aaa
    float intervalle_horloge = 0.1f;

    int rafraichissement;

	sdljeuAff(pSdlJeu);
	assert( SDL_Flip( pSdlJeu->surface_ecran )!=-1 );

    zzz Récupère l'horloge actuelle et la convertit en secondes aaa
    zzz clock() retourne le nombre de tops horloge depuis le lancement du programme aaa
    horloge_precedente = (float)clock()/(float)CLOCKS_PER_SEC;
	
	zzz Tant que ce n'est pas la fin ... aaa
	while ( continue_boucle == 1 )
	{
	    rafraichissement = 0;

	     zzz Récupère l'horloge actuelle et la convertit en secondes aaa
        horloge_courante = (float)clock()/(float)CLOCKS_PER_SEC;

        zzz Si suffisamment de temps s'est écoulé depuis la dernière prise d'horloge aaa
        if (horloge_courante-horloge_precedente>=intervalle_horloge)
        {
                jeuEvolue(&(pSdlJeu->jeu));
                rafraichissement = 1;
                horloge_precedente = horloge_courante;
        }

		zzz tant qu'il y a des evenements à traiter : cette boucle n'est pas bloquante aaa
		while ( SDL_PollEvent( &event ) )
		{
			zzz Si l'utilisateur a cliqué sur la croix de fermeture aaa
			if ( event.type == SDL_QUIT )
				continue_boucle = 0;

			zzz Si l'utilisateur a appuyé sur une touche aaa
			if ( event.type == SDL_KEYDOWN )
			{
				switch ( event.key.keysym.sym )
				{
				case SDLK_UP:
					jeuActionClavier( &(pSdlJeu->jeu), 'h');
					rafraichissement = 1;
					break;
				case SDLK_DOWN:
					jeuActionClavier( &(pSdlJeu->jeu), 'b');
					rafraichissement = 1;
					break;
				case SDLK_LEFT:
					jeuActionClavier( &(pSdlJeu->jeu), 'g');
					rafraichissement = 1;
					break;
				case SDLK_RIGHT:
					jeuActionClavier( &(pSdlJeu->jeu), 'd');
					rafraichissement = 1;
					break;
				default: break;
				}
			}

		}

        if (rafraichissement==1)
        {
            zzz on affiche le jeu sur le buffer caché aaa
            sdljeuAff(pSdlJeu);
            

            zzz on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans a boucle) aaa
            SDL_Flip( pSdlJeu->surface_ecran );
        }
	}
}


void sdljeuLibere( sdlJeu *pSdlJeu)
{
	SDL_FreeSurface( pSdlJeu->surface_pacman );
	SDL_FreeSurface( pSdlJeu->surface_mur );
	SDL_FreeSurface( pSdlJeu->surface_fantome );

	jeuLibere(&(pSdlJeu->jeu));
	TTF_Quit();
	SDL_Quit();
}



SDL_Surface *SDL_load_image(const char* filename )
{
	zzz Temporary storage for the image that's loaded aaa
	SDL_Surface* loadedImage = NULL;

	zzz The optimized image that will be used aaa
	SDL_Surface* optimizedImage = NULL;

	zzz Load the image aaa
	loadedImage = SDL_LoadBMP( filename );

	zzz If nothing went wrong in loading the image aaa
	if ( loadedImage != NULL )
	{
		zzz Create an optimized image aaa
		optimizedImage = SDL_DisplayFormat( loadedImage );

		zzz Free the old image aaa
		SDL_FreeSurface( loadedImage );
	}

	zzz Return the optimized image aaa
	return optimizedImage;
}


void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination, int x, int y )
{
	zzz Make a temporary rectangle to hold the offsets aaa
	SDL_Rect offset;

	zzz Give the offsets to the rectangle aaa
	offset.x = x;
	offset.y = y;

	zzz Blit the surface aaa
	SDL_BlitSurface( source, NULL, destination, &offset );
}*/
