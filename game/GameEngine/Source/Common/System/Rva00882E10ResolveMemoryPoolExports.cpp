// ?rva00882E10ResolveMemoryPoolExports@@YAXXZ
// Address-derived startup resolver for the eight MemoryPool exports.
// The retail routine fills the executable's pointer table by name; it does
// not call the exported routines directly.

typedef void *RvaModuleHandle;
typedef void *RvaProcAddress;

extern "C" __declspec(dllimport) RvaModuleHandle __stdcall GetModuleHandleA(const char *name);
extern "C" __declspec(dllimport) RvaProcAddress __stdcall GetProcAddress(RvaModuleHandle module, const char *name);

extern "C" void *g_rva0130E998;
extern "C" void *g_rva0130E99C;
extern "C" void *g_rva0130E9A0;
extern "C" void *g_rva0130E9A4;
extern "C" void *g_rva0130E9A8;
extern "C" void *__gameMemFreePtr;
extern "C" void *g_rva0130E9B0;
extern "C" void *__gameMemAllocPtr;

void rva00882E10ResolveMemoryPoolExports()
{
	RvaModuleHandle module = GetModuleHandleA(0);

	g_rva0130E9A8 = GetProcAddress(module, "?_Init@MemoryPool@@YAXXZ");
	g_rva0130E9A4 = GetProcAddress(module, "?_Exit@MemoryPool@@YAXXZ");
	__gameMemAllocPtr = GetProcAddress(module, "?_Allocate@MemoryPool@@YAPAXIW4AllocType@1@@Z");
	g_rva0130E9A0 = GetProcAddress(module, "?_Reallocate@MemoryPool@@YAPAXPAXIW4AllocType@1@@Z");
	__gameMemFreePtr = GetProcAddress(module, "?_Free@MemoryPool@@YAXPAXW4AllocType@1@@Z");
	g_rva0130E99C = GetProcAddress(module, "?_IsValidBlock@MemoryPool@@YA_NPAX@Z");
	g_rva0130E9B0 = GetProcAddress(module, "?_GetBlockSize@MemoryPool@@YAIPAX@Z");
	g_rva0130E998 = GetProcAddress(module, "?_VerifyIntegrity@MemoryPool@@YAXXZ");
}
