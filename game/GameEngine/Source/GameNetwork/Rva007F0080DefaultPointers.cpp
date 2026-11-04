extern unsigned char g_Va00BEFFE0;
extern unsigned char g_Va00BEFFF0;

extern void *g_0112A5C4[];

// Former ??_7Rva007F0080Owner@@6B@: table is recorded data row ?g_0112A5C4@@3PAPAXA at VA 0x0112A5C4.
class Rva007F0080Owner
{
public:
    Rva007F0080Owner(void *first, void *second);
private:
    void *m_vtable;
    void *m_first;
    void *m_second;
};

Rva007F0080Owner::Rva007F0080Owner(void *first, void *second)
{
    m_vtable = g_0112A5C4;
    m_first = first ? first : reinterpret_cast<void *>(&g_Va00BEFFE0);
    m_second = second ? second : reinterpret_cast<void *>(&g_Va00BEFFF0);
}
