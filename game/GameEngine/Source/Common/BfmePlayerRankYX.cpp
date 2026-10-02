// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/stringinline
//
// Open-BFME5: the player-rank palantir update at retail 0x00565860, 177 bytes.

#include "StringInline.h"

// The format call used to be spelled through the TU-local stand-in
// UnicodeStringYX, naming retail's callee
// ?format@UnicodeStringYX@@QAAXVUnicodeStringYX@@ZZ -- a name retail has no
// body for.  UnicodeString::format (0x00889190, matched in
// game/Libraries/Source/WWVegas/WWLib/unicode_string.cpp) is the real one, so
// it comes from the by-value string model and is named through the real class.
// The stand-in class itself stays: it is the type this TU's store view takes.

class StringBaseNarrowYX
{
protected:
	StringBaseNarrowYX(const char *text);

	~StringBaseNarrowYX(void);

	char *m_bfmeNarrowYX;
};

class AsciiStringYX : public StringBaseNarrowYX
{
public:
	AsciiStringYX(const char *text) : StringBaseNarrowYX(text)
	{
	}

	~AsciiStringYX(void)
	{
	}
};

class StringBaseWideYX
{
protected:
	StringBaseWideYX(void)
	{
		m_bfmeWideYX = 0;
	}

	StringBaseWideYX(const unsigned short *text);

	StringBaseWideYX(const StringBaseWideYX &other);

	~StringBaseWideYX(void);

	unsigned short *m_bfmeWideYX;
};

class UnicodeStringYX : public StringBaseWideYX
{
public:
	UnicodeStringYX(void)
	{
	}

	UnicodeStringYX(const unsigned short *text) : StringBaseWideYX(text)
	{
	}

	UnicodeStringYX(const UnicodeStringYX &other);

	~UnicodeStringYX(void)
	{
	}

};

class BfmePalantirYX
{
public:
	void bfmeStoreYX(const AsciiStringYX &key, const UnicodeStringYX &value);
};

// Retail's WindowManager global at 0x012F19E8, under the one linked-build
// spelling.  BfmePalantirYX above is this TU's view of the same object.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

static inline BfmePalantirYX *bfmePalantirYXView(void)
{
	return (BfmePalantirYX *)g_rva012F19E8WindowManager;
}

// ?bfmeSetRankYX@@YADH@Z
char bfmeSetRankYX(int rank)
{
	static AsciiStringYX s_bfmeKeyYX("APT:PlayerRank");

	UnicodeStringYX value;

	((UnicodeString &)value).format((UnicodeString)L"%d", rank);

	bfmePalantirYXView()->bfmeStoreYX(s_bfmeKeyYX, value);

	return 1;
}
