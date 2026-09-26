// cl: /DNDEBUG /MD /EHsc
#include <math.h>

extern float Rva01126A68Threshold;
extern const float g_01076C24;
extern float g_bfmeDefaultBU;

// ?Rva00783310GuardedRatio@@YAMMM@Z
float Rva00783310GuardedRatio(float base, float target)
{
	if (base < Rva01126A68Threshold)
		return g_bfmeDefaultBU;
	if (fabsf(target-base) < g_01076C24)
		return g_bfmeDefaultBU;
	return target/base;
}
