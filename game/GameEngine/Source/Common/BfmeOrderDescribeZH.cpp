// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00674C30, 191 bytes.  One of
// thirteen sibling descriptions in the same translation unit: each returns a
// string by value, built from a name fetched by value and a few fields.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

//
// The format call used to be spelled through a TU-local stand-in pair
// (StringBaseNarrowZH/AsciiStringZH), which named retail's callee
// ?format@StringBaseNarrowZH@@QAAXVAsciiStringZH@@ZZ -- a name retail has no
// body for.  AsciiString::format (0x00888FF0, matched in
// game/Libraries/Source/WWVegas/WWLib/AsciiStringNative.cpp) is the real
// one, so it comes from ascii_string.h and is named through the real class.

class StringBaseNarrowZH
{
protected:
	StringBaseNarrowZH(void)
	{
		m_bfmeNarrowZH = 0;
	}

	StringBaseNarrowZH(const char *text);

	StringBaseNarrowZH(const StringBaseNarrowZH &other);

	~StringBaseNarrowZH(void);

	char *m_bfmeNarrowZH;
};

class AsciiStringZH : public StringBaseNarrowZH
{
public:
	AsciiStringZH(void)
	{
	}

	AsciiStringZH(const char *text) : StringBaseNarrowZH(text)
	{
	}

	AsciiStringZH(const AsciiStringZH &other) : StringBaseNarrowZH(other)
	{
	}

	~AsciiStringZH(void)
	{
	}

	const char *bfmeTextZH(void) const
	{
		return (m_bfmeNarrowZH != 0) ? m_bfmeNarrowZH + 8 : "";
	}
};

class BfmeOrderZH
{
public:
	AsciiStringZH bfmeNameZH(void);

	AsciiStringZH bfmeDescribeZH(void);

	char m_bfmePadZH[0x1c];
	unsigned short m_bfmeCommandZH;
	unsigned char m_bfmePlayerZH;
	int m_bfmeFrameZH;
};

AsciiStringZH BfmeOrderZH::bfmeDescribeZH(void)
{
	AsciiStringZH text;

	((AsciiString &)text).format(AsciiString("%s, commandID=%d, originalPlayer=%d, originalExecFrame=%d"),
			bfmeNameZH().bfmeTextZH(), m_bfmeCommandZH, m_bfmePlayerZH, m_bfmeFrameZH);

	return text;
}
