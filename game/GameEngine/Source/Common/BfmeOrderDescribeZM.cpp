// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00674F00, 182 bytes.
// Sibling of 0x00674C30; the fields it reports are what differ.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

//
// The format call used to be spelled through a TU-local stand-in pair
// (StringBaseNarrowZM/AsciiStringZM), which named retail's callee
// ?format@StringBaseNarrowZM@@QAAXVAsciiStringZM@@ZZ -- a name retail has no
// body for.  AsciiString::format (0x00888FF0, matched in
// game/Libraries/Source/WWVegas/WWLib/AsciiStringNative.cpp) is the real
// one, so it comes from ascii_string.h and is named through the real class.

class StringBaseNarrowZM
{
protected:
	StringBaseNarrowZM(void)
	{
		m_bfmeNarrowZM = 0;
	}

	StringBaseNarrowZM(const char *text);

	StringBaseNarrowZM(const StringBaseNarrowZM &other);

	~StringBaseNarrowZM(void);

	char *m_bfmeNarrowZM;
};

class AsciiStringZM : public StringBaseNarrowZM
{
public:
	AsciiStringZM(void)
	{
	}

	AsciiStringZM(const char *text) : StringBaseNarrowZM(text)
	{
	}

	AsciiStringZM(const AsciiStringZM &other) : StringBaseNarrowZM(other)
	{
	}

	~AsciiStringZM(void)
	{
	}

	const char *bfmeTextZM(void) const
	{
		return (m_bfmeNarrowZM != 0) ? m_bfmeNarrowZM + 8 : "";
	}
};

class BfmeOrderZM
{
public:
	AsciiStringZM bfmeNameZM(void);

	AsciiStringZM bfmeDescribeZM(void);

	char m_bfmePadZM[0x1c];
	unsigned char m_bfmeLeavingZM;
};

AsciiStringZM BfmeOrderZM::bfmeDescribeZM(void)
{
	AsciiStringZM text;

	((AsciiString &)text).format(AsciiString("%s, leavingPlayer=%d"),
			bfmeNameZM().bfmeTextZM(), m_bfmeLeavingZM);

	return text;
}
