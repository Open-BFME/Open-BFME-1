// cl: /DNDEBUG /MD /EHsc
#include <math.h>

// Retail 0x01126A68, 0x01076C24 and 0x01075334 are MSVC float-literal pool
// entries (__real@38d1b717, __real@3c23d70a, __real@3f800000): 1e-4f, 0.01f
// and 1.0f. A safe-divide against three literals, not three globals.

// ?Rva00783310GuardedRatio@@YAMMM@Z
float Rva00783310GuardedRatio(float base, float target)
{
	if (base < 1e-4f)
		return 1.0f;
	if (fabsf(target-base) < 0.01f)
		return 1.0f;
	return target/base;
}
