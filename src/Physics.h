#ifndef _PHYSICS
#define _PHYSICS

#include "Character.h"
#include "Object.h"
#include "Map.h"

void gravity (Character *pChar);
int collision (Character *pChar, Map *pMap);
char *path (Character *pChar, Map *pMap);
#endif
