#ifndef _CHARACTER
#define _CHARACTER

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Position.h"

typedef struct
{
	Position cPosi; 
	int floor;
	int air;
	int life, mana;
	int attack, superAttack;
	int projection;
	int domage;
	int superDomage;
}Character;

/**
Initialisation d'un personnage
*/
void initChar (Character *pChar);

/**
Récuperation de la position du personnage
*/
Position getPosiChar (const Character *pChar);

/**
Changer la position du personnage
*/
void setPosiChar (Character *pChar, const float x, const float y, const float z);

/**
Récupère le nombre de vie
*/
int getLife (const Character *pChar);

/**
Modification de la valeur de la vie
*/
void setLife (Character *pChar, int nbLife);

/**
Récupère le nombre de mana
*/
int getMana (const Character *pChar);

/**
Modification de la valeur du mana
*/
void setMana (Character *pChar, int nbMana);

#endif
