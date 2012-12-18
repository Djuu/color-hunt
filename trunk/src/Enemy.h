#ifndef _ENEMY
#define _ENEMY

#include "Character.h"

typedef struct
{
	Character eChar;
	int panic;
	int idHelp;
	float powerProjection;
	int stateAttack;
}Enemy;

typedef struct
{
	int number;
	Enemy *eEnemy;
}Enemies;

void initEnemy(Enemies *pEnemies, int num);
/** Accesseur Position */
Position getPosiEnemy (const Enemies *pEnemies, int id);
/** Mutateur Position */
void setPosiEnemy (Enemies *pEnemies,int id, const float x, const float y, const float z);
/** Accesseur Life */
int getLifeEnemy (const Enemies *pEnemies, int id);
/** Mutateur Life */
void setLifeEnemy (Enemies *pEnemies, int id, int nbLife);
/** Accesseur Mana */
int getManaEnemy (const Enemies *pEnemies, int id);
/** Mutateur Mana */
void setManaEnemy (Enemies *pEnemies,int id, int nbMana);
/** Modifie v_x pour faire une translation vers la gauche */
void moveEnemyLeft (Enemies *pEnemies,int id);
/** Modifie v_x pour faire une translation vers la droite */
void moveEnemyRight (Enemies *pEnemies,int id);
/** Si l'ennemie est mort , on passe son status a mort */
void deadEnemy(Enemies *pEnemies,int id);
/** Libère la mémoire Ennemie */
void freeEnemies(Enemies *pEnemies);


#endif 
