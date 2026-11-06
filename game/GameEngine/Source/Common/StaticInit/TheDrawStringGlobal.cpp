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
