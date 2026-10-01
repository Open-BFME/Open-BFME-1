// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the message description at retail 0x00674B30, 197 bytes.
// Same shape as the order descriptions, but the name comes from a static
// lookup on the command type rather than from a member.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

//
// The format call used to be spelled through a TU-local stand-in pair
// (StringBaseNarrowZK/AsciiStringZK), which named retail's callee
// ?format@StringBaseNarrowZK@@QAAXVAsciiStringZK@@ZZ -- a name retail has no
// body for.  AsciiString::format (0x00888FF0, matched in
// game/Libraries/Source/WWVegas/WWLib/AsciiStringNative.cpp) is the real
// one, so it comes from ascii_string.h and is named through the real class.

class StringBaseNarrowZK
{
protected:
	StringBaseNarrowZK(void)
	{
		m_bfmeNarrowZK = 0;
	}

	StringBaseNarrowZK(const char *text);

	StringBaseNarrowZK(const StringBaseNarrowZK &other);

	~StringBaseNarrowZK(void);

	char *m_bfmeNarrowZK;
};

class AsciiStringZK : public StringBaseNarrowZK
{
public:
	AsciiStringZK(void)
	{
	}

	AsciiStringZK(const char *text) : StringBaseNarrowZK(text)
	{
	}

	AsciiStringZK(const AsciiStringZK &other) : StringBaseNarrowZK(other)
	{
	}

	~AsciiStringZK(void)
	{
	}

	const char *bfmeTextZK(void) const
	{
		return (m_bfmeNarrowZK != 0) ? m_bfmeNarrowZK + 8 : "";
	}
};

class BfmeMessageZK
{
public:
	static AsciiStringZK bfmeTypeNameZK(int type);

	AsciiStringZK bfmeDescribeZK(void);

	char m_bfmePadAZK[8];
	int m_bfmeFrameZK;
	int m_bfmePlayerZK;
	unsigned short m_bfmeIdZK;
	char m_bfmePadBZK[0x12];
	int m_bfmeTypeZK;
};

AsciiStringZK BfmeMessageZK::bfmeDescribeZK(void)
{
	AsciiStringZK text;

	((AsciiString &)text).format(AsciiString("GameMessage:%s, frame=%d, player=%d, id=%d"),
			bfmeTypeNameZK(m_bfmeTypeZK).bfmeTextZK(), m_bfmeFrameZK, m_bfmePlayerZK,
			m_bfmeIdZK);

	return text;
}
