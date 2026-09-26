// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x008AB8B0..0x008AB8CE. The installed vtable's first slot
// points at the separate one-byte body at 0x008AB8D0.
extern char g_bfmeBase1285Vtable;

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
    : m_vtable(&g_bfmeBase1285Vtable), m_04(-1), m_08(0),
      m_0c(0), m_10(0), m_14(0)
{
}
