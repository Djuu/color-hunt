#ifndef _GAME
#define _GAME

#include "Character.h"

typedef struct
{
	Character gChar;
	Map gMap;
	Object *tabObj;
	Enemy *tabEnemy;
}Game;

/** Initialise le jeu */
void initGame (Game *pGame);

/** Appel la fonction correspondant a la touche appelée */
void controlKey (Game *pGame, const char key);

Map *getGameMap (Game *pGame);
Character *getGameChar (Game* pGame);

#endif

