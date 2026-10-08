// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00C6BA70 (22 B) initializes the global UnicodeString alt at VA 0x012F3AF8:
// it calls the out-of-line default constructor through ILT 0x00041C95 (0x00083D10)
// and registers the cleanup 0x00C70130 (bfmeForward_00C70130) with atexit. The
// global stays defined in KeyboardOptionsMenu.cpp; this TU spells the initializer.

#include "unicode_string.h"

inline void *operator new(unsigned int, void *place) { return place; }

void bfmeForward_00C70130(void);

extern UnicodeString alt;

void rva00C6BA70Initialize(void)
{
	new (&alt) UnicodeString;
	atexit((void (*)(void))bfmeForward_00C70130);
}
