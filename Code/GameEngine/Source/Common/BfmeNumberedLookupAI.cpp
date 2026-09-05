// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the numbered lookup at retail 0x00573580, 158 bytes.  The
// number is printed into a key and the lookup writes its own result straight
// into our caller's return slot.

class StringBaseNarrowAI
{
public:
	void __cdecl format(class AsciiStringAI text, ...);

protected:
	StringBaseNarrowAI(void)
	{
		m_bfmeNarrowAI = 0;
	}

	StringBaseNarrowAI(const char *text);

	StringBaseNarrowAI(const StringBaseNarrowAI &other);

	~StringBaseNarrowAI(void);

	char *m_bfmeNarrowAI;
};

class AsciiStringAI : public StringBaseNarrowAI
{
public:
	AsciiStringAI(void)
	{
	}

	AsciiStringAI(const char *text) : StringBaseNarrowAI(text)
	{
	}

	AsciiStringAI(const AsciiStringAI &other) : StringBaseNarrowAI(other)
	{
	}

	~AsciiStringAI(void)
	{
	}

	const char *bfmeTextAI(void) const
	{
		return (m_bfmeNarrowAI != 0) ? m_bfmeNarrowAI + 8 : "";
	}
};

class BfmeTableAI
{
public:
	AsciiStringAI bfmeLookupAI(AsciiStringAI key);

	AsciiStringAI bfmeNumberedAI(int number);
};

AsciiStringAI BfmeTableAI::bfmeNumberedAI(int number)
{
	AsciiStringAI key;

	key.format(AsciiStringAI("%d"), number);

	return bfmeLookupAI(key);
}
