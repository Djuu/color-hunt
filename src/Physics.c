#include "Physics.h"
#include <math.h>
void gravity (Character *pChar)
{
	pChar->cPosi.y+=pChar->cPosi.v_y;
	pChar->cPosi.v_y += pChar->cPosi.v_grav;

}

int collision (Character *pChar, Map *pMap)
{
	int temp;
	temp=(int)(pChar->cPosi.y);
	char *tab;
	tab = path (pChar, pMap);
	int length=sizeof(tab)/sizeof(char);
	int i;
	for(i=0;i<length;i++)
	{
		if(tab[i]=='#') 
		{
		
			return 1;

		}
	}
	return 0;
}
char *path (Character *pChar, Map *pMap)
{
	char *tab;
	float i;
	int j=1;
	tab=(char*)calloc(1,sizeof(char));
	Position *current;
	current=(Position*)malloc(sizeof(Position));
	
	float posX, posY, posXa, posYa;
	setPosi (current, pChar->cPosi.x, pChar->cPosi.y,0);
	tab[0]=getMapXY(pMap, getPosiXint(current), getPosiYint(current));
	
	for (i=0; i<1; i+=0.01) 
	{
		posX = pChar->cPosi.x + i*pChar->cPosi.v_x;
		posY = pChar->cPosi.y + i*pChar->cPosi.v_y;
	
		if (getPosiXint(current)!=(int)posX || getPosiYint(current)!=(int)posY)
		{
			tab=realloc(tab,(j+1)*sizeof(char));	
			tab[j]=getMapXY(pMap, (int)posX, (int)posY);
			setPosi (current, posX, posY,0);
			j++;
			
		}
		
	} 
	return tab;
}

