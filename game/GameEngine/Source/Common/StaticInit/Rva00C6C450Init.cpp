// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
extern "C" int __cdecl atexit(void (__cdecl *callback)());
// 0x012F8044 is recorded (DIR32) as ?TheBfmeObject_00C70970@@3VGen_00C70970Target@@A;
// define the storage under that symbol.
// Retire ?g_rva012F8044Object@@3VAsciiString@@A
extern "C" { AsciiString __identifier("?TheBfmeObject_00C70970@@3VGen_00C70970Target@@A")("Zoom"); }
