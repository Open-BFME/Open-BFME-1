// cl: /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5 conversions.

#include "ascii_string.h"

class BfmeSinkVUQ
{
public:
	virtual void bfmeSlot0VUQ(int flags);
};

class BfmeBaseVUQ
{
public:
	~BfmeBaseVUQ() { }
	virtual void bfmeSlot0VUQ();
};

class Script : public BfmeBaseVUQ
{
public:
	~Script();
	AsciiString m_bfme04;
	AsciiString m_bfme08;
	AsciiString m_bfme0c;
	char m_bfmePad10[0xc];
	BfmeSinkVUQ *m_condition;
	BfmeSinkVUQ *m_action;
	BfmeSinkVUQ *m_actionFalse;
	char m_bfmePad28[8];
	AsciiString m_bfme30;
};

Script::~Script()
{
	BfmeSinkVUQ *first = m_condition;
	BfmeSinkVUQ *second;
	BfmeSinkVUQ *third;

	if (first != 0)
		first->bfmeSlot0VUQ(1);

	second = m_action;

	if (second != 0)
		second->bfmeSlot0VUQ(1);

	third = m_actionFalse;

	if (third != 0)
		third->bfmeSlot0VUQ(1);
}
