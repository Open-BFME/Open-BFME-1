// cl: /Igame/Libraries/Include/Lib
#include "trig.h"

#include <math.h>


// Retail 0x00873900 (10 B, unreferenced), directly before Sin: the same
// fld [esp+4] / call __CIasin / ret shape as ASin below. Its own body with no
// caller or symbol, so the name keeps the address.
float Rva00873900ASin(float x)
{
    return (float)asin(x);
}

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
