// cl: /DNDEBUG /MD /EHsc
// Apt Math.pow callback; the volatile stack-slot read preserves operand order.
// Retail ends at 0x008A51AE; 0x008A51AF is int3 padding.
#include <math.h>
class AptValue { public: float toNumber(); };
extern AptValue* g_bfmeFallbackDB;
extern AptValue** g_bfmeArr1233;
struct Rva008AE770Stack { int m_count; };
extern Rva008AE770Stack Rva008AE770TheStack;
AptValue* __cdecl Rva008A4EA0MakeFloat(float value);
AptValue* aptMathPow(void* self, int argc)
{
	if (argc < 2)
		return g_bfmeFallbackDB;
	AptValue** values = g_bfmeArr1233;
	int count = Rva008AE770TheStack.m_count;
	AptValue* base = *(AptValue* volatile*)(values + count - 1);
	AptValue* exponent = values[count - 2];
	return Rva008A4EA0MakeFloat((float)pow(base->toNumber(), exponent->toNumber()));
}
