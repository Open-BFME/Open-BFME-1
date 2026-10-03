// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the conditional label store at retail 0x00602DB0, 127 bytes.
// The label arrives by value and is released on both arms; the second
// parameter is never read but is still cleaned up by the callee.
//
// AsciiStringXK is the narrow string retail passed by value here: its copy
// constructor and destructor are the IMPLICIT ones, so the object calls
// AsciiString's inline pair, which forwards to StringBase<char>'s out-of-line
// bodies at 0x00887B60 (copy) and 0x00887940 (releaseBuffer), and `set` is
// AsciiString::set forwarding to 0x00887C90. Naming those three bodies
// directly (a declared-only AsciiStringXK copy ctor/dtor/set) left the object
// referencing names nothing defines.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

struct BfmeBufferXK
{
	int m_bfmeRef;						// +0x00
	short m_bfmeLength;					// +0x04
};

class AsciiStringXK : public AsciiString
{
	// Retail's AsciiString is a plain StringBase<char> (one 4-byte m_data), so
	// deriving adds no data and no vtable: the class is still four bytes.
};

class BfmeStrXK : private AsciiStringXK
{
public:
	BfmeStrXK(const AsciiStringXK &other) : AsciiStringXK(other) {}
	~BfmeStrXK(void) {}

	void bfmeSetXK(const AsciiStringXK &other)
	{
		set(other);
	}
};

class Gen_00602DB0
{
public:
	bool bfmeStoreXK(AsciiStringXK value, int unused);

	char m_bfmePad00[0x0C];					// +0x00
	BfmeStrXK m_bfmeLabel;					// +0x0C
};

// ?bfmeStoreXK@Gen_00602DB0@@QAE_NVAsciiStringXK@@H@Z
bool Gen_00602DB0::bfmeStoreXK(AsciiStringXK value, int unused)
{
	// m_data is private to StringBase<char>; the narrow string is exactly the
	// header pointer at +0x00, which is what the old protected member read.
	const BfmeBufferXK *buffer = *(const BfmeBufferXK *const *)&value;

	if (buffer == 0)
		return false;

	if (buffer->m_bfmeLength == 0)
		return false;

	BfmeStrXK *slot = &m_bfmeLabel;

	slot->bfmeSetXK(value);

	return true;
}
