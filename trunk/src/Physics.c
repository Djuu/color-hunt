#include "Physics.h"
#include <math.h>
void gravity (Character *pChar)
{
	
	pChar->cPosi.v_y += pChar->cPosi.v_grav;

}


float path (Character *pChar, Map *pMap)
{
	char *tab;
	float i;
	int j=1;
	tab=(char*)calloc(1,sizeof(char));
	Position *current;
	current=(Position*)malloc(sizeof(Position));
	
	float posX, posY, posYd, posXd, posYr, posXr, posYl, posXl;
	setPosi (current, pChar->cPosi.x, pChar->cPosi.y,0);
	/*tab[0]=getMapXY(pMap, getPosiXint(current), getPosiYint(current));*/
	
	for (i=0.01; i<=1; i+=0.01) 
	{
		posX = pChar->cPosi.x + i*pChar->cPosi.v_x;
		posY = pChar->cPosi.y + i*pChar->cPosi.v_y;
		
		posYd = pChar->cPosi.y + i*pChar->cPosi.v_y+1;
		posXd = pChar->cPosi.x + i*pChar->cPosi.v_x+1;
		
		posYr = pChar->cPosi.y + i*pChar->cPosi.v_y;
		posXr = pChar->cPosi.x + i*pChar->cPosi.v_x+1;
		
		posYl = pChar->cPosi.y + i*pChar->cPosi.v_y+1;
		posXl = pChar->cPosi.x + i*pChar->cPosi.v_x;
		
			/*tab=realloc(tab,(j+1)*sizeof(char));	
			tab[j]=getMapXY(pMap, (int)posX, (int)posY);*/
			if(getMapXY(pMap, (int)posX, (int)posY)=='#' || getMapXY(pMap, (int)posXd, (int)posYd)=='#' 
			|| getMapXY(pMap, (int)posXr, (int)posYr)=='#' || getMapXY(pMap, (int)posXl, (int)posYl)=='#') 
			{
				
				return i-0.01;
				

			}
			setPosi (current, posX, posY,0);
			
		
		
	} 
	return 1;
}

void collision (Character *pChar, Map *pMap)
{

	pChar->cPosi.y+=path (pChar, pMap)*pChar->cPosi.v_y;
	pChar->cPosi.x+=path (pChar, pMap)*pChar->cPosi.v_x;
	if(getMapXY(pMap, (int)pChar->cPosi.y+1, (int)pChar->cPosi.x )=='#')
	{
		pChar->cPosi.v_y = 0;
		printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	}
	printf("%f ", pChar->cPosi.v_y);
		
		 
	
}
