// cl: /DNDEBUG /MD /EHsc
struct BfmeStringData3AF0
{
    unsigned short m_refCount;
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
void bfmeGoEMIa();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void bfmeRva00C6DC50InitializeDefaultString()
{
    ++g_bfmeDefaultString1284.m_refCount;
    atexit(bfmeGoEMIa);
}
