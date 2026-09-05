// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the hero-rank palantir update at retail 0x00565720, 255 bytes.
// The format string is not a literal here: it is fetched from the text table
// by label and returned by value, so it arrives as a struct return slot.

class StringBaseNarrowZE
{
protected:
	StringBaseNarrowZE(const char *text);

	StringBaseNarrowZE(const StringBaseNarrowZE &other);

	~StringBaseNarrowZE(void);

	char *m_bfmeNarrowZE;
};

class AsciiStringZE : public StringBaseNarrowZE
{
public:
	AsciiStringZE(const char *text) : StringBaseNarrowZE(text)
	{
	}

	AsciiStringZE(const AsciiStringZE &other) : StringBaseNarrowZE(other)
	{
	}

	~AsciiStringZE(void)
	{
	}
};

class StringBaseWideZE
{
protected:
	StringBaseWideZE(void)
	{
		m_bfmeWideZE = 0;
	}

	StringBaseWideZE(const StringBaseWideZE &other);

	~StringBaseWideZE(void);

	unsigned short *m_bfmeWideZE;
};

class UnicodeStringZE : public StringBaseWideZE
{
public:
	UnicodeStringZE(void)
	{
	}

	UnicodeStringZE(const UnicodeStringZE &other);

	~UnicodeStringZE(void)
	{
	}

	void __cdecl format(UnicodeStringZE text, ...);
};

class BfmeTextZE
{
public:
	virtual void bfmeSlot0ZE(void) = 0;
	virtual void bfmeSlot1ZE(void) = 0;
	virtual void bfmeSlot2ZE(void) = 0;
	virtual void bfmeSlot3ZE(void) = 0;
	virtual void bfmeSlot4ZE(void) = 0;
	virtual void bfmeSlot5ZE(void) = 0;
	virtual void bfmeSlot6ZE(void) = 0;
	virtual void bfmeSlot7ZE(void) = 0;
	virtual void bfmeSlot8ZE(void) = 0;
	virtual UnicodeStringZE bfmeFetchZE(AsciiStringZE label, int *exists) = 0;
};

class BfmePalantirZE
{
public:
	void bfmeStoreZE(const AsciiStringZE &key, const UnicodeStringZE &value);
};

extern BfmeTextZE *g_bfmeTextZE;					// retail 0x012F147C
extern BfmePalantirZE *g_bfmePalantirZE;			// retail 0x012F19E8

// ?bfmeHeroRankZE@@YADH@Z
char bfmeHeroRankZE(int rank)
{
	static AsciiStringZE s_bfmeLabelZE("APT:RankLabel");

	static AsciiStringZE s_bfmeKeyZE("APT:HeroRank");

	UnicodeStringZE value;

	value.format(g_bfmeTextZE->bfmeFetchZE(s_bfmeLabelZE, 0), rank);

	g_bfmePalantirZE->bfmeStoreZE(s_bfmeKeyZE, value);

	return 1;
}
