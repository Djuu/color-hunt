#include "Physics.h"
#include <math.h>
void gravity (Character *pChar)
{
	
	pChar->cPosi.v_y += pChar->cPosi.v_grav;
	

}


float path (Character *pChar, Map *pMap)
{
	float i;
	Position *current;
	current=(Position*)malloc(sizeof(Position));
	
	float posX, posY, posYd, posXd, posYr, posXr, posYl, posXl;
	setPosi (current, pChar->cPosi.x, pChar->cPosi.y,0);

	
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
		

			if (getMapXY(pMap, (int)(posX-0.5), (int)posY)=='#' || getMapXY(pMap, (int)(posXl-0.5), (int)posYl)=='#')
			{
				pChar -> air = 1;
			}
			else if (getMapXY(pMap, (int)(posXd+0.5), (int)posYd)=='#' || getMapXY(pMap, (int)(posXr+0.5), (int)posYr)=='#')
			{
				pChar -> air = 2;
			}
			else 
			{
				pChar -> air = 0;
			}
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
	
	pChar->cPosi.v_y*=path (pChar, pMap);
	pChar->cPosi.v_x*=path (pChar, pMap);
	
	pChar->cPosi.y+=pChar->cPosi.v_y;
	pChar->cPosi.x+=pChar->cPosi.v_x;
	
	if (getMapXY(pMap, (int)(pChar->cPosi.x), (int)(pChar->cPosi.y+1.5))=='#' || 
	    getMapXY(pMap, (int)(pChar->cPosi.x+1), (int)(pChar->cPosi.y+1.5))=='#')
	{
		pChar->floor = 1;
	} 
	else
	{
		pChar->floor = 0;
		
	}
	

	
}
