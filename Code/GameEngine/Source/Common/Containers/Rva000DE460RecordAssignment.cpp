// stlport
// cl: /DNDEBUG /D_STLP_USE_STATIC_LIB /EHsc

// Opaque 16-byte record assigned at retail 0x000DE460.
// The first member is an AsciiString (+0x00); the second is the canonical
// STLport vector<AsciiString> (+0x04). Calls prove assignment of both.
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct Rva000DE460Record
{
	AsciiString text00;
	std::vector<AsciiString> strings04;

	Rva000DE460Record &operator=( const Rva000DE460Record &that );
};

Rva000DE460Record &Rva000DE460Record::operator=( const Rva000DE460Record &that )
{
	text00 = that.text00;
	strings04 = that.strings04;
	return *this;
}
