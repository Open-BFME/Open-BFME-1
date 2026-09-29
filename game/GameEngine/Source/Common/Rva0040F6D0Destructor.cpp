// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Destructor of the 0x0040EE10 owner. Body is the two cleanups (stop-movie
// then delete-views), then UnicodeString + two AsciiString members, then the
// SubsystemInterface base.

#include "string_base.h"

#include "ascii_string.h"

#include "unicode_string.h"

template <int N>
class BfmeGapF6D0
{
public:
	char m_bytes[N];
};

class BfmeBase1134
{
public:
	virtual ~BfmeBase1134();

private:
	int m_bfme04;
};

class BfmeObjEE : public BfmeBase1134
{
public:
	virtual ~BfmeObjEE();
	void bfmeGoEE();
	void bfmeDelViews();

	BfmeGapF6D0<0xA4> m_pad08;
	UnicodeString m_atAC;
	BfmeGapF6D0<0x1C> m_padB0;
	AsciiString m_atCC;
	BfmeGapF6D0<0x1C> m_padD0;
	AsciiString m_atEC;
};

// ??1BfmeObjEE@@UAE@XZ
BfmeObjEE::~BfmeObjEE()
{
	bfmeGoEE();
	bfmeDelViews();
}
