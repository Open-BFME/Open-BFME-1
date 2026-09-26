// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the exit state constructor at retail 0x00171680, 53 bytes.
// The state name goes straight into the by-value argument the base
// initialiser takes, and the vftable is installed after the field.

class StringBaseNarrowAV
{
protected:
	StringBaseNarrowAV(const char *text) throw();

	StringBaseNarrowAV(const StringBaseNarrowAV &other) throw();

	~StringBaseNarrowAV(void) throw();

	char *m_bfmeNarrowAV;
};

class AsciiStringAV : public StringBaseNarrowAV
{
public:
	AsciiStringAV(const char *text) throw() : StringBaseNarrowAV(text)
	{
	}

	AsciiStringAV(const AsciiStringAV &other) throw() : StringBaseNarrowAV(other)
	{
	}

	~AsciiStringAV(void) throw()
	{
	}
};

extern "C" void *bfmeVftableAV[];

class BfmeStateAV
{
public:
	BfmeStateAV(void *owner);

	void bfmeBaseInitAV(void *owner, AsciiStringAV name) throw();

	void *m_bfmeVfptrAV;
	char m_bfmePadAV[32];
	int m_bfmeFieldAV;
};

BfmeStateAV::BfmeStateAV(void *owner)
{
	bfmeBaseInitAV(owner, AsciiStringAV("AIExitState"));

	m_bfmeFieldAV = 0;

	m_bfmeVfptrAV = bfmeVftableAV;
}
