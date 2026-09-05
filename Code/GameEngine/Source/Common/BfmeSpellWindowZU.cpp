// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the spell-window name at retail 0x0058BA80, 141 bytes.
// A free function returning the built string by value.

class StringBaseNarrowZU
{
public:
	void __cdecl format(class AsciiStringZU text, ...);

protected:
	StringBaseNarrowZU(void)
	{
		m_bfmeNarrowZU = 0;
	}

	StringBaseNarrowZU(const char *text);

	StringBaseNarrowZU(const StringBaseNarrowZU &other);

	~StringBaseNarrowZU(void);

	char *m_bfmeNarrowZU;
};

class AsciiStringZU : public StringBaseNarrowZU
{
public:
	AsciiStringZU(void)
	{
	}

	AsciiStringZU(const char *text) : StringBaseNarrowZU(text)
	{
	}

	AsciiStringZU(const AsciiStringZU &other) : StringBaseNarrowZU(other)
	{
	}

	~AsciiStringZU(void)
	{
	}

	const char *bfmeTextZU(void) const
	{
		return (m_bfmeNarrowZU != 0) ? m_bfmeNarrowZU + 8 : "";
	}
};

// ?bfmeSpellWindowZU@@YA?AVAsciiStringZU@@H@Z
AsciiStringZU bfmeSpellWindowZU(int slot)
{
	AsciiStringZU name;

	name.format(AsciiStringZU("SpellBookUI/Spell%d"), slot + 1);

	return name;
}
