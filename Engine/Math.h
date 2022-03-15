#pragma once
#define MATH_EXTEND_H
#define TURN_ANGLE_DIR 90 // how many angle to turn a 4 direction. Add this on Get_Angle_From()

// Independent File //

#include "Cpplib.h"
#include <ctime>
#include <sys/time.h>

#define PI 3.1415926535

// Used for non-moving objects.
struct IAxis
{
	int x; 
	int y;
};
struct FAxis
{
	float x; 
	float y;
};
struct IRange
{
	int min;
	int max;
};
struct FRange
{
	float min;
	float max;
};
struct ISize
{
	int w;
	int h;
};
struct FSize
{
	float w;
	float h;
};
struct Delta_Time
{
	uint32_t current   = 0;
	uint32_t last_time = 0;
};

template<typename T>
IRange  IRange_Equal(const std::vector<T>& array_vector);

// Get Radian or Degree without changing initial value.
float 	Get_Radian(float degree);
float   Get_Degree(float radian);

// Convert to Radian or Degree chaging its value.
float 	To_Radian(float &degree);
float   To_Degree(float &radian);

float   Get_Squared(float n);
float   To_Squared(float &n);

int 	Get_Point_Distance(IAxis A, IAxis B);
float 	Get_Point_Distance(FAxis  A, FAxis B);
float 	Get_Distance_Squared(IAxis A, IAxis B);
float 	Get_Distance_Squared(FAxis  A, FAxis  B);

double 	Sin_To_Degree(double angle);
double	Cos_To_Degree(double angle);

float 	Get_Angle_From(FAxis cur, FAxis dst);

void 	Wait_Time(float seconds);
int     Get_Random(IRange range);

// Type difference. Returns same from original.

float 	Get_Point_Distance(IAxis A, FAxis B);
float 	Get_Point_Distance(FAxis  A, IAxis B);
double 	Get_Distance_Squared(IAxis A, FAxis B);
double 	Get_Distance_Squared(FAxis  A, IAxis  B);

float 	Get_Angle_From(FAxis cur, IAxis dst);
float 	Get_Angle_From(IAxis cur, FAxis dst);



#include "Math_Templates.h"