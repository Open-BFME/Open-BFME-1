// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the player-rank palantir update at retail 0x00565860, 177 bytes.

class StringBaseNarrowYX
{
protected:
	StringBaseNarrowYX(const char *text);

	~StringBaseNarrowYX(void);

	char *m_bfmeNarrowYX;
};

class AsciiStringYX : public StringBaseNarrowYX
{
public:
	AsciiStringYX(const char *text) : StringBaseNarrowYX(text)
	{
	}

	~AsciiStringYX(void)
	{
	}
};

class StringBaseWideYX
{
protected:
	StringBaseWideYX(void)
	{
		m_bfmeWideYX = 0;
	}

	StringBaseWideYX(const unsigned short *text);

	StringBaseWideYX(const StringBaseWideYX &other);

	~StringBaseWideYX(void);

	unsigned short *m_bfmeWideYX;
};

class UnicodeStringYX : public StringBaseWideYX
{
public:
	UnicodeStringYX(void)
	{
	}

	UnicodeStringYX(const unsigned short *text) : StringBaseWideYX(text)
	{
	}

	UnicodeStringYX(const UnicodeStringYX &other);

	~UnicodeStringYX(void)
	{
	}

	void __cdecl format(UnicodeStringYX text, ...);
};

class BfmePalantirYX
{
public:
	void bfmeStoreYX(const AsciiStringYX &key, const UnicodeStringYX &value);
};

extern BfmePalantirYX *g_bfmePalantirYX;			// retail 0x012F19E8

// ?bfmeSetRankYX@@YADH@Z
char bfmeSetRankYX(int rank)
{
	static AsciiStringYX s_bfmeKeyYX("APT:PlayerRank");

	UnicodeStringYX value;

	value.format(UnicodeStringYX(L"%d"), rank);

	g_bfmePalantirYX->bfmeStoreYX(s_bfmeKeyYX, value);

	return 1;
}
