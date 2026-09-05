// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the AIFollowWaypointPathState constructor at retail 0x0017FA10, 83 bytes.
// Same family as 0x00185700: the state name goes into the by-value argument
// the base initialiser takes.

class StringBaseNarrowBA
{
protected:
	StringBaseNarrowBA(const char *text) throw();

	StringBaseNarrowBA(const StringBaseNarrowBA &other) throw();

	~StringBaseNarrowBA(void) throw();

	char *m_bfmeNarrowBA;
};

class AsciiStringBA : public StringBaseNarrowBA
{
public:
	AsciiStringBA(const char *text) throw() : StringBaseNarrowBA(text)
	{
	}

	AsciiStringBA(const AsciiStringBA &other) throw() : StringBaseNarrowBA(other)
	{
	}

	~AsciiStringBA(void) throw()
	{
	}
};

extern "C" void *bfmeVftableBA[];

class BfmeStateBA
{
public:
	BfmeStateBA(void *owner, char first, char second);

	void bfmeBaseInitBA(void *owner, AsciiStringBA name) throw();

	void *volatile m_bfmeVfptrBA;
	char m_bfmePadBA[0x4c];
	volatile int m_bfmeABA;
	volatile int m_bfmeBBA;
	volatile int m_bfmeCBA;
	volatile int m_bfmeDBA;
	volatile int m_bfmeEBA;
	volatile int m_bfmeFBA;
	volatile char m_bfmeGBA;
	volatile char m_bfmeHBA;
	volatile char m_bfmeIBA;
};

BfmeStateBA::BfmeStateBA(void *owner, char first, char second)
{
	bfmeBaseInitBA(owner, AsciiStringBA("AIFollowWaypointPathState"));

	m_bfmeVfptrBA = bfmeVftableBA;

	m_bfmeABA = 0;
	m_bfmeBBA = 0;
	m_bfmeCBA = 0;
	m_bfmeDBA = 0;
	m_bfmeEBA = 0;
	m_bfmeFBA = 0;

	m_bfmeGBA = 0;
	m_bfmeHBA = first;
	m_bfmeIBA = second;
}
