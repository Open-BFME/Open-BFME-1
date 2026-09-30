// Open-BFME: shutdown helper reconstructed from retail RVA 0x00C71040.

#include <windows.h>


extern CRITICAL_SECTION g_bfmeRva012D6DE0CriticalSection;
extern bool g_012D6DF8;

void Rva00C71040Shutdown()
{
    DeleteCriticalSection(&g_bfmeRva012D6DE0CriticalSection);
    g_012D6DF8 = 0;
}
