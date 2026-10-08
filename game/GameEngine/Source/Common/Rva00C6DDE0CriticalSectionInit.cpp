// cl: /O2 /MD /Iinputs/reference/shims/sweep
#include <windows.h>

CRITICAL_SECTION g_bfmeRva012D6DE0CriticalSection;
// Retail .data VA 0x012D6DF8 (initialised 1): armed flag the atexit shutdown
// 0x00C71040 clears and the device-reset path 0x0090F050 reads.
bool g_012D6DF8 = true;
void Rva00C71040Shutdown();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void bfmeRva00C6DDE0InitializeCriticalSection()
{
    InitializeCriticalSection(&g_bfmeRva012D6DE0CriticalSection);
    atexit(Rva00C71040Shutdown);
}
