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
float path (Character *pChar, Map *pMap)
{
	float i;
	float posX, posY, posYd, posXd, posYr, posXr, posYl, posXl;
	Position *current;
	current=(Position*)malloc(sizeof(Position));

	setPosi (current, pChar->cPosi.x, pChar->cPosi.y,0);

	
	for (i=0.01; i<=1; i+=0.01) 
	{
		Position charPosition;
		charPosition = getPosiChar(pChar);
		posX = charPosition.x + i*charPosition.v_x;
		posY = charPosition.y + i*charPosition.v_y;

		posYd = charPosition.y + i*charPosition.v_y+1;
		posXd = charPosition.x + i*charPosition.v_x+1;

		posYr = charPosition.y + i*charPosition.v_y;
		posXr = charPosition.x + i*charPosition.v_x+1;

		posYl = charPosition.y + i*charPosition.v_y+1;
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
/*			if(getMapXY(pMap, (int)posX, (int)posY)=='E' || getMapXY(pMap, (int)posXd, (int)posYd)=='E' 
			|| getMapXY(pMap, (int)posXr, (int)posYr)=='E' || getMapXY(pMap, (int)posXl, (int)posYl)=='E') 
			{
				if(nbLife>0)
				{ 
					nbLife--;
				}
				setLife (pChar,nbLife);
				printf(" %d \n", getLife (pChar));
				return i-0.01;

			}
			
		
*/	
			
			
			
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


/*
Description : fonction interne qui identifie les cases que le personnage parcoure et renvoi une valeur en fonction de la distance qui seppare le personnage de l'ennemie
Retourne : reel
*/
float pathEnemy(Character *pChar, Enemies *pEnemies ,int id)
{

	float i;
	int j;
	int nbLife =getLife (pChar);
	float posX, posY, posYd, posXd, posYr, posXr, posYl, posXl;
	float posXe, posYe, posYde, posXde, posYre, posXre, posYle, posXle;
	Position *current;
	current=(Position*)malloc(sizeof(Position));
	
	setPosi (current, pChar->cPosi.x, pChar->cPosi.y,0);
	
		for (i=0.01; i<=1; i+=0.01) 
		{
			Position charPosition;
			Position enemyPosition;
			
			charPosition = getPosiChar(pChar);
			posX = charPosition.x + i*charPosition.v_x;
			posY = charPosition.y + i*charPosition.v_y;

			posYd = charPosition.y + i*charPosition.v_y+1;
			posXd = charPosition.x + i*charPosition.v_x+1;

			posYr = charPosition.y + i*charPosition.v_y;
			posXr = charPosition.x + i*charPosition.v_x+1;

			posYl = charPosition.y + i*charPosition.v_y+1;
			posXl = charPosition.x + i*charPosition.v_x;
		
		
			
			enemyPosition=getPosiEnemy(pEnemies,id);
			
			posXe = enemyPosition.x + i*enemyPosition.v_x;
			posYe = enemyPosition.y + i*enemyPosition.v_y;

			posYde = enemyPosition.y + i*enemyPosition.v_y+1; 
			posXde = enemyPosition.x + i*enemyPosition.v_x+1;

			posYre = enemyPosition.y + i*enemyPosition.v_y;
			posXre = enemyPosition.x + i*enemyPosition.v_x+1;

			posYle = enemyPosition.y + i*enemyPosition.v_y+1;
			posXle = enemyPosition.x + i*enemyPosition.v_x;


			 if((posXe < posXr+0.1 && posX-0.1 < posXre) && (posY+0.1<posYde && posYe<posYl-0.1))
			 {
			 
			 	nbLife -=10;
			 	printf("%f \n",i);
			 	return i-0.01;
			 		
			 }
		
		}
		return 1;
}


void collisionEnemies (Character *pChar, Enemies *pEnemies)
{
	int j;
	
		for(j=0;j<pEnemies ->number; j++)
		{
			pChar->cPosi.v_y*=pathEnemy(pChar, pEnemies,j);
			pChar->cPosi.v_x*=pathEnemy(pChar, pEnemies,j);
	
		}
	
	
	
	
	
}
