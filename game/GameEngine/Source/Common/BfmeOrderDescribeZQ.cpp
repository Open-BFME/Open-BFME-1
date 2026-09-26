// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x006758C0, 185 bytes.
// Sibling of 0x00674C30; the fields it reports are what differ.

class StringBaseNarrowZQ
{
public:
	void __cdecl format(class AsciiStringZQ text, ...);

protected:
	StringBaseNarrowZQ(void)
	{
		m_bfmeNarrowZQ = 0;
	}

	StringBaseNarrowZQ(const char *text);

	StringBaseNarrowZQ(const StringBaseNarrowZQ &other);

	~StringBaseNarrowZQ(void);

	char *m_bfmeNarrowZQ;
};

class AsciiStringZQ : public StringBaseNarrowZQ
{
public:
	AsciiStringZQ(void)
	{
	}

	AsciiStringZQ(const char *text) : StringBaseNarrowZQ(text)
	{
	}

	AsciiStringZQ(const AsciiStringZQ &other) : StringBaseNarrowZQ(other)
	{
	}

	~AsciiStringZQ(void)
	{
	}

	const char *bfmeTextZQ(void) const
	{
		return (m_bfmeNarrowZQ != 0) ? m_bfmeNarrowZQ + 8 : "";
	}
};

class BfmeOrderZQ
{
public:
	AsciiStringZQ bfmeNameZQ(void);

	AsciiStringZQ bfmeDescribeZQ(void);

	char m_bfmePadZQ[0x1c];
	int m_bfmeStartFrameZQ;
	int m_bfmeEndFrameZQ;
};

AsciiStringZQ BfmeOrderZQ::bfmeDescribeZQ(void)
{
	AsciiStringZQ text;

	text.format(AsciiStringZQ("%s, startFrame=%d endFrame=%d"),
			bfmeNameZQ().bfmeTextZQ(), m_bfmeStartFrameZQ, m_bfmeEndFrameZQ);

	return text;
}
