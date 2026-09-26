// cl: /EHsc
//
// Retail 0x00C4F76E is an anonymous MSVC 7.1 constructor-cleanup boundary.
// Its parent is not recoverable from the Unwind@ label, so this translation
// unit keeps the host identity anonymous.  The body is the compiler-generated
// vector-destructor cleanup for four 4-byte AsciiString objects at offset
// 0x7c in the host.

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

extern void ascii_string_array_unwind_ext();

class GenAsciiArrayBase
{
public:
	GenAsciiArrayBase();
	virtual ~GenAsciiArrayBase();
};

class GenAsciiArrayHost : public GenAsciiArrayBase
{
public:
	GenAsciiArrayHost();
	char pad[0x78];
	AsciiString values[4];
};

// ??0GenAsciiArrayHost@@QAE@XZ absent-from-retail
GenAsciiArrayHost::GenAsciiArrayHost()
{
	ascii_string_array_unwind_ext();
}
