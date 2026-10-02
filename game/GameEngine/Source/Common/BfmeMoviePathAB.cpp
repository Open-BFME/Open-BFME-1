// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the movie-path builder at retail 0x0081C7E0, 128 bytes.
// The name comes from a function pointer held in the object, which returns
// its string by value, so the stack slot it fills is the local destroyed at
// the end.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

//
// The format call used to be spelled through a TU-local stand-in
// (StringBaseNarrowAB::format), which named retail's callee
// ?format@StringBaseNarrowAB@@QAAXVAsciiStringAB@@ZZ -- a name retail has no
// body for.  AsciiString::format (0x00888FF0, matched in
// game/Libraries/Source/WWVegas/WWLib/AsciiStringNative.cpp) is the real
// one, so it comes from ascii_string.h and is named through the real class.

class StringBaseNarrowAB
{
protected:
	StringBaseNarrowAB(void)
	{
		m_bfmeNarrowAB = 0;
	}

	StringBaseNarrowAB(const char *text);

	StringBaseNarrowAB(const StringBaseNarrowAB &other);

	~StringBaseNarrowAB(void);

	char *m_bfmeNarrowAB;
};

class AsciiStringAB : public StringBaseNarrowAB
{
public:
	AsciiStringAB(void)
	{
	}

	AsciiStringAB(const char *text) : StringBaseNarrowAB(text)
	{
	}

	AsciiStringAB(const AsciiStringAB &other) : StringBaseNarrowAB(other)
	{
	}

	~AsciiStringAB(void)
	{
	}

	const char *bfmeTextAB(void) const
	{
		return (m_bfmeNarrowAB != 0) ? m_bfmeNarrowAB + 8 : "";
	}
};

class BfmeHookAB
{
public:
	void bfmeMakeNameAB(AsciiStringAB &out);

	char m_bfmePadAB[8];
	AsciiStringAB (__cdecl *m_bfmeFuncAB)(void);
};

void BfmeHookAB::bfmeMakeNameAB(AsciiStringAB &out)
{
	if (m_bfmeFuncAB != 0)
		((AsciiString &)out).format(AsciiString("Data/%s/Movies/"), m_bfmeFuncAB().bfmeTextAB());
}
