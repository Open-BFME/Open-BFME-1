// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00675D40, 219 bytes.
// Sibling of 0x00675A80 with two string fields rather than one.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

//
// The format call used to be spelled through a TU-local stand-in pair
// (StringBaseNarrowZS/AsciiStringZS), which named retail's callee
// ?format@StringBaseNarrowZS@@QAAXVAsciiStringZS@@ZZ -- a name retail has no
// body for.  AsciiString::format (0x00888FF0, matched in
// game/Libraries/Source/WWVegas/WWLib/AsciiStringNative.cpp) is the real
// one, so it comes from ascii_string.h and is named through the real class.

class StringBaseNarrowZS
{
protected:
	StringBaseNarrowZS(void)
	{
		m_bfmeNarrowZS = 0;
	}

	StringBaseNarrowZS(const char *text);

	StringBaseNarrowZS(const StringBaseNarrowZS &other);

	~StringBaseNarrowZS(void);

	char *m_bfmeNarrowZS;
};

class AsciiStringZS : public StringBaseNarrowZS
{
public:
	AsciiStringZS(void)
	{
	}

	AsciiStringZS(const char *text) : StringBaseNarrowZS(text)
	{
	}

	AsciiStringZS(const AsciiStringZS &other) : StringBaseNarrowZS(other)
	{
	}

	~AsciiStringZS(void)
	{
	}

	const char *bfmeTextZS(void) const
	{
		return (m_bfmeNarrowZS != 0) ? m_bfmeNarrowZS + 8 : "";
	}
};

class BfmeOrderZS
{
public:
	AsciiStringZS bfmeNameZS(void);

	AsciiStringZS bfmeDescribeZS(void);

	char m_bfmePadZS[0x1c];
	AsciiStringZS m_bfmeAuthKeyZS;
	AsciiStringZS m_bfmeAuthTokenZS;
};

AsciiStringZS BfmeOrderZS::bfmeDescribeZS(void)
{
	AsciiStringZS text;

	((AsciiString &)text).format(AsciiString("%s, authToken=%s, authKey=%s"),
			bfmeNameZS().bfmeTextZS(), m_bfmeAuthTokenZS.bfmeTextZS(),
			m_bfmeAuthKeyZS.bfmeTextZS());

	return text;
}