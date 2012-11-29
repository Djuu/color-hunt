#include "SDLGame.h"

const int TAILLE_SPRITE=20;
const int CHAR_SPRITE_W =52;
const int CHAR_SPRITE_H =54;
const int SCREEN_WIDTH =800;
const int SCREEN_HEIGHT =600;

SDL_Surface *SDL_load_image(const char* filename );
void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination, int x, int y);

void initSDL(SdlGame *pSdlGame)
{
	
	Game *pGame;
	//int direction =0;
	/*Déplacer la map*/
	int i;
	pSdlGame->scrollX=0;
	pSdlGame->scrollY=0;
	
	pGame = &(pSdlGame -> pGame);

	initGame(pGame,"Map/WorldMap.txt");

	pSdlGame->rectScreen.x=0;
	pSdlGame->rectScreen.y=0;

	SDL_Init(SDL_INIT_VIDEO);
	pSdlGame -> surfaceScreen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32, SDL_HWSURFACE|SDL_DOUBLEBUF);/*|SDL_FULLSCREEN);*/
	SDL_WM_SetCaption( "ColorHunt", NULL );


/*Background*/
  
  SDL_Surface* temp = IMG_Load("data/bg.png");
  pSdlGame->surfaceBG = SDL_DisplayFormat(temp);


	pSdlGame -> surfaceChar =  IMG_Load("data/hero3.png");
	if (pSdlGame->surfaceChar ==NULL)
		pSdlGame->surfaceChar =  IMG_Load("../data/hero3.png");
	assert( pSdlGame->surfaceChar!=NULL);

	/*Surface de tableau d'ennemie*/
	pSdlGame -> surfaceEnemies = calloc(pSdlGame -> pGame.gEnemies.number, sizeof(SDL_Surface*));
	for(i=0; i<pSdlGame -> pGame.gEnemies.number; i++)
	{
		pSdlGame -> surfaceEnemies[i] = IMG_Load("data/goomba.jpg");
		if (pSdlGame->surfaceEnemies[i] ==NULL)
			pSdlGame->surfaceEnemies[i] = IMG_Load("../data/goomba.jpg");
		assert( pSdlGame->surfaceEnemies[i]!=NULL);
	}	
	
	pSdlGame -> surfaceEarth = IMG_Load("data/grass2.png");
	if (pSdlGame->surfaceEarth==NULL)	
		pSdlGame->surfaceEarth = IMG_Load("../data/grass2.png");
	assert( pSdlGame->surfaceEarth!=NULL);
	
pSdlGame -> surfaceGrass = IMG_Load("data/grass4.png");
	if (pSdlGame->surfaceGrass==NULL)	
		pSdlGame->surfaceGrass = IMG_Load("../data/grass4.png");
	assert( pSdlGame->surfaceGrass!=NULL);

	InitSprite (&(pSdlGame->pSprite),pSdlGame -> surfaceChar, CHAR_SPRITE_W,CHAR_SPRITE_H);
	
}


/*
Procedure : privee
Description: procedure perpettant d'afficher les sprites et les SDL_Surface sur l'ecran
*/
void sdlDisplay(SdlGame *pSdlGame)
{
	int i,j, k;
	int xmin,xmax,ymin,ymax;
	SDL_Rect positionTile;
	
	Game *pGame = &(pSdlGame->pGame);
	Character *pChar= getGameChar(pGame);
	Enemies *pEnemies = getGameEnemies(pGame);
	Map *pMap=getGameMap(pGame);
	SDL_Rect posiChar, posiEnemy;
	/*Position posiEnemy;*/
	
	
	/*Background*/
	SDL_BlitSurface(pSdlGame->surfaceBG, NULL, pSdlGame->surfaceScreen, NULL);
	
	
	posiChar.x = getPosiChar(pChar).x*TAILLE_SPRITE - pSdlGame->scrollX;
	posiChar.y = getPosiChar(pChar).y*TAILLE_SPRITE- pSdlGame->scrollY;

	
	/* Remplir l'écran de blanc */
	//SDL_FillRect( pSdlGame->surfaceScreen, &pSdlGame->surfaceScreen->clip_rect, SDL_MapRGB( pSdlGame->surfaceScreen->format, 0xFF, 0xFF, 0xFF ));

	
	assert(getDimX(pMap)!=0);
	
/*
Recadrage de la fenetre sur une partie de la map et affichage de la map au fur et a mesure que le personnage avance
*/
	xmin = pSdlGame->scrollX/TAILLE_SPRITE;
	xmax = (pSdlGame->scrollX + SCREEN_WIDTH)/TAILLE_SPRITE+1;
	ymin = pSdlGame->scrollY/TAILLE_SPRITE;
	ymax = (pSdlGame->scrollY + SCREEN_HEIGHT)/TAILLE_SPRITE;
	

	for (i=xmin;i<xmax;++i)
	{
		for (j=ymin;j<ymax;++j)
		{
			
			
			switch (pSdlGame->pGame.gMap.tab[j][i])
			{
				case '#':
				positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
			positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceEarth,NULL, pSdlGame->surfaceScreen, &positionTile);
				break;
				case '%':
				positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
			positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceGrass,NULL, pSdlGame->surfaceScreen, &positionTile);
				break;
				
			
			}
		} 
				
	}
	
	pSdlGame->rcSprite.x=CHAR_SPRITE_W*pSdlGame->pSprite.frame;
	pSdlGame->rcSprite.y=CHAR_SPRITE_H*pSdlGame->pSprite.direction;
	pSdlGame->rcSprite.w=CHAR_SPRITE_W;
	pSdlGame->rcSprite.h=CHAR_SPRITE_H;
	SDL_BlitSurface(pSdlGame->pSprite.source, &(pSdlGame->rcSprite),  pSdlGame->surfaceScreen, &posiChar);
	//SDL_BlitSurface(pSdlGame->surfaceChar,NULL, pSdlGame->surfaceScreen, &posiChar);
	
	for(k=0; k<pSdlGame -> pGame.gEnemies.number; k++)
	{
		posiEnemy.x = getPosiEnemy(pEnemies,k).x*TAILLE_SPRITE- pSdlGame->scrollX;
		posiEnemy.y = getPosiEnemy(pEnemies,k).y*TAILLE_SPRITE- pSdlGame->scrollY;
		SDL_BlitSurface(pSdlGame->surfaceEnemies[k],NULL, pSdlGame->surfaceScreen, &posiEnemy);
	}
	
}
void keyManagment2(SdlGame *pSdlGame)
{
	if(pSdlGame->pKey.kLeft==1)
	{
		controlKey2(&(pSdlGame->pGame), 'g');
	}
	if(pSdlGame->pKey.kRight==1)
	{
		controlKey2(&(pSdlGame->pGame), 'd');
	}
	if (pSdlGame->pKey.kJump ==1)
	{
		controlKey2(&(pSdlGame->pGame), 'h');
	}
	if (pSdlGame->pKey.kDown ==1)
	{
		controlKey2(&(pSdlGame->pGame), 'b');
	}
	if(pSdlGame->pKey.kLeft==0 && pSdlGame->pKey.kRight==0)
	{
		initSpeedX(&(pSdlGame->pGame));
	}
	if(pSdlGame->pKey.kJump==0 && pSdlGame->pKey.kDown==0)
	{
		initSpeedY(&(pSdlGame->pGame));
	}


}
void keyManagment(SdlGame *pSdlGame)
{
	int i;
	for(i=0; i<pSdlGame -> pGame.gEnemies.number; i++)
	{
		if(collision(&(pSdlGame->pGame.gChar.cPosi),&(pSdlGame->pGame.gEnemies.eEnemy[i].eChar.cPosi))==1)
		{
			pSdlGame->pGame.gChar.projection = 1;
		}
		else if (collision(&(pSdlGame->pGame.gChar.cPosi),&(pSdlGame->pGame.gEnemies.eEnemy[i].eChar.cPosi))==2)
		{
	
			pSdlGame->pGame.gChar.projection = 2;
		}
	}
		if(pSdlGame->pGame.gChar.projection == 0)	
		{
			
			if(pSdlGame->pKey.kLeft==1)
			{
				MoveSprite (&(pSdlGame->pSprite), left);
				controlKey(&(pSdlGame->pGame), 'g');
				

		
			}
			if(pSdlGame->pKey.kRight==1)
			{
				MoveSprite (&(pSdlGame->pSprite), right);
				controlKey(&(pSdlGame->pGame), 'd');
				

			}
			if (pSdlGame->pKey.kJump ==1)
			{
					controlKey(&(pSdlGame->pGame), 's');
			}
			if(pSdlGame->pKey.kLeft==0 && pSdlGame->pKey.kRight==0)
			{
				initSpeedX(&(pSdlGame->pGame));
			}
		
	}

	
}


void loopSDL(SdlGame *pSdlGame)
{
	int k;
	SDL_Event event;
	int continueLoop=1;
	int refresh=1;
	int temp;
	Game *pGame = &(pSdlGame->pGame);
	Character *pChar= getGameChar(pGame);
	Map *pMap=getGameMap(pGame);
	int tempCol;
	tempCol=0;
	float powerDetect;
	powerDetect=0.0;
	/* Horloges (en secondes) */
	float currentClock, previousClock;
	
	/* Intervalle de temps (en secondes) entre deux évolutions du Game */
	/* Changer la valeur pour ralentir ou accélérer le déplacement des fantomes */
	float clockInterval = 0.02f;
	
	/* Récupère l'horloge actuelle et la convertit en secondes */
    /* clock() retourne le nombre de tops horloge depuis le lancement du programme */
	previousClock = (float)clock()/(float)CLOCKS_PER_SEC;
    

/*	animSpInit(pSdlGame->rcSprite,128,0, TAILLE_SPRITE,TAILLE_SPRITE);*/
	
	pSdlGame->pKey.kLeft =0;
	pSdlGame->pKey.kRight =0;
	pSdlGame->pKey.kJump =0;
	pSdlGame->pKey.kDown =0;
	
	while(continueLoop==1)
	{
		   
		/*pSdlGame->rcSprite.x=getPosiX(&(pSdlGame->Game.perso));
		pSdlGame->rcSprite.y=getPosiY(&(pSdlGame->Game.perso));*/
		/*Position du sprite*/
		
		
		
		
		
		 /* Récupère l'horloge actuelle et la convertit en secondes */
		currentClock = (float)clock()/(float)CLOCKS_PER_SEC;

       
	


/* Evenement des touches */		
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_LEFT:
							pSdlGame->pKey.kLeft=1; 
							break;
						case SDLK_RIGHT:
							pSdlGame->pKey.kRight=1;
							break;	
						case SDLK_UP:
							pSdlGame->pKey.kJump =1;
							break;	
						case SDLK_DOWN:
							pSdlGame->pKey.kDown =1;
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
							pSdlGame->pKey.kLeft=0; 
							break;
						case SDLK_RIGHT:
							pSdlGame->pKey.kRight=0;
							break;
						case SDLK_UP:
							pSdlGame->pKey.kJump = 0;
							break;
						case SDLK_DOWN:
							pSdlGame->pKey.kDown =0;
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
			
/* Application de la gravite et des collisions */

if(pGame -> level != 1)
{		
			
			
			/*collisionEnemies(&(pSdlGame->pGame.gChar),&(pSdlGame->pGame.gEnemies));*/
			

	 		collisionMap (pChar, pMap);
	 		
			/*collision (&(pSdlGame->pGame.gEnemies.eEnemy[1].eChar), &(pSdlGame->pGame.gMap));*/
			gravity (&(pSdlGame->pGame.gChar));
			for(k=0; k< pSdlGame->pGame.gEnemies.number; k++)
			{
				collisionMap (&(pSdlGame->pGame.gEnemies.eEnemy[k].eChar), pMap);
				gravity (&(pSdlGame->pGame.gEnemies.eEnemy[k].eChar));
			}
	
			warpMap(pGame);	
			moveEnemy (&(pSdlGame->pGame.gEnemies),1);
			if (pGame -> level == 2)
			{
				pSdlGame->scrollX=0;
				pSdlGame->scrollY=0;
				pGame -> level =42;
			}
		/*	printf(" posX : %f \n posY :%f \n\n ", getPosiChar(pChar).x , getPosiChar(pChar).y); 
		printf(" Vret : %d \n " , pGame -> level);  */
		        refresh = 1;
		        previousClock = currentClock;
			
			/* Limitation de la fenetre de scrolling*/
			if (pSdlGame->scrollX<0)
				pSdlGame->scrollX=0;
			if (pSdlGame->scrollX+SCREEN_WIDTH>TAILLE_SPRITE*pMap->dimx-1)
				pSdlGame->scrollX=TAILLE_SPRITE*pMap->dimx-SCREEN_WIDTH;
		//	printf("======>%f<======", pSdlGame->pGame.gChar.cPosi.v_x);
	//	for(k=0; k< pSdlGame->pGame.gEnemies.number; k++)
	//	{
			//printf("======> %d <=======\n ", collision(&(pSdlGame->pGame.gChar.cPosi),&(pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi)));
		
			
			
			
	
			keyManagment(pSdlGame);	
			if(pSdlGame->pGame.gChar.projection == 1)
			{
					if(powerDetect<4)
					{
						action(&(pSdlGame->pGame.gChar.cPosi), powerDetect);
						powerDetect+=0.4;
					}
					else
					{
						powerDetect=0;
						pSdlGame->pGame.gChar.projection=0;
					}
				
			}
			if (pSdlGame->pGame.gChar.projection == 2)
			{
				if(powerDetect<4)
				{
					action(&(pSdlGame->pGame.gChar.cPosi), -powerDetect);
					powerDetect+=0.4;
				}
				else
				{
					powerDetect=0;
					pSdlGame->pGame.gChar.projection=0;
				}
			}
				
			
	/*Deplacement de l'ecran*/
		temp = (int)(getPosiChar(pChar).x*TAILLE_SPRITE-pSdlGame->scrollX);
		if(temp > SCREEN_WIDTH*1/2-10 && temp < SCREEN_WIDTH*1/2+10 && temp >0 && temp<SCREEN_WIDTH)
			pSdlGame->scrollX+=pChar->cPosi.v_x*TAILLE_SPRITE;
		//printf("temp = %d_______SCREEN_WIDTH*1/2= %d\n", temp, SCREEN_WIDTH*1/2);
	/*	if(temp == SCREEN_WIDTH*1/2 && temp >0 && temp<SCREEN_WIDTH )
						pSdlGame->scrollX+=pChar->cPosi.v_x*TAILLE_SPRITE;*/
		
		}
		else
		{
		
			keyManagment2(pSdlGame);
			collisionMap (pChar, pMap);
			warpMap(pGame);
		
		
		}
				
	}
		
					
		if (refresh==1)
		{
			
		    /* on affiche le Game sur le buffer caché */
		    sdlDisplay(pSdlGame);

		    /* on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle) */
		    SDL_Flip( pSdlGame->surfaceScreen);
		}
		
	}
	DestructionSprite (&(pSdlGame->pSprite));
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


