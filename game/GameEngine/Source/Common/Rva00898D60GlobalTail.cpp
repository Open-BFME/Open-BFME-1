// Open-BFME: two-global virtual tail chain reconstructed from retail RVA 0x00898D60.

class Rva00898D60Target
{
public:
    virtual void slot0(void) = 0;
    virtual void slot1(void) = 0;
    virtual void invoke(void) = 0;
};

// 0x013379BC is the fallback value database pointer, defined as AptValue *
// by Bfme5AppendFallback8CAFF0.cpp (?g_bfmeFallbackDB@@3PAVAptValue@@A).
class AptValue;
extern AptValue *g_bfmeFallbackDB;
extern Rva00898D60Target *g_Rva01337A20;

void Rva00898D60Invoke(void)
{
    reinterpret_cast<Rva00898D60Target *>(g_bfmeFallbackDB)->invoke();
    g_Rva01337A20->invoke();
}
