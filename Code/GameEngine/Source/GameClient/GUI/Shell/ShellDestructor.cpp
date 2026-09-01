// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Shell::~Shell, retail 0x0057F7A0, 253 bytes.

typedef int Int;
typedef unsigned int UnsignedInt;

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

protected:
	AsciiString m_name;
};

class WindowLayout
{
public:
	virtual void runInit(void *) = 0;
	virtual ~WindowLayout();
	virtual void runUpdate(void *) = 0;
	virtual void runShutdown(void *) = 0;
	virtual void hide(Int) = 0;
	virtual void bringForward() = 0;
	virtual void addWindow(void *) = 0;
	virtual void removeWindow(void *) = 0;
	virtual void destroyWindows() = 0;

	void deleteInstance() { delete this; }

};

class AnimateWindowManager
{
public:
	virtual ~AnimateWindowManager();
};

class ShellMenuSchemeManager
{
public:
	~ShellMenuSchemeManager();
};

class AudioManager
{
public:
	virtual void unused00() = 0;
	virtual void unused01() = 0;
	virtual void unused02() = 0;
	virtual void unused03() = 0;
	virtual void unused04() = 0;
	virtual void unused05() = 0;
	virtual void unused06() = 0;
	virtual void unused07() = 0;
	virtual void unused08() = 0;
	virtual void unused09() = 0;
	virtual void unused10() = 0;
	virtual void unused11() = 0;
	virtual void unused12() = 0;
	virtual void unused13() = 0;
	virtual void unused14() = 0;
	virtual void unused15() = 0;
	virtual void unused16() = 0;
	virtual void unused17() = 0;
	virtual void unused18() = 0;
	virtual void stopAudioEvent(UnsignedInt handle) = 0;
};

extern AudioManager *TheAudio;

class Shell : public SubsystemInterface
{
public:
	virtual ~Shell();
	virtual void init();
	virtual bool loadIniFilesFromLegend();
	virtual void reset();
	virtual void update();
	virtual void draw();

	void popImmediate();

private:
	WindowLayout *m_screenStack[16];
	Int m_screenCount;
	WindowLayout *m_background;
	bool m_clearBackground;
	bool m_pendingPush;
	bool m_pendingPop;
	AsciiString m_pendingPushName;
	bool m_isShellActive;
	bool m_shellMapOn;
	AnimateWindowManager *m_animateWindowManager;
	ShellMenuSchemeManager *m_schemeManager;
	UnsignedInt m_musicHandle;
	WindowLayout *m_saveLoadMenuLayout;
	WindowLayout *m_popupReplayLayout;
};

Shell::~Shell()
{
	WindowLayout *newTop = m_screenCount ? m_screenStack[m_screenCount - 1] : 0;
	while (newTop)
	{
		popImmediate();
		newTop = m_screenCount ? m_screenStack[m_screenCount - 1] : 0;
	}

	if (m_animateWindowManager)
		delete m_animateWindowManager;
	m_animateWindowManager = 0;

	if (m_schemeManager)
		delete m_schemeManager;
	m_schemeManager = 0;

	if (m_saveLoadMenuLayout)
	{
		m_saveLoadMenuLayout->destroyWindows();
		m_saveLoadMenuLayout->deleteInstance();
		m_saveLoadMenuLayout = 0;
	}

	if (m_popupReplayLayout)
	{
		m_popupReplayLayout->destroyWindows();
		m_popupReplayLayout->deleteInstance();
		m_popupReplayLayout = 0;
	}

	if (TheAudio)
	{
		TheAudio->stopAudioEvent(m_musicHandle);
		m_musicHandle = 1;
	}
}
