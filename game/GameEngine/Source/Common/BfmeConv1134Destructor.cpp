// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Destructor of BfmeA1134. The constructor TU zeros the same slots that the
// string default ctor would; this TU is the unwind: five AsciiString members
// in reverse declaration order, then the SubsystemInterface base.

#include "string_base.h"

#include "ascii_string.h"

// The base is the real SubsystemInterface, not a TU-local stand-in: retail's
// 0x009A1A40 body is its destructor, and the header's `AsciiString m_name` at
// +0x04 is the same four bytes the old `int m_bfme04` placeholder stood for.
typedef bool Bool;
#include "System/subsystem_interface.h"

template <int N>
class BfmeGap1134
{
public:
	char m_bytes[N];
};

class BfmeA1134 : public SubsystemInterface
{
public:
	virtual ~BfmeA1134();

	AsciiString m_at08;
	AsciiString m_at0c;
	AsciiString m_at10;
	BfmeGap1134<0xC> m_pad14;
	AsciiString m_at20;
	BfmeGap1134<0x78> m_pad24;
	AsciiString m_at9c;
};

// ??1BfmeA1134@@UAE@XZ
BfmeA1134::~BfmeA1134()
{
}
