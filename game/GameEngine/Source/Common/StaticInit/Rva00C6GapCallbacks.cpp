// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "ascii_string.h"

// Retail CRT cleanup callbacks. The initializers at 00C6A8F0 and 00C6A910
// register these exact entry points, and their globals occupy 012ED4EC/F0.
extern AsciiString g_rva012ED4EC;
extern AsciiString g_rva012ED4F0;

void Rva00C6FC60Release()
{
    g_rva012ED4EC.~AsciiString();
}

void Rva00C6FC70Release()
{
    g_rva012ED4F0.~AsciiString();
}

// CRT initializer table slot RVA 00EA5E28 points to 00C6E380.
// The registered callback is independently matched at 00C71600.
extern "C" int __cdecl atexit(void (__cdecl *callback)());
void bfmeGoDXE();

void Rva00C6E380Register()
{
    atexit(bfmeGoDXE);
}
