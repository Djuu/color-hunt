#ifndef _POSITION
#define _POSITION 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define SPRITE_SIZE 20

typedef struct
{
	float x,y,z;
	double v_x;
	double v_grav;
	double v_y;
	float spriteSizeW;
	float spriteSizeH;
	int direction;
	

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
Renvoi la position entière en x
*/
int getPosiXint(const Position *pPosi);

/** 
Renvoi la position entière en y
*/
int getPosiYint(const Position *pPosi);

/** 
Renvoi la position entière en z
*/
int getPosiZint(const Position *pPosi);

/** 
Fixer une position 
*/
void setPosi (Position *pPosi, const float x, const float y, const float z); 

void refreshDirection(Position *pPosi);

#endif 
