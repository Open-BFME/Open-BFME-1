// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/stringinline
//
// Open-BFME5: the numbered display name at retail 0x00451240, 212 bytes.  A
// count above one is appended in brackets, and the append reads both the
// characters and the length behind a single null test.

#include "StringInline.h"

// The format call used to be spelled through the TU-local stand-in
// UnicodeStringAP, naming retail's callee
// ?format@UnicodeStringAP@@QAAXVUnicodeStringAP@@ZZ -- a name retail has no
// body for.  UnicodeString::format (0x00889190, matched in
// game/Libraries/Source/WWVegas/WWLib/unicode_string.cpp) is the real one, so
// it comes from the by-value string model and is named through the real class.
// The stand-in class itself stays: it is these methods' return type, so retail
// mangles the enclosing bodies with it.

class StringBaseWideAP
{
public:
	void bfmeConcatAP(const unsigned short *text, int length);

protected:
	StringBaseWideAP(void)
	{
		m_bfmeWideAP = 0;
	}

	StringBaseWideAP(const unsigned short *text);

	StringBaseWideAP(const StringBaseWideAP &other);

	~StringBaseWideAP(void);

	unsigned short *m_bfmeWideAP;
};

class UnicodeStringAP : public StringBaseWideAP
{
public:
	UnicodeStringAP(void)
	{
	}

	UnicodeStringAP(const unsigned short *text) : StringBaseWideAP(text)
	{
	}

	UnicodeStringAP(const UnicodeStringAP &other) : StringBaseWideAP(other)
	{
	}

	~UnicodeStringAP(void)
	{
	}

	const unsigned short *bfmeTextAP(void) const
	{
		return (m_bfmeWideAP != 0) ? m_bfmeWideAP + 4 : L"";
	}

	int bfmeLengthAP(void) const
	{
		return (m_bfmeWideAP != 0) ? m_bfmeWideAP[2] : 0;
	}
};

class BfmeEntryAP
{
public:
	UnicodeStringAP bfmeBaseNameAP(void);

	UnicodeStringAP bfmeDisplayNameAP(void);

	char m_bfmePadAP[0x20];
	int m_bfmeCountAP;
};

UnicodeStringAP BfmeEntryAP::bfmeDisplayNameAP(void)
{
	UnicodeStringAP name = bfmeBaseNameAP();

	int count = m_bfmeCountAP;

	if (count >= 2)
	{
		UnicodeStringAP suffix;

		((UnicodeString &)suffix).format((UnicodeString)L" (%d)", count);

		name.bfmeConcatAP(suffix.bfmeTextAP(), suffix.bfmeLengthAP());
	}

	return name;
}
