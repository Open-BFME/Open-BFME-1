// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x00C6DF30 is the namespace-scope dynamic initializer for the
// StringClass global at 0x01346718: it runs the (0, false) constructor and
// registers the 0x00C712C0 atexit cleanup, which destroys the string.
// Defining the global here lets MSVC emit those bytes as its compiler-local
// _$E1; the ledger row names that COFF symbol via object-symbol=_$E1.
#include "wwstring.h"

// 0x01346718 is recorded (DIR32) as ?TheBfmeObject_00C712C0@@3VGen_00C712C0Target@@A,
// the name its consumers bind; define the storage under that symbol.
// Retire ?g_bfmeRva01346718Str@@3VStringClass@@A
extern "C" { StringClass __identifier("?TheBfmeObject_00C712C0@@3VGen_00C712C0Target@@A")(0, false); }

// Retail 0x00C6DFD0 initializes the StringClass global at 0x01346E74.
// 0x01346E74 is recorded (DIR32) as ?TheBfmeObject_009372E0@@3VGen_009372E0Target@@A;
// define the storage under that symbol.
// Retire ?g_bfmeRva01346E74Str@@3VStringClass@@A
extern "C" { StringClass __identifier("?TheBfmeObject_009372E0@@3VGen_009372E0Target@@A")(0, false); }
