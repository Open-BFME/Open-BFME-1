// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the player-table palantir write at retail 0x0052B540, 125 bytes.
// The value is handed in by the caller here; only the key is built, from a row
// and a column.

class StringBaseNarrowZG
{
public:
	void __cdecl format(class AsciiStringZG text, ...);

protected:
	StringBaseNarrowZG(void)
	{
		m_bfmeNarrowZG = 0;
	}

	StringBaseNarrowZG(const char *text);

	StringBaseNarrowZG(const StringBaseNarrowZG &other);

	~StringBaseNarrowZG(void);

	char *m_bfmeNarrowZG;
};

class AsciiStringZG : public StringBaseNarrowZG
{
public:
	AsciiStringZG(void)
	{
	}

	AsciiStringZG(const char *text) : StringBaseNarrowZG(text)
	{
	}

	AsciiStringZG(const AsciiStringZG &other);

	~AsciiStringZG(void)
	{
	}
};

class UnicodeStringZG;

class BfmePalantirZG
{
public:
	void bfmeStoreZG(const AsciiStringZG &key, const UnicodeStringZG &value);
};

extern BfmePalantirZG *g_bfmePalantirZG;			// retail 0x012F19E8

// ?bfmePlayerTableZG@@YGXHHABVUnicodeStringZG@@@Z
void __stdcall bfmePlayerTableZG(int row, int column, const UnicodeStringZG &value)
{
	AsciiStringZG key;

	key.format(AsciiStringZG("PlayerTable:%d:%d"), row, column);

	g_bfmePalantirZG->bfmeStoreZG(key, value);
}
