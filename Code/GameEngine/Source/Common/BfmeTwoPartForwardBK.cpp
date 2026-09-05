// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the two-part forward at retail 0x00731800, 69 bytes.  Both
// strings are copied into the by-value arguments the target takes, and
// nothing runs without a target.

class StringBaseNarrowBK
{
protected:
	StringBaseNarrowBK(const StringBaseNarrowBK &other) throw();

	~StringBaseNarrowBK(void) throw();

	char *m_bfmeNarrowBK;
};

class AsciiStringBK : public StringBaseNarrowBK
{
public:
	AsciiStringBK(const AsciiStringBK &other) throw() : StringBaseNarrowBK(other)
	{
	}

	~AsciiStringBK(void) throw()
	{
	}
};

class BfmeTargetBK
{
public:
	void bfmeFirstBK(AsciiStringBK text, int value) throw();

	void bfmeSecondBK(AsciiStringBK text) throw();
};

class BfmeForwarderBK
{
public:
	void bfmeSetBK(const AsciiStringBK &first, int value,
			const AsciiStringBK &second);

	char m_bfmePadBK[0x10];
	BfmeTargetBK *m_bfmeTargetBK;
};

void BfmeForwarderBK::bfmeSetBK(const AsciiStringBK &first, int value,
		const AsciiStringBK &second)
{
	if (m_bfmeTargetBK != 0)
	{
		m_bfmeTargetBK->bfmeFirstBK(first, value);

		m_bfmeTargetBK->bfmeSecondBK(second);
	}
}
