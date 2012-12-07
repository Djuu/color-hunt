#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <assert.h>

#include "SDLGame.h"

int main(int argc, char *argv[])
{


	SdlGame pSdlGame;	
	initSDL(&pSdlGame);
	loopSDL(&pSdlGame);
	/*freeSdl(&pSdlGame);*/
	return 0;
}
