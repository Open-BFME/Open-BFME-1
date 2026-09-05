// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the crate pick-up state constructor at retail 0x0015D000, 53 bytes.
// The state name goes straight into the by-value argument the base
// initialiser takes, and the vftable is installed after the field.

class StringBaseNarrowAU
{
protected:
	StringBaseNarrowAU(const char *text) throw();

	StringBaseNarrowAU(const StringBaseNarrowAU &other) throw();

	~StringBaseNarrowAU(void) throw();

	char *m_bfmeNarrowAU;
};

class AsciiStringAU : public StringBaseNarrowAU
{
public:
	AsciiStringAU(const char *text) throw() : StringBaseNarrowAU(text)
	{
	}

	AsciiStringAU(const AsciiStringAU &other) throw() : StringBaseNarrowAU(other)
	{
	}

	~AsciiStringAU(void) throw()
	{
	}
};

extern "C" void *bfmeVftableAU[];

class BfmeStateAU
{
public:
	BfmeStateAU(void *owner);

	void bfmeBaseInitAU(void *owner, AsciiStringAU name) throw();

	void *m_bfmeVfptrAU;
	char m_bfmePadAU[76];
	int m_bfmeFieldAU;
};

BfmeStateAU::BfmeStateAU(void *owner)
{
	bfmeBaseInitAU(owner, AsciiStringAU("AIAttackPickUpCrateState"));

	m_bfmeFieldAU = 0;

	m_bfmeVfptrAU = bfmeVftableAU;
}
