// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the numbered display name at retail 0x00451240, 212 bytes.  A
// count above one is appended in brackets, and the append reads both the
// characters and the length behind a single null test.

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

	void __cdecl format(UnicodeStringAP text, ...);

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

		suffix.format(UnicodeStringAP(L" (%d)"), count);

		name.bfmeConcatAP(suffix.bfmeTextAP(), suffix.bfmeLengthAP());
	}

	return name;
}
