// ?Rva0022FC80@@YAMM@Z
// cl: /DNDEBUG /MD /O2
// Retail 0x0022FC80 (33 bytes): float curve blend t*sqrt(t) + t*t*(1.0f - t).
// The compound-assign on weight is the lever: it forces retail's
// fld t / fmul t / fld global / fsub t x87 schedule, where plain
// expression spellings fold into a different order. Identity is NOT
// recovered: free function under an opaque address-derived name.
// The pooled float at 0x01075334 is 1.0f (g_bfmeDefaultBU).
#include <math.h>
#pragma intrinsic(sqrt)

extern float g_bfmeDefaultBU; // retail 0x01075334, 1.0f

float __cdecl Rva0022FC80(float t)
{
	float eased = t * (float)sqrt(t);
	float weight = t * t;
	weight *= g_bfmeDefaultBU - t;
	return eased + weight;
}
