// cl: /Igame/Libraries/Include/Lib
#include "trig.h"

#include <math.h>


float Sin(float radians)
{
    return sinf(radians);
}

float Cos(float radians)
{
    return cosf(radians);
}

float Tan(float radians)
{
    return tanf(radians);
}

float ACos(float x)
{
    return (float)acos(x);
}

float ASin(float x)
{
    return (float)asin(x);
}

float deg2rad(float degrees)
{
    return degrees * 0.01745329238474369f;
}

float rad2deg(float radians)
{
    return radians * 57.2957763671875f;
}
