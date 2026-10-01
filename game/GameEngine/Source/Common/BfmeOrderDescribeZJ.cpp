// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00674E10, 191 bytes.  One of
// thirteen sibling descriptions in the same translation unit: each returns a
// string by value, built from a name fetched by value and a few fields.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

//
// The format call used to be spelled through a TU-local stand-in pair
// (StringBaseNarrowZJ/AsciiStringZJ), which named retail's callee
// ?format@StringBaseNarrowZJ@@QAAXVAsciiStringZJ@@ZZ -- a name retail has no
// body for.  AsciiString::format (0x00888FF0, matched in
// game/Libraries/Source/WWVegas/WWLib/AsciiStringNative.cpp) is the real
// one, so it comes from ascii_string.h and is named through the real class.

class StringBaseNarrowZJ
{
protected:
	StringBaseNarrowZJ(void)
	{
		m_bfmeNarrowZJ = 0;
	}

	StringBaseNarrowZJ(const char *text);

	StringBaseNarrowZJ(const StringBaseNarrowZJ &other);

	~StringBaseNarrowZJ(void);

	char *m_bfmeNarrowZJ;
};

class AsciiStringZJ : public StringBaseNarrowZJ
{
public:
	AsciiStringZJ(void)
	{
	}

	AsciiStringZJ(const char *text) : StringBaseNarrowZJ(text)
	{
	}

	AsciiStringZJ(const AsciiStringZJ &other) : StringBaseNarrowZJ(other)
	{
	}

	~AsciiStringZJ(void)
	{
	}

	const char *bfmeTextZJ(void) const
	{
		return (m_bfmeNarrowZJ != 0) ? m_bfmeNarrowZJ + 8 : "";
	}
};

class BfmeOrderZJ
{
public:
	AsciiStringZJ bfmeNameZJ(void);

	AsciiStringZJ bfmeDescribeZJ(void);

	char m_bfmePadZJ[0x1c];
	unsigned short m_bfmeCommandZJ;
	unsigned char m_bfmePlayerZJ;
	int m_bfmeFrameZJ;
};

AsciiStringZJ BfmeOrderZJ::bfmeDescribeZJ(void)
{
	AsciiStringZJ text;

	((AsciiString &)text).format(AsciiString("%s, commandID=%d, originalPlayer=%d, originalExecFrame=%d"),
			bfmeNameZJ().bfmeTextZJ(), m_bfmeCommandZJ, m_bfmePlayerZJ, m_bfmeFrameZJ);

	return text;
}
