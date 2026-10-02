// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Include/Precompiled /Igame/GameEngine/Source/Common/System /Igame/Libraries/Source/WWVegas/WWLib
//
// Destructor of the 0x0040EE10 owner. Body is the two cleanups (stop-movie
// then delete-views), then UnicodeString + two AsciiString members, then the
// SubsystemInterface base -- the real class, since the base destructor body at
// 0x009A1A40 is ??1SubsystemInterface@@UAE@XZ.  Its vptr + m_name make it eight
// bytes, which is what puts the first pad at +0x08.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h

#include "PreRTS.h"

#include "subsystem_interface.h"

#include "string_base.h"

#include "ascii_string.h"

#include "unicode_string.h"

template <int N>
class BfmeGapF6D0
{
public:
	char m_bytes[N];
};

class BfmeObjEE : public SubsystemInterface
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
