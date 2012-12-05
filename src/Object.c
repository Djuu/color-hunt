#include "Object.h"

void initObjects(Objects *pObjects, int num, int type)
{
	
	int i = 0;
	assert(num >= 0);
	pObjects -> number = num;
	//pObjects->oObject = calloc(pObjects -> number, sizeof(Object));
	
	for (i = 0; i< num; i++)
	{
		initObject(&(pObjects -> oObject[i]));
		pObjects ->oObject[i].type = type;
	}
}

void initObject(Object *pObject)
{
	pObject->oPosi.v_x = 0;
	pObject->oPosi.v_y=0;
	pObject->oPosi.v_grav = 0.08;
	pObject->oPosi.spriteSizeW =1;
	pObject->oPosi.spriteSizeH =2.5;
}

void moveObjectR(Object *pObject)
{
	pObject->oPosi.v_x = 0.1;
}

void moveObjectL(Object *pObject)
{
	pObject->oPosi.v_x = -0.1;
}

void applySpeedObject(Object *pObject)
{
	pObject->oPosi.x +=pObject->oPosi.v_x ;
	pObject->oPosi.y +=pObject->oPosi.v_y;
}
