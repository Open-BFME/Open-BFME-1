// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;

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
    char m_name[4];
};

class AsciiString
{
private:
    void *m_data;
};

class AnimateWindowManager;
class ShellMenuSchemeManager;

class WindowLayout
{
public:
    virtual void runInit(void *) = 0;
    virtual ~WindowLayout();
    virtual void unused02() = 0;
    virtual void unused03() = 0;
    virtual void unused04() = 0;
    virtual void unused05() = 0;
    virtual void unused06() = 0;
    virtual void unused07() = 0;
    virtual void destroyWindows() = 0;

    void deleteInstance() { delete this; }
};

class IMEManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void detatch();
};

extern IMEManager *TheIMEManager;

class Shell : public SubsystemInterface
{
public:
    virtual ~Shell();
    virtual void init();
    virtual bool loadIniFilesFromLegend();
    virtual void reset();
    virtual void update();
    virtual void draw();

protected:
    void doPop(Bool impendingPush);

private:
    WindowLayout *top()
    {
        if (m_screenCount == 0)
            return 0;
        return m_screenStack[m_screenCount - 1];
    }

    void unlinkScreen(WindowLayout *screen)
    {
        if (screen == 0)
            return;
        if (m_screenStack[m_screenCount - 1] == screen)
            m_screenStack[--m_screenCount] = 0;
    }

    WindowLayout *m_screenStack[16];
    int m_screenCount;
    WindowLayout *m_background;
    Bool m_clearBackground;
    Bool m_pendingPush;
    Bool m_pendingPop;
    AsciiString m_pendingPushName;
    Bool m_isShellActive;
    Bool m_shellMapOn;
    AnimateWindowManager *m_animateWindowManager;
    ShellMenuSchemeManager *m_schemeManager;
    unsigned int m_musicHandle;
    WindowLayout *m_saveLoadMenuLayout;
    WindowLayout *m_popupReplayLayout;
};

// ?doPop@Shell@@IAEX_N@Z
void Shell::doPop(Bool impendingPush)
{
    WindowLayout *currentTop = top();
    unlinkScreen(currentTop);

    currentTop->destroyWindows();
    currentTop->deleteInstance();

    WindowLayout *newTop = top();

    if (newTop && !impendingPush && !m_clearBackground)
        newTop->runInit(0);
    else
        m_clearBackground = false;

	if (TheIMEManager)
		TheIMEManager->detatch();
}
