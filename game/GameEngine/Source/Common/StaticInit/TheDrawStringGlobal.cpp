// cl: /O2 /Ob0 /MD /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x00C6B960 constructs the global at 0x012F257C and registers
// its TU-local cleanup. Disable inlining to preserve its constructor call.
#include "ascii_string.h"
AsciiString theDrawString;
