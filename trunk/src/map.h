#ifndef _MAP
#define _MAP

typedef struct
{
	int dimx;
	int dimy;
	char **tab;
}map;

/**
Description : Initialisation de la map. Allocation du tableau
*/
void mapInit(map *pMap);

/**
Description : Affichage de la map
*/
/*void mapAffiche(map *pMap);*/

const char mapGetXY(const map *, const int x, const int y);

/**
Function
Description : renvoie la taille horizontale de la map 
Retoure : entier
*/
int getDimX(const map*);
/**
Function
Description : renvoie la taille verticale de la map 
Retoure : entier
*/
int getDimY(const map*);
#endif