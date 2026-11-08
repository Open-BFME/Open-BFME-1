// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x008AB8B0..0x008AB8CE. The installed vtable's first slot
// points at the separate one-byte body at 0x008AB8D0.
// Retail 0x01136854 is the vftable COMDAT ??_7BfmeBase1286@@6B@ (emitted by Rva008BE450Constructor/
// Rva008BE450DerivedDestructor); the stand-in name g_bfmeBase1285Vtable resolved nothing.
extern "C" const char __identifier("??_7BfmeBase1286@@6B@")[];

class Rva008AB8B0Base
{
public:
    Rva008AB8B0Base();
    void rva008ab8d0();
private:
    const void *m_vtable;
    int m_04;
    int m_08;
    void *m_0c;
    void *m_10;
    unsigned char m_14;
};

Rva008AB8B0Base::Rva008AB8B0Base()
    : m_vtable((const void *)__identifier("??_7BfmeBase1286@@6B@")), m_04(-1), m_08(0),
      m_0c(0), m_10(0), m_14(0)
{
}

// Vtable 0x01136854 slot 0 points here; its semantic name is not witnessed.
void Rva008AB8B0Base::rva008ab8d0()
{
}
