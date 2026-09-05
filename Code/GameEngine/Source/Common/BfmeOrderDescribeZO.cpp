// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x006756E0, 185 bytes.
// Sibling of 0x00674C30; the fields it reports are what differ.

class StringBaseNarrowZO
{
public:
	void __cdecl format(class AsciiStringZO text, ...);

protected:
	StringBaseNarrowZO(void)
	{
		m_bfmeNarrowZO = 0;
	}

	StringBaseNarrowZO(const char *text);

	StringBaseNarrowZO(const StringBaseNarrowZO &other);

	~StringBaseNarrowZO(void);

	char *m_bfmeNarrowZO;
};

class AsciiStringZO : public StringBaseNarrowZO
{
public:
	AsciiStringZO(void)
	{
	}

	AsciiStringZO(const char *text) : StringBaseNarrowZO(text)
	{
	}

	AsciiStringZO(const AsciiStringZO &other) : StringBaseNarrowZO(other)
	{
	}

	~AsciiStringZO(void)
	{
	}

	const char *bfmeTextZO(void) const
	{
		return (m_bfmeNarrowZO != 0) ? m_bfmeNarrowZO + 8 : "";
	}
};

class BfmeOrderZO
{
public:
	AsciiStringZO bfmeNameZO(void);

	AsciiStringZO bfmeDescribeZO(void);

	char m_bfmePadZO[0x1c];
	int m_bfmeLeaveFrameZO;
	int m_bfmeLeavePlayerZO;
};

AsciiStringZO BfmeOrderZO::bfmeDescribeZO(void)
{
	AsciiStringZO text;

	text.format(AsciiStringZO("%s, leavePlayer=%d playerLeaveFrame=%d"),
			bfmeNameZO().bfmeTextZO(), m_bfmeLeavePlayerZO, m_bfmeLeaveFrameZO);

	return text;
}
