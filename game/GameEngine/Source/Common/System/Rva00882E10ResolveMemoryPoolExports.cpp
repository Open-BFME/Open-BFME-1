// ?rva00882E10ResolveMemoryPoolExports@@YAXXZ
// Address-derived startup resolver for the eight MemoryPool exports.
// The retail routine fills the executable's pointer table by name; it does
// not call the exported routines directly.

typedef void *RvaModuleHandle;
typedef void *RvaProcAddress;

extern "C" __declspec(dllimport) RvaModuleHandle __stdcall GetModuleHandleA(const char *name);
extern "C" __declspec(dllimport) RvaProcAddress __stdcall GetProcAddress(RvaModuleHandle module, const char *name);

// The pointer table this routine fills is defined here, once: retail keeps it
// as eight consecutive zero-filled .bss dwords (VA 0x0130E998..0x0130E9B7) and
// this is the only code that writes them; mem_ops.cpp, memory_pool.cpp and the
// CRT shims only read them. Each slot's type is the export stored in it.
extern "C" {
void (__cdecl *g_rva0130E998)(void);                         // _VerifyIntegrity
bool (__cdecl *g_rva0130E99C)(void *);                       // _IsValidBlock
void *(__cdecl *g_rva0130E9A0)(void *, unsigned int, int);   // _Reallocate
void (__cdecl *g_rva0130E9A4)(void);                         // _Exit
void (__cdecl *g_rva0130E9A8)(void);                         // _Init
void (__cdecl *__gameMemFreePtr)(void *, int);               // _Free
unsigned int (__cdecl *g_rva0130E9B0)(void *);               // _GetBlockSize
void *(__cdecl *__gameMemAllocPtr)(unsigned int, int);       // _Allocate
}

typedef void (__cdecl *RvaVoidFn)(void);
typedef bool (__cdecl *RvaIsValidFn)(void *);
typedef void *(__cdecl *RvaReallocFn)(void *, unsigned int, int);
typedef void (__cdecl *RvaFreeFn)(void *, int);
typedef unsigned int (__cdecl *RvaSizeFn)(void *);
typedef void *(__cdecl *RvaAllocFn)(unsigned int, int);

void rva00882E10ResolveMemoryPoolExports()
{
	RvaModuleHandle module = GetModuleHandleA(0);

	g_rva0130E9A8 = (RvaVoidFn)GetProcAddress(module, "?_Init@MemoryPool@@YAXXZ");
	g_rva0130E9A4 = (RvaVoidFn)GetProcAddress(module, "?_Exit@MemoryPool@@YAXXZ");
	__gameMemAllocPtr = (RvaAllocFn)GetProcAddress(module, "?_Allocate@MemoryPool@@YAPAXIW4AllocType@1@@Z");
	g_rva0130E9A0 = (RvaReallocFn)GetProcAddress(module, "?_Reallocate@MemoryPool@@YAPAXPAXIW4AllocType@1@@Z");
	__gameMemFreePtr = (RvaFreeFn)GetProcAddress(module, "?_Free@MemoryPool@@YAXPAXW4AllocType@1@@Z");
	g_rva0130E99C = (RvaIsValidFn)GetProcAddress(module, "?_IsValidBlock@MemoryPool@@YA_NPAX@Z");
	g_rva0130E9B0 = (RvaSizeFn)GetProcAddress(module, "?_GetBlockSize@MemoryPool@@YAIPAX@Z");
	g_rva0130E998 = (RvaVoidFn)GetProcAddress(module, "?_VerifyIntegrity@MemoryPool@@YAXXZ");
}
