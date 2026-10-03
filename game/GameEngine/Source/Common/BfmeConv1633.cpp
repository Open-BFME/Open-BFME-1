// cl: /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5 conversions.
//
// WHAT 0x00887940 IS. The ledger matches that body as
// StringBase<char>::releaseBuffer and exports it there; the definition is
// game/Libraries/Source/string/StringBase.cpp. Releasing the buffer IS what
// this constructor's three calls do, so the three members are the four-byte
// strings ascii_string.h declares (AsciiString adds no data to
// StringBase<char>), and clear() is the header's inline wrapper around
// releaseBuffer -- the same call, spelled through the real header instead of a
// redeclared StringBase. That keeps +0x04, +0x08, +0x0C and +0x10 unchanged.
//
// The one vftable slot stays the address-derived bfmeSlot0VUE: the vftable the
// constructor installs sits at VA 0x010EC780 and its first slot points at
// 0x00415078, unnamed mid-function bytes of
// ?drawContained@Drawable@@AAEXPBUIRegion2D@@@Z, so no real name exists to
// spell. It is defined inline here: retail's copy of that slot is not recovered,
// so the class must not have a key function, or the vftable would reference a
// body nothing defines.

#include "ascii_string.h"

class BfmeOwnVUE
{
public:
	BfmeOwnVUE();
	virtual void bfmeSlot0VUE() {}
	AsciiString m_bfme04;
	AsciiString m_bfme08;
	AsciiString m_bfme0c;
	char m_bfme10;
};

BfmeOwnVUE::BfmeOwnVUE()
	: m_bfme10(0)
{
	m_bfme04.clear();
	m_bfme0c.clear();
	m_bfme08.clear();
}
