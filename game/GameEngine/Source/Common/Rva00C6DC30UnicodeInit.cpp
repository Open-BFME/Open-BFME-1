// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00C6DC30 is the dynamic initializer of the exported
// UnicodeString::TheEmptyString (export ?TheEmptyString@UnicodeString@@2V1@B,
// RVA 0x00F36E54): it calls the UnicodeString default ctor through
// ILT 0x00041C95 -> 0x00083D10 on VA 0x01336E54 and registers the 0x00C70F10
// cleanup. This TU is the one definition of that datum.
#include "unicode_string.h"
const UnicodeString UnicodeString::TheEmptyString;
