#include "Enemy.h"

void initEnemy(Enemies *pEnemies, int num)
{
	
	int i = 0;
	assert(num >= 0);
	pEnemies->eEnemy = calloc(num, sizeof(Enemy));
	pEnemies -> number = num;
	for (i = 0; i< num; i++)
	{
		printf("%f\n",pEnemies -> eEnemy[i].eChar.cPosi.x);
		initChar(&(pEnemies -> eEnemy[i].eChar));
			
	}
	
}


Position getPosiEnemy (const Enemies *pEnemies, int id)
{

	return pEnemies -> eEnemy[id].eChar.cPosi;
}

void setPosiEnemy (Enemies *pEnemies,int id, const float x, const float y, const float z)
{
	assert(pEnemies != NULL);
	pEnemies -> eEnemy[id].eChar.cPosi.x = x;
	pEnemies -> eEnemy[id].eChar.cPosi.y = y;
	pEnemies -> eEnemy[id].eChar.cPosi.z = z;
}

int getLifeEnemy (const Enemies *pEnemies, int id)
{
	assert(pEnemies -> eEnemy[id].eChar.life >= 0 || pEnemies -> eEnemy[id].eChar.life <= 100);
	return pEnemies -> eEnemy[id].eChar.life;
}

void setLifeEnemy (Enemies *pEnemies, int id, int nbLife)
{
	assert(nbLife >= 0 || nbLife <= 0);
	pEnemies -> eEnemy[id].eChar.life = nbLife;
}

int getManaEnemy (const Enemies *pEnemies, int id)
{
	assert(pEnemies -> eEnemy[id].eChar.mana >= 0 || pEnemies -> eEnemy[id].eChar.mana <= 100);
	return pEnemies -> eEnemy[id].eChar.mana;
}

void setManaEnemy (Enemies *pEnemies,int id, int nbMana)
{
	assert(nbMana >= 0 || nbMana <= 0);
	pEnemies -> eEnemy[id].eChar.mana = nbMana;
}

