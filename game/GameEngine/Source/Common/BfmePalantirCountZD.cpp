// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the palantir count update at retail 0x00565940, 252 bytes.
// A negative count blanks the property; a negative total prints the count
// alone; otherwise the pair is printed as "count/total".

extern "C" __declspec(dllimport) unsigned int wcslen(const unsigned short *text);

class StringBaseNarrowZD
{
protected:
	StringBaseNarrowZD(const char *text);

	~StringBaseNarrowZD(void);

	char *m_bfmeNarrowZD;
};

class AsciiStringZD : public StringBaseNarrowZD
{
public:
	AsciiStringZD(const char *text) : StringBaseNarrowZD(text)
	{
	}

	~AsciiStringZD(void)
	{
	}
};

class StringBaseWideZD
{
public:
	void set(const unsigned short *text, int length);

protected:
	StringBaseWideZD(void)
	{
		m_bfmeWideZD = 0;
	}

	StringBaseWideZD(const unsigned short *text);

	StringBaseWideZD(const StringBaseWideZD &other);

	~StringBaseWideZD(void);

	unsigned short *m_bfmeWideZD;
};

class UnicodeStringZD : public StringBaseWideZD
{
public:
	UnicodeStringZD(void)
	{
	}

	UnicodeStringZD(const unsigned short *text) : StringBaseWideZD(text)
	{
	}

	UnicodeStringZD(const UnicodeStringZD &other);

	~UnicodeStringZD(void)
	{
	}

	void __cdecl format(UnicodeStringZD text, ...);
};

class BfmePalantirZD
{
public:
	void bfmeStoreZD(const AsciiStringZD &key, const UnicodeStringZD &value);
};

extern BfmePalantirZD *g_bfmePalantirZD;			// retail 0x012F19E8

// ?bfmePalantirCountZD@@YADHH@Z
char bfmePalantirCountZD(int count, int total)
{
	static AsciiStringZD s_bfmeKeyZD("APT:PalantirCommandPoints");

	UnicodeStringZD value;

	if (count >= 0)
	{
		if (total >= 0)
			value.format(UnicodeStringZD(L"%d/%d"), total, count);
		else
			value.format(UnicodeStringZD(L"%d"), count);
	}
	else
		value.set(L" ", wcslen(L" "));

	g_bfmePalantirZD->bfmeStoreZD(s_bfmeKeyZD, value);

	return 1;
}
