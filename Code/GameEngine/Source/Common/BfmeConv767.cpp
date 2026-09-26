// cl: /ICode/Libraries/Source/WWVegas/WWLib
//
// Rva00367E30Logic::rva003870f0, retail 0x003870F0, 45 bytes.
//
// __thiscall AsciiString getter taking const AsciiString& (hidden return
// slot, ret 8): forwards the name to the store at this+0x170 (ILT 0x00014943,
// 0x003636C0) and copy-constructs the result (StringBase<char> 0x00887B60)
// into the return slot. The matched caller Rva003BF540::applyOwner
// (0x003BF190 +0xDA) calls it on TheBfmeGameLogic through ILT 0x000228DB.
// Address-derived name; see reverse/identity_evidence/0x003870F0.md.

#include "ascii_string.h"

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

class BfmeSubDRE
{
public:
	void *bfmeOneDRE(void *what);
};

struct Rva00367E30Logic
{
	AsciiString rva003870f0(const AsciiString &name);

	unsigned char m_head[0x170];
	BfmeSubDRE m_bfmeSub;
};

AsciiString Rva00367E30Logic::rva003870f0(const AsciiString &name)
{
	return *(const AsciiString *)m_bfmeSub.bfmeOneDRE((void *)&name);
}
