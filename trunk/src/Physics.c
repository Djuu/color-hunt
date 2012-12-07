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
float pathMap (Character *pChar, Map *pMap)
{
	float i;
	float k, l;
	float posX, posY, posYd, posXd, posYr, posXr, posYl, posXl;

	

	
	for (i=0.01; i<=1; i+=0.01) 
	{
		for (k=0; k<pChar->cPosi.spriteSizeH; k+=0.5)
		{
			for (l=0; l<pChar->cPosi.spriteSizeW; l+=0.9)
			{
			
				Position charPosition;
				charPosition = getPosiChar(pChar);
				posX = charPosition.x + i*charPosition.v_x;
				posY = charPosition.y + i*charPosition.v_y;

				posYd = charPosition.y + i*charPosition.v_y+k;
				posXd = charPosition.x + i*charPosition.v_x+l;

				posYr = charPosition.y + i*charPosition.v_y;
				posXr = charPosition.x + i*charPosition.v_x+l;

				posYl = charPosition.y + i*charPosition.v_y+k;
				posXl = charPosition.x + i*charPosition.v_x;
			

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

			}
		}
		
	} 
	return 1;
}




/*
Description : fonction interne qui identifie les cases que le personnage parcoure et renvoi une valeur en fonction de la distance qui seppare le personnage de l'ennemie
Retourne : reel
*/
int collision(Position *pPosi1, Position *pPosi2)
{

	float i;
	float posX, posY;
	float posXe, posYe;
	float sP1H = pPosi1->spriteSizeH;
	float sP1W = pPosi1->spriteSizeW;
	float sP2H = pPosi2->spriteSizeH;
	float sP2W = pPosi2->spriteSizeW;
	
	
		for (i=0.01; i<=1.0; i+=0.01) 
		{
			while(sP1H>0 && sP1W>0 && sP2H>0 && sP2W>0)
			{
					posX = pPosi1 -> x + i*pPosi1 -> v_x;
					posY = pPosi1 -> y + i*pPosi1 -> v_y;
			
					posXe = pPosi2 -> x + i*pPosi2 -> v_x;
					posYe = pPosi2 -> y + i*pPosi2 -> v_y;


					sP1H-=0.01;
					sP1W-=0.01;
					sP2H-=0.01;
					sP2W-=0.01;


					 if ((posX > posXe && posX<posXe+sP2W+1) && (posY+sP1H>posYe && posY<posYe+sP2H))
					 {
						return 1; /*si pPosi1 vient par la gauche*/
					
					}
					if((posXe > posX && posXe < posX+sP1W+1) &&(posY+sP1H>posYe && posY<posYe+sP2H))
					 {
						return 2; /*si pPosi1 vient par la droite*/
							
					 }
					  
					
					 
					 
				 }
	
		
		}
		return 0;
}


