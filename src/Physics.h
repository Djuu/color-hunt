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
void collision (Character *pChar, Map *pMap);

float pathEnemy(Character *pChar, Enemies *pEnemies ,int id);
#endif
