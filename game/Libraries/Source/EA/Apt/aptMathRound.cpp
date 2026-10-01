// ?aptMathRound@@YAPAVAptValue@@PAXH@Z
// cl: /DNDEBUG /MD /EHsc
class AptValue { public: float toNumber(); };
class AptInteger { public: static AptValue* Create(int value); };
extern AptValue* g_bfmeFallbackDB;
extern AptValue** g_bfmeArr1233;
struct Rva008AE770Stack { int m_count; };
extern Rva008AE770Stack Rva008AE770TheStack;
extern const float BfmeZeroRange;
extern const float g_bfmeK1253;
AptValue* aptMathRound(void* self, int argc)
{
	if (argc <= 0)
		return g_bfmeFallbackDB;
	float v = g_bfmeArr1233[Rva008AE770TheStack.m_count - 1]->toNumber();
	if (v > BfmeZeroRange) {
		v += g_bfmeK1253;
		return AptInteger::Create((int)v);
	}
	v -= g_bfmeK1253;
	return AptInteger::Create((int)v);
}
