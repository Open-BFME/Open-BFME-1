// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the guarded label setter at retail 0x000ED960, 85 bytes.  The
// label arrives by value -- its address is taken out of the argument slot for
// set and again for the trailing release -- and the store is skipped when the
// target is absent.

class AsciiStringXG
{
public:
	AsciiStringXG(const AsciiStringXG &other);
	~AsciiStringXG(void);

	void set(const AsciiStringXG &other);

private:
	char *m_bfmeData;
};

class BfmeStrXG : private AsciiStringXG
{
public:
	BfmeStrXG(const AsciiStringXG &other) : AsciiStringXG(other) {}
	~BfmeStrXG(void) {}

	void bfmeSetXG(const AsciiStringXG &other)
	{
		set(other);
	}
};

class BfmeTargetXG
{
public:
	char m_bfmePad000[0x270];				// +0x000
	BfmeStrXG m_bfmeLabel;					// +0x270
};

class Gen_000ED960
{
public:
	void bfmeApplyXG(AsciiStringXG value);

	int m_bfme00;						// +0x00
	BfmeTargetXG *m_bfmeTarget;				// +0x04
};

// ?bfmeApplyXG@Gen_000ED960@@QAEXVAsciiStringXG@@@Z
void Gen_000ED960::bfmeApplyXG(AsciiStringXG value)
{
	if (m_bfmeTarget != 0)
		m_bfmeTarget->m_bfmeLabel.bfmeSetXG(value);
}
