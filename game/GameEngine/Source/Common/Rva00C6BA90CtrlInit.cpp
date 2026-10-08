// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00C6BA90 (22 B) initializes the global UnicodeString ctrl at VA 0x012F3AFC:
// it calls the canonical out-of-line UnicodeString default constructor through ILT
// 0x00041C95 -> 0x00083D10 on that object, then registers the cleanup 0x00C70140
// (bfmeForward_00C70140) with atexit. The global itself stays defined in
// KeyboardOptionsMenu.cpp; this TU spells the initializer as a function.

#include "unicode_string.h"

inline void *operator new(unsigned int, void *place) { return place; }

void bfmeForward_00C70140(void);

extern UnicodeString ctrl;

void rva00C6BA90Initialize(void)
{
	new (&ctrl) UnicodeString;
	atexit((void (*)(void))bfmeForward_00C70140);
}
