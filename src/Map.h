#ifndef _MAP
#define _MAP

typedef struct
{
	int dimx;
	int dimy;
	char **tab;
}Map;

/**
Description : Initialisation de la map. Allocation du tableau
*/
void initMap(Map *pMap);

/**
Description : Affichage de la map
*/
/*void mapAffiche(map *pMap);*/

const char getMapXY(const Map *, const int x, const int y);

/**
Function
Description : renvoie la taille horizontale de la map 
Retoure : entier
*/
int getDimX(const Map*);
/**
Function
Description : renvoie la taille verticale de la map 
Retoure : entier
*/
int getDimY(const Map*);

void setDimX(Map* , int);

void setDimY(Map* , int);
#endif
