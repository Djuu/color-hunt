#include <stdio.h>
#include <stdlib.h>

#include "Animation.h"

void animSpInit(SDL_Rect spAnim, int spDimX, int spDimY,int spDimL, int spDimH)
{
	spAnim.x=spDimX;
	spAnim.y=spDimY;
	spAnim.w=spDimL;
	spAnim.h=spDimH;
}

