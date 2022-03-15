#include <SDL.h>
#include <iostream>
#include "Math.h"
#include "Shapes.h"
#define DIRECTION_2 2 	
#define DIRECTION_4 4 		
#define DIRECTION_8 8 
#define DIRECTION_NOT_COLLIDED 16

enum DIRECTION
{
	DIRECTION_LEFT, 		DIRECTION_RIGHT, 	DIRECTION_TOP, 			DIRECTION_BOTTOM,
	DIRECTION_TOPLEFT, 		DIRECTION_TOPRIGHT, DIRECTION_BOTTOMLEFT,	DIRECTION_BOTTOMRIGHT,
	DIRECTION_TOTAL,        DIRECTION_NOT_KNOWN = 32
};

namespace Engine 
{

int Rect_Collided(IRect base, IRect obj, DIRECTION colliding_direction = DIRECTION_NOT_KNOWN);
int Rect_Collided(FRect base, FRect obj, DIRECTION colliding_direction = DIRECTION_NOT_KNOWN);

int Rect_Collided(IRect base, FRect obj, DIRECTION colliding_direction = DIRECTION_NOT_KNOWN);
int Rect_Collided(FRect base, IRect obj, DIRECTION colliding_direction = DIRECTION_NOT_KNOWN);

// INTS
bool Circle_Precise_Collided(ICircle base, ICircle obj);
bool Circle_Collided(ICircle base, ICircle obj);
bool Circle_Collided(ICircle base, IRect obj);
bool Circle_Collided(ICircle base, FRect  obj);
bool Circle_Collided(FCircle base, IRect  obj);


// FLOATS
bool Circle_Precise_Collided(FCircle base, FCircle obj);
bool Circle_Collided(FCircle base, FRect obj);
bool Circle_Collided(FCircle base, FCircle obj);



// TWO DIIFFERENCE ARGV
// the base argumant(1st)'s type takes precedence.
bool Circle_Precise_Collided(ICircle base, FCircle obj);
bool Circle_Precise_Collided(FCircle base, ICircle obj);

bool Circle_Collided(ICircle base, FCircle obj);
bool Circle_Collided(FCircle base, ICircle obj);
}