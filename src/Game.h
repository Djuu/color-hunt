#ifndef _GAME
#define _GAME

#include "Map.h"
#include "Physics.h"
#include "Enemy.h"

#define consumedMana 20

typedef struct
{
	Character gChar;
	Character gPnj;
	Enemies gEnemies;
	Map gMap;
	Objects gObjects;
	int level;
}Game;

/** Initialise le jeu */
void initGame (Game *pGame, const char* pMap);
/** Appel la fonction correspondant a la touche appelée */
void controlKey (Game *pGame, const char key);
Map *getGameMap (Game *pGame);
Character *getGameChar (Game* pGame);
void initSpeedX(Game *pGame);
void initSpeedY(Game *pGame);
Enemies *getGameEnemies(Game *pGame);
int warpMap (Game *pGame);
void collisionMap (Position *pPosi, Map *pMap);
int collision(Position *pPosi1, Position *pPosi2);
Character *getGamePnj(Game *pGame);
void down(Game *pGame);
void up(Game *pGame);
void controlKey2 (Game *pGame, const char key);
void attack(Game *pGame);
Objects *getGameObjects(Game *pGame);
void superAttack(Game *pGame);
void superAttackDmg(Game *pGame);
void right2(Game *pGame);
void left2(Game *pGame);
/**
 Description : projection de pPosi1 par pPosi2 avec une force power
*/


void enemyAttack(Game *pGame);
/**
Retourn : id de l'ennemie le plus proche
*/
int distanceEnemies(Game *pGame);
void collisionObjects (Position *pPosi, Objects *pObjects);

void flyMod(Game *pGame);

void detect(Game *pGame);

int detectPnj(Game *pGame);
#endif

