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

// The string this builder hands back is an AsciiString: retail's scope-exit
// release at 0x0081C7E0 calls 0x00887940, the one narrow StringBase release,
// and the bytes read the label through the 8-byte StringBase header offset with
// the null-string fallback. So AsciiStringAB derives from the real AsciiString
// instead of a TU-local one-pointer stand-in whose destructor spelled
// ??1StringBaseNarrowAB@@IAE@XZ -- a name nothing defines. The inline base
// destructor chains to ?releaseBuffer@?$StringBase@D@@AAEXXZ, which
// StringBase.cpp defines, and str() is the same narrow read the stand-in spelled
// by hand. The class name is kept, so the signature and every compiled byte stay
// put.
class AsciiStringAB : public AsciiString
{
public:
	AsciiStringAB(void)
	{
	}

	AsciiStringAB(const char *text) : AsciiString(text)
	{
	}

	AsciiStringAB(const AsciiStringAB &other) : AsciiString(other)
	{
	}

	~AsciiStringAB(void)
	{
	}

	const char *bfmeTextAB(void) const
	{
		return str();
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
		out.format(AsciiString("Data/%s/Movies/"), m_bfmeFuncAB().bfmeTextAB());
}
