// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the AIMoveToState constructor at retail 0x00185700, 50 bytes.
// The state name goes straight into the by-value argument the base
// initialiser takes, and the vftable is installed after the flag.

class StringBaseNarrowAT
{
protected:
	StringBaseNarrowAT(const char *text) throw();

	StringBaseNarrowAT(const StringBaseNarrowAT &other) throw();

	~StringBaseNarrowAT(void) throw();

	char *m_bfmeNarrowAT;
};

class AsciiStringAT : public StringBaseNarrowAT
{
public:
	AsciiStringAT(const char *text) throw() : StringBaseNarrowAT(text)
	{
	}

	AsciiStringAT(const AsciiStringAT &other) throw() : StringBaseNarrowAT(other)
	{
	}

	~AsciiStringAT(void) throw()
	{
	}
};

extern "C" void *bfmeVftableAT[];			// retail 0x0109B370

class BfmeMoveToStateAT
{
public:
	BfmeMoveToStateAT(void *owner);

	void bfmeBaseInitAT(void *owner, AsciiStringAT name) throw();

	void *m_bfmeVfptrAT;
	char m_bfmePadAT[0x4c];
	char m_bfmeReadyBfmeAT;
};

BfmeMoveToStateAT::BfmeMoveToStateAT(void *owner)
{
	bfmeBaseInitAT(owner, AsciiStringAT("AIMoveToState"));

	m_bfmeReadyBfmeAT = 1;

	m_bfmeVfptrAT = bfmeVftableAT;
}
