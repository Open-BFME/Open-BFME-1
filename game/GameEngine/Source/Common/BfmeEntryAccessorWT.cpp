// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the override-aware entry accessor at retail 0x0043FE70,
// 210 bytes.  Copies the member entry into a local, replaces its text from the
// global override when that override's buffer is non-empty, and returns the
// local by value.  One of four identical siblings.

struct BfmeBufferWT
{
	int m_bfmeRef;						// +0x00
	short m_bfmeLength;					// +0x04
};

class AsciiStringWT
{
public:
	AsciiStringWT(const AsciiStringWT &other);
	~AsciiStringWT(void);

	void set(const AsciiStringWT &other);

protected:
	BfmeBufferWT *m_bfmeData;				// +0x00
};

class BfmeStrWT : private AsciiStringWT
{
public:
	BfmeStrWT(const BfmeStrWT &other) : AsciiStringWT(other) {}
	~BfmeStrWT(void) {}

	void bfmeSetWT(const BfmeStrWT &other)
	{
		set(other);
	}

	bool bfmeFilledWT(void) const
	{
		return m_bfmeData != 0 && m_bfmeData->m_bfmeLength != 0;
	}
};

struct BfmeEntryWT
{
	BfmeEntryWT(const BfmeEntryWT &other)
		: m_bfmeText(other.m_bfmeText),
		  m_bfmeA(other.m_bfmeA),
		  m_bfmeB(other.m_bfmeB),
		  m_bfmeC(other.m_bfmeC)
	{
	}

	BfmeStrWT m_bfmeText;					// +0x00
	int m_bfmeA;						// +0x04
	bool m_bfmeB;						// +0x08
	int m_bfmeC;						// +0x0C
};

class BfmeGlobalWT
{
public:
	char m_bfmePad000[0x124];				// +0x000
	BfmeEntryWT m_bfmeOverride;				// +0x124
};

extern BfmeGlobalWT *g_bfmeGlobalWT;				// retail 0x012F1484

class Gen_0043FE70
{
public:
	BfmeEntryWT bfmeEntryWT(void) const;

	char m_bfmePad000[0x804];				// +0x000
	BfmeEntryWT m_bfmeSlot;					// +0x804
};

// ?bfmeEntryWT@Gen_0043FE70@@QBE?AUBfmeEntryWT@@XZ
BfmeEntryWT Gen_0043FE70::bfmeEntryWT(void) const
{
	BfmeEntryWT entry(m_bfmeSlot);

	const BfmeEntryWT *override = &g_bfmeGlobalWT->m_bfmeOverride;

	if (override->m_bfmeText.bfmeFilledWT())
	{
		entry.m_bfmeText.bfmeSetWT(override->m_bfmeText);

		entry.m_bfmeA = override->m_bfmeA;
		entry.m_bfmeB = override->m_bfmeB;
	}

	return entry;
}
