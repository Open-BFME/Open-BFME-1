// ?aptMathAtan2@@YAPAVAptValue@@PAXH@Z
// cl: /DNDEBUG /MD /EHsc
#include <math.h>
#pragma intrinsic(sin, cos, atan2)
class AptValue { public: float toNumber(); };
extern AptValue* g_bfmeFallbackDB;
extern AptValue** g_bfmeArr1233;
extern int g_bfmeCount1233;
AptValue* __cdecl Rva008A4EA0MakeFloat(float value);
AptValue* aptMathAtan2(void* self, int argc)
{
	if (argc < 2)
		return g_bfmeFallbackDB;
	AptValue* top = g_bfmeArr1233[g_bfmeCount1233 - 1];
	AptValue* second = g_bfmeArr1233[g_bfmeCount1233 - 2];
	float x = second->toNumber();
	float y = top->toNumber();
	return Rva008A4EA0MakeFloat((float)atan2(y, x));
}
