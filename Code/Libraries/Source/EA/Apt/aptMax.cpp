// ?aptMax@@YAPAVAptValue@@PAXH@Z
// cl: /DNDEBUG /MD /EHsc
class AptValue { public: float toNumber(); };
extern AptValue* g_bfmeFallbackDB;
extern AptValue** g_bfmeArr1233;
extern int g_bfmeCount1233;
AptValue* __cdecl Rva008A4EA0MakeFloat(float value);
AptValue* aptMax(void* self, int argc)
{
	if (argc < 2)
		return g_bfmeFallbackDB;
	AptValue* a = g_bfmeArr1233[g_bfmeCount1233 - 1];
	AptValue* b = g_bfmeArr1233[g_bfmeCount1233 - 2];
	float fa = a->toNumber();
	AptValue* pick = (b->toNumber() > fa) ? a : b;
	float result = pick->toNumber();
	return Rva008A4EA0MakeFloat(result);
}
