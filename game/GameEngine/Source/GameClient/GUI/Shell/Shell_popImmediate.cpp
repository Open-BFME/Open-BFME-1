// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Shell::popImmediate, retail 0x0057F4E0.

typedef bool Bool;
typedef int Int;

class GameWindow;

#include "ascii_string.h"

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual Bool loadIniFilesFromLegend();
	virtual void slot03();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual Bool slot06(Int);
	virtual void slot07();
	virtual void slot08(Int);

protected:
	AsciiString m_name;
};

class AnimateWindowManager;
class ShellMenuSchemeManager;

// BFME's virtual order is established by matched WindowLayout callers; the
// operation names correspond to the same Shell lifetime path in GeneralsMD.
class WindowLayout
{
public:
	virtual void runInit(void *) = 0;
	virtual ~WindowLayout();
	virtual void runUpdate(void *) = 0;
	virtual void runShutdown(void *) = 0;
	virtual void hide(Bool) = 0;
	virtual void bringForward() = 0;
	virtual void addWindow(GameWindow *) = 0;
	virtual void removeWindow(GameWindow *) = 0;
	virtual void destroyWindows() = 0;

	void deleteInstance() { delete this; }
};

// BFME's enlarged SubsystemInterface places IMEManagerInterface::detatch at
// vtable slot 0x28.  The retail IMEManager vtable at 0x010F9978 confirms that
// slot routes to IMEManager::detatch at 0x0048CD50.
class IMEManagerInterface : public SubsystemInterface
{
public:
	virtual ~IMEManagerInterface();
	virtual void attach(GameWindow *) = 0;
	virtual void detatch() = 0;
};

extern IMEManagerInterface *TheIMEManager;

class Shell : public SubsystemInterface
{
public:
	void popImmediate();

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
	Bool m_pendingPush;
	Bool m_pendingPop;
	Bool m_bfmeState4E;
	Bool m_bfmeState4F;
	Bool m_clearBackground;
	char m_padding51[3];
	AsciiString m_pendingPushName;
	Bool m_isShellActive;
	Bool m_shellMapOn;
	AnimateWindowManager *m_animateWindowManager;
	ShellMenuSchemeManager *m_schemeManager;
	unsigned int m_musicHandle;
	WindowLayout *m_saveLoadMenuLayout;
	WindowLayout *m_popupReplayLayout;
};

void Shell::popImmediate()
{
	WindowLayout *screen = top();

	if (screen == 0)
		return;

	m_pendingPop = false;

	Bool immediatePop = true;
	screen->runShutdown(&immediatePop);

	// Retail inlines the complete Shell::doPop(false) lifetime path here.
	WindowLayout *currentTop = top();
	unlinkScreen(currentTop);

	currentTop->destroyWindows();
	currentTop->deleteInstance();

	WindowLayout *newTop = top();
	if (newTop && !m_clearBackground)
		newTop->runInit(0);
	else
		m_clearBackground = false;

	if (TheIMEManager)
		TheIMEManager->detatch();

	if (TheIMEManager)
		TheIMEManager->detatch();
}
