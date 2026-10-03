// ?aptMax@@YAPAVAptValue@@PAXH@Z
// cl: /DNDEBUG /MD /EHsc
class AptValue { public: float toNumber(); };
extern AptValue* g_bfmeFallbackDB;
struct Rva008AE770Stack
{
	int m_count;
	int m_rva0133874C;
	AptValue** m_rva01338750;
};
extern Rva008AE770Stack Rva008AE770TheStack;
AptValue* __cdecl Rva008A4EA0MakeFloat(float value);
AptValue* aptMax(void* self, int argc)
{
	if (argc < 2)
		return g_bfmeFallbackDB;
	AptValue* a = Rva008AE770TheStack.m_rva01338750[Rva008AE770TheStack.m_count - 1];
	AptValue* b = Rva008AE770TheStack.m_rva01338750[Rva008AE770TheStack.m_count - 2];
	float fa = a->toNumber();
	AptValue* pick = (b->toNumber() > fa) ? a : b;
	float result = pick->toNumber();
	return Rva008A4EA0MakeFloat(result);
}
