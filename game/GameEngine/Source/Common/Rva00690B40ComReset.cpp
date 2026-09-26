// Open-BFME5: clean C++ conversion of the COM reference reset.

extern "C" __declspec(dllimport) void __stdcall CoUninitialize(void);
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

struct Rva00690B40Unknown;
typedef unsigned long (__stdcall *Rva00690B40Release)(Rva00690B40Unknown *);

struct Rva00690B40Unknown
{
    Rva00690B40Release *vtable;
};

class Rva00690B40Owner
{
public:
    void reset();

private:
    char m_pad00[0x0C];
    int m_comInitialized;
    Rva00690B40Unknown *m_unknown;
};

void Rva00690B40Owner::reset()
{
    Rva00690B40Unknown *unknown = m_unknown;
    if (unknown != 0) {
        unknown->vtable[2](unknown);
        m_unknown = 0;
    }
    if (m_comInitialized >= 0) {
        CoUninitialize();
        _ReadWriteBarrier();
    }
}
