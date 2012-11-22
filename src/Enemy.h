#ifndef _ENEMY
#define _ENEMY

#include "Character.h"

typedef struct
{
	Character eChar;
}Enemy;

typedef struct
{
	int number;
	Enemy *eEnemy;
}Enemies;

void initEnemy(Enemies *pEnemies, int num);
Position getPosiEnemy (const Enemies *pEnemies, int id);
void setPosiEnemy (Enemies *pEnemies,int id, const float x, const float y, const float z);
int getLifeEnemy (const Enemies *pEnemies, int id);
void setLifeEnemy (Enemies *pEnemies, int id, int nbLife);
int getManaEnemy (const Enemies *pEnemies, int id);
void setManaEnemy (Enemies *pEnemies,int id, int nbMana);

#endif 
