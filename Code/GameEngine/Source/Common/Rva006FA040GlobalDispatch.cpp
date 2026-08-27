// Open-BFME: guarded global virtual dispatch reconstructed from retail RVA 0x006FA040.

class Rva006FA040Target
{
public:
#define RVA006FA040_SLOT(n) virtual void slot##n(void) = 0;
    RVA006FA040_SLOT(0)
    RVA006FA040_SLOT(1)
    RVA006FA040_SLOT(2)
    RVA006FA040_SLOT(3)
    RVA006FA040_SLOT(4)
    RVA006FA040_SLOT(5)
    RVA006FA040_SLOT(6)
    RVA006FA040_SLOT(7)
    RVA006FA040_SLOT(8)
    RVA006FA040_SLOT(9)
    RVA006FA040_SLOT(10)
#undef RVA006FA040_SLOT
    virtual void invoke(int value) = 0;
    virtual void invokeAlternate(int value) = 0;
};

extern Rva006FA040Target *g_Rva012F6464Target;

void Rva006FA040Invoke(int value)
{
    if (g_Rva012F6464Target != 0)
    {
        g_Rva012F6464Target->invoke(value);
    }
}

void Rva006FA0A0Invoke(int value)
{
    if (g_Rva012F6464Target != 0)
    {
        g_Rva012F6464Target->invokeAlternate(value);
    }
}
