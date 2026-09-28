// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x00C6AFE0 is the namespace-scope dynamic initializer for the
// AsciiString array global at 0x012EF430 (0x20 elements): array-constructs it
// via ??_L@YGXPAXIHP6EX0@Z1@Z and registers the TU-local atexit cleanup.
// Defining the global here lets MSVC emit those bytes as its compiler-local
// _$E1; the ledger row names that COFF symbol via object-symbol=_$E1.
#include "ascii_string.h"
AsciiString g_rva012EF430[0x20];
