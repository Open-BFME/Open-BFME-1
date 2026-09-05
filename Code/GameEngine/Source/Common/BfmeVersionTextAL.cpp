// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the version text at retail 0x000AED00, 198 bytes.  The format
// string is not a literal: it is fetched from the text table by label and its
// characters are handed to the temporary that format takes by value.

class StringBaseWideAL
{
protected:
	StringBaseWideAL(void)
	{
		m_bfmeWideAL = 0;
	}

	StringBaseWideAL(const unsigned short *text);

	StringBaseWideAL(const StringBaseWideAL &other);

	~StringBaseWideAL(void);

	unsigned short *m_bfmeWideAL;
};

class UnicodeStringAL : public StringBaseWideAL
{
public:
	UnicodeStringAL(void)
	{
	}

	UnicodeStringAL(const unsigned short *text) : StringBaseWideAL(text)
	{
	}

	UnicodeStringAL(const UnicodeStringAL &other) : StringBaseWideAL(other)
	{
	}

	~UnicodeStringAL(void)
	{
	}

	void __cdecl format(UnicodeStringAL text, ...);

	const unsigned short *bfmeTextAL(void) const
	{
		return (m_bfmeWideAL != 0) ? m_bfmeWideAL + 4 : L"";
	}
};

class BfmeTextAL
{
public:
	virtual void bfmeSlot0AL(void) = 0;
	virtual void bfmeSlot1AL(void) = 0;
	virtual void bfmeSlot2AL(void) = 0;
	virtual void bfmeSlot3AL(void) = 0;
	virtual void bfmeSlot4AL(void) = 0;
	virtual void bfmeSlot5AL(void) = 0;
	virtual void bfmeSlot6AL(void) = 0;
	virtual void bfmeSlot7AL(void) = 0;
	virtual void bfmeSlot8AL(void) = 0;
	virtual void bfmeSlot9AL(void) = 0;
	virtual UnicodeStringAL bfmeFetchAL(const char *label, int *exists) = 0;
};

extern BfmeTextAL *g_bfmeTextAL;			// retail 0x012F147C

class BfmeVersionAL
{
public:
	UnicodeStringAL bfmeVersionTextAL(void);

	int m_bfmeMajorAL;
	int m_bfmeMinorAL;
};

UnicodeStringAL BfmeVersionAL::bfmeVersionTextAL(void)
{
	UnicodeStringAL text;

	text.format(UnicodeStringAL(g_bfmeTextAL->bfmeFetchAL("Version:Format2", 0).bfmeTextAL()),
			m_bfmeMajorAL, m_bfmeMinorAL);

	return text;
}
