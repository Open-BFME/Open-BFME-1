// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// By-value AsciiString getter, RVA 0x001E2640, 35 bytes: copies the string at
// this+0x80 into the caller's return slot through the out-of-line
// StringBase<char> copy constructor (0x00887B60) and returns it (ret 4).
// Its ?dup_ row used to borrow PeerDefs.cpp's
// GameSpyInfo::getCachedLocalPlayerStats, which copies a PSPlayerStats from
// the same offset instead. It sits among the WeaponTemplate bodies
// (0x001E2670 bfmeRangeBase, 0x001E2730 getAttackRange). Identity not
// recovered: the owner is named for the address.
#include "ascii_string.h"

class Rva001E2640Owner
{
public:
	AsciiString rva001E2640() const;

private:
	char m_unknown00[0x80];
	AsciiString m_text;						// +0x80
};

AsciiString Rva001E2640Owner::rva001E2640() const
{
	return m_text;
}
