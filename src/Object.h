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
}Object;

typedef struct
{
	Object oObject[20];
	int number;
}Objects;

void initObject(Object *pObject);

void initObjects(Objects *pObjects, int num, int type);
void moveObjectR(Object *pObject);

void moveObjectL(Object *pObject);

void applySpeedObject(Object *pObject);

#endif 
