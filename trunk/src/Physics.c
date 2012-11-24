#include "Physics.h"
#include <math.h>
void gravity (Character *pChar)
{
	
	pChar->cPosi.v_y += pChar->cPosi.v_grav;
	

}


/*
Description : fonction interne qui identifie les cases que le personnage parcoure et renvoi une faleur en fonction de la distance qui seppare le personnage de "la case de collision" 
Retourne : reel
*/
float pathMap (Position *pPosi, Map *pMap)
{
	float i;
	float posX, posY, posYd, posXd, posYr, posXr, posYl, posXl;
	Position *current;
	current=(Position*)malloc(sizeof(Position));

	setPosi (current, pPosi -> x, pPosi -> y,0);

	
	for (i=0.01; i<=1; i+=0.01) 
	{
		
		posX = pPosi -> x + i*pPosi -> v_x;
		posY = pPosi -> y + i*pPosi -> v_y;

		posYd = pPosi -> y + i*pPosi -> v_y+1;
		posXd = pPosi -> x + i*pPosi -> v_x+1;

		posYr = pPosi -> y + i*pPosi -> v_y;
		posXr = pPosi -> x + i*pPosi -> v_x+1;

		posYl = pPosi -> y + i*pPosi -> v_y+1;
		posXl = pPosi -> x + i*pPosi -> v_x;
	

		if (getMapXY(pMap, (int)(posX-0.5), (int)posY)=='#' || getMapXY(pMap, (int)(posXl-0.5), (int)posYl)=='#')
		{
			pPosi -> air = 1;
		}
		else if (getMapXY(pMap, (int)(posXd+0.5), (int)posYd)=='#' || getMapXY(pMap, (int)(posXr+0.5), (int)posYr)=='#')
		{
			pPosi -> air = 2;
		}
		else 
		{
			pPosi -> air = 0;
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




/*
Description : fonction interne qui identifie les cases que le personnage parcoure et renvoi une valeur en fonction de la distance qui seppare le personnage de l'ennemie
Retourne : reel
*/
float path(Position *pPosi1, Position *pPosi2)
{

	float i;
	float posX, posY, posYd, posXd, posYr, posXr, posYl, posXl;
	float posXe, posYe, posYde, posXde, posYre, posXre, posYle, posXle;
	Position *current;
	current=(Position*)malloc(sizeof(Position));
	
	setPosi (current, pPosi1 -> x, pPosi1 -> y,0);
	
		for (i=0.01; i<=1; i+=0.01) 
		{

			posX = pPosi1 -> x + i*pPosi1 -> v_x;
			posY = pPosi1 -> y + i*pPosi1 -> v_y;

			posYd = pPosi1 -> y + i*pPosi1 -> v_y+1;
			posXd = pPosi1 -> x + i*pPosi1 -> v_x+1;

			posYr = pPosi1 -> y + i*pPosi1 -> v_y;
			posXr = pPosi1 -> x + i*pPosi1 -> v_x+1;

			posYl = pPosi1 -> y + i*pPosi1 -> v_y+1;
			posXl = pPosi1 -> x + i*pPosi1 -> v_x;
		
		
	
			
			posXe = pPosi2 -> x + i*pPosi2 -> v_x;
			posYe = pPosi2 -> y + i*pPosi2 -> v_y;

			posYde = pPosi2 -> y + i*pPosi2 -> v_y+1; 
			posXde = pPosi2 -> x + i*pPosi2 -> v_x+1;

			posYre = pPosi2 -> y + i*pPosi2 -> v_y;
			posXre = pPosi2 -> x + i*pPosi2 -> v_x+1;

			posYle = pPosi2 -> y + i*pPosi2 -> v_y+1;
			posXle = pPosi2 -> x + i*pPosi2 -> v_x;


			 if((posXe < posXr+0.1 && posX-0.1 < posXre) && (posY<posYde && posYe<posYl))
			 {
			 
			 	return i-0.01;
			 		
			 }
		
		}
		return 1;
}


