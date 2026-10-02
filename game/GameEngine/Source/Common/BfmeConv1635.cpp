// Open-BFME5 conversions.

// The member at +0 is a narrow string: the destructor calls the ONE narrow
// release, 0x00887940 (StringBase<char>::releaseBuffer, private, hence AAEXXZ
// in the ledger) exactly once, which is what an inline AsciiString destructor
// emits.  Spelled that way here too, as in Bfme7NarrowStringChainDestructors.cpp;
// the former bfme* spelling called a name no object defines.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef AsciiString BfmeStrVUF;

class BfmeSinkVUF
{
public:
	virtual void bfmeSlot0VUF(int flags);
};

class BfmeOwnVUF
{
public:
	~BfmeOwnVUF();
	BfmeStrVUF m_bfme00;
	char m_bfmePad04[8];
	int m_bfme0c;
	BfmeSinkVUF *m_bfme10;
};

BfmeOwnVUF::~BfmeOwnVUF()
{
	BfmeSinkVUF *sink = m_bfme10;

	m_bfme0c = 0;

	if (sink != 0)
		sink->bfmeSlot0VUF(1);

	m_bfme10 = 0;
}
