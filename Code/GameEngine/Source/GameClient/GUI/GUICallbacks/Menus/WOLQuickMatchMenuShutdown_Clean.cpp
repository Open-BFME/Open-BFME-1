// cl: /DNDEBUG /MD /EHsc /Ireference/shims/asciistring_downloadmanager
// Open-BFME5: convert the BFME quick-match shutdown callback to clean C++.

typedef bool Bool;

class GameWindow;

class WindowLayout
{
public:
	void WOLQuickMatchMenuShutdown(void *userData);
};

class GameSpyInfo
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual void slot1F();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot2A(); virtual void slot2B();
	virtual void slot2C(); virtual void slot2D(); virtual void slot2E(); virtual void slot2F();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39();
	virtual void unregisterTextWindow(GameWindow *window);
};

class GameEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D();
	virtual Bool getQuitting() const;
};

#include "ascii_string.h"

class Shell
{
public:
	void reverseAnimatewindow();
};

class GameWindowTransitionsHandler
{
public:
	void reverse(AsciiString groupName);
};

struct QuickMatchScreen
{
	unsigned char m_padding[0x294];
	GameWindow *m_textWindow;
};

extern GameSpyInfo *TheGameSpyInfo;
extern GameEngine *TheGameEngine;
extern QuickMatchScreen *TheQuickMatchScreen;
extern GameWindow * volatile parentWOLQuickMatch;
extern GameWindow * volatile buttonBack;
extern const void *selectedImage;
extern const void *unselectedImage;
extern volatile Bool isShuttingDown;
extern Shell *TheShell;
extern GameWindowTransitionsHandler *TheTransitionHandler;

void j_00031e0d(void);
void j_00048e73(void);
void RaiseGSMessageBox(void);

typedef void (__fastcall *QuickMatchSaveFunction)(QuickMatchScreen *);
typedef void (__fastcall *ImmediateShutdownFunction)(WindowLayout *);

// ?WOLQuickMatchMenuShutdown@@YAXPAVWindowLayout@@PAX@Z
#pragma comment(linker, "/alternatename:?WOLQuickMatchMenuShutdown@@YAXPAVWindowLayout@@PAX@Z=?WOLQuickMatchMenuShutdown@WindowLayout@@QAEXPAX@Z")
void WindowLayout::WOLQuickMatchMenuShutdown(void *userData)
{
	GameWindow *textWindow = TheQuickMatchScreen->m_textWindow;
	TheGameSpyInfo->unregisterTextWindow(textWindow);

	if (!TheGameEngine->getQuitting())
		((QuickMatchSaveFunction)j_00031e0d)(TheQuickMatchScreen);

	TheQuickMatchScreen = 0;
	if (*(Bool *)userData)
	{
		parentWOLQuickMatch = 0;
		buttonBack = 0;
		isShuttingDown = true;
		((ImmediateShutdownFunction)j_00048e73)(this);
		return;
	}

	parentWOLQuickMatch = 0;
	buttonBack = 0;
	isShuttingDown = true;

	TheShell->reverseAnimatewindow();
	TheTransitionHandler->reverse("WOLQuickMatchMenuFade");

	RaiseGSMessageBox();
}
