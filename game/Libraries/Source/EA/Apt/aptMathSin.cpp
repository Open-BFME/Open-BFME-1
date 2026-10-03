// ?aptMathSin@@YAPAVAptValue@@PAXH@Z
// cl: /DNDEBUG /MD /EHsc
#include <math.h>
#pragma intrinsic(sin, cos, atan2)
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
AptValue* aptMathSin(void* self, int argc)
{
	if (argc < 1)
		return g_bfmeFallbackDB;
	AptValue** args = Rva008AE770TheStack.m_rva01338750;
	float v = args[Rva008AE770TheStack.m_count - 1]->toNumber();
	return Rva008A4EA0MakeFloat((float)sin(v));
}
