// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00675A80, 201 bytes.
// Sibling of 0x00674C30, but the field it reports is itself a string, so the
// null-test-and-skip-the-header expansion appears twice.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

//
// The format call used to be spelled through a TU-local stand-in pair
// (StringBaseNarrowZR/AsciiStringZR), which named retail's callee
// ?format@StringBaseNarrowZR@@QAAXVAsciiStringZR@@ZZ -- a name retail has no
// body for.  AsciiString::format (0x00888FF0, matched in
// game/Libraries/Source/WWVegas/WWLib/AsciiStringNative.cpp) is the real
// one, so it comes from ascii_string.h and is named through the real class.

class StringBaseNarrowZR
{
protected:
	StringBaseNarrowZR(void)
	{
		m_bfmeNarrowZR = 0;
	}

	StringBaseNarrowZR(const char *text);

	StringBaseNarrowZR(const StringBaseNarrowZR &other);

	~StringBaseNarrowZR(void);

	char *m_bfmeNarrowZR;
};

class AsciiStringZR : public StringBaseNarrowZR
{
public:
	AsciiStringZR(void)
	{
	}

	AsciiStringZR(const char *text) : StringBaseNarrowZR(text)
	{
	}

	AsciiStringZR(const AsciiStringZR &other) : StringBaseNarrowZR(other)
	{
	}

	~AsciiStringZR(void)
	{
	}

	const char *bfmeTextZR(void) const
	{
		return (m_bfmeNarrowZR != 0) ? m_bfmeNarrowZR + 8 : "";
	}
};

class BfmeOrderZR
{
public:
	AsciiStringZR bfmeNameZR(void);

	AsciiStringZR bfmeDescribeZR(void);

	char m_bfmePadZR[0x1c];
	AsciiStringZR m_bfmeChallengeZR;
};

AsciiStringZR BfmeOrderZR::bfmeDescribeZR(void)
{
	AsciiStringZR text;

	((AsciiString &)text).format(AsciiString("%s, challenge=%s"),
			bfmeNameZR().bfmeTextZR(), m_bfmeChallengeZR.bfmeTextZR());

	return text;
}
