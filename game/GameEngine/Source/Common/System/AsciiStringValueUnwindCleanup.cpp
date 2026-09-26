// cl: /EHsc
//
// Retail 0x00C45380 is an anonymous MSVC 7.1 cleanup body.  Its boundary is
// named only Unwind@01045380; no parent identity survives the retail image.
// A by-value AsciiString result with a live four-byte pad is the smallest clean
// C++ shape that emits the tagged parameter cleanup at [ebp-0x14].

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

extern void ascii_string_value_unwind_ext(void *value);

class GenAsciiValueCleanupHost
{
public:
	AsciiString make(AsciiString left, const char *right);
};

// ?make@GenAsciiValueCleanupHost@@QAE?AVAsciiString@@V2@PBD@Z absent-from-retail
AsciiString GenAsciiValueCleanupHost::make(AsciiString left, const char *right)
{
	char pad[4];
	ascii_string_value_unwind_ext(pad);
	left += right;
	return left;
}
