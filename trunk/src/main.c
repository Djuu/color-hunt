#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "sdlJeu.h"


int main(int argc, char *argv[])
{

	Jeu pJeu;
	sdlJeu pSdlJeu;

	/*pMap = NULL;*/
	/*mapInit(&pMap);*/
	/*mapAffiche(&pMap);*/
	 
	
	
	sdlInitialisation(&pSdlJeu);
	sdlBoucle(&pSdlJeu);

	return 0;
}
