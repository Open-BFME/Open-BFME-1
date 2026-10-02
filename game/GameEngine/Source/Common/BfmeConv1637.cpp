// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME5 conversions.
//
// BfmeStrVUG is the narrow string retail releases at 0x00887940 -- the body
// does `lea ecx,[esi+0x0c] / call 0x00887940`, i.e. StringBase<char>:
// releaseBuffer through AsciiString's inline destructor. The Bfme* method name
// it used to carry (bfmeClearVUG) names a symbol nothing defines.

#include "ascii_string.h"

class BfmeStrVUG : public AsciiString
{
};

class BfmeSubVUG
{
public:
	virtual void bfmeSlot0VUG(int flags);
	int m_bfme04;
};

class BfmeRefVUG
{
public:
	char m_bfmePad00[0x24];
	BfmeSubVUG m_bfme24;
};

class BfmeOwnVUG
{
public:
	~BfmeOwnVUG();
	char m_bfmePad00[0xc];
	BfmeStrVUG m_bfme0c;
	BfmeRefVUG *m_bfme10;
};

BfmeOwnVUG::~BfmeOwnVUG()
{
	BfmeRefVUG *ref = m_bfme10;

	if (ref != 0)
	{
		BfmeSubVUG *sub = &ref->m_bfme24;
		int count = --sub->m_bfme04;

		if (count <= 0)
			sub->bfmeSlot0VUG(1);
	}
}