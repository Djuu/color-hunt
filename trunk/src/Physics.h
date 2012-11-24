#ifndef _PHYSICS
#define _PHYSICS

#include "Enemy.h"
#include "Object.h"
#include "Map.h"


/**
Description : application de la gravitation 
*/
void gravity (Character *pChar);

/**
Description : application des collisions 
*/
float pathMap (Position *pPosi, Map *pMap);

float path(Position *pPosi1, Position *pPosi2);
#endif
