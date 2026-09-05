// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00674C30, 191 bytes.  One of
// thirteen sibling descriptions in the same translation unit: each returns a
// string by value, built from a name fetched by value and a few fields.

class StringBaseNarrowZH
{
public:
	void __cdecl format(class AsciiStringZH text, ...);

protected:
	StringBaseNarrowZH(void)
	{
		m_bfmeNarrowZH = 0;
	}

	StringBaseNarrowZH(const char *text);

	StringBaseNarrowZH(const StringBaseNarrowZH &other);

	~StringBaseNarrowZH(void);

	char *m_bfmeNarrowZH;
};

class AsciiStringZH : public StringBaseNarrowZH
{
public:
	AsciiStringZH(void)
	{
	}

	AsciiStringZH(const char *text) : StringBaseNarrowZH(text)
	{
	}

	AsciiStringZH(const AsciiStringZH &other) : StringBaseNarrowZH(other)
	{
	}

	~AsciiStringZH(void)
	{
	}

	const char *bfmeTextZH(void) const
	{
		return (m_bfmeNarrowZH != 0) ? m_bfmeNarrowZH + 8 : "";
	}
};

class BfmeOrderZH
{
public:
	AsciiStringZH bfmeNameZH(void);

	AsciiStringZH bfmeDescribeZH(void);

	char m_bfmePadZH[0x1c];
	unsigned short m_bfmeCommandZH;
	unsigned char m_bfmePlayerZH;
	int m_bfmeFrameZH;
};

AsciiStringZH BfmeOrderZH::bfmeDescribeZH(void)
{
	AsciiStringZH text;

	text.format(AsciiStringZH("%s, commandID=%d, originalPlayer=%d, originalExecFrame=%d"),
			bfmeNameZH().bfmeTextZH(), m_bfmeCommandZH, m_bfmePlayerZH, m_bfmeFrameZH);

	return text;
}
