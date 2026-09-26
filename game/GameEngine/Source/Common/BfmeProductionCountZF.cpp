// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the production-count palantir update at retail 0x00565450,
// 210 bytes.  Unlike its siblings the property key is built per call, and the
// blank value comes from a stack character rather than from a literal.

class StringBaseNarrowZF
{
public:
	void __cdecl format(class AsciiStringZF text, ...);

protected:
	StringBaseNarrowZF(void)
	{
		m_bfmeNarrowZF = 0;
	}

	StringBaseNarrowZF(const char *text);

	StringBaseNarrowZF(const StringBaseNarrowZF &other);

	~StringBaseNarrowZF(void);

	char *m_bfmeNarrowZF;
};

class AsciiStringZF : public StringBaseNarrowZF
{
public:
	AsciiStringZF(void)
	{
	}

	AsciiStringZF(const char *text) : StringBaseNarrowZF(text)
	{
	}

	AsciiStringZF(const AsciiStringZF &other);

	~AsciiStringZF(void)
	{
	}
};

class StringBaseWideZF
{
public:
	void set(const unsigned short *text, int length);

protected:
	StringBaseWideZF(void)
	{
		m_bfmeWideZF = 0;
	}

	StringBaseWideZF(const unsigned short *text);

	StringBaseWideZF(const StringBaseWideZF &other);

	~StringBaseWideZF(void);

	unsigned short *m_bfmeWideZF;
};

class UnicodeStringZF : public StringBaseWideZF
{
public:
	UnicodeStringZF(void)
	{
	}

	UnicodeStringZF(const unsigned short *text) : StringBaseWideZF(text)
	{
	}

	UnicodeStringZF(const UnicodeStringZF &other);

	~UnicodeStringZF(void)
	{
	}

	void __cdecl format(UnicodeStringZF text, ...);
};

class BfmePalantirZF
{
public:
	void bfmeStoreZF(const AsciiStringZF &key, const UnicodeStringZF &value);
};

extern BfmePalantirZF *g_bfmePalantirZF;			// retail 0x012F19E8

// ?bfmeProductionCountZF@@YAXHH@Z
void bfmeProductionCountZF(int slot, int count)
{
	AsciiStringZF key;

	key.format(AsciiStringZF("APT:PalantirCommand%dProductionCount"), slot + 1);

	UnicodeStringZF value;

	if (count > 0)
		value.format(UnicodeStringZF(L"%d"), count);
	else
	{
		unsigned short blank[2] = L" ";

		value.set(blank, 1);
	}

	g_bfmePalantirZF->bfmeStoreZF(key, value);
}
