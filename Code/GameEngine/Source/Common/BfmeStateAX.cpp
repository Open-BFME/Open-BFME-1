// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the AIBackAwayState constructor at retail 0x001804B0, 57 bytes.
// Same family as 0x00185700: the state name goes into the by-value argument
// the base initialiser takes.

class StringBaseNarrowAX
{
protected:
	StringBaseNarrowAX(const char *text) throw();

	StringBaseNarrowAX(const StringBaseNarrowAX &other) throw();

	~StringBaseNarrowAX(void) throw();

	char *m_bfmeNarrowAX;
};

class AsciiStringAX : public StringBaseNarrowAX
{
public:
	AsciiStringAX(const char *text) throw() : StringBaseNarrowAX(text)
	{
	}

	AsciiStringAX(const AsciiStringAX &other) throw() : StringBaseNarrowAX(other)
	{
	}

	~AsciiStringAX(void) throw()
	{
	}
};

extern "C" void *bfmeVftableAX[];

class BfmeStateAX
{
public:
	BfmeStateAX(void *owner);

	void bfmeBaseInitAX(void *owner, AsciiStringAX name) throw();

	void *m_bfmeVfptrAX;
	char m_bfmePadAX[0x4c];
	int m_bfmeCountAX;
	char m_bfmeFirstAX;
	char m_bfmePadBAX[3];
	char m_bfmeSecondAX;
};

BfmeStateAX::BfmeStateAX(void *owner)
{
	bfmeBaseInitAX(owner, AsciiStringAX("AIBackAwayState"));

	m_bfmeFirstAX = 0;

	m_bfmeCountAX = 0;

	m_bfmeSecondAX = 0;

	m_bfmeVfptrAX = bfmeVftableAX;
}
