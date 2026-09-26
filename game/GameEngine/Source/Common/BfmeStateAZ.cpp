// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the AITNGuardAttackAggressorState constructor at retail 0x0018AE90, 61 bytes.
// Same family as 0x00185700: the state name goes into the by-value argument
// the base initialiser takes.

class StringBaseNarrowAZ
{
protected:
	StringBaseNarrowAZ(const char *text) throw();

	StringBaseNarrowAZ(const StringBaseNarrowAZ &other) throw();

	~StringBaseNarrowAZ(void) throw();

	char *m_bfmeNarrowAZ;
};

class AsciiStringAZ : public StringBaseNarrowAZ
{
public:
	AsciiStringAZ(const char *text) throw() : StringBaseNarrowAZ(text)
	{
	}

	AsciiStringAZ(const AsciiStringAZ &other) throw() : StringBaseNarrowAZ(other)
	{
	}

	~AsciiStringAZ(void) throw()
	{
	}
};

extern "C" void *bfmeVftableAZ[];
extern "C" void *bfmeGuardTableAZ[];

class BfmeStateAZ
{
public:
	BfmeStateAZ(void *owner);

	void bfmeBaseInitAZ(void *owner, AsciiStringAZ name) throw();

	void *volatile m_bfmeVfptrAZ;
	char m_bfmePadAZ[0x20];
	void *volatile m_bfmeTableAZ;
	volatile int m_bfmeFirstAZ;
	volatile int m_bfmeSecondAZ;
};

BfmeStateAZ::BfmeStateAZ(void *owner)
{
	bfmeBaseInitAZ(owner, AsciiStringAZ("AITNGuardAttackAggressorState"));

	m_bfmeVfptrAZ = bfmeVftableAZ;

	m_bfmeFirstAZ = 0;

	m_bfmeTableAZ = bfmeGuardTableAZ;

	m_bfmeSecondAZ = 0;
}
