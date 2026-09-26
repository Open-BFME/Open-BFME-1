// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the AITNGuardOuter constructor at retail 0x0018AD00, 61 bytes.
// Same family as 0x00185700: the state name goes into the by-value argument
// the base initialiser takes.

class StringBaseNarrowAY
{
protected:
	StringBaseNarrowAY(const char *text) throw();

	StringBaseNarrowAY(const StringBaseNarrowAY &other) throw();

	~StringBaseNarrowAY(void) throw();

	char *m_bfmeNarrowAY;
};

class AsciiStringAY : public StringBaseNarrowAY
{
public:
	AsciiStringAY(const char *text) throw() : StringBaseNarrowAY(text)
	{
	}

	AsciiStringAY(const AsciiStringAY &other) throw() : StringBaseNarrowAY(other)
	{
	}

	~AsciiStringAY(void) throw()
	{
	}
};

extern "C" void *bfmeVftableAY[];
extern "C" void *bfmeGuardTableAY[];

class BfmeStateAY
{
public:
	BfmeStateAY(void *owner);

	void bfmeBaseInitAY(void *owner, AsciiStringAY name) throw();

	void *volatile m_bfmeVfptrAY;
	char m_bfmePadAY[0x20];
	void *volatile m_bfmeTableAY;
	volatile int m_bfmeFirstAY;
	volatile int m_bfmeSecondAY;
};

BfmeStateAY::BfmeStateAY(void *owner)
{
	bfmeBaseInitAY(owner, AsciiStringAY("AITNGuardOuter"));

	m_bfmeVfptrAY = bfmeVftableAY;

	m_bfmeFirstAY = 0;

	m_bfmeTableAY = bfmeGuardTableAY;

	m_bfmeSecondAY = 0;
}
