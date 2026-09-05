// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00675A80, 201 bytes.
// Sibling of 0x00674C30, but the field it reports is itself a string, so the
// null-test-and-skip-the-header expansion appears twice.

class StringBaseNarrowZR
{
public:
	void __cdecl format(class AsciiStringZR text, ...);

protected:
	StringBaseNarrowZR(void)
	{
		m_bfmeNarrowZR = 0;
	}

	StringBaseNarrowZR(const char *text);

	StringBaseNarrowZR(const StringBaseNarrowZR &other);

	~StringBaseNarrowZR(void);

	char *m_bfmeNarrowZR;
};

class AsciiStringZR : public StringBaseNarrowZR
{
public:
	AsciiStringZR(void)
	{
	}

	AsciiStringZR(const char *text) : StringBaseNarrowZR(text)
	{
	}

	AsciiStringZR(const AsciiStringZR &other) : StringBaseNarrowZR(other)
	{
	}

	~AsciiStringZR(void)
	{
	}

	const char *bfmeTextZR(void) const
	{
		return (m_bfmeNarrowZR != 0) ? m_bfmeNarrowZR + 8 : "";
	}
};

class BfmeOrderZR
{
public:
	AsciiStringZR bfmeNameZR(void);

	AsciiStringZR bfmeDescribeZR(void);

	char m_bfmePadZR[0x1c];
	AsciiStringZR m_bfmeChallengeZR;
};

AsciiStringZR BfmeOrderZR::bfmeDescribeZR(void)
{
	AsciiStringZR text;

	text.format(AsciiStringZR("%s, challenge=%s"),
			bfmeNameZR().bfmeTextZR(), m_bfmeChallengeZR.bfmeTextZR());

	return text;
}
