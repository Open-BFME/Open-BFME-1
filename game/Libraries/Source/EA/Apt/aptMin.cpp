// ?aptMin@@YAPAVAptValue@@PAXH@Z
// cl: /DNDEBUG /MD /EHsc
class AptValue { public: float toNumber(); };
extern AptValue* g_bfmeFallbackDB;
extern AptValue** g_bfmeArr1233;
struct Rva008AE770Stack { int m_count; };
extern Rva008AE770Stack Rva008AE770TheStack;
AptValue* __cdecl Rva008A4EA0MakeFloat(float value);
AptValue* aptMin(void* self, int argc)
{
	if (argc < 2)
		return g_bfmeFallbackDB;
	AptValue* a = g_bfmeArr1233[Rva008AE770TheStack.m_count - 1];
	AptValue* b = g_bfmeArr1233[Rva008AE770TheStack.m_count - 2];
	float fa = a->toNumber();
	AptValue* pick = (b->toNumber() < fa) ? a : b;
	float result = pick->toNumber();
	return Rva008A4EA0MakeFloat(result);
}
