#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

#include "Map.h"

void mapInit(Map *pMap,const char * Name)
{
	int x, y;
	FILE *f = fopen(Name,"r");
  	if (f == NULL)
	{
		printf("Impossible d'ouvrir le fichier %s\n",Name);
		exit(1);
	}
	
	fscanf(f ,"%d %d",&(pMap -> dimx),&(pMap -> dimy));
	pMap->tab = (char **)malloc(sizeof(char *)*pMap->dimy);
	for (y=0; y<pMap->dimy; y++)
		pMap->tab[y] = (char *)malloc(sizeof(char)*pMap->dimx);

	for(y=0;y<pMap->dimy;++y)
	{
		for(x=0;x<pMap->dimx;++x)
		{
			fscanf(f,"%c",&(pMap->tab[y][x]));
		}
	}	
	
	fclose(f);
}


char getMapXY(const Map *pMap, const int x, const int y)
{
	assert( x>=0) ;
	assert( y>=0) ;
	assert( x<pMap->dimx ) ;
	assert( y<pMap->dimy ) ;
	return pMap->tab[y][x];
}

int getDimX(const Map* pMap)
{
	return pMap->dimx;
}

int getDimY(const Map* pMap)
{
	return pMap->dimy;
}

void freeMap(Map* pMap)
{
	int y;
		for (y=0; y<pMap->dimy; y++)
			free(pMap->tab[y]);	
}
