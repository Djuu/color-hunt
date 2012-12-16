#include <assert.h>
#include <time.h>
#include <math.h>
#include <SDL/SDL_ttf.h>
#include "SDLGame.h"

const int TAILLE_SPRITE= 20;
const int CHAR_SPRITE_W =52;
const int CHAR_SPRITE_H =54;
const int SCREEN_WIDTH =800;
const int SCREEN_HEIGHT =600;


void initSDL(SdlGame *pSdlGame)
{
	
	Game *pGame;
	int k;
	int i;
	pSdlGame->scrollX=0;
	pSdlGame->scrollY=0;
	pSdlGame->dialogue =0;
	pGame = &(pSdlGame -> pGame);
	pSdlGame ->confirmMenu = 0;
	pSdlGame ->choiceMenu = 1;
	pSdlGame ->choiceDialogue = 1;
	pSdlGame ->confirmDialogue = 0;
	pSdlGame->choiceSpeech = 2.0;
	initDialogue(&(pSdlGame->pTree)); /*Initialisation de l'arbre de dialogue*/
	
	pSdlGame->flyMode =0;
	
	
	affichageArborescent((pSdlGame->pTree));
	SDL_Init(SDL_INIT_VIDEO);
	if(TTF_Init() == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	pSdlGame -> surfaceScreen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32, SDL_HWSURFACE|SDL_DOUBLEBUF);/*|SDL_FULLSCREEN);*/
	SDL_WM_SetCaption( "ColorHunt", NULL );
	
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) 
	{
	  printf("%s", Mix_GetError());
	}
	initGame(pGame,"Map/WorldMap.txt");
	
		pSdlGame ->font = TTF_OpenFont("data/fonts/times.ttf", 20);
	if (pSdlGame ->font == NULL)
	{
		printf("Erreur de chargement de police ! \n");
		exit(1);
	}
/*MENU*/

	/*Background*/
	SDL_Surface* tempMenu = IMG_Load("data/image/menuBG.jpg");
	pSdlGame ->surfaceMenuBG = SDL_DisplayFormat(tempMenu);
	assert( pSdlGame->surfaceMenuBG!=NULL);
	
	SDL_Surface* tempWMap = IMG_Load("data/image/BGWorldMap.png");
	pSdlGame ->surfaceMapBG= SDL_DisplayFormat(tempWMap);
	assert( pSdlGame->surfaceMapBG!=NULL);

	pSdlGame ->surfaceStart = IMG_Load("data/image/startButton.png");
	if (pSdlGame ->surfaceStart==NULL)	
		pSdlGame ->surfaceStart = IMG_Load("../data/image/startButton.png");
	assert( pSdlGame ->surfaceStart!=NULL);
	
	pSdlGame ->surfaceExit = IMG_Load("data/image/exitButton.png");
	if (pSdlGame ->surfaceExit==NULL)	
		pSdlGame ->surfaceExit = IMG_Load("../data/image/exitButton.png");
	assert( pSdlGame ->surfaceExit!=NULL);	
	
	
	
	
/*Background*/
  
	SDL_Surface* temp = IMG_Load("data/image/bg1.jpg");
	pSdlGame->surfaceBG = SDL_DisplayFormat(temp);
	assert( pSdlGame->surfaceBG!=NULL);

	pSdlGame -> surfaceChar =  IMG_Load("data/image/hero4.png");
	if (pSdlGame->surfaceChar ==NULL)
		pSdlGame->surfaceChar =  IMG_Load("../data/image/hero4.png");
	assert( pSdlGame->surfaceChar!=NULL);

	/*Surface de tableau d'ennemie*/
	pSdlGame -> pSpritesEnemy = (Sprites*)malloc(pSdlGame -> pGame.gEnemies.number * sizeof(Sprites));

	pSdlGame -> surfaceEnemies = IMG_Load("data/image/SpriteEnemy.png");
		if (pSdlGame->surfaceEnemies ==NULL)
			pSdlGame->surfaceEnemies = IMG_Load("../data/image/SpriteEnemy.png");
		assert( pSdlGame->surfaceEnemies!=NULL);
	
	pSdlGame -> surfaceEarth = IMG_Load("data/image/grass2.png");
	if (pSdlGame->surfaceEarth==NULL)	
		pSdlGame->surfaceEarth = IMG_Load("../data/image/grass2.png");
	assert( pSdlGame->surfaceEarth!=NULL);
	
pSdlGame -> surfaceGrass = IMG_Load("data/image/grass4.png");
	if (pSdlGame->surfaceGrass==NULL)	
		pSdlGame->surfaceGrass = IMG_Load("../data/image/grass4.png");
	assert( pSdlGame->surfaceGrass!=NULL);

pSdlGame -> surfaceLife = IMG_Load("data/image/lifeGauge.png");
	if (pSdlGame->surfaceLife==NULL)	
		pSdlGame->surfaceLife = IMG_Load("../data/image/lifeGauge.png");
	assert( pSdlGame->surfaceLife!=NULL);
	
pSdlGame -> surfaceMana = IMG_Load("data/image/manaGauge.png");
	if (pSdlGame->surfaceMana==NULL)	
		pSdlGame->surfaceMana = IMG_Load("../data/image/manaGauge.png");
	assert( pSdlGame->surfaceMana!=NULL);

pSdlGame ->surfaceLifeBG = IMG_Load("data/image/lifeBg.png");
	if (pSdlGame->surfaceLifeBG==NULL)	
		pSdlGame->surfaceLifeBG = IMG_Load("../data/image/lifeBg.png");
	assert( pSdlGame->surfaceLifeBG!=NULL);
	
pSdlGame ->surfaceBall = IMG_Load("data/image/block.png");
	if (pSdlGame->surfaceBall==NULL)	
		pSdlGame->surfaceBall = IMG_Load("../data/image/block.png");
	assert( pSdlGame->surfaceBall!=NULL);
	
pSdlGame ->surfaceBall2 = IMG_Load("data/image/block.png");
	if (pSdlGame->surfaceBall2==NULL)	
		pSdlGame->surfaceBall2 = IMG_Load("../data/image/block.png");
	assert( pSdlGame->surfaceBall2!=NULL);

pSdlGame -> surfaceCharMap =  IMG_Load("data/image/charMap.png");
	if (pSdlGame->surfaceCharMap ==NULL)
		pSdlGame->surfaceCharMap =  IMG_Load("../data/image/charMap.png");
	assert( pSdlGame->surfaceCharMap!=NULL);
	
pSdlGame ->surfaceBorder = IMG_Load("data/image/border2.png");
	if (pSdlGame->surfaceBorder==NULL)	
		pSdlGame->surfaceBorder = IMG_Load("../data/image/border2.png");
	assert( pSdlGame->surfaceBorder!=NULL);
	
pSdlGame ->surfaceMapEarth1 = IMG_Load("data/image/wearth1.png");
	if (pSdlGame->surfaceMapEarth1==NULL)	
		pSdlGame->surfaceMapEarth1 = IMG_Load("../data/image/wearth1.png");
	assert( pSdlGame->surfaceMapEarth1!=NULL);
	
pSdlGame ->surfaceMapEarth2 = IMG_Load("data/image/wearth2.png");
	if (pSdlGame->surfaceMapEarth2==NULL)	
		pSdlGame->surfaceMapEarth2 = IMG_Load("../data/image/wearth2.png");
	assert( pSdlGame->surfaceMapEarth2!=NULL);
	
pSdlGame ->surfaceMapGrass1 = IMG_Load("data/image/wgrass.png");
	if (pSdlGame->surfaceMapGrass1==NULL)	
		pSdlGame->surfaceMapGrass1 = IMG_Load("../data/image/wgrass.png");
	assert( pSdlGame->surfaceMapGrass1!=NULL);
	
pSdlGame ->surfaceMapGrass2 = IMG_Load("data/image/wgrass2.png");
	if (pSdlGame->surfaceMapGrass2==NULL)	
		pSdlGame->surfaceMapGrass2 = IMG_Load("../data/image/wgrass2.png");
	assert( pSdlGame->surfaceMapGrass2!=NULL);
	
pSdlGame ->surfaceMapGED = IMG_Load("data/image/wgrassEartthD.png");
	if (pSdlGame->surfaceMapGED==NULL)	
		pSdlGame->surfaceMapGED = IMG_Load("../data/image/wgrassEartthD.png");
	assert( pSdlGame->surfaceMapGED!=NULL);
	
pSdlGame ->surfaceMapGEDL = IMG_Load("data/image/wgrassEartthDL.png");
	if (pSdlGame->surfaceMapGEDL==NULL)	
		pSdlGame->surfaceMapGEDL = IMG_Load("../data/image/wgrassEartthDL.png");
	assert( pSdlGame->surfaceMapGEDL!=NULL);
	
pSdlGame ->surfaceMapGEDR = IMG_Load("data/image/wgrassEartthDR.png");
	if (pSdlGame->surfaceMapGEDR==NULL)	
		pSdlGame->surfaceMapGEDR = IMG_Load("../data/image/wgrassEartthDR.png");
	assert( pSdlGame->surfaceMapGEDR!=NULL);
	
pSdlGame ->surfaceMapGEL = IMG_Load("data/image/wgrassEartthL.png");
	if (pSdlGame->surfaceMapGEL==NULL)	
		pSdlGame->surfaceMapGEL = IMG_Load("../data/image/wgrassEartthL.png");
	assert( pSdlGame->surfaceMapGEL!=NULL);
	
pSdlGame ->surfaceMapGER = IMG_Load("data/image/wgrassEartthR.png");
	if (pSdlGame->surfaceMapGER==NULL)	
		pSdlGame->surfaceMapGER = IMG_Load("../data/image/wgrassEartthR.png");
	assert( pSdlGame->surfaceMapGER!=NULL);
	
pSdlGame ->surfaceMapGEU = IMG_Load("data/image/wgrassEartthU.png");
	if (pSdlGame->surfaceMapGEU==NULL)	
		pSdlGame->surfaceMapGEU = IMG_Load("../data/image/wgrassEartthU.png");
	assert( pSdlGame->surfaceMapGEU!=NULL);
	
pSdlGame ->surfaceMapGEUL = IMG_Load("data/image/wgrassEartthUL.png");
	if (pSdlGame->surfaceMapGEUL==NULL)	
		pSdlGame->surfaceMapGEUL = IMG_Load("../data/image/wgrassEartthUL.png");
	assert( pSdlGame->surfaceMapGEUL!=NULL);
	
pSdlGame ->surfaceMapGEUR = IMG_Load("data/image/wgrassEartthUR.png");
	if (pSdlGame->surfaceMapGEUR==NULL)	
		pSdlGame->surfaceMapGEUR = IMG_Load("../data/image/wgrassEartthUR.png");
	assert( pSdlGame->surfaceMapGEUR!=NULL);
	
pSdlGame ->surfaceMapWater = IMG_Load("data/image/Water.png");
	if (pSdlGame->surfaceMapWater==NULL)	
		pSdlGame->surfaceMapWater = IMG_Load("../data/image/Water.png");
	assert( pSdlGame->surfaceMapWater!=NULL);
	
pSdlGame ->surfaceMapWaterD = IMG_Load("data/image/WaterD.png");
	if (pSdlGame->surfaceMapWaterD==NULL)	
		pSdlGame->surfaceMapWaterD = IMG_Load("../data/image/WaterD.png");
	assert( pSdlGame->surfaceMapWaterD!=NULL);
	
pSdlGame ->surfaceMapWaterU = IMG_Load("data/image/WaterU.png");
	if (pSdlGame->surfaceMapWaterU==NULL)	
		pSdlGame->surfaceMapWaterU = IMG_Load("../data/image/WaterU.png");
	assert( pSdlGame->surfaceMapWaterU!=NULL);
	
pSdlGame ->surfaceMapWaterR = IMG_Load("data/image/WaterR.png");
	if (pSdlGame->surfaceMapWaterR==NULL)	
		pSdlGame->surfaceMapWaterR = IMG_Load("../data/image/WaterR.png");
	assert( pSdlGame->surfaceMapWaterR!=NULL);
	
pSdlGame ->surfaceMapWaterL = IMG_Load("data/image/WaterL.png");
	if (pSdlGame->surfaceMapWaterL==NULL)	
		pSdlGame->surfaceMapWaterL = IMG_Load("../data/image/WaterL.png");
	assert( pSdlGame->surfaceMapWaterL!=NULL);

pSdlGame ->surfaceMapWaterCDL = IMG_Load("data/image/WaterCDL.png");
	if (pSdlGame->surfaceMapWaterCDL==NULL)	
		pSdlGame->surfaceMapWaterCDL = IMG_Load("../data/image/WaterCDL.png");
	assert( pSdlGame->surfaceMapWaterCDL!=NULL);
	
pSdlGame ->surfaceMapWaterCUL = IMG_Load("data/image/WaterCUL.png");
	if (pSdlGame->surfaceMapWaterCUL==NULL)	
		pSdlGame->surfaceMapWaterCUL = IMG_Load("../data/image/WaterCUL.png");
	assert( pSdlGame->surfaceMapWaterCUL!=NULL);
	
pSdlGame ->surfaceMapWaterCDR = IMG_Load("data/image/WaterCDR.png");
	if (pSdlGame->surfaceMapWaterCDR==NULL)	
		pSdlGame->surfaceMapWaterCDR = IMG_Load("../data/image/WaterCDR.png");
	assert( pSdlGame->surfaceMapWaterCDR!=NULL);
	
pSdlGame ->surfaceMapWaterCUR = IMG_Load("data/image/WaterCUR.png");
	if (pSdlGame->surfaceMapWaterCUR==NULL)	
		pSdlGame->surfaceMapWaterCUR = IMG_Load("../data/image/WaterCUR.png");
	assert( pSdlGame->surfaceMapWaterCUR!=NULL);
	
pSdlGame ->surfaceMapCDL = IMG_Load("data/image/wgrassEartthCDL.png");
	if (pSdlGame->surfaceMapCDL==NULL)	
		pSdlGame->surfaceMapCDL = IMG_Load("../data/image/wgrassEartthCDL.png");
	assert( pSdlGame->surfaceMapCDL!=NULL);
	
pSdlGame ->surfaceMapCDR = IMG_Load("data/image/wgrassEartthCDR.png");
	if (pSdlGame->surfaceMapCDR==NULL)	
		pSdlGame->surfaceMapCDR = IMG_Load("../data/image/wgrassEartthCDR.png");
	assert( pSdlGame->surfaceMapCDR!=NULL);
	
pSdlGame ->surfaceMapCUL = IMG_Load("data/image/wgrassEartthCUL.png");
	if (pSdlGame->surfaceMapCUL==NULL)	
		pSdlGame->surfaceMapCUL = IMG_Load("../data/image/wgrassEartthCUL.png");
	assert( pSdlGame->surfaceMapCUL!=NULL);
	
pSdlGame ->surfaceMapCUR = IMG_Load("data/image/wgrassEartthCUR.png");
	if (pSdlGame->surfaceMapCUR==NULL)	
		pSdlGame->surfaceMapCUR = IMG_Load("../data/image/wgrassEartthCUR.png");
	assert( pSdlGame->surfaceMapCUR!=NULL);
	
pSdlGame ->surfaceMapCastle = IMG_Load("data/image/castle.png");
	if (pSdlGame->surfaceMapCastle==NULL)	
		pSdlGame->surfaceMapCastle = IMG_Load("../data/image/castle.png");
	assert( pSdlGame->surfaceMapCastle!=NULL);
	
pSdlGame ->surfaceMapTree = IMG_Load("data/image/Tree.png");
	if (pSdlGame->surfaceMapTree==NULL)	
		pSdlGame->surfaceMapTree = IMG_Load("../data/image/Tree.png");
	assert( pSdlGame->surfaceMapTree!=NULL);


pSdlGame ->surfaceDial = IMG_Load("data/image/dialogue.png");
	if (pSdlGame->surfaceDial==NULL)	
		pSdlGame->surfaceDial = IMG_Load("../data/image/dialogue.png");
	assert( pSdlGame->surfaceDial!=NULL);
	
pSdlGame ->surfaceDialYes = IMG_Load("data/image/grass2.png");
	if (pSdlGame->surfaceDialYes==NULL)	
		pSdlGame->surfaceDialYes = IMG_Load("../data/image/grass2.png");
	assert( pSdlGame->surfaceDialYes!=NULL);

pSdlGame ->surfaceDialNo = IMG_Load("data/image/grass4.png");
	if (pSdlGame->surfaceDialNo==NULL)	
		pSdlGame->surfaceDialNo = IMG_Load("../data/image/grass4.png");
	assert( pSdlGame->surfaceDialNo!=NULL);	
	
pSdlGame ->surfaceKing = IMG_Load("data/image/king.png");
	if (pSdlGame->surfaceKing==NULL)	
		pSdlGame->surfaceKing = IMG_Load("../data/image/king.png");
	assert( pSdlGame->surfaceDial!=NULL);

/*Initialisation des sprites*/
	pSdlGame->pSprites.source = pSdlGame -> surfaceChar; /*incrementation du sprite global*/
	/*Cour vers la droite*/
	InitSprite (&(pSdlGame->pSprites),right, 52, 56, 31, 15);	
	/*Cour vers la gauche*/
	InitSprite (&(pSdlGame->pSprites),left, 52, 56, 31, 15);
	/*attaque epee droite*/
	InitSprite (&(pSdlGame->pSprites),attackR, 98, 56, 17, 0);
	/*attaque epee gauche*/
	InitSprite (&(pSdlGame->pSprites),attackL, 98, 56, 17, 0);
	/*attaque feu droite*/
	InitSprite (&(pSdlGame->pSprites),attackFR, 52, 56, 11, 0);
	/*attaque feu gauche*/
	InitSprite (&(pSdlGame->pSprites),attackFL, 52, 56, 11, 0);
	/*boule de feu droit*/
	InitSprite (&(pSdlGame->pSprites),fireBallR, 30, 56, 5, 0);
	/*boule de feu gauche*/
	InitSprite (&(pSdlGame->pSprites),fireBallL, 30, 56, 5, 0);
	/*Attend droite*/
	InitSprite (&(pSdlGame->pSprites),stayR, 52, 56, 7, 0);
	/*Attend gauche*/
	InitSprite (&(pSdlGame->pSprites),stayL, 52, 56, 7, 0);
	/*KO droit*/
	InitSprite (&(pSdlGame->pSprites),KOR, 52, 56, 5, 5);
	/*KO gauche*/
	InitSprite (&(pSdlGame->pSprites),KOL, 52, 56, 5, 0);
	/*fly droit*/
	InitSprite (&(pSdlGame->pSprites),flyR, 40, 56, 6, 0);
	/*fly gauche*/
	InitSprite (&(pSdlGame->pSprites),flyL, 40, 58, 6, 0);

	

	
	

	for(k=0; k<pSdlGame -> pGame.gEnemies.number; k++)
	{
		
		pSdlGame->pSpritesEnemy[k].source = pSdlGame->surfaceEnemies;
		
		/*Attend gauche*/
		InitSprite (&(pSdlGame->pSpritesEnemy[k]),0, 31, 52, 3, 0);
		/*Attend droite*/
		InitSprite (&(pSdlGame->pSpritesEnemy[k]),1, 31, 52, 3, 0);
		/*Cour vers la gauche*/
		InitSprite (&(pSdlGame->pSpritesEnemy[k]),2, 28, 52, 6, 0);
		/*Cour vers la droite*/
		InitSprite (&(pSdlGame->pSpritesEnemy[k]),3, 28, 52, 6, 0);
		
		/*Attaque gauche*/
		InitSprite (&(pSdlGame->pSpritesEnemy[k]),4, 61, 52, 8, 0);
		/*Attaque droite*/
		InitSprite (&(pSdlGame->pSpritesEnemy[k]),5, 61, 52, 8, 0);
	}
	
	pSdlGame->pSpritesWorldMap.source = pSdlGame -> surfaceCharMap;
		
	
	/*Cour vers le haut*/
	InitSprite (&(pSdlGame->pSpritesWorldMap),0, 17, 24, 3, 0);
	/*Cour vers la droite*/
	InitSprite (&(pSdlGame->pSpritesWorldMap),1, 17, 24, 3, 0);	
	/*Cour vers le bas*/
	InitSprite (&(pSdlGame->pSpritesWorldMap),2, 17, 24, 3, 0);
	/*Cour vers la gauche*/
	InitSprite (&(pSdlGame->pSpritesWorldMap),3, 17, 24, 3, 0);
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
	printf("POSITION_Sprite = %d\n", pSdlGame -> pSprites.position);
	Game *pGame = &(pSdlGame->pGame);
	Character *pChar= getGameChar(pGame);
	Character *pPnj= getGamePnj(pGame);
	Enemies *pEnemies = getGameEnemies(pGame);
	Map *pMap=getGameMap(pGame);
	SDL_Rect posiEnemy,posiChar, posiFireBall;
	/*Position posiEnemy;*/
if(pSdlGame -> choiceMenu == 1 && pSdlGame ->confirmMenu==1)	
{
	if(pGame -> level != 1)
	{
	/*Background*/
	SDL_BlitSurface(pSdlGame->surfaceBG, NULL, pSdlGame->surfaceScreen, NULL);

	
	posiChar.x = getPosiChar(pChar).x*TAILLE_SPRITE - pSdlGame->scrollX;
	posiChar.y = getPosiChar(pChar).y*TAILLE_SPRITE - pSdlGame->scrollY;

	displaySprite(&(pSdlGame->pSprites), posiChar, pSdlGame->surfaceScreen);
	
	posiFireBall.x = pSdlGame->pGame.gObjects.oObject[1].oPosi.x*TAILLE_SPRITE- pSdlGame->scrollX;
	posiFireBall.y = pSdlGame->pGame.gObjects.oObject[1].oPosi.y*TAILLE_SPRITE- pSdlGame->scrollY;
	
	displaySprite(&(pSdlGame->pSprites), posiFireBall, pSdlGame->surfaceScreen);
	
	for(k=0; k<pSdlGame -> pGame.gEnemies.number; k++)
	{
		posiEnemy.x = getPosiEnemy(pEnemies,k).x*TAILLE_SPRITE- pSdlGame->scrollX;
		posiEnemy.y = getPosiEnemy(pEnemies,k).y*TAILLE_SPRITE- pSdlGame->scrollY;
		displaySprite(&(pSdlGame->pSpritesEnemy[k]), posiEnemy, pSdlGame->surfaceScreen);
	}
	
	displayGauge(pSdlGame->surfaceLifeBG, pSdlGame->surfaceLife , pSdlGame->surfaceMana, pSdlGame->surfaceScreen, pSdlGame->pGame.gChar.life,pSdlGame->pGame.gChar.mana);
	
	
	SDL_Rect positionBall;
	
	SDL_Rect positionBall2;
	positionBall.x = pSdlGame->pGame.gObjects.oObject[2].oPosi.x*TAILLE_SPRITE- pSdlGame->scrollX;
	positionBall.y = pSdlGame->pGame.gObjects.oObject[2].oPosi.y*TAILLE_SPRITE- pSdlGame->scrollY;
	
	rotationObject(pSdlGame->surfaceBall, positionBall, &(pSdlGame->pGame.gObjects.oObject[2].angle), 0.01, pSdlGame->surfaceScreen);
	stabilizeObject(&(pSdlGame->pGame.gObjects.oObject[2]));
	
	positionBall2.x = pSdlGame->pGame.gObjects.oObject[3].oPosi.x*TAILLE_SPRITE- pSdlGame->scrollX;
	positionBall2.y = pSdlGame->pGame.gObjects.oObject[3].oPosi.y*TAILLE_SPRITE- pSdlGame->scrollY;
	
	rotationObject(pSdlGame->surfaceBall2, positionBall2, &(pSdlGame->pGame.gObjects.oObject[3].angle), 0.01, pSdlGame->surfaceScreen);
	stabilizeObject(&(pSdlGame->pGame.gObjects.oObject[3]));
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
				default:
					break;
			}
		} 
				
	}
}
else
{
		/*Background*/
	SDL_BlitSurface(pSdlGame->surfaceMapBG, NULL, pSdlGame->surfaceScreen, NULL);

	
	
		xmin = pSdlGame->scrollX/TAILLE_SPRITE;
		xmax = (pSdlGame->scrollX + SCREEN_WIDTH)/TAILLE_SPRITE+1;
		ymin = pSdlGame->scrollY/TAILLE_SPRITE;
		ymax = (pSdlGame->scrollY + SCREEN_HEIGHT)/TAILLE_SPRITE+1;
		for (i=xmin;i<xmax;++i)
		{
			for (j=ymin;j<ymax;++j)
			{
				switch (pSdlGame->pGame.gMap.tab[j][i])
				{
					case '#':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceBorder,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;
					
					case 'l':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapEarth1,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case '|':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapEarth2,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case '(':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapGEL,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case ')':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapGER,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;
					
					case '^':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapGEU,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case ',':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapGED,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case 'y':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapGEDL,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case 'x':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapGEDR,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case '<':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapGEUL,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case '>':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapGEUR,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;			
					
					case 'o':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapGrass1,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case '0':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapGrass2,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case 'C':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapEarth1,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;
					
					case 'w':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapWater,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case 'L':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapCUR,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;
					
					case ';':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapCUL,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;
					
					case ':':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapCDR,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;
					
					case '.':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapCDL,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;
					
					case 'g':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapWaterR,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case 'd':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapWaterD,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;
					
					case 'j':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapWaterCDR,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case 'u':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapWaterU,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case 'k':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapWaterCUR,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case 'v':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapWaterL,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case 'm':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapWaterCUL,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case 'n':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapWaterCDL,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
							
					case 'c':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapGrass1,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;
					
					case 'K':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapGrass1,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;
					
											
					
					
				}
			}
		}
		/*Position du Pnj*/
		SDL_Rect posiPnj;
		posiPnj.x = getPosiChar(pPnj).x*TAILLE_SPRITE - pSdlGame->scrollX;
		posiPnj.y = getPosiChar(pPnj).y*TAILLE_SPRITE - pSdlGame->scrollY;
		/*Blit objets*/
		for (i=xmin;i<xmax;++i)
		{
			for (j=ymin;j<ymax;++j)
			{
				switch (pSdlGame->pGame.gMap.tab[j][i])
				{	
					case 'c':
					positionTile.x=i*TAILLE_SPRITE - pSdlGame->scrollX;
					positionTile.y=j*TAILLE_SPRITE - pSdlGame->scrollY;
					SDL_BlitSurface(pSdlGame->surfaceMapCastle,NULL, pSdlGame->surfaceScreen, &positionTile);
					break;	
					
					case 'K':
					SDL_BlitSurface(pSdlGame->surfaceKing,NULL, pSdlGame->surfaceScreen, &posiPnj);
					break;
				}
			}
		}
				
	posiChar.x = getPosiChar(pChar).x*TAILLE_SPRITE - pSdlGame->scrollX;
	posiChar.y = getPosiChar(pChar).y*TAILLE_SPRITE - pSdlGame->scrollY;

	displaySprite(&(pSdlGame->pSpritesWorldMap), posiChar, pSdlGame->surfaceScreen);
	if(pSdlGame->dialogue == 2)
	{
		/*Position et blit du dialogue*/
		SDL_Rect positionDial;
		positionDial.x = 0;
		positionDial.y = SCREEN_HEIGHT - SCREEN_HEIGHT/2.5;
		SDL_BlitSurface(pSdlGame->surfaceDial, NULL, pSdlGame->surfaceScreen, &positionDial);
		
		SDL_Rect positionText1;
		positionText1.x = positionDial.x+20;
		positionText1.y = positionDial.y+50;
		SDL_BlitSurface(pSdlGame->surfaceText1, NULL, pSdlGame->surfaceScreen, &positionText1);
		SDL_Rect positionText2;
		positionText2.x = positionDial.x+20;
		positionText2.y = positionDial.y+80;
		SDL_BlitSurface(pSdlGame->surfaceText2, NULL, pSdlGame->surfaceScreen, &positionText2);
		SDL_Rect positionText3;
		positionText3.x = positionDial.x+20;
		positionText3.y = positionDial.y+110;
		SDL_BlitSurface(pSdlGame->surfaceText3, NULL, pSdlGame->surfaceScreen, &positionText3);
		
		/*Bouttons*/
		SDL_Rect positionDialYes;
		positionDialYes.x = (pSdlGame->surfaceDial->w-100)/4;
		positionDialYes.y = positionDial.y+(pSdlGame->surfaceDial->h - (pSdlGame->surfaceDial->h)/4);
		SDL_BlitSurface(pSdlGame->surfaceDialYes, NULL, pSdlGame->surfaceScreen, &positionDialYes);
		
		SDL_Rect positionDialNo;
		positionDialNo.x = (pSdlGame->surfaceDial->w-100) - (pSdlGame->surfaceDial->w-100)/4;
		positionDialNo.y = positionDial.y+(pSdlGame->surfaceDial->h - (pSdlGame->surfaceDial->h)/4);
		SDL_BlitSurface(pSdlGame->surfaceDialNo, NULL, pSdlGame->surfaceScreen, &positionDialNo);
	}
	}
}
else
{
	SDL_BlitSurface(pSdlGame->surfaceMenuBG,NULL, pSdlGame->surfaceScreen, NULL);
	
		SDL_Rect positionStart;
		positionStart.x = 0;
		positionStart.y = 0;
		SDL_BlitSurface(pSdlGame->surfaceStart,NULL, pSdlGame->surfaceScreen, &positionStart);
		
		SDL_Rect positionExit;
		positionExit.x = 0;
		positionExit.y = 200;
		SDL_BlitSurface(pSdlGame->surfaceExit,NULL, pSdlGame->surfaceScreen, &positionExit);
		
		
	
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
	
	
	pSdlGame->pGame.gPnj.cPosi.spriteSizeW = (float)(pSdlGame->pSprites.aSprite[pSdlGame->pSprites.position].height)/(float)TAILLE_SPRITE;
	pSdlGame->pGame.gPnj.cPosi.spriteSizeH = (float)(pSdlGame->pSprites.aSprite[pSdlGame->pSprites.position].height)/(float)TAILLE_SPRITE;

	
	for(k=0; k< pSdlGame->pGame.gEnemies.number; k++)
	{
		if (pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.floor == 1)	
		{
			pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.spriteSizeW = (float)(pSdlGame->pSpritesEnemy[k].aSprite[pSdlGame->pSpritesEnemy[k].position].width)/(float)TAILLE_SPRITE;
		}
		else
		{
			pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.spriteSizeW = 2;
		}
	//	printf("&&&&&&&&&&&&&&&&&&&&&&&&&&& TAILLE = %f\n", (float)(((pSdlGame->pSpritesEnemy[k].aSprite[pSdlGame->pSpritesEnemy[k].position].height)/(float)TAILLE_SPRITE)+0.5));
		pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.spriteSizeH = (float)(((pSdlGame->pSpritesEnemy[k].aSprite[pSdlGame->pSpritesEnemy[k].position].height)/(float)TAILLE_SPRITE));
	}
}


void keyManagment2(SdlGame *pSdlGame)
{
	if(pSdlGame->dialogue == 0)
	{
		if(pSdlGame->pKey.kLeft==1)
		{
			controlKey2(&(pSdlGame->pGame), 'g');
			animSprite (&(pSdlGame->pSpritesWorldMap), 3, 0, 0);
		}
		if(pSdlGame->pKey.kRight==1)
		{
			controlKey2(&(pSdlGame->pGame), 'd');
			animSprite (&(pSdlGame->pSpritesWorldMap), 1, 0, 0);
		}
		if (pSdlGame->pKey.kUp ==1)
		{
			controlKey2(&(pSdlGame->pGame), 'h');
			animSprite (&(pSdlGame->pSpritesWorldMap), 0, 0, 0);
		}
		if (pSdlGame->pKey.kDown ==1)
		{
			controlKey2(&(pSdlGame->pGame), 'b');
			animSprite (&(pSdlGame->pSpritesWorldMap), 2, 0, 0);
		}
	}
	else if (pSdlGame->dialogue == 2) 
	{
		if(pSdlGame->pKey.kLeft==1)
		{
			if (pSdlGame -> choiceDialogue == 2)
			{
				pSdlGame -> choiceDialogue = 1;
				
			}
		}
		if(pSdlGame->pKey.kRight==1)
		{
			if (pSdlGame -> choiceDialogue == 1)
			{
				pSdlGame -> choiceDialogue = 2;
				
			}
		}
		if(pSdlGame->pKey.kReturn == 1 && pSdlGame -> choiceDialogue == 1)
		{
			pSdlGame->dialogue = 1;
			pSdlGame->confirmDialogue = 1;
		}
		else if(pSdlGame->pKey.kReturn == 1 && pSdlGame -> choiceDialogue == 2)
		{
			pSdlGame->dialogue = 1;
			pSdlGame->confirmDialogue = 1;
		}
		if (pSdlGame -> choiceDialogue == 0 && (pSdlGame->pKey.kRight==1 || pSdlGame->pKey.kLeft==1))
		{
			pSdlGame -> choiceDialogue = 1;
		}
		
		
	}
	//printf ("CHOIX DIAL = %d, CONFIRMDIAL = %f , SPEECH = %f\n", pSdlGame -> choiceDialogue, pSdlGame->confirmDialogue, pSdlGame->choiceSpeech);
	
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

				if(pSdlGame->pGame.gChar.attack == 0 && pSdlGame->pGame.gChar.superAttack == 0 && pSdlGame->flyMode == 0)
				{
					animSprite (&(pSdlGame->pSprites), left, 0, pSdlGame->pGame.gChar.cPosi.direction);
				}
				controlKey(&(pSdlGame->pGame), 'g');
			}

			if(pSdlGame->pKey.kRight==1)
			{
				

				if(pSdlGame->pGame.gChar.attack == 0 && pSdlGame->pGame.gChar.superAttack == 0 && pSdlGame->flyMode == 0)
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

	 if(pSdlGame->flyMode == 0)
	 {
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
			
			if(tempA == 1)
			{
				if (pSdlGame->pSprites.direction == 0)
				{
					
					animSprite (&(pSdlGame->pSprites), fireBallR, 0, pSdlGame->pGame.gChar.cPosi.direction);
					
				}
				if (pSdlGame->pSprites.direction == 1)
				{
					
					animSprite (&(pSdlGame->pSprites), fireBallL, 0, pSdlGame->pGame.gChar.cPosi.direction);
					
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
	}
	if (pSdlGame->pKey.kCtrlL == 1)
	{
			pSdlGame->flyMode=1;
			controlKey(&(pSdlGame->pGame), 'o');
			if (pSdlGame->pGame.gChar.cPosi.direction == 0)
			{
				animSprite (&(pSdlGame->pSprites), flyR, 0, pSdlGame->pGame.gChar.cPosi.direction);
			}
			if (pSdlGame->pGame.gChar.cPosi.direction == 1)
			{
				animSprite (&(pSdlGame->pSprites), flyL, 0, pSdlGame->pGame.gChar.cPosi.direction);
			}
			
			
	}
	if (pSdlGame->pKey.kCtrlL == 0)
	{
			pSdlGame->flyMode=0;
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
	/*		printf("animstpite 4 = %d\n", pSdlGame->pSpritesEnemy[k].aSprite[4].end);
			printf("animstpite 5 = %d\n", pSdlGame->pSpritesEnemy[k].aSprite[5].end);
			printf("\n");
*/
		//	printf("attackState = %d  ===== EnemiNB = %d ___ direction = %d\n", pSdlGame ->pGame.gEnemies.eEnemy[k].stateAttack, k, pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction);
		/*	if (pSdlGame ->pGame.gEnemies.eEnemy[k].stateAttack == 1)
			{
				if (pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction == 1)
				{
					printf("GAUAUPIUHGDOUYIGSODIS\n");
					pSdlGame->pSpritesEnemy[k].aSprite[4].end = 0;
				}
				if (pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction == 0)
				{
					printf("AAUAUPIUHGDOUYIGSODIS\n");
					pSdlGame->pSpritesEnemy[k].aSprite[5].end = 0;
				}
			}*/
			
		
			
			if (pSdlGame->pSpritesEnemy[k].aSprite[4].end == 1 && pSdlGame->pSpritesEnemy[k].aSprite[5].end == 1 
			&& fabs (pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.x - pSdlGame->pGame.gChar.cPosi.x) > 3)
			{
				
				pSdlGame ->pGame.gEnemies.eEnemy[k].stateAttack = 1;
				pSdlGame ->pGame.gEnemies.eEnemy[k].eChar.attack = 0;
	
	
			}
			
		//	printf("end(4) = %d_____end(5)= %d\n", pSdlGame->pSpritesEnemy[k].aSprite[4].end, pSdlGame->pSpritesEnemy[k].aSprite[5].end);
		//	printf("Enemie = %d, attack = %d\n",k,pSdlGame->pGame.gEnemies.eEnemy[k].eChar.attack );
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
			
//pSdlGame ->pGame.gEnemies.eEnemy[k].eChar.cPosi.x - pSdlGame ->pGame.gChar.cPosi.x)< 0
			if(pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.x < pSdlGame->pGame.gChar.cPosi.x && pSdlGame->pSpritesEnemy[k].direction == 1)
			{
				pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction = 0;
				pSdlGame->pSpritesEnemy[k].aSprite[4].end =1;
				pSdlGame->pSpritesEnemy[k].aSprite[5].end =1;
			}
			if (pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.x > pSdlGame->pGame.gChar.cPosi.x && pSdlGame->pSpritesEnemy[k].direction == 1)
			{
				pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction = 1;
				pSdlGame->pSpritesEnemy[k].aSprite[4].end =1;
				pSdlGame->pSpritesEnemy[k].aSprite[5].end =1;
			}
			
			if ((pSdlGame->pGame.gEnemies.eEnemy[k].stateAttack == 0 && pSdlGame ->pGame.gEnemies.eEnemy[k].eChar.attack == 1 
			&& (pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction == 0))
			|| pSdlGame->pSpritesEnemy[k].aSprite[5].end == 0)
			{
				pSdlGame->pSpritesEnemy[k].aSprite[5].end = 0;
				animSprite (&(pSdlGame->pSpritesEnemy[k]), 5, 1, 0);
			}
			if ((pSdlGame->pGame.gEnemies.eEnemy[k].stateAttack == 0  && pSdlGame ->pGame.gEnemies.eEnemy[k].eChar.attack == 1 
			&& (pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.direction == 1))
			|| pSdlGame->pSpritesEnemy[k].aSprite[4].end == 0)
			{
				pSdlGame->pSpritesEnemy[k].aSprite[4].end = 0;
				animSprite (&(pSdlGame->pSpritesEnemy[k]), 4, 1, 1);
			}
			
				
			
			}
			
}
void dialogueAction(SdlGame *pSdlGame, int loop)
{
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
		if (strcmp(discutionDialogue(&(pSdlGame->pTree), pSdlGame->choiceSpeech), "&exit&")==1)
		{
			exit(1);
			loop=0;
		}
		if(strcmp(discutionDialogue(&(pSdlGame->pTree), pSdlGame->choiceSpeech), "&ok&")==0)
		{
				pSdlGame->dialogue = 0;
		}
}

void dialogueSpeak(SdlGame *pSdlGame, float choice)
{

	SDL_Color color = {0, 0, 0};
	char dialTab[300];
	int k=0;
	while(discutionDialogue(&(pSdlGame->pTree), choice)[k]!='\0')
	{
		dialTab[k]=discutionDialogue(&(pSdlGame->pTree), choice)[k];
		k++;
	}
	dialTab[k] = '\0';
	printf("%s\n",dialTab);
	printf("%d\n",k);
	//printf("%s",discutionDialogue(&(pSdlGame->pTree), 0.0));

	int i=0;
	int j=0;
	int l=0;
	int p=0;
	int q=0;
	int r=0;
	int s=0;
	while (dialTab[p]!='\0')
	{
		if (k<79)
		{
			char dialTab1[k];
			if(i<=k)
			{
					dialTab1[i] = dialTab[i];
					i++;
				
			}
			if(i==k)
			{
				dialTab1[i]='\0';
				printf("Dial1 = %s\n", dialTab1);
				pSdlGame->surfaceText1 = TTF_RenderText_Blended(pSdlGame->font,dialTab1, color);
				pSdlGame->surfaceText2 = TTF_RenderText_Blended(pSdlGame->font,"", color);
				pSdlGame->surfaceText3 = TTF_RenderText_Blended(pSdlGame->font,"", color);
			}
		}
		else if (k<156)
		{
			char dialTab1[79];
			char dialTab2[k-79];
			if(j<=78)
			{
					dialTab1[j] = dialTab[j];
					j++;
			}
			if(j==79)
			{
				dialTab1[j]='\0';
				pSdlGame->surfaceText1 = TTF_RenderText_Blended(pSdlGame->font,dialTab1, color);
			}
			if(j>78 && j<=k)
			{
					dialTab2[q] = dialTab[j];
					q++;
			}
			if(j==k+1)
			{
				dialTab2[q]='\0';
				pSdlGame->surfaceText2 = TTF_RenderText_Blended(pSdlGame->font,dialTab2, color);
				pSdlGame->surfaceText3 = TTF_RenderText_Blended(pSdlGame->font,"", color);
			}
		}
		else if (k<235)
		{
			char dialTab1[79];
			char dialTab2[79];
			char dialTab3[k-155];
			if(l<=78)
			{
					dialTab1[l] = dialTab[l];
					l++;

			}
			if(l==79)
			{
				dialTab1[l]='\0';
				printf("ICI 1\n");
				pSdlGame->surfaceText1 = TTF_RenderText_Blended(pSdlGame->font,dialTab1, color);
			}
			if(l>78 && l<=156)
			{
					dialTab2[r] = dialTab[l];
					l++;
					r++;
					
			}
			if(l==157)
			{
				dialTab2[r]='\0';
				printf("ICI 2\n");
				pSdlGame->surfaceText2 = TTF_RenderText_Blended(pSdlGame->font,dialTab2, color);
			}
			
			if(l>156 && l<=k)
			{
					dialTab3[s] = dialTab[l];
					l++;
					s++;
				
			}
			if (l==k+1)
			{
				dialTab3[s]='\0';
				printf("ICI 3\n");
				pSdlGame->surfaceText3 = TTF_RenderText_Blended(pSdlGame->font,dialTab3, color);
			}
		}
		p++;
	}

	
}
void loopSDL(SdlGame *pSdlGame)
{


	int k,l, m;
	SDL_Event event;
	SDL_Event eventMenu;
	int continueLoop=1;
	int refresh=1;
	int temp;
	int temp2;
	Game *pGame = &(pSdlGame->pGame);
	Character *pChar= getGameChar(pGame);
	Character *pPnj= getGamePnj(pGame);
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
	pSdlGame->pKey.kReturn = 0;
	
	bgBW(pSdlGame->surfaceBG, 1); /*gestion de la saturation de l'arrière plan*/

	audioBG();
	audioWind();

while(continueLoop == 1)
{	
	if (pSdlGame->dialogue == 1)
	{
		dialogueAction(pSdlGame,continueLoop);	
	}
	//printf("LOOP \n");
	
	if (pSdlGame ->confirmMenu !=1)
	{
	while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_UP:
							if (pSdlGame -> choiceMenu == 2)
							{
								pSdlGame -> choiceMenu =1;
								
							}
							break;
						case SDLK_DOWN:
							if (pSdlGame -> choiceMenu == 1)
							{
								pSdlGame -> choiceMenu = 2;
								
							}
							break;	
						case SDLK_RETURN:
							pSdlGame ->confirmMenu = 1;
							
							break;
							
						case SDLK_ESCAPE:
							continueLoop = 0;
							break;
						default:
						break;
					}
			}
			
		}
	}
	//printf("choice = %d, confirm = %d\n",pSdlGame -> choiceMenu , pSdlGame ->confirmMenu);
	if(pSdlGame -> choiceMenu == 2 && pSdlGame ->confirmMenu==1)
	{
			continueLoop =0;
	}
	if(pSdlGame -> choiceMenu == 1 && pSdlGame ->confirmMenu==1)
	{
	//printf("GAME \n");
	refresh = 0;
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
							if (pSdlGame -> pGame.gChar.mana >= consumedMana)
							{
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
							}
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
						case SDLK_RETURN:
							pSdlGame->pKey.kReturn = 1;
							
							break;
						case SDLK_ESCAPE:
							pSdlGame ->confirmMenu=0;
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
						case SDLK_RETURN:
							pSdlGame->pKey.kReturn = 0;
							pSdlGame->confirmDialogue =0;
							break;
						case SDLK_ESCAPE:

							pSdlGame ->confirmMenu =0;
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

			/*collisionEnemies(&(pSdlGame->pGame.gChar),&(pSdlGame->pGame.gEnemies));*/
			applySpeedObject(&(pSdlGame->pGame.gObjects.oObject[1]));
			superAttackDmg(&(pSdlGame -> pGame));
	/*		printf("OBJET .X : %f\n",pSdlGame->pGame.gObjects.oObject[1].oPosi.x);*/
			
		
			
			


	 		attack(&(pSdlGame -> pGame));
	 		
	 		detect(&(pSdlGame->pGame));
	 		
				
			
			animEnemies(pSdlGame);
			colisionSprite(pSdlGame);
			
			collisionObjects (&(pChar->cPosi), &(pGame -> gObjects));
			
			collisionObjects (&(pGame -> gObjects.oObject[2].oPosi), &(pGame -> gObjects));
			
			collisionMap (&(pChar->cPosi), pMap);
			enemyAttack(&(pSdlGame -> pGame));
			//printf("DIRECTION HERO = %d, V_Xhero = %d _____ ATTACK = %d\n",pSdlGame->pGame.gChar.cPosi.direction,pSdlGame->pGame.gChar.cPosi.v_x, pSdlGame->pGame.gChar.attack);
			/*collision (&(pSdlGame->pGame.gEnemies.eEnemy[1].eChar), &(pSdlGame->pGame.gMap));*/
			gravity (&(pSdlGame->pGame.gChar.cPosi));
			collisionMap (&(pSdlGame->pGame.gObjects.oObject[2].oPosi), pMap);
						collisionMap (&(pSdlGame->pGame.gObjects.oObject[3].oPosi), pMap);
			gravity (&(pSdlGame->pGame.gObjects.oObject[2].oPosi));
			gravity (&(pSdlGame->pGame.gObjects.oObject[3].oPosi));
			
			//printf("v_y = %f\n", pSdlGame->pGame.gObjects.oObject[2].oPosi.v_y);

			for(k=0; k< pSdlGame->pGame.gEnemies.number; k++)
			{
				if(pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.x >0 && pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi.y >0)
				{
				
					collisionMap (&(pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi), pMap);
					gravity (&(pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi));
					refreshDirection(&(pSdlGame->pGame.gEnemies.eEnemy[k].eChar.cPosi));
				}
			}
			
			refreshDirection(&(pSdlGame->pGame.gChar.cPosi));
			
			
			warpMap(pGame);	
			if (pGame -> level != 1 && pGame -> level != 42)
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
						printf("x : %f  y : %f \n",pSdlGame->pGame.gChar.cPosi.x,pSdlGame->pGame.gChar.cPosi.y);
		
		}
		else
		{
		
			
			if (pSdlGame->scrollX<0)
				pSdlGame->scrollX=0;
			if (pSdlGame->scrollX+SCREEN_WIDTH>TAILLE_SPRITE*pMap->dimx-1)
				pSdlGame->scrollX=TAILLE_SPRITE*pMap->dimx-SCREEN_WIDTH;
				
			if (pSdlGame->scrollY<0)
				pSdlGame->scrollY=0;
			if (pSdlGame->scrollY+SCREEN_HEIGHT>TAILLE_SPRITE*pMap->dimy-1)
				pSdlGame->scrollY=TAILLE_SPRITE*pMap->dimy-SCREEN_HEIGHT;
		
			keyManagment2(pSdlGame);
			pSdlGame->pGame.gChar.cPosi.spriteSizeW = 1.2;
			pSdlGame->pGame.gChar.cPosi.spriteSizeH = 1.2;
			collisionMap (&(pChar->cPosi), pMap);
			warpMap(pGame);
			temp = (int)(getPosiChar(pChar).x*TAILLE_SPRITE-pSdlGame->scrollX);
			temp2 = (int)(getPosiChar(pChar).y*TAILLE_SPRITE-pSdlGame->scrollY);
			
			if(((temp > SCREEN_WIDTH*3/4  && pChar->cPosi.v_x >0) || (temp < SCREEN_WIDTH*1/4 && pChar->cPosi.v_x <0)) && temp >0 && temp<SCREEN_WIDTH)
				pSdlGame->scrollX+=pChar->cPosi.v_x*TAILLE_SPRITE;
				
			if (temp <0)
				pSdlGame->scrollX=0;
			
			
			if(((temp2 > SCREEN_HEIGHT*3/4  && pChar->cPosi.v_y >0) || (temp2 < SCREEN_HEIGHT*1/4 && pChar->cPosi.v_y <0) )&& temp2 >0 && temp2<SCREEN_HEIGHT)
				pSdlGame->scrollY+=pChar->cPosi.v_y*TAILLE_SPRITE;
		
			if(pSdlGame->dialogue == 1 && pSdlGame->confirmDialogue == 1)
			{
				dialogueSpeak(pSdlGame, searchElement(pSdlGame->choiceSpeech, pSdlGame ->pTree, pSdlGame -> choiceDialogue, pSdlGame->confirmDialogue));
				pSdlGame->choiceSpeech = searchElement(pSdlGame->choiceSpeech, pSdlGame ->pTree, pSdlGame -> choiceDialogue, pSdlGame->confirmDialogue );
				pSdlGame->dialogue = 2;
				pSdlGame->confirmDialogue =0;
				pSdlGame->choiceDialogue = 0;
			}
			else if (pSdlGame->choiceSpeech == 2.0 && pSdlGame->dialogue == 1)
			{
				
				dialogueSpeak(pSdlGame,pSdlGame->choiceSpeech);
				pSdlGame->dialogue = 2;
				pSdlGame->confirmDialogue = 0;
			}
printf("DIALOGUE = %d\n",pSdlGame->dialogue);
			
			
			if(collision(&(pChar->cPosi), &(pPnj->cPosi))==1 && pSdlGame->dialogue != 2)
			{
					pSdlGame->dialogue = 1;

			}
		}
		if (refresh==1)
		{
			
		    /* on affiche le Game sur le buffer caché */
		    sdlDisplay(pSdlGame);
	//printf("DISPLAY \n");
		    /* on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle) */
		    SDL_Flip( pSdlGame->surfaceScreen);
		} 
				
	}
		
		
	}
				
		
		    /* on affiche le Game sur le buffer caché */
		    sdlDisplay(pSdlGame);
	//printf("DISPLAY \n");
		    /* on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle) */
		    SDL_Flip( pSdlGame->surfaceScreen);
		   
	
		
	}
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

