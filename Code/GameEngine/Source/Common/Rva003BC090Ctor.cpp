// cl: /DNDEBUG /MD /O2 /EHsc /Ireference/shims/stringinline
// Open-BFME5: VNE-family ctor with AsciiString at +0xC. Retail 0x003BC090, 133B.
// Base unsigned*0.03f clamp inlines; derived vftable then StringBase copy at +0xC.

#include "StringInline.h"

class BfmeBaseVNH
{
public:
	BfmeBaseVNH(unsigned w, char f);
	virtual ~BfmeBaseVNH();
	virtual void handle();

	unsigned m_bfme04;
	char m_bfme08;
};

BfmeBaseVNH::~BfmeBaseVNH()
{
}

BfmeBaseVNH::BfmeBaseVNH(unsigned w, char f)
{
	m_bfme08 = f;
	m_bfme04 = (int)((float)w * 0.03f);
	if (m_bfme04 < 1)
		m_bfme04 = 1;
}

class BfmeRectVNH : public BfmeBaseVNH
{
public:
	BfmeRectVNH(unsigned w, const AsciiString &s, char f);

	AsciiString m_name;
};

// ??0BfmeRectVNH@@QAE@IABVAsciiString@@D@Z
BfmeRectVNH::BfmeRectVNH(unsigned w, const AsciiString &s, char f)
	: BfmeBaseVNH(w, f)
	, m_name(s)
{
}
