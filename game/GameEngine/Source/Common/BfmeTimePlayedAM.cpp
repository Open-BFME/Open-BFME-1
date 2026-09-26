// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the time-played text at retail 0x0009C4B0, 205 bytes.  Seconds
// come in as a float and are reduced to whole days plus the hours left over.

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

	void __cdecl format(UnicodeStringAM text, ...);
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
	virtual UnicodeStringAM bfmeFetchAM(const char *label, int *exists) = 0;
};

extern BfmeTextAM *g_bfmeTextAM;			// retail 0x012F147C

// ?bfmeTimePlayedAM@@YG?AVUnicodeStringAM@@M@Z
UnicodeStringAM __stdcall bfmeTimePlayedAM(float seconds)
{
	UnicodeStringAM text;

	int hours = (int)seconds / 60 / 60;

	text.format(g_bfmeTextAM->bfmeFetchAM("Apt:TimePlayed", 0), hours / 24, hours % 24);

	return text;
}
