#ifndef _OBJECT
#define _OBJECT

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Position.h"

typedef struct
{
	int type;
	Position oPosi;
	float xS;
	float yS;
	int state;
	double angle;
	int status;
	
}Object;

typedef struct
{
	Object oObject[20];
	int number;
}Objects;

void initObject(Object *pObject);

void initObjects(Objects *pObjects, int num, int type);
/** Applique une translation vers la droite à un objet */
void moveObjectR(Object *pObject);
/** Applique une translation vers la gauche à un objet */
void moveObjectL(Object *pObject);
/** Applique le vecteur direction à la coordonnée */
void applySpeedObject(Object *pObject);
/** Accesseur Position */
Position getPosiObject (const Objects *pObjects, int id);

#endif 
