// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
// Shell::doPush, retail 0x0057FCB0.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

class GameWindow;

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

// BFME makes the WindowLayout operations used by Shell virtual.  The vtable
// order is established by the matched Shell::doPop and popImmediate bodies.
class WindowLayout
{
public:
	virtual void runInit(void *) = 0;
	virtual ~WindowLayout();
	virtual void runUpdate(void *) = 0;
	virtual void runShutdown(void *) = 0;
	virtual void hide(Bool) = 0;
	virtual void bringForward() = 0;
};

// Only the prefix through winCreateLayout is needed here.  Its +0x6c slot and
// by-value AsciiString signature are established by the matched implementation
// at 0x004889A0 and the other retail callers of TheWindowManager.
class GameWindowManager
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual WindowLayout *winCreateLayout(AsciiString filename) = 0;
};

class IMEManagerInterface : public SubsystemInterface
{
public:
	virtual ~IMEManagerInterface();
	virtual void attach(GameWindow *) = 0;
	virtual void detatch() = 0;
};

class GameSpyInfo;

extern GameSpyInfo *TheGameSpyInfo;
extern GameWindowManager *TheWindowManager;
extern IMEManagerInterface *TheIMEManager;

void GameSpyCloseAllOverlays();

class Shell : public SubsystemInterface
{
protected:
	void doPush(AsciiString layoutFile);

	void linkScreen(WindowLayout *screen)
	{
		if (screen == 0)
			return;
		if (m_screenCount == 16)
			return;
		m_screenStack[m_screenCount++] = screen;
	}

private:
	WindowLayout *m_screenStack[16];
	Int m_screenCount;
};

void Shell::doPush(AsciiString layoutFile)
{
	if (TheGameSpyInfo)
		GameSpyCloseAllOverlays();

	WindowLayout *newScreen = TheWindowManager->winCreateLayout(layoutFile);
	linkScreen(newScreen);

	if (TheIMEManager)
		TheIMEManager->detatch();

	newScreen->runInit(0);
	newScreen->bringForward();
}
