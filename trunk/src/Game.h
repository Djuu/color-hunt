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
void initSpeedX(Game *pGame);
void initSpeedY(Game *pGame);
Enemies *getGameEnemies(Game *pGame);
void warpMap (Game *pGame);
void collisionMap (Character *pChar, Map *pMap);

void down(Game *pGame);
void up(Game *pGame);
void controlKey2 (Game *pGame, const char key);

/**
 Description : projection de pPosi1 par pPosi2 avec une force power
*/
void action(Position *pPosi, float power);
#endif

