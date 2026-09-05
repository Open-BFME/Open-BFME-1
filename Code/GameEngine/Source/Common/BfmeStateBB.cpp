// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the AIAttackMeleeApproachState constructor at retail 0x0017F7F0, 66 bytes.
// Same family as 0x00185700: the state name goes into the by-value argument
// the base initialiser takes.

class StringBaseNarrowBB
{
protected:
	StringBaseNarrowBB(const char *text) throw();

	StringBaseNarrowBB(const StringBaseNarrowBB &other) throw();

	~StringBaseNarrowBB(void) throw();

	char *m_bfmeNarrowBB;
};

class AsciiStringBB : public StringBaseNarrowBB
{
public:
	AsciiStringBB(const char *text) throw() : StringBaseNarrowBB(text)
	{
	}

	AsciiStringBB(const AsciiStringBB &other) throw() : StringBaseNarrowBB(other)
	{
	}

	~AsciiStringBB(void) throw()
	{
	}
};

extern "C" void *bfmeVftableBB[];

class BfmeStateBB
{
public:
	BfmeStateBB(void *owner);

	void bfmeBaseInitBB(void *owner, AsciiStringBB name) throw();

	void *volatile m_bfmeVfptrBB;
	char m_bfmePadBB[0x4c];
	volatile int m_bfmeABB;
	volatile int m_bfmeBBB;
	volatile int m_bfmeCBB;
	volatile int m_bfmeDBB;
	volatile int m_bfmeEBB;
	volatile int m_bfmeFBB;
};

BfmeStateBB::BfmeStateBB(void *owner)
{
	bfmeBaseInitBB(owner, AsciiStringBB("AIAttackMeleeApproachState"));

	m_bfmeABB = 0;

	m_bfmeVfptrBB = bfmeVftableBB;

	m_bfmeBBB = 0;
	m_bfmeCBB = 0;
	m_bfmeDBB = 0;
	m_bfmeEBB = 0;
	m_bfmeFBB = 0;
}
