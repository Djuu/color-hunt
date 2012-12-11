#include <assert.h>
#include <time.h>

#include "SDLGame.h"

const int TAILLE_SPRITE= 20;
const int CHAR_SPRITE_W =52;
const int CHAR_SPRITE_H =54;
const int SCREEN_WIDTH =800;
const int SCREEN_HEIGHT =600;

SDL_Surface *SDL_load_image(const char* filename );
void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination, int x, int y);

void initSDL(SdlGame *pSdlGame)
{
	
	Game *pGame;
	int k;
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
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) 
	{
	  printf("%s", Mix_GetError());
	}
	
/*Background*/
  
  SDL_Surface* temp = IMG_Load("data/bg1.jpg");
  pSdlGame->surfaceBG = SDL_DisplayFormat(temp);


	pSdlGame -> surfaceChar =  IMG_Load("data/hero4.png");
	if (pSdlGame->surfaceChar ==NULL)
		pSdlGame->surfaceChar =  IMG_Load("../data/hero4.png");
	assert( pSdlGame->surfaceChar!=NULL);

	/*Surface de tableau d'ennemie*/
	pSdlGame -> pSpritesEnemy = (Sprites*)malloc(pSdlGame -> pGame.gEnemies.number * sizeof(Sprites));
	for(i=0; i<pSdlGame -> pGame.gEnemies.number; i++)
	{
		pSdlGame -> surfaceEnemies = IMG_Load("data/SpriteEnemy.png");
		if (pSdlGame->surfaceEnemies ==NULL)
			pSdlGame->surfaceEnemies = IMG_Load("../data/SpriteEnemy.png");
		assert( pSdlGame->surfaceEnemies!=NULL);
	}	
	
	pSdlGame -> surfaceEarth = IMG_Load("data/grass2.png");
	if (pSdlGame->surfaceEarth==NULL)	
		pSdlGame->surfaceEarth = IMG_Load("../data/grass2.png");
	assert( pSdlGame->surfaceEarth!=NULL);
	
pSdlGame -> surfaceGrass = IMG_Load("data/grass4.png");
	if (pSdlGame->surfaceGrass==NULL)	
		pSdlGame->surfaceGrass = IMG_Load("../data/grass4.png");
	assert( pSdlGame->surfaceGrass!=NULL);
	
pSdlGame -> surfaceFireBall = IMG_Load("data/fireBall.png");
	if (pSdlGame->surfaceFireBall==NULL)	
		pSdlGame->surfaceFireBall = IMG_Load("../data/fireBall.png");
	assert( pSdlGame->surfaceFireBall!=NULL);

pSdlGame -> surfaceLife = IMG_Load("data/life.png");
	if (pSdlGame->surfaceLife==NULL)	
		pSdlGame->surfaceLife = IMG_Load("../data/life.png");
	assert( pSdlGame->surfaceLife!=NULL);

pSdlGame ->surfaceLifeBG = IMG_Load("data/lifeBg.png");
	if (pSdlGame->surfaceLifeBG==NULL)	
		pSdlGame->surfaceLifeBG = IMG_Load("../data/lifeBg.png");
	assert( pSdlGame->surfaceLifeBG!=NULL);
	
pSdlGame ->surfaceBall = IMG_Load("data/block.png");
	if (pSdlGame->surfaceBall==NULL)	
		pSdlGame->surfaceBall = IMG_Load("../data/block.png");
	assert( pSdlGame->surfaceBall!=NULL);

/*pSdlGame ->surfaceFilter = IMG_Load("data/filter.png");
	if (pSdlGame->surfaceFilter==NULL)	
		pSdlGame->surfaceFilter = IMG_Load("../data/filter.png");
	assert( pSdlGame->surfaceFilter!=NULL);*/

/*Initialisation des sprites*/
	pSdlGame->pSprites.source = pSdlGame -> surfaceChar; /*incrementation du sprite global*/
	/*Cour vers la droite*/
	InitSprite (&(pSdlGame->pSprites),right, 52, 54, 31, 15);	
	/*Cour vers la gauche*/
	InitSprite (&(pSdlGame->pSprites),left, 52, 54, 31, 15);
	/*attaque epee droite*/
	InitSprite (&(pSdlGame->pSprites),attackR, 98, 56, 17, 0);
	/*attaque epee gauche*/
	InitSprite (&(pSdlGame->pSprites),attackL, 98, 56, 17, 0);
	/*attaque feu droite*/
	InitSprite (&(pSdlGame->pSprites),attackFR, 52, 56, 11, 0);
	/*attaque feu gauche*/
	InitSprite (&(pSdlGame->pSprites),attackFL, 52, 56, 11, 0);
	/*Attend droite*/
	InitSprite (&(pSdlGame->pSprites),stayR, 52, 54, 7, 0);
	/*Attend gauche*/
	InitSprite (&(pSdlGame->pSprites),stayL, 52, 54, 7, 0);
	/*KO droit*/
	InitSprite (&(pSdlGame->pSprites),KOR, 52, 45, 5, 5);
	/*KO gauche*/
	InitSprite (&(pSdlGame->pSprites),KOL, 52, 45, 5, 0);
	/*Saut droite up*/
	/*InitSprite (&(pSdlGame->pSprites),jumpUpR, 54, 55, 8, 8);*/
	/*Saut droite down*/
	/*InitSprite (&(pSdlGame->pSprites),jumpDownR, 52, 50, 8, 8);*/
	
	pSdlGame->pSpritesObject.source = pSdlGame -> surfaceFireBall; /*incrementation du sprite global*/
	/*boule de feu droit*/
	InitSprite (&(pSdlGame->pSpritesObject),0, 30, 56, 5, 0);
	/*boule de feu gauche*/
	InitSprite (&(pSdlGame->pSpritesObject),1, 30, 56, 5, 0);
	
	

	for(k=0; k<pSdlGame -> pGame.gEnemies.number; k++)
	{
		
		pSdlGame->pSpritesEnemy[k].source = pSdlGame->surfaceEnemies;
		
		/*Attend droite*/
		InitSprite (&(pSdlGame->pSpritesEnemy[k]),1, 31, 38, 3, 0);
		/*Attend gauche*/
		InitSprite (&(pSdlGame->pSpritesEnemy[k]),0, 31, 38, 3, 0);
		/*Cour vers la droite*/
		InitSprite (&(pSdlGame->pSpritesEnemy[k]),3, 28, 42, 6, 0);
		/*Cour vers la gauche*/
		InitSprite (&(pSdlGame->pSpritesEnemy[k]),2, 28, 42, 6, 0);
		/*Attaque gauche*/
		InitSprite (&(pSdlGame->pSpritesEnemy[k]),4, 61, 63, 8, 0);
		/*Attaque droite*/
		InitSprite (&(pSdlGame->pSpritesEnemy[k]),5, 61, 63, 8, 0);
	}
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
	SDL_Rect posiEnemy,posiChar, posiFireBall;
	/*Position posiEnemy;*/
	
	
	/*Background*/
	SDL_BlitSurface(pSdlGame->surfaceBG, NULL, pSdlGame->surfaceScreen, NULL);

	
	posiChar.x = getPosiChar(pChar).x*TAILLE_SPRITE - pSdlGame->scrollX;
	posiChar.y = getPosiChar(pChar).y*TAILLE_SPRITE - pSdlGame->scrollY;

	displaySprite(&(pSdlGame->pSprites), posiChar, pSdlGame->surfaceScreen);
	
	posiFireBall.x = pSdlGame->pGame.gObjects.oObject[1].oPosi.x*TAILLE_SPRITE- pSdlGame->scrollX;
	posiFireBall.y = pSdlGame->pGame.gObjects.oObject[1].oPosi.y*TAILLE_SPRITE- pSdlGame->scrollY;
	
	displaySprite(&(pSdlGame->pSpritesObject), posiFireBall, pSdlGame->surfaceScreen);
	
	for(k=0; k<pSdlGame -> pGame.gEnemies.number; k++)
	{
		posiEnemy.x = getPosiEnemy(pEnemies,k).x*TAILLE_SPRITE- pSdlGame->scrollX;
		posiEnemy.y = getPosiEnemy(pEnemies,k).y*TAILLE_SPRITE- pSdlGame->scrollY;
		displaySprite(&(pSdlGame->pSpritesEnemy[k]), posiEnemy, pSdlGame->surfaceScreen);
	}
	
	displayGauge(pSdlGame->surfaceLifeBG, pSdlGame->surfaceLife, pSdlGame->surfaceScreen, pSdlGame->pGame.gChar.life);
	
	
	
	SDL_Rect positionBall;
	positionBall.x = pSdlGame->pGame.gObjects.oObject[2].oPosi.x*TAILLE_SPRITE- pSdlGame->scrollX;
	positionBall.y = pSdlGame->pGame.gObjects.oObject[2].oPosi.y*TAILLE_SPRITE- pSdlGame->scrollY;
	
	rotationObject(pSdlGame->surfaceBall, positionBall, &(pSdlGame->pGame.gObjects.oObject[2].angle), 0.01, pSdlGame->surfaceScreen);
	stabilizeObject(&(pSdlGame->pGame.gObjects.oObject[2]));
	//printf("x = %d, y= %d\n", positionBall.x, positionBall.y);
	//printf("angle = %f\n",pSdlGame->pGame.gObjects.oObject[2].angle);

//	pSdlGame->pGame.gObjects.oObject[2].angle++;
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
	/*SDL_Rect rFilter;
	rFilter.x=100;
	rFilter.y=100;
	
	SDL_BlitSurface(pSdlGame->surfaceFilter, NULL,  pSdlGame->surfaceScreen, &rFilter);*/
	
	
	/*SDL_BlitSurface(pSdlGame->surfaceChar,NULL, pSdlGame->surfaceScreen, &posiChar);*/
	
	
	
}

void colisionSprite(SdlGame *pSdlGame)
{
	int k;
	/*printf("position : %d, valeur = %d\n", pSdlGame->pSprites.position, pSdlGame->pSprites.aSprite[pSdlGame->pSprites.position].height);*/
	if (pSdlGame->pGame.gChar.cPosi.floor == 1)	/*Si on n'est pas en l'air*/
	{
		pSdlGame->pGame.gChar.cPosi.spriteSizeW = (float)(pSdlGame->pSprites.aSprite[pSdlGame->pSprites.position].width)/(float)TAILLE_SPRITE;
	}
	else
	{
		pSdlGame->pGame.gChar.cPosi.spriteSizeW = 2;
	}
	pSdlGame->pGame.gChar.cPosi.spriteSizeH = (float)(pSdlGame->pSprites.aSprite[pSdlGame->pSprites.position].height)/(float)TAILLE_SPRITE;
	
	/*for(k=0; k< pSdlGame->pGame.gEnemies.number; k++)
	{
		if (pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.floor == 1)	
		{
			pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.spriteSizeW = (float)(pSdlGame->pSpritesEnemy[k].aSprite[pSdlGame->pSpritesEnemy[k].position].width)/(float)TAILLE_SPRITE;
		}
		else
		{
			pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.spriteSizeW = 2;
		}
		//pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.spriteSizeH = (float)(pSdlGame->pSpritesEnemy[k].aSprite[pSdlGame->pSpritesEnemy[k].position].height)/(float)TAILLE_SPRITE;
	}*/
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
	if (pSdlGame->pKey.kUp ==1)
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
	if(pSdlGame->pKey.kUp==0 && pSdlGame->pKey.kDown==0)
	{
			
		initSpeedY(&(pSdlGame->pGame));
	}


}
void keyManagment(SdlGame *pSdlGame)
{
	int i;

			
		if(pSdlGame->pGame.gChar.projection == 0 && pSdlGame->pGame.gChar.attack ==0 && pSdlGame->pGame.gChar.superAttack == 0)
		{
			
			if(pSdlGame->pKey.kLeft==1)
			{

				if(pSdlGame->pGame.gChar.attack == 0 && pSdlGame->pGame.gChar.superAttack == 0)
				{
					animSprite (&(pSdlGame->pSprites), left, 0, pSdlGame->pGame.gChar.cPosi.direction);
				}
				controlKey(&(pSdlGame->pGame), 'g');
			}

			if(pSdlGame->pKey.kRight==1)
			{
				

				if(pSdlGame->pGame.gChar.attack == 0 && pSdlGame->pGame.gChar.superAttack == 0)
				{
					animSprite (&(pSdlGame->pSprites), right, 0, pSdlGame->pGame.gChar.cPosi.direction);
				}
				controlKey(&(pSdlGame->pGame), 'd');
			}


			if (pSdlGame->pKey.kJump ==1)
			{
				/*pSdlGame->pAnim.jump =1;*/
				controlKey(&(pSdlGame->pGame), 's');
			}
	/*	if (pSdlGame->pAnim.jump == 1)
		{
				if (pSdlGame->pSprites.direction == 0)
				{
					if(pSdlGame->pGame.gChar.cPosi.v_y!=0)
					{
						printf("aaaaaaaaaaaaaaaaaaa\n");
						animSprite (&(pSdlGame->pSprites), jumpUpR, 0, pSdlGame->pGame.gChar.cPosi.direction);
					}
					else
					{
						animSprite (&(pSdlGame->pSprites), jumpDownR, 1, pSdlGame->pGame.gChar.cPosi.direction);
					}
				}	
			
		}*/
		
		}

	
			if (pSdlGame->pKey.kCtrlR == 1)
			{  
				pSdlGame->pGame.gChar.attack =1;
				if (pSdlGame->pSprites.direction == 0)
				{
					controlKey(&(pSdlGame->pGame), 'a');
					animSprite (&(pSdlGame->pSprites), attackR, 1, pSdlGame->pGame.gChar.cPosi.direction);
				}
				if (pSdlGame->pSprites.direction == 1)
				{
					controlKey(&(pSdlGame->pGame), 'a');
					animSprite (&(pSdlGame->pSprites), attackL, 1, pSdlGame->pGame.gChar.cPosi.direction);
				}
				
			}
			
			if (pSdlGame->pKey.kShift == 1)
			{  
				pSdlGame->pGame.gChar.superAttack =1;
				if (pSdlGame->pSprites.direction == 0)
				{
					
					controlKey(&(pSdlGame->pGame), 'A');
					animSprite (&(pSdlGame->pSprites), attackFR, 1, pSdlGame->pGame.gChar.cPosi.direction);
					
					
				}
				if (pSdlGame->pSprites.direction == 1)
				{
					controlKey(&(pSdlGame->pGame), 'A');
					animSprite (&(pSdlGame->pSprites), attackFL, 1, pSdlGame->pGame.gChar.cPosi.direction);
				}
				
			}
			static int tempA; 
			if (pSdlGame->pGame.gChar.superAttack == 1 )
			{
				tempA=1;
			}
			
			if(tempA = 1)
			{
				if (pSdlGame->pSprites.direction == 0)
				{
					
					animSprite (&(pSdlGame->pSpritesObject), fireBallR, 0, pSdlGame->pGame.gChar.cPosi.direction);
					
				}
				if (pSdlGame->pSprites.direction == 1)
				{
					
					animSprite (&(pSdlGame->pSpritesObject), fireBallL, 0, pSdlGame->pGame.gChar.cPosi.direction);
					
				}
			}
			
			
			
			if(pSdlGame->pKey.kLeft==0 && pSdlGame->pKey.kRight==0 && pSdlGame->pGame.gChar.attack == 0  && pSdlGame->pGame.gChar.superAttack == 0)
			{
				initSpeedX(&(pSdlGame->pGame));
				if((pSdlGame->pSprites.aSprite[attackR].end==1 || pSdlGame->pSprites.aSprite[attackL].end==1) &&
				(pSdlGame->pSprites.aSprite[attackFR].end==1 || pSdlGame->pSprites.aSprite[attackFL].end==1) && 
				/*(pSdlGame->pSprites.aSprite[jumpUpR].end==1 || pSdlGame->pSprites.aSprite[jumpDownR].end==1) && */
				(pSdlGame->pSprites.aSprite[KOR].end==1 || pSdlGame->pSprites.aSprite[KOL].end==1))
				{
					if (pSdlGame->pSprites.direction == 0)
					{
						animSprite (&(pSdlGame->pSprites), stayR, 0, pSdlGame->pGame.gChar.cPosi.direction);
					}
					else if(pSdlGame->pSprites.direction == 1)
					{
						animSprite (&(pSdlGame->pSprites), stayL, 0, pSdlGame->pGame.gChar.cPosi.direction);
					}
				}
			}
			if (pSdlGame->pSprites.aSprite[attackR].end==1 && pSdlGame->pSprites.aSprite[attackL].end==1)
			{
				pSdlGame->pKey.kCtrlR = 0;	
		
				pSdlGame->pGame.gChar.attack = 0;
			
			}

			if (pSdlGame->pSprites.aSprite[attackFR].end==1 && pSdlGame->pSprites.aSprite[attackFL].end==1)
			{
				pSdlGame->pKey.kShift = 0;	
				pSdlGame->pGame.gChar.superAttack = 0;
				
			}
		/*	if (pSdlGame->pSprites.aSprite[jumpUpR].end==1 && pSdlGame->pSprites.aSprite[jumpDownR].end==1)
			{
				
				pSdlGame->pAnim.jump = 0;
				
			}*/
	/*	if(pSdlGame->pSprites.aSprite[KOR].end==1 && pSdlGame->pSprites.aSprite[KOL].end==1)
		{
			pSdlGame->pGame.gChar.projection=0;
		}
	*/	
	if (pSdlGame->pKey.kCtrlL == 1)
	{
			
			controlKey(&(pSdlGame->pGame), 'o');
			
	}
	if (pSdlGame->pKey.kCtrlL == 0)
	{
			controlKey(&(pSdlGame->pGame), 'n');
	}
	if (pSdlGame->pKey.kUp ==1 && pSdlGame->pKey.kCtrlL == 1)
	{
		controlKey(&(pSdlGame->pGame), 'u');
	}
	

	
}

void animEnemies(SdlGame *pSdlGame)
{
	int k;
		for(k=0; k< pSdlGame->pGame.gEnemies.number; k++)
		{
			
			
			if (pSdlGame ->pGame.gEnemies.eEnemy[k].stateAttack == 1)
			{
				if (pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction == 1)
				{
					pSdlGame->pSpritesEnemy[k].aSprite[4].end = 0;
				}
				if (pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction == 0)
				{
					pSdlGame->pSpritesEnemy[k].aSprite[5].end = 0;
				}
			}
			if (pSdlGame->pSpritesEnemy[k].aSprite[4].end == 1 && pSdlGame->pSpritesEnemy[k].aSprite[5].end == 1)
			{
				pSdlGame ->pGame.gEnemies.eEnemy[k].stateAttack = 0;
				pSdlGame ->pGame.gEnemies.eEnemy[k].eChar.attack = 0;
			}
	printf("end(4) = %d_____end(5)= %d\n", pSdlGame->pSpritesEnemy[k].aSprite[4].end, pSdlGame->pSpritesEnemy[k].aSprite[5].end);
			printf("Enemie = %d, attack = %d\n",k,pSdlGame->pGame.gEnemies.eEnemy[k].eChar.attack );
			if (pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.v_x <0 && pSdlGame->pGame.gEnemies.eEnemy[k].eChar.attack == 0)
			{
					animSprite (&(pSdlGame->pSpritesEnemy[k]), 2, 0, pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction);
			}
			if (pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.v_x >0 && pSdlGame->pGame.gEnemies.eEnemy[k].eChar.attack == 0)
			{
				animSprite (&(pSdlGame->pSpritesEnemy[k]), 3, 0, pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction);
			}
			if (pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.v_x == 0 &&  pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction ==0  && pSdlGame->pGame.gEnemies.eEnemy[k].eChar.attack == 0)
			{
				animSprite (&(pSdlGame->pSpritesEnemy[k]), 1, 0, pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction);
			}
			if (pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.v_x == 0 &&  pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction ==1  && pSdlGame->pGame.gEnemies.eEnemy[k].eChar.attack == 0)
			{
				animSprite (&(pSdlGame->pSpritesEnemy[k]), 0, 0, pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction);
			}		
			if (pSdlGame->pGame.gEnemies.eEnemy[k].stateAttack == 1 && pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction == 1)
			{
				animSprite (&(pSdlGame->pSpritesEnemy[k]), 5, 1, pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction);
			}
			if (pSdlGame->pGame.gEnemies.eEnemy[k].stateAttack == 1 && pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction == 0)
			{
				animSprite (&(pSdlGame->pSpritesEnemy[k]), 4, 1, pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction);
			}
		}	
		
		
}

void loopSDL(SdlGame *pSdlGame)
{
	int k,l, m;
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
	
	pSdlGame->pKey.kLeft = 0;
	pSdlGame->pKey.kRight = 0;
	pSdlGame->pKey.kJump = 0;
	pSdlGame->pKey.kUp = 0;
	pSdlGame->pKey.kDown = 0;
	pSdlGame->pKey.kCtrlR = 0;
	pSdlGame->pKey.kCtrlL = 0;
	pSdlGame->pKey.kShift = 0;
	
	bgBW(pSdlGame->surfaceBG, 1); /*gestion de la saturation de l'arrière plan*/

	audioBG();
	audioWind();
	
	
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
						case SDLK_SPACE:
					/*		if (pSdlGame->pSprites.direction == 0)
							{
								pSdlGame->pSprites.aSprite[jumpUpR].end=0;
								pSdlGame->pSprites.aSprite[jumpDownR].end=0;
							}*/
							pSdlGame->pKey.kJump =1;
							break;	
						case SDLK_UP:
							pSdlGame->pKey.kUp =1;
							break;	
						case SDLK_DOWN:
							pSdlGame->pKey.kDown =1;
							break;	
						case SDLK_RCTRL:
							
							if (pSdlGame->pSprites.frame !=0 && pSdlGame->pGame.gChar.attack == 0)
							{
								pSdlGame->pSprites.frame=0;
							}
							if (pSdlGame->pSprites.frame==0)
							{
								audioSward();
							}
							if (pSdlGame->pSprites.direction == 0)
							{
								pSdlGame->pSprites.aSprite[attackR].end=0;
								
							}
							if(pSdlGame->pSprites.direction == 1)
							{
								pSdlGame->pSprites.aSprite[attackL].end=0;
							}
							
							pSdlGame->pKey.kCtrlR =1;
							
							break;		
						case SDLK_RSHIFT:
							
							if (pSdlGame->pSprites.frame !=0 && pSdlGame->pGame.gChar.superAttack == 0)
							{
								pSdlGame->pSprites.frame=0;
							}
							if (pSdlGame->pSprites.frame==0)
							{
								audioFireBall();
							}
							if (pSdlGame->pSprites.direction == 0)
							{
								pSdlGame->pSprites.aSprite[attackFR].end=0;
							}
							if(pSdlGame->pSprites.direction == 1)
							{
								pSdlGame->pSprites.aSprite[attackFL].end=0;
							}
							
							pSdlGame->pKey.kShift =1;
							break;		
						case SDLK_LCTRL:
							if(pSdlGame->pKey.kCtrlL == 0)
							{
								pSdlGame->pKey.kCtrlL = 1;
							}
							else if(pSdlGame->pKey.kCtrlL == 1)
							{
								pSdlGame->pKey.kCtrlL = 0;	
							}
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
							if (pSdlGame->pGame.gChar.attack == 0 && pSdlGame->pGame.gChar.superAttack == 0)
							{
								pSdlGame->pSprites.frame=0;
							}
							pSdlGame->pKey.kLeft=0; 							
							break;
						case SDLK_RIGHT:
							if (pSdlGame->pGame.gChar.attack == 0 && pSdlGame->pGame.gChar.superAttack == 0)
							{
								pSdlGame->pSprites.frame=0;
							}
							pSdlGame->pKey.kRight=0;							
							break;
						case SDLK_SPACE:
							pSdlGame->pKey.kJump = 0;
							break;
						case SDLK_UP:
							pSdlGame->pKey.kUp = 0;
							break;
						case SDLK_DOWN:
							pSdlGame->pKey.kDown = 0;
							break;
						case SDLK_RCTRL:
							
							break;
						case SDLK_RSHIFT:
							
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
			
			 
			//audioWind(); /*son arrier plan "wind"*/
			
			for(l=0; l< pSdlGame->pGame.gObjects.number; l++)
			{
				collision(&(pSdlGame->pGame.gChar.cPosi),&(pSdlGame->pGame.gObjects.oObject[l].oPosi));
			}
			/*collisionEnemies(&(pSdlGame->pGame.gChar),&(pSdlGame->pGame.gEnemies));*/
			applySpeedObject(&(pSdlGame->pGame.gObjects.oObject[1]));
			superAttackDmg(&(pSdlGame -> pGame));
	/*		printf("OBJET .X : %f\n",pSdlGame->pGame.gObjects.oObject[1].oPosi.x);*/
			colisionSprite(pSdlGame);
	 		collisionMap (&(pChar->cPosi), pMap);
	 		

	 		
	 		attack(&(pSdlGame -> pGame));
	 		
	 		detect(&(pSdlGame->pGame));
			animEnemies(pSdlGame);
			enemyAttack(&(pSdlGame -> pGame));
			
			/*collision (&(pSdlGame->pGame.gEnemies.eEnemy[1].eChar), &(pSdlGame->pGame.gMap));*/
			gravity (&(pSdlGame->pGame.gChar.cPosi));
			collisionMap (&(pSdlGame->pGame.gObjects.oObject[2].oPosi), pMap);
			gravity (&(pSdlGame->pGame.gObjects.oObject[2].oPosi));
			
			//printf("v_y = %f\n", pSdlGame->pGame.gObjects.oObject[2].oPosi.v_y);

			for(k=0; k< pSdlGame->pGame.gEnemies.number; k++)
			{
				if(pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.x >0 && pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.y >0)
				{
					pSdlGame->pGame.gEnemies.eEnemy[k].eChar.attack=0;
					gravity (&(pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi));
					collisionMap (&(pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi), pMap);
					refreshDirection(&(pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi));
				}
			}
			
			refreshDirection(&(pSdlGame->pGame.gChar.cPosi));
			
			warpMap(pGame);	
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
		
			keyManagment(pSdlGame);	
			
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! A METTRE A L EXTERIEUR DE SDLGAME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/			
/*Projection apres impacte*/

		
			if(pSdlGame->pGame.gChar.projection == 1 && pSdlGame->pGame.gChar.attack!=1 && pSdlGame->pGame.gChar.superAttack!=1)
			{
					animSprite (&(pSdlGame->pSprites), KOL, 1, pSdlGame->pGame.gChar.cPosi.direction);
					
			}
			if (pSdlGame->pGame.gChar.projection == 2 && pSdlGame->pGame.gChar.attack!=1 && pSdlGame->pGame.gChar.superAttack!=1)
			{
				animSprite (&(pSdlGame->pSprites), KOR, 1, pSdlGame->pGame.gChar.cPosi.direction);
				
			}
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/					
			
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
			collisionMap (&(pChar->cPosi), pMap);
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






void freeSdl(SdlGame *pSdlGame)
{
	SDL_FreeSurface (pSdlGame->surfaceScreen);
	SDL_FreeSurface (pSdlGame->surfaceChar);
	SDL_FreeSurface (pSdlGame->surfaceEarth);
	SDL_FreeSurface (pSdlGame->surfaceGrass);
	SDL_FreeSurface (pSdlGame->surfaceBG);
	freeSprite(&(pSdlGame->pSprites));
	Mix_CloseAudio();
	SDL_Quit();
}

