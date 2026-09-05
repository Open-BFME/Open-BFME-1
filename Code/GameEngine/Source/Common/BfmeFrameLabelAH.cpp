// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the frame label at retail 0x00664680, 153 bytes.  A negative
// frame is wrapped into the positive range before it is printed.

class StringBaseNarrowAH
{
public:
	void __cdecl format(class AsciiStringAH text, ...);

protected:
	StringBaseNarrowAH(void)
	{
		m_bfmeNarrowAH = 0;
	}

	StringBaseNarrowAH(const char *text);

	StringBaseNarrowAH(const StringBaseNarrowAH &other);

	~StringBaseNarrowAH(void);

	char *m_bfmeNarrowAH;
};

class AsciiStringAH : public StringBaseNarrowAH
{
public:
	AsciiStringAH(void)
	{
	}

	AsciiStringAH(const char *text) : StringBaseNarrowAH(text)
	{
	}

	AsciiStringAH(const AsciiStringAH &other) : StringBaseNarrowAH(other)
	{
	}

	~AsciiStringAH(void)
	{
	}

	const char *bfmeTextAH(void) const
	{
		return (m_bfmeNarrowAH != 0) ? m_bfmeNarrowAH + 8 : "";
	}
};

class BfmeFrameAH
{
public:
	AsciiStringAH bfmeLabelAH(void);

	int m_bfmeFrameAH;
	int m_bfmeCountAH;
};

AsciiStringAH BfmeFrameAH::bfmeLabelAH(void)
{
	AsciiStringAH label;

	int frame = m_bfmeFrameAH;

	if (frame < 0)
		frame += 0x10000;

	label.format(AsciiStringAH("%d(%d)"), frame, m_bfmeCountAH);

	return label;
}
