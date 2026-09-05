// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: a constructor at retail 0x006BA2D0, 83 bytes.  The name is a
// member initialiser, the scalar fields are cleared in the order the original
// wrote them, and the trailing array is memset.

extern "C" void *memset(void *dest, int fill, unsigned int count);

class StringBaseNarrowBQ
{
protected:
	StringBaseNarrowBQ(const StringBaseNarrowBQ &other) throw();

	~StringBaseNarrowBQ(void) throw();

	char *m_bfmeNarrowBQ;
};

class AsciiStringBQ : public StringBaseNarrowBQ
{
public:
	AsciiStringBQ(const AsciiStringBQ &other) throw() : StringBaseNarrowBQ(other)
	{
	}

	~AsciiStringBQ(void) throw()
	{
	}
};

class BfmeRecordBQ
{
public:
	BfmeRecordBQ(int owner, const AsciiStringBQ &name);

	AsciiStringBQ m_bfmeNameBQ;
	int m_bfmeOwnerBQ;
	int m_bfmeSlotsBQ[9];
	int m_bfmeABQ;
	int m_bfmeBBQ;
	int m_bfmeCBQ;
	int m_bfmeDBQ;
	int m_bfmeEBQ;
	char m_bfmeFBQ;
	char m_bfmeGBQ;
	char m_bfmeHBQ;
};

BfmeRecordBQ::BfmeRecordBQ(int owner, const AsciiStringBQ &name)
		: m_bfmeNameBQ(name)
{
	m_bfmeCBQ = 0;
	m_bfmeDBQ = 0;
	m_bfmeGBQ = 0;
	m_bfmeABQ = 0;
	m_bfmeBBQ = 0;
	m_bfmeEBQ = 0;
	m_bfmeFBQ = 0;
	m_bfmeHBQ = 0;

	m_bfmeOwnerBQ = owner;

	memset(m_bfmeSlotsBQ, 0, sizeof(m_bfmeSlotsBQ));
}
