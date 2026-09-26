// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00674F00, 182 bytes.
// Sibling of 0x00674C30; the fields it reports are what differ.

class StringBaseNarrowZM
{
public:
	void __cdecl format(class AsciiStringZM text, ...);

protected:
	StringBaseNarrowZM(void)
	{
		m_bfmeNarrowZM = 0;
	}

	StringBaseNarrowZM(const char *text);

	StringBaseNarrowZM(const StringBaseNarrowZM &other);

	~StringBaseNarrowZM(void);

	char *m_bfmeNarrowZM;
};

class AsciiStringZM : public StringBaseNarrowZM
{
public:
	AsciiStringZM(void)
	{
	}

	AsciiStringZM(const char *text) : StringBaseNarrowZM(text)
	{
	}

	AsciiStringZM(const AsciiStringZM &other) : StringBaseNarrowZM(other)
	{
	}

	~AsciiStringZM(void)
	{
	}

	const char *bfmeTextZM(void) const
	{
		return (m_bfmeNarrowZM != 0) ? m_bfmeNarrowZM + 8 : "";
	}
};

class BfmeOrderZM
{
public:
	AsciiStringZM bfmeNameZM(void);

	AsciiStringZM bfmeDescribeZM(void);

	char m_bfmePadZM[0x1c];
	unsigned char m_bfmeLeavingZM;
};

AsciiStringZM BfmeOrderZM::bfmeDescribeZM(void)
{
	AsciiStringZM text;

	text.format(AsciiStringZM("%s, leavingPlayer=%d"),
			bfmeNameZM().bfmeTextZM(), m_bfmeLeavingZM);

	return text;
}
