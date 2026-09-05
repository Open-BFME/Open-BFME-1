// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00675D40, 219 bytes.
// Sibling of 0x00675A80 with two string fields rather than one.

class StringBaseNarrowZS
{
public:
	void __cdecl format(class AsciiStringZS text, ...);

protected:
	StringBaseNarrowZS(void)
	{
		m_bfmeNarrowZS = 0;
	}

	StringBaseNarrowZS(const char *text);

	StringBaseNarrowZS(const StringBaseNarrowZS &other);

	~StringBaseNarrowZS(void);

	char *m_bfmeNarrowZS;
};

class AsciiStringZS : public StringBaseNarrowZS
{
public:
	AsciiStringZS(void)
	{
	}

	AsciiStringZS(const char *text) : StringBaseNarrowZS(text)
	{
	}

	AsciiStringZS(const AsciiStringZS &other) : StringBaseNarrowZS(other)
	{
	}

	~AsciiStringZS(void)
	{
	}

	const char *bfmeTextZS(void) const
	{
		return (m_bfmeNarrowZS != 0) ? m_bfmeNarrowZS + 8 : "";
	}
};

class BfmeOrderZS
{
public:
	AsciiStringZS bfmeNameZS(void);

	AsciiStringZS bfmeDescribeZS(void);

	char m_bfmePadZS[0x1c];
	AsciiStringZS m_bfmeAuthKeyZS;
	AsciiStringZS m_bfmeAuthTokenZS;
};

AsciiStringZS BfmeOrderZS::bfmeDescribeZS(void)
{
	AsciiStringZS text;

	text.format(AsciiStringZS("%s, authToken=%s, authKey=%s"),
			bfmeNameZS().bfmeTextZS(), m_bfmeAuthTokenZS.bfmeTextZS(),
			m_bfmeAuthKeyZS.bfmeTextZS());

	return text;
}
