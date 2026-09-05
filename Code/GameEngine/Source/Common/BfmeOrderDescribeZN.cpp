// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00674FF0, 181 bytes.
// Sibling of 0x00674C30; the fields it reports are what differ.

class StringBaseNarrowZN
{
public:
	void __cdecl format(class AsciiStringZN text, ...);

protected:
	StringBaseNarrowZN(void)
	{
		m_bfmeNarrowZN = 0;
	}

	StringBaseNarrowZN(const char *text);

	StringBaseNarrowZN(const StringBaseNarrowZN &other);

	~StringBaseNarrowZN(void);

	char *m_bfmeNarrowZN;
};

class AsciiStringZN : public StringBaseNarrowZN
{
public:
	AsciiStringZN(void)
	{
	}

	AsciiStringZN(const char *text) : StringBaseNarrowZN(text)
	{
	}

	AsciiStringZN(const AsciiStringZN &other) : StringBaseNarrowZN(other)
	{
	}

	~AsciiStringZN(void)
	{
	}

	const char *bfmeTextZN(void) const
	{
		return (m_bfmeNarrowZN != 0) ? m_bfmeNarrowZN + 8 : "";
	}
};

class BfmeOrderZN
{
public:
	AsciiStringZN bfmeNameZN(void);

	AsciiStringZN bfmeDescribeZN(void);

	char m_bfmePadZN[0x1c];
	int m_bfmeDestroyZN;
};

AsciiStringZN BfmeOrderZN::bfmeDescribeZN(void)
{
	AsciiStringZN text;

	text.format(AsciiStringZN("%s, destroyPlayer=%d"),
			bfmeNameZN().bfmeTextZN(), m_bfmeDestroyZN);

	return text;
}
