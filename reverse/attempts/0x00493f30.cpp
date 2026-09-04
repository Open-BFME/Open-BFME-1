// ?updateState@Rva00493F30TransitionState@@QAE_NXZ
// partial score=0.9 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /MD /EHsc

typedef bool Bool;

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
	unsigned int m_flags;
	unsigned char m_padding1[0x20c];
	Rva00493F30Controller m_controller;
	unsigned char m_padding2[0x1c];
	unsigned int m_mode;
	unsigned char m_padding3[0x14];
	volatile unsigned int m_previousFlags;
};

Bool Rva00493F30TransitionState::updateState(void)
{
	const unsigned int transitionFlag = 0x10;
	if ((m_previousFlags & transitionFlag) == 0)
	{
		if ((m_flags & transitionFlag) != 0 && (m_mode & 1) != 0)
			m_controller.begin();
	}
	else if ((m_flags & transitionFlag) == 0)
	{
		finishTransition();
	}
	m_previousFlags = m_flags;
	if ((m_mode & 1) != 0)
		m_controller.update();
	return true;
}
