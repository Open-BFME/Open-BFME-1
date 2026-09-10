// ?updateAt00505B40@Rva505C80WindowVisibilityThunk@@QAEXXZ
// partial score=0.94 date=2026-09-10
// Address-derived body 0x00505B40..0x00505BD3 (147 bytes).
// callers_of.py names WOLQuickMatchMenuSystem at 0x0050A470 as its caller.

class GameWindow
{
public:
	bool winIsHidden(void);
	void winHide(bool hide);
};

class GameSpyInfo
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
};

class Shell
{
public:
	void pop(void);
};

class Shell40D9 : public Shell
{
};

// This class and setState are already identified by the adjacent
// Rva505C80WindowVisibilityThunk body and its ILT pin.  The new method name
// remains address-derived because the caller does not expose a retail name.
class Rva505C80WindowVisibilityThunk
{
public:
	void updateAt00505B40(void);
	void setState(bool enabled);

	unsigned char m_pad000[0x22c];
	GameWindow *m_gate;
	unsigned char m_pad230[0x34];
	GameWindow *m_finalWindow;
	unsigned char m_pad268[0x24];
	GameWindow *m_firstWindow;
	void *m_unused290;
	GameWindow *m_secondWindow;
	void *m_unused298;
	GameWindow *m_fourthWindow;
	void *m_unused2a0;
	GameWindow *m_thirdWindow;
	void *m_unused2a8;
	GameWindow *m_fifthWindow;
};

extern GameSpyInfo *TheGameSpyInfo;
extern Shell40D9 *TheShell;

void Rva505C80WindowVisibilityThunk::updateAt00505B40(void)
{
	if (!m_gate->winIsHidden())
	{
		GameSpyInfo *info = TheGameSpyInfo;
		*reinterpret_cast<unsigned char *>(0x012F4801u) = 1;
		info->slot07();
		Shell40D9 *shell = TheShell;
		*reinterpret_cast<volatile void **>(0x012F4804u) = reinterpret_cast<void *>(0x011033C0u);
		shell->pop();
		return;
	}

	setState(true);
		m_firstWindow->winHide(true);
		m_secondWindow->winHide(true);
		m_thirdWindow->winHide(true);
		m_fourthWindow->winHide(true);
		m_fifthWindow->winHide(true);
		m_finalWindow->winHide(false);
}
