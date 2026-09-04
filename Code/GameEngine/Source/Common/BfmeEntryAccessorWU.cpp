// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the override-aware entry accessor at retail 0x00442460,
// 210 bytes.  Copies the member entry into a local, replaces its text from the
// global override when that override's buffer is non-empty, and returns the
// local by value.  One of four identical siblings.

struct BfmeBufferWU
{
	int m_bfmeRef;						// +0x00
	short m_bfmeLength;					// +0x04
};

class AsciiStringWU
{
public:
	AsciiStringWU(const AsciiStringWU &other);
	~AsciiStringWU(void);

	void set(const AsciiStringWU &other);

protected:
	BfmeBufferWU *m_bfmeData;				// +0x00
};

class BfmeStrWU : private AsciiStringWU
{
public:
	BfmeStrWU(const BfmeStrWU &other) : AsciiStringWU(other) {}
	~BfmeStrWU(void) {}

	void bfmeSetWU(const BfmeStrWU &other)
	{
		set(other);
	}

	bool bfmeFilledWU(void) const
	{
		return m_bfmeData != 0 && m_bfmeData->m_bfmeLength != 0;
	}
};

struct BfmeEntryWU
{
	BfmeEntryWU(const BfmeEntryWU &other)
		: m_bfmeText(other.m_bfmeText),
		  m_bfmeA(other.m_bfmeA),
		  m_bfmeB(other.m_bfmeB),
		  m_bfmeC(other.m_bfmeC)
	{
	}

	BfmeStrWU m_bfmeText;					// +0x00
	int m_bfmeA;						// +0x04
	bool m_bfmeB;						// +0x08
	int m_bfmeC;						// +0x0C
};

class BfmeGlobalWU
{
public:
	char m_bfmePad000[0x100];				// +0x000
	BfmeEntryWU m_bfmeOverride;				// +0x100
};

extern BfmeGlobalWU *g_bfmeGlobalWU;				// retail 0x012F1484

class Gen_00442460
{
public:
	BfmeEntryWU bfmeEntryWU(void) const;

	char m_bfmePad000[0x7D4];				// +0x000
	BfmeEntryWU m_bfmeSlot;					// +0x7D4
};

// ?bfmeEntryWU@Gen_00442460@@QBE?AUBfmeEntryWU@@XZ
BfmeEntryWU Gen_00442460::bfmeEntryWU(void) const
{
	BfmeEntryWU entry(m_bfmeSlot);

	const BfmeEntryWU *override = &g_bfmeGlobalWU->m_bfmeOverride;

	if (override->m_bfmeText.bfmeFilledWU())
	{
		entry.m_bfmeText.bfmeSetWU(override->m_bfmeText);

		entry.m_bfmeA = override->m_bfmeA;
		entry.m_bfmeB = override->m_bfmeB;
	}

	return entry;
}
