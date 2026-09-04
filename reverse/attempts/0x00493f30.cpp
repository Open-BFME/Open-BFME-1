// ?updateState@Rva00493F30TransitionState@@QAE_NXZ
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /MD /EHsc

typedef bool Bool;

class BfmeTransitionFlags
{
public:
	explicit BfmeTransitionFlags(unsigned int bits = 0) : m_bits(bits) {}

	Bool testForAny(const BfmeTransitionFlags &that) const volatile
	{
		unsigned int value = m_bits;
		value &= that.m_bits;
		return value != 0;
	}

	unsigned int m_bits;
};

class Rva00493F30Controller
{
public:
	virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
	virtual void begin(void);
	virtual void update(void);
};

class Rva00493F30TransitionState
{
public:
	Bool updateState(void);
	void finishTransition(void);
private:
	unsigned char m_padding0[8];
	BfmeTransitionFlags m_flags;
	unsigned char m_padding1[0x20c];
	Rva00493F30Controller m_controller;
	unsigned char m_padding2[0x1c];
	unsigned int m_mode;
	unsigned char m_padding3[0x14];
	volatile BfmeTransitionFlags m_previousFlags;
};

Bool Rva00493F30TransitionState::updateState(void)
{
	const BfmeTransitionFlags transitionFlag(0x10);
	if (!m_previousFlags.testForAny(transitionFlag))
	{
		if (m_flags.testForAny(transitionFlag) && (m_mode & 1) != 0)
			m_controller.begin();
	}
	else if (!m_flags.testForAny(transitionFlag))
	{
		finishTransition();
	}
	m_previousFlags.m_bits = m_flags.m_bits;
	if ((m_mode & 1) != 0)
		m_controller.update();
	return true;
}
