class GameWindow
{
public:
	bool winIsHidden();
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
	void pop();
};

class Rva505C80WindowVisibilityThunk
{
public:
	void updateAt00505B40();
	void setState(bool enabled);

	char m_pad000[0x22c];
	GameWindow *m_gate;
	char m_pad230[0x34];
	GameWindow *m_finalWindow;
	char m_pad268[0x24];
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
extern Shell *TheShell;

void Rva505C80WindowVisibilityThunk::updateAt00505B40()
{
	if (!m_gate->winIsHidden())
	{
		GameSpyInfo *info = TheGameSpyInfo;
		void **vtable = *reinterpret_cast<void ***>(info);
		*reinterpret_cast<unsigned char *>(0x012F4801u) = 1;
		reinterpret_cast<void (__fastcall *)(GameSpyInfo *)>(vtable[7])(info);
		Shell *shell = TheShell;
		*reinterpret_cast<volatile void **>(0x012F4804u) = reinterpret_cast<void *>(0x011033C0u);
		shell->pop();
		return;
	}

	setState(true);
	m_firstWindow->winHide(true);
	m_secondWindow->winHide(true);
	m_thirdWindow->winHide(true);
	m_fourthWindow->winHide(true);
	m_fifthWindow->winHide(false);
	m_finalWindow->winHide(false);
}
