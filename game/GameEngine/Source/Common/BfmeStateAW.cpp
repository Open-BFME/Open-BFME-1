// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the second crate pick-up state constructor at retail 0x0018AE00, 53 bytes.
// The state name goes straight into the by-value argument the base
// initialiser takes, and the vftable is installed after the field.

class StringBaseNarrowAW
{
protected:
	StringBaseNarrowAW(const char *text) throw();

	StringBaseNarrowAW(const StringBaseNarrowAW &other) throw();

	~StringBaseNarrowAW(void) throw();

	char *m_bfmeNarrowAW;
};

class AsciiStringAW : public StringBaseNarrowAW
{
public:
	AsciiStringAW(const char *text) throw() : StringBaseNarrowAW(text)
	{
	}

	AsciiStringAW(const AsciiStringAW &other) throw() : StringBaseNarrowAW(other)
	{
	}

	~AsciiStringAW(void) throw()
	{
	}
};

extern "C" void *bfmeVftableAW[];

class BfmeStateAW
{
public:
	BfmeStateAW(void *owner);

	void bfmeBaseInitAW(void *owner, AsciiStringAW name) throw();

	void *m_bfmeVfptrAW;
	char m_bfmePadAW[76];
	int m_bfmeFieldAW;
};

BfmeStateAW::BfmeStateAW(void *owner)
{
	bfmeBaseInitAW(owner, AsciiStringAW("AIAttackPickUpCrateState"));

	m_bfmeFieldAW = 0;

	m_bfmeVfptrAW = bfmeVftableAW;
}
