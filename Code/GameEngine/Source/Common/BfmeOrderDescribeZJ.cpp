// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00674E10, 191 bytes.  One of
// thirteen sibling descriptions in the same translation unit: each returns a
// string by value, built from a name fetched by value and a few fields.

class StringBaseNarrowZJ
{
public:
	void __cdecl format(class AsciiStringZJ text, ...);

protected:
	StringBaseNarrowZJ(void)
	{
		m_bfmeNarrowZJ = 0;
	}

	StringBaseNarrowZJ(const char *text);

	StringBaseNarrowZJ(const StringBaseNarrowZJ &other);

	~StringBaseNarrowZJ(void);

	char *m_bfmeNarrowZJ;
};

class AsciiStringZJ : public StringBaseNarrowZJ
{
public:
	AsciiStringZJ(void)
	{
	}

	AsciiStringZJ(const char *text) : StringBaseNarrowZJ(text)
	{
	}

	AsciiStringZJ(const AsciiStringZJ &other) : StringBaseNarrowZJ(other)
	{
	}

	~AsciiStringZJ(void)
	{
	}

	const char *bfmeTextZJ(void) const
	{
		return (m_bfmeNarrowZJ != 0) ? m_bfmeNarrowZJ + 8 : "";
	}
};

class BfmeOrderZJ
{
public:
	AsciiStringZJ bfmeNameZJ(void);

	AsciiStringZJ bfmeDescribeZJ(void);

	char m_bfmePadZJ[0x1c];
	unsigned short m_bfmeCommandZJ;
	unsigned char m_bfmePlayerZJ;
	int m_bfmeFrameZJ;
};

AsciiStringZJ BfmeOrderZJ::bfmeDescribeZJ(void)
{
	AsciiStringZJ text;

	text.format(AsciiStringZJ("%s, commandID=%d, originalPlayer=%d, originalExecFrame=%d"),
			bfmeNameZJ().bfmeTextZJ(), m_bfmeCommandZJ, m_bfmePlayerZJ, m_bfmeFrameZJ);

	return text;
}
