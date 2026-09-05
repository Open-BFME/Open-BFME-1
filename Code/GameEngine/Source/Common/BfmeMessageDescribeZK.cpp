// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the message description at retail 0x00674B30, 197 bytes.
// Same shape as the order descriptions, but the name comes from a static
// lookup on the command type rather than from a member.

class StringBaseNarrowZK
{
public:
	void __cdecl format(class AsciiStringZK text, ...);

protected:
	StringBaseNarrowZK(void)
	{
		m_bfmeNarrowZK = 0;
	}

	StringBaseNarrowZK(const char *text);

	StringBaseNarrowZK(const StringBaseNarrowZK &other);

	~StringBaseNarrowZK(void);

	char *m_bfmeNarrowZK;
};

class AsciiStringZK : public StringBaseNarrowZK
{
public:
	AsciiStringZK(void)
	{
	}

	AsciiStringZK(const char *text) : StringBaseNarrowZK(text)
	{
	}

	AsciiStringZK(const AsciiStringZK &other) : StringBaseNarrowZK(other)
	{
	}

	~AsciiStringZK(void)
	{
	}

	const char *bfmeTextZK(void) const
	{
		return (m_bfmeNarrowZK != 0) ? m_bfmeNarrowZK + 8 : "";
	}
};

class BfmeMessageZK
{
public:
	static AsciiStringZK bfmeTypeNameZK(int type);

	AsciiStringZK bfmeDescribeZK(void);

	char m_bfmePadAZK[8];
	int m_bfmeFrameZK;
	int m_bfmePlayerZK;
	unsigned short m_bfmeIdZK;
	char m_bfmePadBZK[0x12];
	int m_bfmeTypeZK;
};

AsciiStringZK BfmeMessageZK::bfmeDescribeZK(void)
{
	AsciiStringZK text;

	text.format(AsciiStringZK("GameMessage:%s, frame=%d, player=%d, id=%d"),
			bfmeTypeNameZK(m_bfmeTypeZK).bfmeTextZK(), m_bfmeFrameZK, m_bfmePlayerZK,
			m_bfmeIdZK);

	return text;
}
