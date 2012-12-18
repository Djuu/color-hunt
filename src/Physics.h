#ifndef _PHYSICS
#define _PHYSICS

#include "Enemy.h"
#include "Object.h"
#include "Map.h"


/**
Description : application de la gravitation 
*/
void gravity (Position *pPosi);

/**
Description : Renvoi la distance a parcourir avant de rencontrer un obstacle
*/
float pathMap (Position *pPosi, Map *pMap);

/**
Description : application de la collision entre deux position

 */
float path(Position *pPosi1, Position *pPosi2);
/** Effectue la translation nécessaire apres une rotation */
void stabilizeObject(Object *pObject);




#endif
