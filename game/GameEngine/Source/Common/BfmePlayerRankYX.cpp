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

// Retail's WindowManager global at 0x012F19E8, under the one linked-build
// spelling.  BfmePalantirYX above is this TU's view of the same object.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

static inline BfmePalantirYX *bfmePalantirYXView(void)
{
	return (BfmePalantirYX *)g_rva012F19E8WindowManager;
}

// ?bfmeSetRankYX@@YADH@Z
char bfmeSetRankYX(int rank)
{
	static AsciiStringYX s_bfmeKeyYX("APT:PlayerRank");

	UnicodeStringYX value;

	value.format(UnicodeStringYX(L"%d"), rank);

	bfmePalantirYXView()->bfmeStoreYX(s_bfmeKeyYX, value);

	return 1;
}
