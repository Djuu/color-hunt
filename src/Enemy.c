#include "Enemy.h"

void initEnemy(Enemies *pEnemies, int num)
{
	
	int i = 0;
	assert(num >= 0);
	pEnemies->eEnemy = calloc(num, sizeof(Enemy));
	pEnemies -> number = num;
	
	for (i = 0; i< num; i++)
	{
		initChar(&(pEnemies -> eEnemy[i].eChar));
		pEnemies -> eEnemy[i].eChar.cPosi.spriteSizeW = 1;
		pEnemies -> eEnemy[i].eChar.cPosi.spriteSizeH = 2.5;
		pEnemies -> eEnemy[i].panic = 0;
		pEnemies -> eEnemy[i].idHelp = 0;
		pEnemies -> eEnemy[i].powerProjection = 0.0;
		pEnemies -> eEnemy[i].stateAttack =0;
		
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

void moveEnemyLeft (Enemies *pEnemies,int id)
{
	if (pEnemies -> eEnemy[id].stateAttack == 0 && pEnemies -> eEnemy[id].eChar.attack == 0)
	{
		pEnemies -> eEnemy[id].eChar.cPosi.v_x=-0.2;
	}
}
void moveEnemyRight (Enemies *pEnemies,int id)
{
	if (pEnemies -> eEnemy[id].stateAttack == 0 && pEnemies -> eEnemy[id].eChar.attack == 0)
	{
		pEnemies -> eEnemy[id].eChar.cPosi.v_x=0.2;
	}
}

void deadEnemy(Enemies *pEnemies,int id)
{
	if(pEnemies -> eEnemy[id].eChar.life <= 0)
	{
		pEnemies -> eEnemy[id].eChar.cPosi.x =-10;
		pEnemies -> eEnemy[id].eChar.cPosi.y = -10;
		pEnemies -> eEnemy[id].eChar.cPosi.v_y =0;
		pEnemies -> eEnemy[id].eChar.cPosi.v_x =0;
	}
}
