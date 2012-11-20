#ifndef _PHYSICS
#define _PHYSICS

#include "Character.h"
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

#endif
