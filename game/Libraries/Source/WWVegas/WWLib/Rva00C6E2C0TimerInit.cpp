// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
#include "mmsys.h"

// Cleanup at 0x00C71590 calls timeEndPeriod(1). It was ledgered as an alias
// of SysTimeClass's destructor bytes, but retail links without identical-COMDAT
// folding and this initializer registers it as a plain atexit callback, so
// it is defined here beside its only registrar.
void a_00c71590()
{
    timeEndPeriod(1);
}

extern "C" int __cdecl atexit(void (__cdecl *callback)());

void bfmeRva00C6E2C0InitializeTimerResolution()
{
    timeBeginPeriod(1);
    atexit(a_00c71590);
}
