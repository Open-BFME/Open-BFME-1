// ?aptMathCeil@@YAPAVAptValue@@PAXH@Z
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: Apt script Math.ceil callback (59 B gap): argc<1 returns the
// fallback value else the top stack value converted and wrapped.
extern "C" double __cdecl ceil(double);
class AptValue { public: float toNumber(); int toInteger(); };
extern AptValue* g_bfmeFallbackDB;
extern AptValue** g_bfmeArr1233;
extern int g_bfmeCount1233;
AptValue* __cdecl Rva008A4EA0MakeFloat(float value);
AptValue* __cdecl Rva008B6D70MakeValue(int value);
AptValue* aptMathCeil(void* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	float v = g_bfmeArr1233[g_bfmeCount1233 - 1]->toNumber();
	return Rva008A4EA0MakeFloat((float)ceil(v));
}
