// ?aptMathRound@@YAPAVAptValue@@PAXH@Z
// cl: /DNDEBUG /MD /EHsc
class AptValue { public: float toNumber(); };
// 0x008A11E0 is matched in functions.csv as AptInteger::Create returning
// AptInteger* (Libraries/Source/EA/Apt/AptIntegerCreate.cpp), so the local
// declaration spells that return type and the uses cast, as the other Apt
// translation units do.
class AptInteger { public: static AptInteger* Create(int value); };
extern AptValue* g_bfmeFallbackDB;
struct Rva008AE770Stack
{
	int m_count;
	int m_rva0133874C;
	AptValue** m_rva01338750;
};
extern Rva008AE770Stack Rva008AE770TheStack;
extern const float BfmeZeroRange;
extern const float g_rva0107533C;
AptValue* aptMathRound(void* self, int argc)
{
	if (argc <= 0)
		return g_bfmeFallbackDB;
	AptValue** args = Rva008AE770TheStack.m_rva01338750;
	float v = args[Rva008AE770TheStack.m_count - 1]->toNumber();
	if (v > BfmeZeroRange) {
		v += g_rva0107533C;
		return (AptValue*)AptInteger::Create((int)v);
	}
	v -= g_rva0107533C;
	return (AptValue*)AptInteger::Create((int)v);
}

// Shared readonly float at retail VA 0x0107533C: 00 00 00 3F (0.5f).
// aptMathRound at RVA 0x008A4E40 uses fadd/fsub dword at +0x2F/+0x44.
// No original EA name is proven. Keep the definition after the memory uses.
extern const float g_rva0107533C = 0.5f;
