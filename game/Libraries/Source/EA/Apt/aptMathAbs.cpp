// ?aptMathAbs@@YAPAVAptValue@@PAXH@Z
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: Apt script Math.abs callback (48 B gap): argc<1 returns the
// fallback value else the top stack value converted and wrapped.
#include <math.h>
#pragma intrinsic(atan, log, sqrt, tan, abs)
class AptValue { public: float toNumber(); int toInteger() const; };
extern AptValue* g_bfmeFallbackDB;
struct Rva008AE770Stack
{
	int m_count;
	int m_rva0133874C;
	AptValue** m_rva01338750;
};

extern Rva008AE770Stack Rva008AE770TheStack;
AptValue* __cdecl Rva008A4EA0MakeFloat(float value);
// Retail call at RVA 0x008A4F87 reaches the existing factory at
// 0x008A11E0 with one integer and caller cleanup; its result is a pointer.
class AptInteger { public: static AptInteger *Create(int value); };
AptValue* aptMathAbs(void* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	AptValue** args = Rva008AE770TheStack.m_rva01338750;
	int v = args[Rva008AE770TheStack.m_count - 1]->toInteger();
	return reinterpret_cast<AptValue *>(AptInteger::Create(abs(v)));
}
