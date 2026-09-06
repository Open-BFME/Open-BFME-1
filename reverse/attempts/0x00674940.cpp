// ?bfmeDescribeZH@BfmeOrderZH@@QAE?AVAsciiStringZH@@XZ
// partial score=0.93 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00674940, size 195.
//
// Same family as the already-landed siblings BfmeOrderDescribeZT.cpp
// (0x00676290, name comes from a virtual owner call) and
// BfmeMessageDescribeZK.cpp (0x00674B30, right after this one, name from a
// static lookup). Here the name comes from a plain (non-virtual, direct-call)
// member accessor on the order itself -- ?bfmeNameZH@BfmeOrderZH@@QAE?AVAsciiStringZH@@XZ,
// pinned at 0x0002D204, still a dump -- and the trailing three %d fields are
// read directly from this+0x1c/+0x20/+0x24. The format literal at 0x0111A620
// is "%s, logicFrame=%d, clientFrame=%d, totalCommands=%d".

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
	int m_bfmeLogicFrameZH;		// +0x1c
	int m_bfmeClientFrameZH;	// +0x20
	int m_bfmeTotalCommandsZH;	// +0x24
};

AsciiStringZH BfmeOrderZH::bfmeDescribeZH(void)
{
	AsciiStringZH text;

	int totalCommands = m_bfmeTotalCommandsZH;
	int clientFrame = m_bfmeClientFrameZH;
	int logicFrame = m_bfmeLogicFrameZH;

	text.format(AsciiStringZH("%s, logicFrame=%d, clientFrame=%d, totalCommands=%d"),
			bfmeNameZH().bfmeTextZH(), logicFrame, clientFrame, totalCommands);

	return text;
}
