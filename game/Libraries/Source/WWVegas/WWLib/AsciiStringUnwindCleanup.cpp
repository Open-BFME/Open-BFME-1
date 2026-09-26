// cl: /EHsc
//
// This translation unit owns one anonymous MSVC 7.1 unwind body.  The retail
// boundary at 0x00BFD990 is named only `Unwind@00ffd990`; it has no recoverable
// parent identity.  A by-value AsciiString return with one external action is
// the smallest clean C++ shape that emits the same tagged-string cleanup:
// `mov/test/and`, a jump to the retail AsciiString destructor, and `ret`.
// The host and method are deliberately absent from retail; only their compiler
// local `$L` body is claimed below.

#include "ascii_string.h"

extern void ascii_string_unwind_ext();

class GenAsciiCleanupHost
{
public:
	AsciiString make(const char *text);
};

// ?make@GenAsciiCleanupHost@@QAE?AVAsciiString@@PBD@Z absent-from-retail
AsciiString GenAsciiCleanupHost::make(const char *text)
{
	AsciiString value;
	value = text;
	ascii_string_unwind_ext();
	return value;
}
