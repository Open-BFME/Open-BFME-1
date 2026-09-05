// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the palantir resource update at retail 0x00565620, 197 bytes.
// A function-local static holds the property key; the value is formatted from
// the argument, or set to a single space when the argument is negative.

class StringBaseYW
{
protected:
	StringBaseYW(void)
	{
		m_bfmeDataYW = 0;
	}

	StringBaseYW(const char *text);

	StringBaseYW(const StringBaseYW &other);

	~StringBaseYW(void);

	char *m_bfmeDataYW;
};

class AsciiStringYW : public StringBaseYW
{
public:
	AsciiStringYW(void)
	{
	}

	AsciiStringYW(const char *text) : StringBaseYW(text)
	{
	}

	AsciiStringYW(const AsciiStringYW &other);

	~AsciiStringYW(void)
	{
	}

	void __cdecl format(AsciiStringYW text, ...);

	void set(const char *text, int length);
};

class BfmePalantirYW
{
public:
	void bfmeStoreYW(const AsciiStringYW &key, const AsciiStringYW &value);
};

extern BfmePalantirYW *g_bfmePalantirYW;			// retail 0x012F19E8

// ?bfmeSetPalantirYW@@YAXH@Z
void bfmeSetPalantirYW(int count)
{
	static AsciiStringYW s_bfmeKeyYW("APT:PalantirResources");

	AsciiStringYW value;

	if (count >= 0)
		value.format(AsciiStringYW("%d"), count);
	else
		value.set(" ", 1);

	g_bfmePalantirYW->bfmeStoreYW(s_bfmeKeyYW, value);
}
