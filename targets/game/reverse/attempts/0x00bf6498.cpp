// ?d_00bf6498@@YAXXZ
// partial score=0.0 date=2026-10-02
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/stringinline
//
// Open-BFME5: the time-played text at retail 0x0009C4B0, 205 bytes.  Seconds
// come in as a float and are reduced to whole days plus the hours left over.

#include "StringInline.h"

// The format call used to be spelled through the TU-local stand-in
// UnicodeStringAM, naming retail's callee
// ?format@UnicodeStringAM@@QAAXVUnicodeStringAM@@ZZ -- a name retail has no
// body for.  UnicodeString::format (0x00889190, matched in
// game/Libraries/Source/WWVegas/WWLib/unicode_string.cpp) is the real one, so
// it comes from the by-value string model and is named through the real class.
// The stand-in class itself stays: it is this function's return type, so retail
// mangles the enclosing body with it.

class StringBaseWideAM
{
protected:
	StringBaseWideAM(void)
	{
		m_bfmeWideAM = 0;
	}

	StringBaseWideAM(const StringBaseWideAM &other);

	~StringBaseWideAM(void);

	unsigned short *m_bfmeWideAM;
};

class UnicodeStringAM : public StringBaseWideAM
{
public:
	UnicodeStringAM(void)
	{
	}

	UnicodeStringAM(const UnicodeStringAM &other) : StringBaseWideAM(other)
	{
	}

	~UnicodeStringAM(void)
	{
	}
};

class BfmeTextAM
{
public:
	virtual void bfmeSlot0AM(void) = 0;
	virtual void bfmeSlot1AM(void) = 0;
	virtual void bfmeSlot2AM(void) = 0;
	virtual void bfmeSlot3AM(void) = 0;
	virtual void bfmeSlot4AM(void) = 0;
	virtual void bfmeSlot5AM(void) = 0;
	virtual void bfmeSlot6AM(void) = 0;
	virtual void bfmeSlot7AM(void) = 0;
	virtual void bfmeSlot8AM(void) = 0;
	virtual void bfmeSlot9AM(void) = 0;
	// Retail returns its real UnicodeString here; the pure virtual is called
	// through the vftable, so nothing of it is named in this object.
	virtual UnicodeString bfmeFetchAM(const char *label, int *exists) = 0;
};

extern BfmeTextAM *g_bfmeTextAM;			// retail 0x012F147C

// ?bfmeTimePlayedAM@@YG?AVUnicodeStringAM@@M@Z
UnicodeStringAM __stdcall bfmeTimePlayedAM(float seconds)
{
	UnicodeStringAM text;

	int hours = (int)seconds / 60 / 60;

	((UnicodeString &)text).format(g_bfmeTextAM->bfmeFetchAM("Apt:TimePlayed", 0), hours / 24, hours % 24);

	return text;
}
