// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the AIBackAwayState constructor at retail 0x001804B0, 57 bytes.
// Same family as 0x00185700: the state name goes into the by-value argument
// the base initialiser takes.

class StringBaseNarrowBC
{
protected:
	StringBaseNarrowBC(const char *text) throw();

	StringBaseNarrowBC(const StringBaseNarrowBC &other) throw();

	~StringBaseNarrowBC(void) throw();

	char *m_bfmeNarrowBC;
};

class AsciiStringBC : public StringBaseNarrowBC
{
public:
	AsciiStringBC(const char *text) throw() : StringBaseNarrowBC(text)
	{
	}

	AsciiStringBC(const AsciiStringBC &other) throw() : StringBaseNarrowBC(other)
	{
	}

	~AsciiStringBC(void) throw()
	{
	}
};

extern "C" void *bfmeVftableBC[];

class BfmeStateBC
{
public:
	BfmeStateBC(void *owner, const char *name);

	void bfmeBaseInitBC(void *owner, AsciiStringBC name) throw();

	void *volatile m_bfmeVfptrBC;
	char m_bfmePadBC[0x4c];
	volatile int m_bfmeCountBC;
	volatile char m_bfmeFlagBC;
};

BfmeStateBC::BfmeStateBC(void *owner, const char *name)
{
	bfmeBaseInitBC(owner, AsciiStringBC(name));

	m_bfmeFlagBC = 0;

	m_bfmeCountBC = 0;

	m_bfmeVfptrBC = bfmeVftableBC;
}
