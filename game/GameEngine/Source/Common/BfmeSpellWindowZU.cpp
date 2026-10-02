// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the spell-window name at retail 0x0058BA80, 141 bytes.
// A free function returning the built string by value.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

//
// The format call used to be spelled through a TU-local stand-in pair
// (StringBaseNarrowZU/AsciiStringZU), which named retail's callee
// ?format@StringBaseNarrowZU@@QAAXVAsciiStringZU@@ZZ -- a name retail has no
// body for.  AsciiString::format (0x00888FF0, matched in
// game/Libraries/Source/WWVegas/WWLib/AsciiStringNative.cpp) is the real
// one, so it comes from ascii_string.h and is named through the real class.

class StringBaseNarrowZU
{
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

	((AsciiString &)name).format(AsciiString("SpellBookUI/Spell%d"), slot + 1);

	return name;
}
