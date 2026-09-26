// Open-BFME: two-global virtual tail chain reconstructed from retail RVA 0x00898D60.

class Rva00898D60Target
{
public:
    virtual void slot0(void) = 0;
    virtual void slot1(void) = 0;
    virtual void invoke(void) = 0;
};

extern Rva00898D60Target *g_Rva013379BC;
extern Rva00898D60Target *g_Rva01337A20;

void Rva00898D60Invoke(void)
{
    g_Rva013379BC->invoke();
    g_Rva01337A20->invoke();
}
