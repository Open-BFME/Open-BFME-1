// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/stringinline
//
// Open-BFME5: the version text at retail 0x000AED00, 198 bytes.  The format
// string is not a literal: it is fetched from the text table by label and its
// characters are handed to the temporary that format takes by value.

#include "StringInline.h"

// The format call used to be spelled through the TU-local stand-in
// UnicodeStringAL, naming retail's callee
// ?format@UnicodeStringAL@@QAAXVUnicodeStringAL@@ZZ -- a name retail has no
// body for.  UnicodeString::format (0x00889190, matched in
// game/Libraries/Source/WWVegas/WWLib/unicode_string.cpp) is the real one, so
// it comes from the by-value string model and is named through the real class.
// The existing UnicodeStringAL return view is also used by the four matched
// callers. It has no storage beyond its native UnicodeString base. Its inline
// lifetime members now reach the matched StringBase<unsigned short> bodies.
// bfmeTextAL keeps the original inlined character access at header +8.

class UnicodeStringAL : public UnicodeString
{
public:
	UnicodeStringAL(void)
	{
	}

	UnicodeStringAL(const unsigned short *text) : UnicodeString(text)
	{
	}

	UnicodeStringAL(const UnicodeStringAL &other) : UnicodeString(other)
	{
	}

	~UnicodeStringAL(void)
	{
	}

	const unsigned short *bfmeTextAL(void) const
	{
		const unsigned short *data = *reinterpret_cast<const unsigned short *const *>(this);
		return data ? data + 4 : L"";
	}
};

class BfmeTextAL
{
public:
	virtual void bfmeSlot0AL(void) = 0;
	virtual void bfmeSlot1AL(void) = 0;
	virtual void bfmeSlot2AL(void) = 0;
	virtual void bfmeSlot3AL(void) = 0;
	virtual void bfmeSlot4AL(void) = 0;
	virtual void bfmeSlot5AL(void) = 0;
	virtual void bfmeSlot6AL(void) = 0;
	virtual void bfmeSlot7AL(void) = 0;
	virtual void bfmeSlot8AL(void) = 0;
	virtual void bfmeSlot9AL(void) = 0;
	// Retail returns its real UnicodeString here; the pure virtual is called
	// through the vftable, so nothing of it is named in this object.
	virtual UnicodeString bfmeFetchAL(const char *label, int *exists) = 0;
};

class GameTextInterface;
extern GameTextInterface *TheGameText;			// retail 0x012F147C

class BfmeVersionAL
{
public:
	UnicodeStringAL bfmeVersionTextAL(void);

	int m_bfmeMajorAL;
	int m_bfmeMinorAL;
};

UnicodeStringAL BfmeVersionAL::bfmeVersionTextAL(void)
{
	UnicodeStringAL text;

	((UnicodeString &)text).format((UnicodeString)(((UnicodeStringAL &)reinterpret_cast<BfmeTextAL *>(TheGameText)->bfmeFetchAL("Version:Format2", 0)).bfmeTextAL()),
			m_bfmeMajorAL, m_bfmeMinorAL);

	return text;
}
