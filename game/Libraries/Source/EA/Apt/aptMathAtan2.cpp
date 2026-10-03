// ?aptMathAtan2@@YAPAVAptValue@@PAXH@Z
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
AptValue* aptMathAtan2(void* self, int argc)
{
	if (argc < 2)
		return g_bfmeFallbackDB;
	AptValue* top = Rva008AE770TheStack.m_rva01338750[Rva008AE770TheStack.m_count - 1];
	AptValue* second = Rva008AE770TheStack.m_rva01338750[Rva008AE770TheStack.m_count - 2];
	float x = second->toNumber();
	float y = top->toNumber();
	return Rva008A4EA0MakeFloat((float)atan2(y, x));
}
