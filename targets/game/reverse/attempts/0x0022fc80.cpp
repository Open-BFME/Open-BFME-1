// ?rva0022fc80Curve@@YAMM@Z
// partial score=0.7 date=2026-09-26
// Retail 0x0022FC80 computes a smooth scalar blend using the shared unit float.
#include <math.h>
#pragma intrinsic(sqrt)

extern float g_bfmeDefaultBU;
float __cdecl rva0022fc80Curve(float t)
{
	float eased = t * (float)sqrt(t);
	float weight = t * t;
	return eased + weight * (g_bfmeDefaultBU - t);
}
