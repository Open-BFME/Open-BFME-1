// Identity: retail export ordinal 1363 names MemoryPool::_Free at RVA 00882BA0.
// The 12-byte block links and size are witnessed by this body and allocator siblings.
// The tracker callee is the landed Rva008838F0Owner::rva008839B0.
// cl: /O2 /DNDEBUG /MD
#include "memory_pool.h"
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *);
extern "C" __declspec(dllimport) int __stdcall HeapFree(void *, unsigned long, void *);
void memset32(void *, int, unsigned int);
class Rva008838F0Owner { public: void rva008839B0(int, void *); };
struct Rva00882BA0Block {
    Rva00882BA0Block **m_field00;
    Rva00882BA0Block *m_field04;
    unsigned int m_size08;
};
extern int g_rva0130E9FC;
extern unsigned int g_rva0130E9F4;
extern unsigned int g_rva00883040Count;
extern unsigned char g_rva0130E9F9;
extern void *g_rva0130E9C4;
extern char g_rva0130E9D8[24];
extern unsigned int *g_rva0130E9BC;
extern unsigned int g_rva0130EA04, g_rva0130EA08, g_rva012D4D0C, g_rva0130E9C8;
extern Rva00882BA0Block **g_rva0130E9CC, **g_rva0130E9D4;
void MemoryPool::_Free(void *ptr, AllocType type)
{
    if (!ptr || !g_rva0130E9FC) return;
    unsigned int *large = (unsigned int *)ptr - 1;
    unsigned int size = *large;
    g_rva0130E9F4 -= size;
    if (size > g_rva00883040Count * 4) {
        if (g_rva0130E9F9) ((Rva008838F0Owner *)0x0130EA10)->rva008839B0(type, ptr);
        EnterCriticalSection(g_rva0130E9D8);
        HeapFree(g_rva0130E9C4, 0, large);
        LeaveCriticalSection(g_rva0130E9D8);
        return;
    }
    Rva00882BA0Block *block = (Rva00882BA0Block *)ptr - 1;
    --g_rva0130E9BC[(block->m_size08 - 1) >> 2];
    if (g_rva0130E9F9) ((Rva008838F0Owner *)0x0130EA10)->rva008839B0(-666, block + 1);
    EnterCriticalSection(g_rva0130E9D8);
    *block->m_field00 = block->m_field04;
    if (block->m_field04) block->m_field04->m_field00 = block->m_field00;
    unsigned int count = g_rva0130EA04;
    block->m_field00 = 0;
    if (count) {
        memset32(block + 1, 0xDEADC0DE, size);
        if (size >= g_rva0130EA08 && size <= g_rva012D4D0C) {
            Rva00882BA0Block *old = g_rva0130E9CC[g_rva0130E9C8];
            g_rva0130E9CC[g_rva0130E9C8] = block;
            block = old;
            if (++g_rva0130E9C8 == count) g_rva0130E9C8 = 0;
            if (!block) { LeaveCriticalSection(g_rva0130E9D8); return; }
        }
    }
    unsigned int index = (block->m_size08 - 1) >> 2;
    block->m_field04 = g_rva0130E9D4[index];
    g_rva0130E9D4[index] = block;
    LeaveCriticalSection(g_rva0130E9D8);
}

