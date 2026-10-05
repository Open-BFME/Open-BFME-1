// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/stringinline
//
// Open-BFME5: the hero-rank palantir update at retail 0x00565720, 255 bytes.
// The format string is not a literal here: it is fetched from the text table
// by label and returned by value, so it arrives as a struct return slot.

#include "StringInline.h"

// The format call used to be spelled through the TU-local stand-in
// UnicodeStringZE, naming retail's callee
// ?format@UnicodeStringZE@@QAAXVUnicodeStringZE@@ZZ -- a name retail has no
// body for.  UnicodeString::format (0x00889190, matched in
// game/Libraries/Source/WWVegas/WWLib/unicode_string.cpp) is the real one, so
// it comes from the by-value string model and is named through the real class.
// The stand-in class itself stays: it is the type this TU's store view takes.

class StringBaseNarrowZE
{
protected:
	StringBaseNarrowZE(const char *text);

	StringBaseNarrowZE(const StringBaseNarrowZE &other);

	~StringBaseNarrowZE(void);

	char *m_bfmeNarrowZE;
};

class AsciiStringZE : public StringBaseNarrowZE
{
public:
	AsciiStringZE(const char *text) : StringBaseNarrowZE(text)
	{
	}

	AsciiStringZE(const AsciiStringZE &other) : StringBaseNarrowZE(other)
	{
	}

	~AsciiStringZE(void)
	{
	}
};

class StringBaseWideZE
{
protected:
	StringBaseWideZE(void)
	{
		m_bfmeWideZE = 0;
	}

	StringBaseWideZE(const StringBaseWideZE &other);

	~StringBaseWideZE(void);

	unsigned short *m_bfmeWideZE;
};

class UnicodeStringZE : public StringBaseWideZE
{
public:
	UnicodeStringZE(void)
	{
	}

	UnicodeStringZE(const UnicodeStringZE &other);

	~UnicodeStringZE(void)
	{
	}
};

class BfmeTextZE
{
public:
	virtual void bfmeSlot0ZE(void) = 0;
	virtual void bfmeSlot1ZE(void) = 0;
	virtual void bfmeSlot2ZE(void) = 0;
	virtual void bfmeSlot3ZE(void) = 0;
	virtual void bfmeSlot4ZE(void) = 0;
	virtual void bfmeSlot5ZE(void) = 0;
	virtual void bfmeSlot6ZE(void) = 0;
	virtual void bfmeSlot7ZE(void) = 0;
	virtual void bfmeSlot8ZE(void) = 0;
	// Retail returns its real UnicodeString here; the pure virtual is called
	// through the vftable, so nothing of it is named in this object.
	virtual UnicodeString bfmeFetchZE(AsciiStringZE label, int *exists) = 0;
};

// TU-local view of retail 0x012F19E8 (EA's WindowManager *).  The global is
// declared under its one canonical mangled name; this view keeps the members
// this body needs and is cast at the use site.
class WindowManager;

class BfmePalantirZE
{
public:
	void bfmeStoreZE(const AsciiStringZE &key, const UnicodeStringZE &value);
};

class GameTextInterface;
extern GameTextInterface *TheGameText;					// retail 0x012F147C
extern WindowManager *g_rva012F19E8WindowManager;	// retail 0x012F19E8

// ?bfmeHeroRankZE@@YADH@Z
char bfmeHeroRankZE(int rank)
{
	static AsciiStringZE s_bfmeLabelZE("APT:RankLabel");

	static AsciiStringZE s_bfmeKeyZE("APT:HeroRank");

	UnicodeStringZE value;

	((UnicodeString &)value).format(reinterpret_cast<BfmeTextZE *>(TheGameText)->bfmeFetchZE(s_bfmeLabelZE, 0), rank);

	((BfmePalantirZE *)g_rva012F19E8WindowManager)->bfmeStoreZE(s_bfmeKeyZE, value);

	return 1;
}
