// cl: /MD /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x00C6B960 constructs the global at 0x012F257C and registers
// its TU-local cleanup. Disable inlining to preserve its constructor call.
#include "ascii_string.h"
AsciiString theDrawString;
AsciiString theInputString;
// ?RvaObject012ED828@@3VAsciiString@@A at retail VA 0x012ED828: empty
// AsciiString (retail .data holds zeros; see
// targets/game/reverse/identity_evidence/012ed828-asciistring.md).
// Homed here with the other orphan AsciiString globals; used only by
// address from Rva00C6FCC0Cleanup.cpp.
AsciiString RvaObject012ED828;
// ?RvaObject012ED82C@@3VAsciiString@@A at retail VA 0x012ED82C: empty
// AsciiString (retail .data holds zeros; see
// targets/game/reverse/identity_evidence/012ed82c-asciistring.md).
// Adjacent sibling of RvaObject012ED828, same home and use pattern.
AsciiString RvaObject012ED82C;
// ?RvaObject012EF180@@3VAsciiString@@A at retail VA 0x012EF180: empty
// AsciiString (retail .data holds zeros; see
// targets/game/reverse/identity_evidence/012ef180-asciistring.md).
// Same orphan pattern; used only by address from Rva00C6FCC0Cleanup.cpp.
AsciiString RvaObject012EF180;
// ?RvaObject012EF1E4@@3VAsciiString@@A at retail VA 0x012EF1E4: empty
// AsciiString (retail .data holds zeros; see
// targets/game/reverse/identity_evidence/012ef1e4-asciistring.md).
// Same orphan pattern; used only by address from Rva00C6FCC0Cleanup.cpp.
AsciiString RvaObject012EF1E4;
