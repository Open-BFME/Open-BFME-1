// ?BfmeLess0052F070@@YG_NPBUBfmeNamedInline0052F070@@0@Z
// partial score=0.85 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/asciistring_downloadmanager

// Open-BFME7: case-insensitive-string-family lane. Retail 0x0052F070 (54 B) and
// 0x0052E940 (56 B), both dumped in Code/gen_asm/d_0052bd50.asm, are the same
// shape: a free comparator taking two pointers off the stack (no ecx/this),
// testing a leading flag byte at +0, and falling back to
// StringBase<char>::compareNoCase on a nested AsciiString at +4 through the
// ILT thunk at 0x00027471 (pinned ?bfmeCallDSC@@YGHPAX@Z). Landed neighbour
// S4SortElem12Less0052E880.cpp shows the same "flag first, name second"
// comparator idiom for a different sort-element shape (pointer + int keys);
// here the flag and the name live inline in the same struct, so both operands
// come straight off the stack instead of through a pointer indirection.
// Use the downloadmanager AsciiString/StringBase shim: AsciiString there is a
// single m_text pointer, so a leading bool field aligns the nested string at
// exactly +4, matching retail's "add edi,4" / "lea ecx,[esi+4]".
#include "Common/AsciiString.h"

struct BfmeNamedInline0052F070
{
	bool m_bfmeHasName;			// +0x0
	AsciiString m_bfmeName;			// +0x4
};

bool __stdcall BfmeLess0052F070(const BfmeNamedInline0052F070 *a, const BfmeNamedInline0052F070 *b)
{
	bool bEmpty = (b->m_bfmeHasName == 0);
	bool aEmpty = (a->m_bfmeHasName == 0);
	if ((int)aEmpty ^ (int)bEmpty)
		return a->m_bfmeHasName;
	return ((const StringBase<char> *)&a->m_bfmeName)->compareNoCase(*(const StringBase<char> *)&b->m_bfmeName) < 0;
}
