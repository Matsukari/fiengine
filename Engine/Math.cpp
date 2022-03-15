#include "Math.h"


float Get_Degree(float radian)
{
	return radian * (PI / 180.0f);
}
float Get_Radian(float degree)
{
	return degree * (180.0f / PI);
}
float To_Radian(float &degree)
{
	return degree = Get_Radian(degree); // becomes radian
}
float To_Degree(float &radian)
{
	return radian = Get_Degree(radian); // becormes degree
}

float Get_Squared(float n)
{
	return n * n;
}
float To_Squared(float& n)
{
	n = (n * n);
	return n;
}
int Get_Point_Distance(IAxis A, IAxis B)
{
     return static_cast<int>(
     	sqrt(  Get_Squared(static_cast<int>(A.x - B.x)) + 
     		   Get_Squared(static_cast<int>(A.y - B.y))  ));
}
float Get_Point_Distance(FAxis A, FAxis B)
{
     return sqrtf(  Get_Squared(A.x - B.x) + Get_Squared(A.y - B.y) );
}

float Get_Distance_Squared(IAxis A, IAxis B)
{
	float delta_x = (B.x - A.x);
	float delta_y = (B.y - A.y);

	return Get_Squared(delta_x) + Get_Squared(delta_y);
}
float Get_Distance_Squared(FAxis A, FAxis B)
{
	float delta_x = (B.x - A.x);
	float delta_y = (B.y - A.y);

	return Get_Squared(delta_x) + Get_Squared(delta_y);
}


double Sin_To_Degree(double angle)
{
	return sin(Get_Degree(angle));
}
double Cos_To_Degree(double angle)
{
	return cos(Get_Degree(angle));
}

float Get_Angle_From(FAxis cur, FAxis dst)
{
	return Get_Degree(atan2(dst.y - cur.y, dst.x - cur.x));
}

void Wait_Time(float seconds)
{
	clock_t start_time      = clock();
	float   seconds_to_wait = seconds * CLOCKS_PER_SEC;

	// Wait until current time passes seconds given;
	while (clock() < start_time + seconds_to_wait);
}

int Get_Random(IRange range)
{
	timeval t;

	Wait_Time(0.0001);

	gettimeofday(&t, NULL);
	srand(t.tv_usec * t.tv_sec);
	
	// if minimum is negative then possible results reduces from that minimum to half maximum,
	// make up by adding extra half to make it whole again after reault.
	if (range.min < 0) {range.max *= 2;}

	return (rand() % range.max) + range.min;
}


//___________________________________________________________________________________________________________________________________
//		DIFFERENCE TYPES
//
//___________________________________________________________________________________________________________________________________
// Preforming arithmetic operation on int and float yields type FLOAT.
float Get_Point_Distance(IAxis A, FAxis B)
{
    return sqrtf(  Get_Squared(A.x - B.x) + Get_Squared(A.y - B.y)  );
}
float Get_Point_Distance(FAxis  A, IAxis B)
{
    return sqrtf(  Get_Squared(A.x - B.x) + Get_Squared(A.y - B.y)  );
}
double Get_Distance_Squared(IAxis A, FAxis B)
{
	float delta_x = B.x - A.x;
	float delta_y = B.y - A.y;

	return (Get_Squared(delta_x) + Get_Squared(delta_y));
}
double Get_Distance_Squared(FAxis  A, IAxis  B)
{
	float delta_x = B.x - A.x;
	float delta_y = B.y - A.y;

	return Get_Squared(delta_x) + Get_Squared(delta_y);
}

float Get_Angle_From(FAxis cur, IAxis dst)
{
	return Get_Degree(atan2f(dst.y - cur.y, dst.x - cur.x));
}
float Get_Angle_From(IAxis cur, FAxis dst)
{
	return Get_Degree(atan2f(dst.y - cur.y, dst.x - cur.x));

}
