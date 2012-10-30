#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include "Map.h"

void mapInit(Map *pMap)
{
	int x, y;
	const char Map_defaut[150][200] = {
		"####################",
		"#...................",
		"#...................",
		"#...................",
		"#...................",
		"#...................",
		"#...................",
		"#...................",
		"#...................",
		"#...................",
		"#...................",
		"#...................",
		"#...................",
		"#...................",
		"#...................",
		"#...................",
		"#...................",
		"#...................",
		"#...................",
		"#...........................#####",
		"#...................",
		"#....................####",
		"#...................",
		"#............#####..",
		"#...........#.......",
		"#..........#........",
		
        "############################################################################################################################################################################"
    };
    
    	pMap -> dimx = 200;
	pMap -> dimy = 150;

	pMap->tab = (char **)malloc(sizeof(char *)*pMap->dimy);
	for (y=0; y<pMap->dimy; y++)
		pMap->tab[y] = (char *)malloc(sizeof(char)*pMap->dimx);

	for(y=0;y<pMap->dimy;++y)
		for(x=0;x<pMap->dimx;++x)
			pMap->tab[y][x] = Map_defaut[y][x];
}



const char getMapXY(const Map *pMap, const int x, const int y)
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
