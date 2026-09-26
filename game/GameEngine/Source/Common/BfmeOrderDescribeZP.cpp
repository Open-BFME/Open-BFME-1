// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x006757D0, 181 bytes.
// Sibling of 0x00674C30; the fields it reports are what differ.

class StringBaseNarrowZP
{
public:
	void __cdecl format(class AsciiStringZP text, ...);

protected:
	StringBaseNarrowZP(void)
	{
		m_bfmeNarrowZP = 0;
	}

	StringBaseNarrowZP(const char *text);

	StringBaseNarrowZP(const StringBaseNarrowZP &other);

	~StringBaseNarrowZP(void);

	char *m_bfmeNarrowZP;
};

class AsciiStringZP : public StringBaseNarrowZP
{
public:
	AsciiStringZP(void)
	{
	}

	AsciiStringZP(const char *text) : StringBaseNarrowZP(text)
	{
	}

	AsciiStringZP(const AsciiStringZP &other) : StringBaseNarrowZP(other)
	{
	}

	~AsciiStringZP(void)
	{
	}

	const char *bfmeTextZP(void) const
	{
		return (m_bfmeNarrowZP != 0) ? m_bfmeNarrowZP + 8 : "";
	}
};

class BfmeOrderZP
{
public:
	AsciiStringZP bfmeNameZP(void);

	AsciiStringZP bfmeDescribeZP(void);

	char m_bfmePadZP[0x1c];
	int m_bfmeLeavePlayerZP;
};

AsciiStringZP BfmeOrderZP::bfmeDescribeZP(void)
{
	AsciiStringZP text;

	text.format(AsciiStringZP("%s, leavePlayer=%d"),
			bfmeNameZP().bfmeTextZP(), m_bfmeLeavePlayerZP);

	return text;
}
