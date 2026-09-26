// ?aptMathPow@@YAPAVAptValue@@PAXH@Z
// cl: /DNDEBUG /MD /EHsc
#include <math.h>
class AptValue { public: float toNumber(); };
extern AptValue* g_bfmeFallbackDB;
extern AptValue** g_bfmeArr1233;
extern int g_bfmeCount1233;
AptValue* __cdecl Rva008A4EA0MakeFloat(float value);

AptValue* aptMathPow(void* self, int argc)
{
    if (argc < 2)
        return g_bfmeFallbackDB;
    AptValue* exponent = g_bfmeArr1233[g_bfmeCount1233 - 1];
    AptValue* base = g_bfmeArr1233[g_bfmeCount1233 - 2];
    float baseValue = base->toNumber();
    return Rva008A4EA0MakeFloat((float)pow(exponent->toNumber(), baseValue));
}
