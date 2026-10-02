// Open-BFME: global pointer release reconstructed from retail RVA 0x007EB830.

class Rva007EB830Target
{
public:
    virtual void unused0(void);
    virtual void unused1(void);
    virtual void unused2(void);
    virtual void unused3(void);
    virtual void unused4(void);
    virtual void release(int value);
};

struct Rva007EB810Diag;
extern Rva007EB810Diag *g_Va0130A5A0;

void Rva007EB830Release(void)
{
    if (g_Va0130A5A0 != 0)
    {
        reinterpret_cast<Rva007EB830Target *>(g_Va0130A5A0)->release(1);
    }
    g_Va0130A5A0 = 0;
}
