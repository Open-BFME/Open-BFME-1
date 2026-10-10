// ?Rva00C6B050@@YAXXZ
// partial score=0.3817 date=2026-10-10
// cl: /O2 /MD
#include <new>

class BfmeD1166
{
public:
    BfmeD1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2,
        unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5,
        unsigned int bitIndex6, unsigned int bitIndex7) throw();
    unsigned int m_bitWords[10];
};

extern BfmeD1166 g_rva012EF648;
extern BfmeD1166 g_rva012EF670;
extern BfmeD1166 g_rva012EF698;
extern unsigned int g_rva012EF6C0[10];

// Open BFME 2: Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp
void Rva00C6B050()
{
    new (&g_rva012EF648) BfmeD1166(0, 40, 41, 42, 43, 44, 39, 116);
    new (&g_rva012EF670) BfmeD1166(0, 46, 47, 48, 49, 50, 45, 117);
    new (&g_rva012EF698) BfmeD1166(0, 52, 53, 54, 55, 56, 51, 118);
    g_rva012EF6C0[0] = 0;
    g_rva012EF6C0[1] = 0;
    g_rva012EF6C0[2] = 0;
    g_rva012EF6C0[3] = 0;
    g_rva012EF6C0[4] = 0;
    g_rva012EF6C0[5] = 0;
    g_rva012EF6C0[6] = 0;
    g_rva012EF6C0[7] = 0;
    g_rva012EF6C0[8] = 0;
    g_rva012EF6C0[9] = 0;
}
