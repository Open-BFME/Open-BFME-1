// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00C6BAB0 (22 B) initializes the global UnicodeString shift at VA 0x012F3B00:
// it calls the out-of-line default constructor through ILT 0x00041C95 (0x00083D10)
// and registers the cleanup 0x00C70150 (bfmeForward_00C70150) with atexit. The
// global stays defined in KeyboardOptionsMenu.cpp; this TU spells the initializer.

#include "unicode_string.h"

inline void *operator new(unsigned int, void *place) { return place; }

void bfmeForward_00C70150(void);

extern UnicodeString shift;

void rva00C6BAB0Initialize(void)
{
	new (&shift) UnicodeString;
	atexit((void (*)(void))bfmeForward_00C70150);
}
