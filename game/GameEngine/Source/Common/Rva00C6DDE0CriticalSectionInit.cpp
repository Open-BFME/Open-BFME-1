// cl: /O2 /MD
#include <windows.h>

extern CRITICAL_SECTION g_bfmeRva012D6DE0CriticalSection;
void Rva00C71040Shutdown();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void bfmeRva00C6DDE0InitializeCriticalSection()
{
    InitializeCriticalSection(&g_bfmeRva012D6DE0CriticalSection);
    atexit(Rva00C71040Shutdown);
}
