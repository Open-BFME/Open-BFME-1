// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: DisplayString::getText returns UnicodeString member at +4.

#include "unicode_string.h"

// The real DisplayString::getText at 0x00410080 -- carried here, not in
// DisplayStringGetTextThunk.cpp, because the seven vendored dup-of rows that
// share that TU's body copy an ASCII string: retail encodes
// ??0?$StringBase@D@@AAE@ABV0@@Z (0x00887B60) at their return copy, while the
// real UnicodeString-returning body encodes ??0?$StringBase@G@@AAE@ABV0@@Z
// (0x00888400). One compiled body cannot carry both displacements, so this TU
// spells the delegation the wide string needs and the other TU keeps the
// declared-only copy ctor the ASCII dups need.
#include "string_base.h"

inline UnicodeString::UnicodeString(const UnicodeString &stringSrc)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		*(const StringBase<unsigned short> *)&stringSrc);
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	virtual UnicodeString getText();
private:
	UnicodeString m_text;
};

// ?getText@DisplayString@@UAE?AVUnicodeString@@XZ
UnicodeString DisplayString::getText()
{
	return m_text;
}
