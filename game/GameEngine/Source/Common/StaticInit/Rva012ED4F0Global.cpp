// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x00C6A910 is the namespace-scope dynamic initializer for the
// AsciiString global at 0x012ED4F0: default-constructs it and registers the
// TU-local atexit cleanup. Defining the global here lets MSVC emit those
// bytes as its compiler-local _$E1; the ledger row names that COFF symbol
// via object-symbol=_$E1.
#include "ascii_string.h"
AsciiString g_rva012ED4F0;
