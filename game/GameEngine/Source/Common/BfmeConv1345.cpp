// cl: /Iinputs/reference/shims/stringbaseascii /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5 conversions.

#include "Common/AsciiString.h"

struct BfmeVecUXA
{
	float m_bfmeX;
	float m_bfmeY;
};

int bfmeCrossUXA(const BfmeVecUXA *a, const BfmeVecUXA *b, const BfmeVecUXA *c)
{
	return (int)((c->m_bfmeY - a->m_bfmeY) * (b->m_bfmeX - a->m_bfmeX)
		- (b->m_bfmeY - a->m_bfmeY) * (c->m_bfmeX - a->m_bfmeX));
}

extern "C" __declspec(dllimport) void __cdecl fclose(void *p);

// The +0x10 member is retail's StringBase<char>: bfmeGoUXB clears it through
// the out-of-line releaseBuffer body (0x00887940) that ascii_string.h declares.
class BfmeThingUXB
{
public:
	virtual void bfmeV0UXB() = 0;
	virtual void bfmeDropUXB() = 0;
	void bfmeGoUXB();
	char m_bfmePad[8];
	void *m_bfmeHandle;
	StringBase<char> m_bfmeStr;
};

void BfmeThingUXB::bfmeGoUXB()
{
	if (m_bfmeHandle) {
		fclose(m_bfmeHandle);
		m_bfmeHandle = 0;
	}
	m_bfmeStr.clear();
	bfmeDropUXB();
}

// The +0x00 member is retail's StringBase<char>. bfmeGoUXC builds it from the
// argument through the out-of-line copy constructor (0x00887B60, matched as
// ??0?$StringBase@D@@AAE@ABV0@@Z). The stringbaseascii shim's AsciiString copy
// constructor is a visible delegation to StringBase<char>'s, so the qualified
// constructor call inlines away and this object references the retail body
// itself rather than an undefined placeholder name -- the respelling
// BfmeConv526 uses for the same private body.
class BfmeThingUXC
{
public:
	BfmeThingUXC *bfmeGoUXC(const char *s, float v);
	void bfmeSetStrUXC(const char *s);
	AsciiString m_bfmeStr;
	int m_bfmeKind;
	int m_bfme08;
	int m_bfme0c;
};

BfmeThingUXC *BfmeThingUXC::bfmeGoUXC(const char *s, float v)
{
	m_bfmeStr.AsciiString::AsciiString(*(const AsciiString *)s);
	m_bfmeKind = 2;
	int n = (int)v;
	m_bfme08 = n;
	m_bfme0c = n;
	return this;
}