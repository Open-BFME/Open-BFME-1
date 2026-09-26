// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00674D20, 191 bytes.  One of
// thirteen sibling descriptions in the same translation unit: each returns a
// string by value, built from a name fetched by value and a few fields.

class StringBaseNarrowZI
{
public:
	void __cdecl format(class AsciiStringZI text, ...);

protected:
	StringBaseNarrowZI(void)
	{
		m_bfmeNarrowZI = 0;
	}

	StringBaseNarrowZI(const char *text);

	StringBaseNarrowZI(const StringBaseNarrowZI &other);

	~StringBaseNarrowZI(void);

	char *m_bfmeNarrowZI;
};

class AsciiStringZI : public StringBaseNarrowZI
{
public:
	AsciiStringZI(void)
	{
	}

	AsciiStringZI(const char *text) : StringBaseNarrowZI(text)
	{
	}

	AsciiStringZI(const AsciiStringZI &other) : StringBaseNarrowZI(other)
	{
	}

	~AsciiStringZI(void)
	{
	}

	const char *bfmeTextZI(void) const
	{
		return (m_bfmeNarrowZI != 0) ? m_bfmeNarrowZI + 8 : "";
	}
};

class BfmeOrderZI
{
public:
	AsciiStringZI bfmeNameZI(void);

	AsciiStringZI bfmeDescribeZI(void);

	char m_bfmePadZI[0x1c];
	unsigned short m_bfmeCommandZI;
	unsigned char m_bfmePlayerZI;
	int m_bfmeFrameZI;
};

AsciiStringZI BfmeOrderZI::bfmeDescribeZI(void)
{
	AsciiStringZI text;

	text.format(AsciiStringZI("%s, commandID=%d, originalPlayer=%d, originalExecFrame=%d"),
			bfmeNameZI().bfmeTextZI(), m_bfmeCommandZI, m_bfmePlayerZI, m_bfmeFrameZI);

	return text;
}
