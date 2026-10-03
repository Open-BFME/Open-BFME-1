// cl: /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5 conversions.

#include "ascii_string.h"

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
// argument through the out-of-line copy constructor (0x00887B60) that
// AsciiString's inline copy constructor forwards to; retail emits that
// constructor call from a member-initializer list (esi-preserving prologue,
// `pop esi; ret 8`), which is why the call cannot be spelled from inside the
// body of a non-constructor member.
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
	// PENDING: the callee is StringBase<char>'s copy constructor, reached from
	// retail's constructor body; a placement new here only matches the bytes
	// with a call to the out-of-line AsciiString copy constructor (0x0005EE50).
	bfmeSetStrUXC(s);
	m_bfmeKind = 2;
	int n = (int)v;
	m_bfme08 = n;
	m_bfme0c = n;
	return this;
}
