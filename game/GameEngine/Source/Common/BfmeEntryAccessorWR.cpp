// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the override-aware entry accessor at retail 0x0043FC50,
// 210 bytes.  Copies the member entry into a local, replaces its text from the
// global override when that override's buffer is non-empty, and returns the
// local by value.  One of four identical siblings.

struct BfmeBufferWR
{
	int m_bfmeRef;						// +0x00
	short m_bfmeLength;					// +0x04
};

class AsciiStringWR
{
public:
	AsciiStringWR(const AsciiStringWR &other);
	~AsciiStringWR(void);

	void set(const AsciiStringWR &other);

protected:
	BfmeBufferWR *m_bfmeData;				// +0x00
};

class BfmeStrWR : private AsciiStringWR
{
public:
	BfmeStrWR(const BfmeStrWR &other) : AsciiStringWR(other) {}
	~BfmeStrWR(void) {}

	void bfmeSetWR(const BfmeStrWR &other)
	{
		set(other);
	}

	bool bfmeFilledWR(void) const
	{
		return m_bfmeData != 0 && m_bfmeData->m_bfmeLength != 0;
	}
};

struct BfmeEntryWR
{
	BfmeEntryWR(const BfmeEntryWR &other)
		: m_bfmeText(other.m_bfmeText),
		  m_bfmeA(other.m_bfmeA),
		  m_bfmeB(other.m_bfmeB),
		  m_bfmeC(other.m_bfmeC)
	{
	}

	BfmeStrWR m_bfmeText;					// +0x00
	int m_bfmeA;						// +0x04
	bool m_bfmeB;						// +0x08
	int m_bfmeC;						// +0x0C
};

class BfmeGlobalWR
{
public:
	char m_bfmePad000[0x10C];				// +0x000
	BfmeEntryWR m_bfmeOverride;				// +0x10C
};

extern BfmeGlobalWR *g_bfmeGlobalWR;				// retail 0x012F1484

class Gen_0043FC50
{
public:
	BfmeEntryWR bfmeEntryWR(void) const;

	char m_bfmePad000[0x7E4];				// +0x000
	BfmeEntryWR m_bfmeSlot;					// +0x7E4
};

// ?bfmeEntryWR@Gen_0043FC50@@QBE?AUBfmeEntryWR@@XZ
BfmeEntryWR Gen_0043FC50::bfmeEntryWR(void) const
{
	BfmeEntryWR entry(m_bfmeSlot);

	const BfmeEntryWR *override = &g_bfmeGlobalWR->m_bfmeOverride;

	if (override->m_bfmeText.bfmeFilledWR())
	{
		entry.m_bfmeText.bfmeSetWR(override->m_bfmeText);

		entry.m_bfmeA = override->m_bfmeA;
		entry.m_bfmeB = override->m_bfmeB;
	}

	return entry;
}
