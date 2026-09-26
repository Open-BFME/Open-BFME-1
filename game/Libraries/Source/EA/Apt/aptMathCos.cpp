// ?aptMathCos@@YAPAVAptValue@@PAXH@Z
// cl: /DNDEBUG /MD /EHsc
#include <math.h>
#pragma intrinsic(sin, cos, atan2)
class AptValue { public: float toNumber(); };
extern AptValue* g_bfmeFallbackDB;
extern AptValue** g_bfmeArr1233;
extern int g_bfmeCount1233;
AptValue* __cdecl Rva008A4EA0MakeFloat(float value);
AptValue* aptMathCos(void* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	float v = g_bfmeArr1233[g_bfmeCount1233 - 1]->toNumber();
	return Rva008A4EA0MakeFloat((float)cos(v));
}
