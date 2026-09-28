// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x00C6DF30 is the namespace-scope dynamic initializer for the
// StringClass global at 0x01346718: it runs the (0, false) constructor and
// registers the 0x00C712C0 atexit cleanup, which destroys the string.
// Defining the global here lets MSVC emit those bytes as its compiler-local
// _$E1; the ledger row names that COFF symbol via object-symbol=_$E1.
#include "wwstring.h"

StringClass g_bfmeRva01346718Str(0, false);
