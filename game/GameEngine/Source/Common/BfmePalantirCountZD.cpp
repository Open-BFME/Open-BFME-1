// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/stringinline
//
// Open-BFME5: the palantir count update at retail 0x00565940, 252 bytes.
// A negative count blanks the property; a negative total prints the count
// alone; otherwise the pair is printed as "count/total".

extern "C" __declspec(dllimport) unsigned int wcslen(const unsigned short *text);

#include "StringInline.h"

// The format call used to be spelled through the TU-local stand-in
// UnicodeStringZD, naming retail's callee
// ?format@UnicodeStringZD@@QAAXVUnicodeStringZD@@ZZ -- a name retail has no
// body for.  UnicodeString::format (0x00889190, matched in
// game/Libraries/Source/WWVegas/WWLib/unicode_string.cpp) is the real one, so
// it comes from the by-value string model and is named through the real class.
// The stand-in class itself stays: it is the type this TU's store view takes.

class StringBaseNarrowZD
{
protected:
	StringBaseNarrowZD(const char *text);

	~StringBaseNarrowZD(void);

	char *m_bfmeNarrowZD;
};

class AsciiStringZD : public StringBaseNarrowZD
{
public:
	AsciiStringZD(const char *text) : StringBaseNarrowZD(text)
	{
	}

	~AsciiStringZD(void)
	{
	}
};

class StringBaseWideZD
{
public:
	void set(const unsigned short *text, int length);

protected:
	StringBaseWideZD(void)
	{
		m_bfmeWideZD = 0;
	}

	StringBaseWideZD(const unsigned short *text);

	StringBaseWideZD(const StringBaseWideZD &other);

	~StringBaseWideZD(void);

	unsigned short *m_bfmeWideZD;
};

class UnicodeStringZD : public StringBaseWideZD
{
public:
	UnicodeStringZD(void)
	{
	}

	UnicodeStringZD(const unsigned short *text) : StringBaseWideZD(text)
	{
	}

	UnicodeStringZD(const UnicodeStringZD &other);

	~UnicodeStringZD(void)
	{
	}
};

// TU-local view of retail 0x012F19E8 (EA's WindowManager *).  The global is
// declared under its one canonical mangled name; this view keeps the members
// this body needs and is cast at the use site.
class WindowManager;

class BfmePalantirZD
{
public:
	void bfmeStoreZD(const AsciiStringZD &key, const UnicodeStringZD &value);
};

extern WindowManager *g_rva012F19E8WindowManager;	// retail 0x012F19E8

// ?bfmePalantirCountZD@@YADHH@Z
char bfmePalantirCountZD(int count, int total)
{
	static AsciiStringZD s_bfmeKeyZD("APT:PalantirCommandPoints");

	UnicodeStringZD value;

	if (count >= 0)
	{
		if (total >= 0)
			((UnicodeString &)value).format((UnicodeString)L"%d/%d", total, count);
		else
			((UnicodeString &)value).format((UnicodeString)L"%d", count);
	}
	else
		value.set(L" ", wcslen(L" "));

	((BfmePalantirZD *)g_rva012F19E8WindowManager)->bfmeStoreZD(s_bfmeKeyZD, value);

	return 1;
}
