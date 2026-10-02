// cl: -Iinputs/reference/shims/stringbaseascii -Igame/Libraries/Source/WWVegas/WWLib

// Retail 0x00664E20 copy-constructs in place at this+4 -- `push edx; lea ecx,
// [esi+4]; call` -- one bare thiscall call with no temporary, so the callee is
// StringBase<char>'s copy constructor, the body the ledger owns as
// ??0?$StringBase@D@@AAE@ABV0@@Z at 0x00887B60 (StringBase.cpp). It is private
// with only AsciiString and UnicodeString as friends, so this spells the call
// the way inputs/reference/shims/stringbaseascii already spells it: the shim's
// public AsciiString(const AsciiString &) is a visible delegation to
// StringBase<char>'s, so the qualified constructor call inlines away and this
// object references the retail body itself instead of a placeholder name.
#include "Common/AsciiString.h"

struct BfmeSubBSF
{
	AsciiString m_name;
};

class BfmeThingBSF
{
public:
	BfmeThingBSF *bfmeGoBSF(unsigned short *src, void *what);

	unsigned short m_bfmeKey;
	unsigned char m_bfmePad[2];
	BfmeSubBSF m_bfmeSub;
};

BfmeThingBSF *BfmeThingBSF::bfmeGoBSF(unsigned short *src, void *what)
{
	m_bfmeKey = *src;
	m_bfmeSub.m_name.AsciiString::AsciiString(*(const AsciiString *)what);
	return this;
}