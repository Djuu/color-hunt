#include <math.h>

#include "Physics.h"

void gravity (Position *pPosi)
{
	
	pPosi->v_y += pPosi->v_grav;
	

}


/*
Description : fonction interne qui identifie les cases que le personnage parcoure et renvoi une faleur en fonction de la distance qui seppare le personnage de "la case de collision" 
Retourne : reel
*/
float pathMap (Position *pPosi, Map *pMap)
{
	float i;
	float k, l;
	float posX, posY, posYd, posXd, posYr, posXr, posYl, posXl;

	

	
	for (i=0.01; i<=1; i+=0.01) 
	{
		for (k=0; k<pPosi->spriteSizeH; k+=0.5)
		{
			for (l=0; l<pPosi->spriteSizeW; l+=0.9)
			{
			
				posX = pPosi->x + i*pPosi->v_x;
				posY = pPosi->y + i*pPosi->v_y;

				posYd = pPosi->y + i*pPosi->v_y+k;
				posXd = pPosi->x + i*pPosi->v_x+l;

				posYr = pPosi->y + i*pPosi->v_y;
				posXr = pPosi->x + i*pPosi->v_x+l;

				posYl = pPosi->y + i*pPosi->v_y+k;
				posXl = pPosi->x + i*pPosi->v_x;
			

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

			}
		}
		
	} 
	return 1;
}


int path(Position *pPosi1, Position *pPosi2)
{
	float i;
	float k, l, m ;
	float posX, posY, posYd, posXd, posYr, posXr, posYl, posXl;
	float oPosX, oPosY, oPosYd, oPosXd, oPosYr, oPosXr, oPosYl, oPosXl;
	
		for (i=0.001; i<=1.0; i+=0.001) 
		{

				
					
				posX = pPosi1->x + i*pPosi1->v_x;
				posY = pPosi1->y + i*pPosi1->v_y;

				posYd = pPosi1->y + i*pPosi1->v_y+pPosi1->spriteSizeH;
				posXd = pPosi1->x + i*pPosi1->v_x+pPosi1->spriteSizeW;

				posYr = pPosi1->y + i*pPosi1->v_y;
				posXr = pPosi1->x + i*pPosi1->v_x+pPosi1->spriteSizeH;

				posYl = pPosi1->y + i*pPosi1->v_y+pPosi1->spriteSizeH;
				posXl = pPosi1->x + i*pPosi1->v_x;
						
						
						
						
				oPosX = pPosi2->x + i*pPosi2->v_x;
				oPosY = pPosi2->y + i*pPosi2->v_y;

				oPosYd = pPosi2->y + i*pPosi2->v_y+pPosi2->spriteSizeH;
				oPosXd = pPosi2->x + i*pPosi2->v_x+pPosi2->spriteSizeW;

				oPosYr = pPosi2->y + i*pPosi2->v_y;
				oPosXr = pPosi2->x + i*pPosi2->v_x+pPosi2->spriteSizeW;

				oPosYl = pPosi2->y + i*pPosi2->v_y+pPosi2->spriteSizeH;
				oPosXl = pPosi2->x + i*pPosi2->v_x;
				
				
				if((oPosX < posXr && posX < oPosXr) && (posY<oPosYd && oPosY<posYd))
				{
				
					return i-0.001;

				}

		} 
	
	return 1;
}


/*
Description : fonction interne qui identifie les cases que le personnage parcoure et renvoi une valeur en fonction de la distance qui seppare le personnage de l'ennemie
Retourne : reel

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
		
					posX = pPosi1 -> x + i*pPosi1 -> v_x;
					posY = pPosi1 -> y + i*pPosi1 -> v_y;
			
					posXe = pPosi2 -> x + i*pPosi2 -> v_x;
					posYe = pPosi2 -> y + i*pPosi2 -> v_y;




					 if ((posX > posXe && posX<posXe+pPosi2->spriteSizeW+1) && (posY+pPosi1->spriteSizeH>posYe && posY<posYe+pPosi2->spriteSizeH))
					 {
						return 1; //si pPosi1 vient par la gauche
					
					}
					if((posXe > posX && posXe < posX+pPosi1->spriteSizeW) &&(posY+pPosi1->spriteSizeH>posYe && posY<posYe+pPosi2->spriteSizeH))
					 {
						return 2; //si pPosi1 vient par la droite
							
					 }
					  
					
					 
					 
				 
	
		
		}
		return 0;
}*/


void stabilizeObject(Object *pObject)
{
	double teta =(pObject->oPosi.v_grav*12.5)*M_PI/180.0;
	double alpha = pObject->angle*M_PI/180.0;
	if (pObject->oPosi.floor == 1)
	{
			if (pObject->angle > 0 && pObject->angle < 90)
			{
				if(pObject->angle < 45)
				{
					pObject->angle -=pObject->oPosi.v_grav*12.5;
					pObject->oPosi.y +=  (pObject->oPosi.spriteSizeW/2.0)*(-cos(alpha -teta) + cos(alpha)) + (pObject->oPosi.spriteSizeH/2.0)*(sin(alpha-teta) - sin(alpha));
					pObject->oPosi.x +=  (pObject->oPosi.spriteSizeW/2.0)*(-sin(alpha -teta) + sin(alpha)) + (pObject->oPosi.spriteSizeH/2.0)*(-cos(alpha-teta) + cos(alpha));
					
					
				}
				else if (pObject->angle > 45)
				{
					pObject->angle +=pObject->oPosi.v_grav*12.5;
					pObject->oPosi.x +=  (pObject->oPosi.spriteSizeW/2.0)*(-cos(alpha -teta) + cos(alpha)) + (pObject->oPosi.spriteSizeH/2.0)*(sin(alpha-teta) - sin(alpha));
					pObject->oPosi.y +=  (pObject->oPosi.spriteSizeW/2.0)*(-sin(alpha -teta) + sin(alpha)) + (pObject->oPosi.spriteSizeH/2.0)*(-cos(alpha-teta) + cos(alpha));
					
				}
		
			}
			else if (pObject->angle > 90 && pObject->angle < 180)
			{
				if(pObject->angle < 135)
				{
					pObject->angle -=pObject->oPosi.v_grav*12.5;
					pObject->oPosi.y +=  (pObject->oPosi.spriteSizeW/2.0)*(-cos(alpha -teta) + cos(alpha)) + (pObject->oPosi.spriteSizeH/2.0)*(sin(alpha-teta) - sin(alpha));
					pObject->oPosi.x +=  (pObject->oPosi.spriteSizeW/2.0)*(-sin(alpha -teta) + sin(alpha)) + (pObject->oPosi.spriteSizeH/2.0)*(-cos(alpha-teta) + cos(alpha));
									
				}
				else if (pObject->angle > 135)
				{
					pObject->angle +=pObject->oPosi.v_grav*12.5;
					pObject->oPosi.x +=  (pObject->oPosi.spriteSizeW/2.0)*(-cos(alpha -teta) + cos(alpha)) + (pObject->oPosi.spriteSizeH/2.0)*(sin(alpha-teta) - sin(alpha));
					pObject->oPosi.y +=  (pObject->oPosi.spriteSizeW/2.0)*(-sin(alpha -teta) + sin(alpha)) + (pObject->oPosi.spriteSizeH/2.0)*(-cos(alpha-teta) + cos(alpha));
				}
			}
			else if (pObject->angle > 180 && pObject->angle < 270)
			{
				if(pObject->angle < 225)
				{
					pObject->angle -=pObject->oPosi.v_grav*12.5;
					pObject->oPosi.y +=  (pObject->oPosi.spriteSizeW/2.0)*(-cos(alpha -teta) + cos(alpha)) + (pObject->oPosi.spriteSizeH/2.0)*(sin(alpha-teta) - sin(alpha));
					pObject->oPosi.x +=  (pObject->oPosi.spriteSizeW/2.0)*(-sin(alpha -teta) + sin(alpha)) + (pObject->oPosi.spriteSizeH/2.0)*(-cos(alpha-teta) + cos(alpha));

				}
				else if (pObject->angle > 225)
				{
					pObject->angle +=pObject->oPosi.v_grav*12.5;
					pObject->oPosi.x +=  (pObject->oPosi.spriteSizeW/2.0)*(-cos(alpha -teta) + cos(alpha)) + (pObject->oPosi.spriteSizeH/2.0)*(sin(alpha-teta) - sin(alpha));
					pObject->oPosi.y +=  (pObject->oPosi.spriteSizeW/2.0)*(-sin(alpha -teta) + sin(alpha)) + (pObject->oPosi.spriteSizeH/2.0)*(-cos(alpha-teta) + cos(alpha));

				}
			}
			else if (pObject->angle > 270 && pObject->angle < 360)
			{
				if(pObject->angle < 315)
				{
					pObject->angle -=pObject->oPosi.v_grav*12.5;
					pObject->oPosi.y +=  (pObject->oPosi.spriteSizeW/2.0)*(-cos(alpha -teta) + cos(alpha)) + (pObject->oPosi.spriteSizeH/2.0)*(sin(alpha-teta) - sin(alpha));
					pObject->oPosi.x +=  (pObject->oPosi.spriteSizeW/2.0)*(-sin(alpha -teta) + sin(alpha)) + (pObject->oPosi.spriteSizeH/2.0)*(-cos(alpha-teta) + cos(alpha));
					
					
				}
				else if (pObject->angle > 315)
				{
					pObject->angle +=pObject->oPosi.v_grav*12.5;
					pObject->oPosi.x +=  (pObject->oPosi.spriteSizeW/2.0)*(-cos(alpha -teta) + cos(alpha)) + (pObject->oPosi.spriteSizeH/2.0)*(sin(alpha-teta) - sin(alpha));
					pObject->oPosi.y +=  (pObject->oPosi.spriteSizeW/2.0)*(-sin(alpha -teta) + sin(alpha)) + (pObject->oPosi.spriteSizeH/2.0)*(-cos(alpha-teta) + cos(alpha));
					
				}
			}
	}
}
