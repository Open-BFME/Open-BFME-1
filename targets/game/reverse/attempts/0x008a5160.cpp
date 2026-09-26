// ?aptMathPow@@YAPAVAptValue@@PAXH@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: Apt script Math.pow callback (79 B gap).
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
	AptValue* a = g_bfmeArr1233[g_bfmeCount1233 - 2];
	AptValue* b = g_bfmeArr1233[g_bfmeCount1233 - 1];
	float base = a->toNumber();
	float exponent = b->toNumber();
	return Rva008A4EA0MakeFloat((float)pow(base, exponent));
}
