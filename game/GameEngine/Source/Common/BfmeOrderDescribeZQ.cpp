// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x006758C0, 185 bytes.
// Sibling of 0x00674C30; the fields it reports are what differ.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

//
// The format call used to be spelled through a TU-local stand-in pair
// (StringBaseNarrowZQ/AsciiStringZQ), which named retail's callee
// ?format@StringBaseNarrowZQ@@QAAXVAsciiStringZQ@@ZZ -- a name retail has no
// body for.  AsciiString::format (0x00888FF0, matched in
// game/Libraries/Source/WWVegas/WWLib/AsciiStringNative.cpp) is the real
// one, so it comes from ascii_string.h and is named through the real class.

class StringBaseNarrowZQ
{
protected:
	StringBaseNarrowZQ(void)
	{
		m_bfmeNarrowZQ = 0;
	}

	StringBaseNarrowZQ(const char *text);

	StringBaseNarrowZQ(const StringBaseNarrowZQ &other);

	~StringBaseNarrowZQ(void);

	char *m_bfmeNarrowZQ;
};

class AsciiStringZQ : public StringBaseNarrowZQ
{
public:
	AsciiStringZQ(void)
	{
	}

	AsciiStringZQ(const char *text) : StringBaseNarrowZQ(text)
	{
	}

	AsciiStringZQ(const AsciiStringZQ &other) : StringBaseNarrowZQ(other)
	{
	}

	~AsciiStringZQ(void)
	{
	}

	const char *bfmeTextZQ(void) const
	{
		return (m_bfmeNarrowZQ != 0) ? m_bfmeNarrowZQ + 8 : "";
	}
};

class BfmeOrderZQ
{
public:
	AsciiStringZQ bfmeNameZQ(void);

	AsciiStringZQ bfmeDescribeZQ(void);

	char m_bfmePadZQ[0x1c];
	int m_bfmeStartFrameZQ;
	int m_bfmeEndFrameZQ;
};

AsciiStringZQ BfmeOrderZQ::bfmeDescribeZQ(void)
{
	AsciiStringZQ text;

	((AsciiString &)text).format(AsciiString("%s, startFrame=%d endFrame=%d"),
			bfmeNameZQ().bfmeTextZQ(), m_bfmeStartFrameZQ, m_bfmeEndFrameZQ);

	return text;
}
