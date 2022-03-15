#include "Collision.h"


namespace Engine {
/*___Rect Collisions________________________________________________________________________________________________________*/
int Rect_Collided(IRect base, IRect obj, DIRECTION colliding_direction)
{
	// Well, just be careful not make the velocity greater than the width of object B cause
	// that will make the object A leap through object B and pass trigger the collision.
	if ( (base.Right()  >= obj.Left()   &&  base.Right() <=  obj.Right())  && 
		 (base.Bottom() >= obj.Top()    &&  base.Top()   <=  obj.Bottom()) )  
		{ 
			return colliding_direction; 
		}

	return DIRECTION_NOT_COLLIDED;
}
int Rect_Collided(FRect base, FRect obj, DIRECTION colliding_direction)
{
	if ( (base.Right()  >= obj.Left()   &&  base.Right() <=  obj.Right())  && 
		 (base.Bottom() >= obj.Top()    &&  base.Top()   <=  obj.Bottom()) )  
		{ 
			return colliding_direction; 
		}

	return DIRECTION_NOT_COLLIDED;
}

int Rect_Collided(IRect base, FRect obj, DIRECTION colliding_direction)
{
	if ( (base.Right()  >= obj.Left()   &&  base.Right() <=  obj.Right())  && 
		 (base.Bottom() >= obj.Top()    &&  base.Top()   <=  obj.Bottom()) )  
		{ 
			return colliding_direction; 
		}

	return DIRECTION_NOT_COLLIDED;
}
int Rect_Collided(FRect base, IRect obj, DIRECTION colliding_direction)
{
	if ( (base.Right()  >= obj.Left()   &&  base.Right() <=  obj.Right())  && 
		 (base.Bottom() >= obj.Top()    &&  base.Top()   <=  obj.Bottom()) )  
		{ 
			return colliding_direction; 
		}

	return DIRECTION_NOT_COLLIDED;
}


// CIRCLE COLLISIONS
//___________________________________________________________________________________________________________________________________
//								INTS
//			
//___________________________________________________________________________________________________________________________________
bool Circle_Precise_Collided(ICircle base, ICircle obj)
{
	if(Get_Point_Distance(IAxis{ base.x, base.y }, IAxis{ obj.x, obj.y }) < base.r + obj.r)
	{
		return true;
	}

	return false;
}
bool Circle_Collided(ICircle base, ICircle obj)
{
	if (Get_Distance_Squared(IAxis{ base.x, base.y }, IAxis{ obj.x, obj.y }) < Get_Squared(base.r + obj.r))
	{
		return true;
	}

	return false;
}
bool Circle_Collided(ICircle base, IRect obj)
{
	float c_x = 0, c_y = 0;

	if (base.x < obj.Left()) 
	{
		c_x = obj.Left();
	}
	else if (base.x > obj.Right()) 
	{
		c_x = obj.Right();
	}
	else
		c_x = base.x; // in center;

	if (base.y < obj.Top()) 
	{
		c_y = obj.Top();
	}
	else if (base.y > obj.Bottom()) 
	{
		c_y = obj.Bottom();
	}
	else
		c_y = base.y; // in center;

	if (Get_Distance_Squared(FAxis{(float)base.x, (float)base.y}, FAxis{c_x, c_y})  <  Get_Squared(base.r))
	{
		return true;
	}

	return false;
}
bool Circle_Collided(FCircle base, IRect obj)
{
	int c_x = 0, c_y = 0;

	if (base.x < obj.Left()) 
	{
		c_x = obj.Left();
	}
	else if (base.x > obj.Right()) 
	{
		c_x = obj.Right();
	}
	else
		c_x = base.x; // in center;

	if (base.y < obj.Top()) 
	{
		c_y = obj.Top();
	}
	else if (base.y > obj.Bottom()) 
	{
		c_y = obj.Bottom();
	}
	else
		c_y = base.y; // in center;

	if (Get_Distance_Squared(FAxis{ base.x, base.y }, IAxis{ c_x, c_y })  <  Get_Squared(base.r))
		return true;

	return false;
}


bool Circle_Collided(ICircle base, FRect obj)
{
	float c_x = 0, c_y = 0;

	if (base.x < obj.Left()) 
	{
		c_x = obj.Left();
	}
	else if (base.x > obj.Right()) 
	{
		c_x = obj.Right();
	}
	else
		c_x = base.x; // in center;

	if (base.y < obj.Top()) 
	{
		c_y = obj.Top();
	}
	else if (base.y > obj.Bottom()) 
	{
		c_y = obj.Bottom();
	}
	else
		c_y = base.y; // in center;

	if (Get_Distance_Squared(IAxis{base.x, base.y}, FAxis{c_x, c_y})  <  Get_Squared(base.r))
	{
		return true;
	}

	return false;
}


//___________________________________________________________________________________________________________________________________
//            FLOATS OVERLOADS
//
//___________________________________________________________________________________________________________________________________

bool Circle_Precise_Collided(FCircle base, FCircle obj)
{
	if(Get_Point_Distance(FAxis{ base.x, base.y }, FAxis{ obj.x, obj.y }) < base.r + obj.r)
	{
		return true;
	}

	return false;
}
bool Circle_Collided(FCircle base, FCircle obj)
{
	if (Get_Distance_Squared(FAxis{ base.x, base.y }, FAxis{ obj.x, obj.y }) < Get_Squared(base.r + obj.r))
	{
		return true;
	}

	return false;
}
bool Circle_Collided(FCircle base, FRect obj)
{
	float c_x = 0, c_y = 0;

	if (base.x < obj.Left()) 
	{
		c_x = obj.Left();
	}
	else if (base.x > obj.Right()) 
	{
		c_x = obj.Right();
	}
	else
		c_x = base.x; // in center;

	if (base.y < obj.Top()) 
	{
		c_y = obj.Top();
	}
	else if (base.y > obj.Bottom()) 
	{
		c_y = obj.Bottom();
	}
	else
		c_y = base.y; // in center;

	if (Get_Distance_Squared(FAxis{ base.x, base.y }, FAxis{ c_x, c_y })  <  Get_Squared(base.r))
		return true;

	return false;
}


//___________________________________________________________________________________________________________________________________
//									TWO DIFFERENCES
//	
//___________________________________________________________________________________________________________________________________
bool Circle_Precise_Collided(ICircle base, FCircle obj)
{
	if(Get_Point_Distance(IAxis{ base.x, base.y }, FAxis{ obj.x, obj.y }) < base.r + obj.r)
	{
		return true;
	}

	return false;
}
bool Circle_Precise_Collided(FCircle base, ICircle obj)
{
	if(Get_Point_Distance(FAxis{ base.x, base.y }, IAxis{ obj.x, obj.y }) < base.r + obj.r)
	{
		return true;
	}

	return false;
}


bool Circle_Collided(ICircle base, FCircle obj)
{
	if (Get_Distance_Squared(IAxis{ base.x, base.y }, FAxis{ obj.x, obj.y }) < Get_Squared(base.r + obj.r))
	{
		return true;
	}

	return false;
}
bool Circle_Collided(FCircle base, ICircle obj)
{
	if (Get_Distance_Squared(FAxis{ base.x, base.y }, IAxis{ obj.x, obj.y }) < Get_Squared(base.r + obj.r))
	{
		return true;
	}

	return false;
}

}