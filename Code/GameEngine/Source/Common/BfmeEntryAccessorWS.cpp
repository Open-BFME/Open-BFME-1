// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the override-aware entry accessor at retail 0x0043FD60,
// 210 bytes.  Copies the member entry into a local, replaces its text from the
// global override when that override's buffer is non-empty, and returns the
// local by value.  One of four identical siblings.

struct BfmeBufferWS
{
	int m_bfmeRef;						// +0x00
	short m_bfmeLength;					// +0x04
};

class AsciiStringWS
{
public:
	AsciiStringWS(const AsciiStringWS &other);
	~AsciiStringWS(void);

	void set(const AsciiStringWS &other);

protected:
	BfmeBufferWS *m_bfmeData;				// +0x00
};

class BfmeStrWS : private AsciiStringWS
{
public:
	BfmeStrWS(const BfmeStrWS &other) : AsciiStringWS(other) {}
	~BfmeStrWS(void) {}

	void bfmeSetWS(const BfmeStrWS &other)
	{
		set(other);
	}

	bool bfmeFilledWS(void) const
	{
		return m_bfmeData != 0 && m_bfmeData->m_bfmeLength != 0;
	}
};

struct BfmeEntryWS
{
	BfmeEntryWS(const BfmeEntryWS &other)
		: m_bfmeText(other.m_bfmeText),
		  m_bfmeA(other.m_bfmeA),
		  m_bfmeB(other.m_bfmeB),
		  m_bfmeC(other.m_bfmeC)
	{
	}

	BfmeStrWS m_bfmeText;					// +0x00
	int m_bfmeA;						// +0x04
	bool m_bfmeB;						// +0x08
	int m_bfmeC;						// +0x0C
};

class BfmeGlobalWS
{
public:
	char m_bfmePad000[0x118];				// +0x000
	BfmeEntryWS m_bfmeOverride;				// +0x118
};

extern BfmeGlobalWS *g_bfmeGlobalWS;				// retail 0x012F1484

class Gen_0043FD60
{
public:
	BfmeEntryWS bfmeEntryWS(void) const;

	char m_bfmePad000[0x7F4];				// +0x000
	BfmeEntryWS m_bfmeSlot;					// +0x7F4
};

// ?bfmeEntryWS@Gen_0043FD60@@QBE?AUBfmeEntryWS@@XZ
BfmeEntryWS Gen_0043FD60::bfmeEntryWS(void) const
{
	BfmeEntryWS entry(m_bfmeSlot);

	const BfmeEntryWS *override = &g_bfmeGlobalWS->m_bfmeOverride;

	if (override->m_bfmeText.bfmeFilledWS())
	{
		entry.m_bfmeText.bfmeSetWS(override->m_bfmeText);

		entry.m_bfmeA = override->m_bfmeA;
		entry.m_bfmeB = override->m_bfmeB;
	}

	return entry;
}
