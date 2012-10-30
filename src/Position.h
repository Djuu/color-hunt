#ifndef _POSITION
#define _POSITION 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct
{
	float x,y,z;
	double v_x;
	double v_grav;
	double v_saut;
	double v_y;

}Position;

/** 
Renvoi la position en x
*/
float getPosiX (const Position *pPosi);

/** 
Renvoi la position en y
*/
float getPosiY (const Position *pPosi);

/** 
Renvoi la position en z
*/
float getPosiZ (const Position *pPosi);

/** 
Fixer une position 
*/
void setPosi (Position *pPosi, const float x, const float y, const float z); 

#endif 
