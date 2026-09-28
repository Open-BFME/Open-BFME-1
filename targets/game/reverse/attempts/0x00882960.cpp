// ?_Allocate@MemoryPool@@YAPAXIW4AllocType@1@@Z
// partial score=0.6751152073732719 date=2026-09-28
// cl: /O2 /DNDEBUG /MD /Igame/GameEngine/Source/Common/System
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
#include <string.h>
#pragma intrinsic(memset)
extern "C" __declspec(dllimport) void *__stdcall HeapAlloc(void *, unsigned long, unsigned int);
// Retail helper requires EAX=count and stack=index; this is an unresolved draft ABI.
void rva00882630(unsigned int index, unsigned int count);
void rva008833C0(void *owner, int type, void *block, unsigned int size, const char *info);
extern unsigned char g_rva0130E9F8;
extern unsigned int g_rva0130E9C0;
extern int Rva0130EA00GuardWords;
extern unsigned int *g_rva0130E9B8;
extern Rva00882BA0Block **g_rva0130E9D0;
extern int g_rva0130E9FC;
extern unsigned int g_rva0130E9F4;
extern unsigned int g_rva00883040Count;
extern unsigned char g_rva0130E9F9;
extern void *g_rva0130E9C4;
extern char g_rva0130E9D8[24];
extern unsigned int *g_rva0130E9BC;
extern unsigned int g_rva0130EA04, g_rva0130EA08, g_rva012D4D0C, g_rva0130E9C8;
extern Rva00882BA0Block **g_rva0130E9CC, **g_rva0130E9D4;
void *MemoryPool::_Allocate(unsigned int size, AllocType type)
{
    if (!size) return 0;
    if (size > 0x10000000) return 0;
    g_rva0130E9F4 += size;
    if (g_rva0130E9F4 > g_rva0130E9C0) g_rva0130E9C0 = g_rva0130E9F4;
    if (size > g_rva00883040Count * 4) {
        EnterCriticalSection(g_rva0130E9D8);
        unsigned int *large = (unsigned int *)HeapAlloc(g_rva0130E9C4, g_rva0130E9F8 ? 8 : 0, size + 4);
        *large = size;
        LeaveCriticalSection(g_rva0130E9D8);
        if (g_rva0130E9F9) rva008833C0((void *)0x0130EA10, type, large + 1, size, 0);
        return large + 1;
    }
    unsigned int index = (size - 1) >> 2;
    EnterCriticalSection(g_rva0130E9D8);
    ++g_rva0130E9BC[index];
    if (g_rva0130E9BC[index] > g_rva0130E9B8[index]) g_rva0130E9B8[index] = g_rva0130E9BC[index];
    if (!g_rva0130E9D4[index]) rva00882630(index, 0x4000 / ((index + 1) * 4));
    Rva00882BA0Block *block = g_rva0130E9D4[index];
    g_rva0130E9D4[index] = block->m_field04;
    block->m_field04 = g_rva0130E9D0[index];
    if (g_rva0130E9D0[index]) g_rva0130E9D0[index]->m_field00 = &block->m_field04;
    block->m_field00 = &g_rva0130E9D0[index];
    Rva00882BA0Block **heads = g_rva0130E9D0;
    int guardWords = Rva0130EA00GuardWords;
    heads[index] = block;
    block->m_size08 = size;
    if (guardWords) memset32((char *)(block + 1) + size, 0x0BADF00D, guardWords * 4);
    if (g_rva0130E9F8) memset(block + 1, 0, size);
    LeaveCriticalSection(g_rva0130E9D8);
    if (g_rva0130E9F9) rva008833C0((void *)0x0130EA10, type, block + 1, size, 0);
    return block + 1;
}
