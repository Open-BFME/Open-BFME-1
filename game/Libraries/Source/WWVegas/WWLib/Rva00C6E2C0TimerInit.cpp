// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
#include "mmsys.h"

// Cleanup at 0x00C71590 calls timeEndPeriod(1).
void a_00c71590();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void bfmeRva00C6E2C0InitializeTimerResolution()
{
    timeBeginPeriod(1);
    atexit(a_00c71590);
}
