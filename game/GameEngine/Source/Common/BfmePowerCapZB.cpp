// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the second palantir property update at retail 0x00565BB0, 175 bytes.

class StringBaseNarrowZB
{
protected:
	StringBaseNarrowZB(const char *text);

	~StringBaseNarrowZB(void);

	char *m_bfmeNarrowZB;
};

class AsciiStringZB : public StringBaseNarrowZB
{
public:
	AsciiStringZB(const char *text) : StringBaseNarrowZB(text)
	{
	}

	~AsciiStringZB(void)
	{
	}
};

class StringBaseWideZB
{
protected:
	StringBaseWideZB(void)
	{
		m_bfmeWideZB = 0;
	}

	StringBaseWideZB(const unsigned short *text);

	StringBaseWideZB(const StringBaseWideZB &other);

	~StringBaseWideZB(void);

	unsigned short *m_bfmeWideZB;
};

class UnicodeStringZB : public StringBaseWideZB
{
public:
	UnicodeStringZB(void)
	{
	}

	UnicodeStringZB(const unsigned short *text) : StringBaseWideZB(text)
	{
	}

	UnicodeStringZB(const UnicodeStringZB &other);

	~UnicodeStringZB(void)
	{
	}

	void __cdecl format(UnicodeStringZB text, ...);
};

class BfmePalantirZB
{
public:
	void bfmeStoreZB(const AsciiStringZB &key, const UnicodeStringZB &value);
};

extern BfmePalantirZB *g_bfmePalantirZB;			// retail 0x012F19E8

// ?bfmePowerCapZB@@YAXH@Z
void bfmePowerCapZB(int cap)
{
	static AsciiStringZB s_bfmeKeyZB("APT:PlayerPowerCap");

	UnicodeStringZB value;

	value.format(UnicodeStringZB(L"%d"), cap);

	g_bfmePalantirZB->bfmeStoreZB(s_bfmeKeyZB, value);
}
