// ?aptMathPow@@YAPAVAptValue@@PAXH@Z
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: Apt script Math.pow callback; the top stack value is the base.
#include <math.h>
class AptValue { public: float toNumber(); };
extern AptValue* g_bfmeFallbackDB;
extern AptValue** g_bfmeArr1233;
extern int g_bfmeCount1233;
AptValue* __cdecl Rva008A4EA0MakeFloat(float value);
AptValue* aptMathPow(void* self, int argc)
{
	if (argc < 2)
		return g_bfmeFallbackDB;
	AptValue* a = g_bfmeArr1233[g_bfmeCount1233 - 1];
	AptValue* b = g_bfmeArr1233[g_bfmeCount1233 - 2];
	return Rva008A4EA0MakeFloat((float)pow(a->toNumber(), b->toNumber()));
}
