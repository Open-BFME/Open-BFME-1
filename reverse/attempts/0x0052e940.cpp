// ?BfmeLess0052E940@BfmeNamedInline0052E940@@QBE_NABU1@@Z
// partial score=0.55 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/asciistring_downloadmanager

// Open-BFME7: case-insensitive-string-family lane, sibling of
// Rva0052F070NamedLess.cpp (stashed at reverse/attempts/0x0052f070.cpp).
// Retail 0x0052E940 (56 B) is the THISCALL member form of the same
// "flag first, name second" comparator idiom: this=ecx (the struct holding
// the flag byte at +0 and an AsciiString at +4), one stack argument (the
// other operand), falls back to StringBase<char>::compareNoCase through the
// ILT thunk at 0x00027471 (pinned ?bfmeCallDSC@@YGHPAX@Z). The flag test
// evaluates the STACK argument's flag first (into cl) then `this`'s flag
// second (into dl), matching landed neighbours 0x0052E880/0x0052E8F0 in the
// same dump (S4SortElem12Less0052E880.cpp, Bfme5InsertionSort.cpp).
#include "Common/AsciiString.h"

struct BfmeNamedInline0052E940
{
	bool m_bfmeHasName;			// +0x0
	AsciiString m_bfmeName;			// +0x4

	bool BfmeLess0052E940(const BfmeNamedInline0052E940 &other) const;
};

bool BfmeNamedInline0052E940::BfmeLess0052E940(const BfmeNamedInline0052E940 &other) const
{
	bool bEmpty = (other.m_bfmeHasName == 0);
	bool aEmpty = (m_bfmeHasName == 0);
	if (aEmpty ^ bEmpty)
		return m_bfmeHasName;
	return ((const StringBase<char> *)&m_bfmeName)->compareNoCase(*(const StringBase<char> *)&other.m_bfmeName) < 0;
}
