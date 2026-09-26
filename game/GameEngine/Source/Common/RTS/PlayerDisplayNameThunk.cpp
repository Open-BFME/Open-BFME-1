// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME8: Player::getPlayerDisplayName returns the UnicodeString member at
// +8. Carried here, not in ControlBarObserver.cpp, because the seven vendored
// dup-of rows that share that TU's body copy an ASCII string -- they encode
// ??0?$StringBase@D@@AAE@ABV0@@Z (0x00887B60) at the return copy, while this
// wide body encodes ??0?$StringBase@G@@AAE@ABV0@@Z (0x00888400). One compiled
// body cannot carry both displacements.
#include "unicode_string.h"

// Retail inlines the copy constructor, so the return copy reaches the base body
// directly; left declared-only, cl emits a call to ??0UnicodeString@@QAE@ABV0@@Z.
#include "string_base.h"

inline UnicodeString::UnicodeString(const UnicodeString &stringSrc)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		*(const StringBase<unsigned short> *)&stringSrc);
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	UnicodeString getPlayerDisplayName();

private:
	void *m_leading[2];
	UnicodeString m_playerDisplayName;
};

// ?getPlayerDisplayName@Player@@QAE?AVUnicodeString@@XZ
UnicodeString Player::getPlayerDisplayName()
{
	return m_playerDisplayName;
}
