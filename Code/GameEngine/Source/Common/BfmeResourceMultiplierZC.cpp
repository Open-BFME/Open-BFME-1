// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the palantir resource-multiplier update at retail 0x00565A80,
// 232 bytes.  A multiplier of exactly one is shown as a blank; anything else
// is formatted, so the value arrives either from format or from the
// set/wcslen idiom.

extern "C" __declspec(dllimport) unsigned int wcslen(const unsigned short *text);

class StringBaseNarrowZC
{
protected:
	StringBaseNarrowZC(const char *text);

	~StringBaseNarrowZC(void);

	char *m_bfmeNarrowZC;
};

class AsciiStringZC : public StringBaseNarrowZC
{
public:
	AsciiStringZC(const char *text) : StringBaseNarrowZC(text)
	{
	}

	~AsciiStringZC(void)
	{
	}
};

class StringBaseWideZC
{
public:
	void set(const unsigned short *text, int length);

protected:
	StringBaseWideZC(void)
	{
		m_bfmeWideZC = 0;
	}

	StringBaseWideZC(const unsigned short *text);

	StringBaseWideZC(const StringBaseWideZC &other);

	~StringBaseWideZC(void);

	unsigned short *m_bfmeWideZC;
};

class UnicodeStringZC : public StringBaseWideZC
{
public:
	UnicodeStringZC(void)
	{
	}

	UnicodeStringZC(const unsigned short *text) : StringBaseWideZC(text)
	{
	}

	UnicodeStringZC(const UnicodeStringZC &other);

	~UnicodeStringZC(void)
	{
	}

	void __cdecl format(UnicodeStringZC text, ...);
};

class BfmePalantirZC
{
public:
	void bfmeStoreZC(const AsciiStringZC &key, const UnicodeStringZC &value);
};

extern BfmePalantirZC *g_bfmePalantirZC;			// retail 0x012F19E8

// ?bfmeMultiplierZC@@YADM@Z
char bfmeMultiplierZC(float multiplier)
{
	static AsciiStringZC s_bfmeKeyZC("APT:PalantirResourceMultiplier");

	UnicodeStringZC value;

	if (multiplier != 1.0f)
		value.format(UnicodeStringZC(L"x%g"), multiplier);
	else
		value.set(L" ", wcslen(L" "));

	g_bfmePalantirZC->bfmeStoreZC(s_bfmeKeyZC, value);

	return 1;
}
