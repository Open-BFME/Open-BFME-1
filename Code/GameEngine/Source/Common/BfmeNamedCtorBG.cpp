// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: a named object constructor at retail 0x0060AAE0, 67 bytes.  The
// caller's name is copied into the by-value argument the base initialiser
// takes, and the vftable lands between two of the field stores.

class StringBaseNarrowBG
{
protected:
	StringBaseNarrowBG(const StringBaseNarrowBG &other) throw();

	~StringBaseNarrowBG(void) throw();

	char *m_bfmeNarrowBG;
};

class AsciiStringBG : public StringBaseNarrowBG
{
public:
	AsciiStringBG(const AsciiStringBG &other) throw() : StringBaseNarrowBG(other)
	{
	}

	~AsciiStringBG(void) throw()
	{
	}
};

extern "C" void *bfmeVftableBG[];

class BfmeNamedBG
{
public:
	BfmeNamedBG(const AsciiStringBG &name);

	void bfmeBaseInitBG(AsciiStringBG name) throw();

	void *volatile m_bfmeVfptrBG;
	char m_bfmePadBG[0x9c];
	volatile char m_bfmeFlagBG;
	char m_bfmePadBBG[3];
	volatile int m_bfmeABG;
	volatile int m_bfmeBBG;
	volatile int m_bfmeCBG;
};

BfmeNamedBG::BfmeNamedBG(const AsciiStringBG &name)
{
	bfmeBaseInitBG(name);

	m_bfmeFlagBG = 0;

	m_bfmeABG = 0;

	m_bfmeBBG = 0;

	m_bfmeVfptrBG = bfmeVftableBG;

	m_bfmeCBG = 0;
}
