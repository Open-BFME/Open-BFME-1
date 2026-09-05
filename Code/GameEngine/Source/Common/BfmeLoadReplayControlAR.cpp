// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the replay-control window load at retail 0x0043E3E0, 40 bytes.
// The window name is built straight into the by-value argument slot, so the
// callee owns it and no unwind frame is needed.

class StringBaseNarrowAR
{
protected:
	StringBaseNarrowAR(const char *text);

	StringBaseNarrowAR(const StringBaseNarrowAR &other);

	~StringBaseNarrowAR(void);

	char *m_bfmeNarrowAR;
};

class AsciiStringAR : public StringBaseNarrowAR
{
public:
	AsciiStringAR(const char *text) : StringBaseNarrowAR(text)
	{
	}

	AsciiStringAR(const AsciiStringAR &other) : StringBaseNarrowAR(other)
	{
	}

	~AsciiStringAR(void)
	{
	}
};

class BfmeWindowManagerAR
{
public:
	virtual void bfmeSlot0AR(void) = 0;
	virtual void bfmeSlot1AR(void) = 0;
	virtual void bfmeSlot2AR(void) = 0;
	virtual void bfmeSlot3AR(void) = 0;
	virtual void bfmeSlot4AR(void) = 0;
	virtual void bfmeSlot5AR(void) = 0;
	virtual void bfmeSlot6AR(void) = 0;
	virtual void bfmeSlot7AR(void) = 0;
	virtual void bfmeSlot8AR(void) = 0;
	virtual void bfmeSlot9AR(void) = 0;
	virtual void bfmeSlot10AR(void) = 0;
	virtual void bfmeSlot11AR(void) = 0;
	virtual void bfmeSlot12AR(void) = 0;
	virtual void bfmeSlot13AR(void) = 0;
	virtual void bfmeSlot14AR(void) = 0;
	virtual void bfmeSlot15AR(void) = 0;
	virtual void bfmeSlot16AR(void) = 0;
	virtual void bfmeSlot17AR(void) = 0;
	virtual void bfmeSlot18AR(void) = 0;
	virtual void bfmeSlot19AR(void) = 0;
	virtual void bfmeSlot20AR(void) = 0;
	virtual void bfmeSlot21AR(void) = 0;
	virtual void bfmeSlot22AR(void) = 0;
	virtual void bfmeSlot23AR(void) = 0;
	virtual void bfmeSlot24AR(void) = 0;
	virtual void bfmeSlot25AR(void) = 0;
	virtual void *bfmeCreateAR(AsciiStringAR name, int a, int b) = 0;
};

extern BfmeWindowManagerAR *g_bfmeWindowManagerAR;	// retail 0x012F1B40
extern void *g_bfmeReplayControlAR;			// retail 0x012F1490

// ?bfmeLoadReplayControlAR@@YAXXZ
void bfmeLoadReplayControlAR(void)
{
	g_bfmeReplayControlAR = g_bfmeWindowManagerAR->bfmeCreateAR(
			AsciiStringAR("ReplayControl.wnd"), 0, 0);
}
