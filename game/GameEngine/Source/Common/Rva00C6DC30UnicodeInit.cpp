// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00C6DC30 calls the matched UnicodeString default ctor through
// ILT 0x00041C95 -> 0x00083D10 on VA 0x01336E54 and registers its matched
// 0x00C70F10 cleanup. The canonical header declares the ctor out of line.
#include "unicode_string.h"
void bfmeForward_00C70F10();
extern "C" int __cdecl atexit(void (__cdecl *)());
void rva00C6DC30Initialize()
{
    const_cast<UnicodeString *>(&UnicodeString::TheEmptyString)->UnicodeString::UnicodeString();
    atexit(bfmeForward_00C70F10);
}
