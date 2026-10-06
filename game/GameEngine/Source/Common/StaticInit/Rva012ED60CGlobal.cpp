// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x00C6AA70 is the namespace-scope dynamic initializer for the
// AsciiString global at 0x012ED60C: default-constructs it and registers the
// TU-local atexit cleanup. Defining the global here lets MSVC emit those
// bytes as its compiler-local _$E1; the ledger row names that COFF symbol
// via object-symbol=_$E1.
#include "ascii_string.h"
// The ledger records this cell as TheOptionGroupName: matched parseOptionGroup
// (0x000945A0) assigns it the group's INI token.
AsciiString TheOptionGroupName;
