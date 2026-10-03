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
struct Rva008AE770Stack
{
	int m_count;
	int m_rva0133874C;
	AptValue** m_rva01338750;
};

extern Rva008AE770Stack Rva008AE770TheStack;
AptValue* __cdecl Rva008A4EA0MakeFloat(float value);
AptValue* aptMathTan(void* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	AptValue** args = Rva008AE770TheStack.m_rva01338750;
	float v = args[Rva008AE770TheStack.m_count - 1]->toNumber();
	return Rva008A4EA0MakeFloat((float)tan(v));
}
