// ?_Init@MemoryPool@@YAXXZ
// partial score=0.5187165775401069 date=2026-09-28
// cl: /O2 /DNDEBUG /MD /Igame/GameEngine/Source/Common/System
#include "memory_pool.h"
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void *);
extern "C" __declspec(dllimport) void *__stdcall HeapCreate(unsigned long, unsigned int, unsigned int);
extern "C" __declspec(dllimport) int __stdcall HeapSetInformation(void *, int, void *, unsigned int);
extern "C" __declspec(dllimport) void *__stdcall HeapAlloc(void *, unsigned long, unsigned int);
void j_0001307f();
// Unresolved private ABI: retail takes count in EAX and index on the stack.
void rva00882630(unsigned int index, unsigned int count);
extern int g_rva0130E9FC;
extern unsigned int g_rva00883040Count;
extern unsigned int g_rva0130EA04;
extern unsigned int *g_rva0130E9F0;
extern unsigned int Rva0130EA00GuardWords;
extern char g_rva0130E9D8[24];
extern void *g_rva0130E9C4;
extern void *g_rva0130E9D4, *g_rva0130E9D0, *g_rva0130E9CC, *g_rva0130E9BC, *g_rva0130E9B8;
void MemoryPool::_Init()
{
    if (g_rva0130E9FC) { ++g_rva0130E9FC; return; }
    j_0001307f();
    ++g_rva0130E9FC;
    InitializeCriticalSection(g_rva0130E9D8);
    unsigned int count = g_rva00883040Count;
    unsigned int bytes = (count * 2 + g_rva0130EA04) * 4;
    if (g_rva0130E9F0) {
        for (unsigned int i = 0; i < count; ++i)
            bytes += g_rva0130E9F0[i] * (i + 4 + 2 * Rva0130EA00GuardWords) * 4;
    }
    g_rva0130E9C4 = HeapCreate(5, bytes, 0);
    unsigned int mode = 2;
    HeapSetInformation(g_rva0130E9C4, 0, &mode, 4);
    g_rva0130E9D4 = HeapAlloc(g_rva0130E9C4, 8, g_rva00883040Count * 4);
    g_rva0130E9D0 = HeapAlloc(g_rva0130E9C4, 8, g_rva00883040Count * 4);
    g_rva0130E9CC = HeapAlloc(g_rva0130E9C4, 8, g_rva0130EA04 * 4);
    g_rva0130E9BC = HeapAlloc(g_rva0130E9C4, 8, g_rva00883040Count * 4);
    g_rva0130E9B8 = HeapAlloc(g_rva0130E9C4, 8, g_rva00883040Count * 4);
    if (g_rva0130E9F0) {
        for (unsigned int i = 0; i < g_rva00883040Count; ++i) {
            unsigned int n = g_rva0130E9F0[i];
            if (n) rva00882630(i, n);
        }
    }
}
