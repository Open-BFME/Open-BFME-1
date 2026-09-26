// cl: /DNDEBUG /MD /EHsc
// RVA 0x0088C4E0: resolve the debug initializer and tail-call it.
#include "debug.h"

extern "C" __declspec(dllimport) void *__stdcall GetModuleHandleA(const char *moduleName);
extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(void *module, const char *symbolName);

typedef int (__cdecl *Rva0088C4E0Initializer)();

int rva0088C4E0PostStaticInitLookup()
{
    void *module = GetModuleHandleA(0);
    Rva0088C4E0Initializer initializer =
        (Rva0088C4E0Initializer)GetProcAddress(module, "?PostStaticInit@Debug@@CAXXZ");
    if (!initializer)
        initializer = (Rva0088C4E0Initializer)&Debug::PostStaticInit;
    return initializer();
}
