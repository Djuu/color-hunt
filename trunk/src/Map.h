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
void mapInit(Map *pMap, const char* Name);

/**
Description : Affichage de la map
*/
/*void mapAffiche(map *pMap);*/

char getMapXY(const Map *, const int x, const int y);

/**
Fonction 
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

/**
Description : donner une valeur à la taille horizontale de la map 
*/
void setDimX(Map* , int);

/**
Description : donner une valeur à la taille verticale de la map 
*/
void setDimY(Map* , int);


void freeMap(Map* pMap);
#endif
