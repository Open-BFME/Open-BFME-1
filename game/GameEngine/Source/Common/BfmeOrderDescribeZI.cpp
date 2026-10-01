// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00674D20, 191 bytes.  One of
// thirteen sibling descriptions in the same translation unit: each returns a
// string by value, built from a name fetched by value and a few fields.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

//
// The format call used to be spelled through a TU-local stand-in pair
// (StringBaseNarrowZI/AsciiStringZI), which named retail's callee
// ?format@StringBaseNarrowZI@@QAAXVAsciiStringZI@@ZZ -- a name retail has no
// body for.  AsciiString::format (0x00888FF0, matched in
// game/Libraries/Source/WWVegas/WWLib/AsciiStringNative.cpp) is the real
// one, so it comes from ascii_string.h and is named through the real class.

class StringBaseNarrowZI
{
protected:
	StringBaseNarrowZI(void)
	{
		m_bfmeNarrowZI = 0;
	}

	StringBaseNarrowZI(const char *text);

	StringBaseNarrowZI(const StringBaseNarrowZI &other);

	~StringBaseNarrowZI(void);

	char *m_bfmeNarrowZI;
};

class AsciiStringZI : public StringBaseNarrowZI
{
public:
	AsciiStringZI(void)
	{
	}

	AsciiStringZI(const char *text) : StringBaseNarrowZI(text)
	{
	}

	AsciiStringZI(const AsciiStringZI &other) : StringBaseNarrowZI(other)
	{
	}

	~AsciiStringZI(void)
	{
	}

	const char *bfmeTextZI(void) const
	{
		return (m_bfmeNarrowZI != 0) ? m_bfmeNarrowZI + 8 : "";
	}
};

class BfmeOrderZI
{
public:
	AsciiStringZI bfmeNameZI(void);

	AsciiStringZI bfmeDescribeZI(void);

	char m_bfmePadZI[0x1c];
	unsigned short m_bfmeCommandZI;
	unsigned char m_bfmePlayerZI;
	int m_bfmeFrameZI;
};

AsciiStringZI BfmeOrderZI::bfmeDescribeZI(void)
{
	AsciiStringZI text;

	((AsciiString &)text).format(AsciiString("%s, commandID=%d, originalPlayer=%d, originalExecFrame=%d"),
			bfmeNameZI().bfmeTextZI(), m_bfmeCommandZI, m_bfmePlayerZI, m_bfmeFrameZI);

	return text;
}
