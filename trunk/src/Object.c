#include "Object.h"

void initObjects(Objects *pObjects, int num, int type)
{
	
	int i = 0;
	assert(num >= 0);
	pObjects -> number = num;
	/*pObjects->oObject = calloc(pObjects -> number, sizeof(Object));*/
	
	for (i = 0; i< num; i++)
	{
		initObject(&(pObjects -> oObject[i]));
		pObjects ->oObject[i].type = type;
		pObjects ->oObject[i].angle=0.0;
		pObjects ->oObject[i].oPosi.v_x = 0;/*0.2*/
		pObjects ->oObject[i].oPosi.v_y=0;
		pObjects ->oObject[i].oPosi.x = -10;/*0.2*/
		pObjects ->oObject[i].oPosi.y=-10;
		pObjects ->oObject[i].oPosi.v_grav = 0.08;/*0.02*/
		pObjects ->oObject[i].oPosi.floor=0;

	}
}

void initObject(Object *pObject)
{
	pObject->xS = -10;
	pObject->yS = -10;
	pObject->oPosi.v_x = 0;
	pObject->oPosi.v_y=0;
	pObject->state = 0;
	pObject->oPosi.x = -10;
	pObject->oPosi.y=-10;
	pObject->oPosi.v_grav = 0.08;
	pObject->oPosi.spriteSizeW =1.5;
	pObject->oPosi.spriteSizeH =2.8;
}

void moveObjectR(Object *pObject)
{
	pObject->oPosi.v_x = 0.5;
}

void moveObjectL(Object *pObject)
{
	pObject->oPosi.v_x = -0.5;
}

void applySpeedObject(Object *pObject)
{
	int temp =0;
	if(pObject->oPosi.x - pObject->xS <= 15 && pObject->oPosi.v_x >0)
	{
		pObject->oPosi.x +=pObject->oPosi.v_x;
		pObject->oPosi.y +=pObject->oPosi.v_y;
		temp=1;
	}
	else if(temp == 0 && pObject->oPosi.v_x >0)
	{
		pObject->oPosi.x = -42;
		pObject->oPosi.y = -42;
	}
	if(pObject->oPosi.x - pObject->xS >= -15 && pObject->oPosi.v_x <0)
	{
		pObject->oPosi.x +=pObject->oPosi.v_x;
		pObject->oPosi.y +=pObject->oPosi.v_y;
	}
	else if(temp == 0 && pObject->oPosi.v_x <0)
	{
		pObject->oPosi.x = -42;
		pObject->oPosi.y = -42;
	}
	
}

