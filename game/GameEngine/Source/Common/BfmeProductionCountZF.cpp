// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the production-count palantir update at retail 0x00565450,
// 210 bytes.  Unlike its siblings the property key is built per call, and the
// blank value comes from a stack character rather than from a literal.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

//
// The format call used to be spelled through the TU-local stand-in pair
// (StringBaseNarrowZF/AsciiStringZF), which named retail's callee
// ?format@StringBaseNarrowZF@@QAAXVAsciiStringZF@@ZZ -- a name retail has no
// body for.  AsciiString::format (0x00888FF0, matched in
// game/Libraries/Source/WWVegas/WWLib/AsciiStringNative.cpp) is the real
// one, so it comes from ascii_string.h and is named through the real class.
// The stand-ins below keep their layout and role: they hold the key local
// and give BfmePalantirZF its by-value argument.

class StringBaseNarrowZF
{
protected:
	StringBaseNarrowZF(void)
	{
		m_bfmeNarrowZF = 0;
	}

	StringBaseNarrowZF(const char *text);

	StringBaseNarrowZF(const StringBaseNarrowZF &other);

	~StringBaseNarrowZF(void);

	char *m_bfmeNarrowZF;
};

class AsciiStringZF : public StringBaseNarrowZF
{
public:
	AsciiStringZF(void)
	{
	}

	AsciiStringZF(const char *text) : StringBaseNarrowZF(text)
	{
	}

	AsciiStringZF(const AsciiStringZF &other);

	~AsciiStringZF(void)
	{
	}
};

class StringBaseWideZF
{
public:
	void set(const unsigned short *text, int length);

protected:
	StringBaseWideZF(void)
	{
		m_bfmeWideZF = 0;
	}

	StringBaseWideZF(const unsigned short *text);

	StringBaseWideZF(const StringBaseWideZF &other);

	~StringBaseWideZF(void);

	unsigned short *m_bfmeWideZF;
};

class UnicodeStringZF : public StringBaseWideZF
{
public:
	UnicodeStringZF(void)
	{
	}

	UnicodeStringZF(const unsigned short *text) : StringBaseWideZF(text)
	{
	}

	UnicodeStringZF(const UnicodeStringZF &other);

	~UnicodeStringZF(void)
	{
	}

	void __cdecl format(UnicodeStringZF text, ...);
};

class BfmePalantirZF
{
public:
	void bfmeStoreZF(const AsciiStringZF &key, const UnicodeStringZF &value);
};

// The global at 0x012F19E8 is EA's
// `WindowManager *g_rva012F19E8WindowManager` (defined in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp); BfmePalantirZF is
// this TU's view of the same object, so the use casts.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;	// retail 0x012F19E8

// ?bfmeProductionCountZF@@YAXHH@Z
void bfmeProductionCountZF(int slot, int count)
{
	AsciiStringZF key;

	((AsciiString &)key).format(AsciiString("APT:PalantirCommand%dProductionCount"), slot + 1);

	UnicodeStringZF value;

	if (count > 0)
		value.format(UnicodeStringZF(L"%d"), count);
	else
	{
		unsigned short blank[2] = L" ";

		value.set(blank, 1);
	}

	((BfmePalantirZF *)g_rva012F19E8WindowManager)->bfmeStoreZF(key, value);
}
