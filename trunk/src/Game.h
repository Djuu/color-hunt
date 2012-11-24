#ifndef _GAME
#define _GAME

#include "Map.h"
#include "Physics.h"
#include "Enemy.h"

typedef struct
{
	Character gChar;
	Enemies gEnemies;
	Map gMap;
	Object *tabObj;
	int level;
}Game;

/** Initialise le jeu */
void initGame (Game *pGame, const char* Map);
/** Appel la fonction correspondant a la touche appelée */
void controlKey (Game *pGame, const char key);
Map *getGameMap (Game *pGame);
Character *getGameChar (Game* pGame);
void initSpeed(Game *pGame);
Enemies *getGameEnemies(Game *pGame);
void warpMap (Game *pGame);
void collisionMap (Game *pGame);
void collision(Game *pGame);
#endif

