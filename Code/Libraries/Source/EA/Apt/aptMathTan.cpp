// ?aptMathTan@@YAPAVAptValue@@PAXH@Z
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: Apt script Math.tan callback (byte-identical shape to the
// already-matched aptMathSqrt at 0x008A51E0, the second 50 B half of the
// scanned 98 B gap): argc<1 returns the fallback value else the top stack
// value converted and wrapped through tan().
#include <math.h>
#pragma intrinsic(atan, log, sqrt, tan, abs)
class AptValue { public: float toNumber(); int toInteger(); };
extern AptValue* g_bfmeFallbackDB;
extern AptValue** g_bfmeArr1233;
extern int g_bfmeCount1233;
AptValue* __cdecl Rva008A4EA0MakeFloat(float value);
AptValue* aptMathTan(void* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	float v = g_bfmeArr1233[g_bfmeCount1233 - 1]->toNumber();
	return Rva008A4EA0MakeFloat((float)tan(v));
}
