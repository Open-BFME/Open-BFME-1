// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?showShell@Shell@@QAEX_N@Z: game/GameEngine/Source/GameClient/GUI/Shell/Shell.cpp
// Open-BFME5: exact C++ reconstruction of BFME shell activation.

#include "Common/AsciiString.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowLayout.h
class WindowLayout
{
public:
	virtual void runInit(void *);
};

struct RetailGlobalData
{
	char pad0[0xB80];
	void *initialFileData;
	char padB84[4];
	bool alternateShell;
	char padB89[0x2B];
	bool shellMapOn;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	void showShell(bool);
	void push(AsciiString, bool immediate = false);

private:
	void *unknown0;
	WindowLayout *screens[17];
	int screenCount;
	char pad4C[12];
	bool shellActive;
};

extern RetailGlobalData *TheGlobalData;
extern Shell *TheShell;
extern "C" __declspec(dllimport) char *getenv(const char *);

void Shell::showShell(bool runInit)
{
	const char *initial = (const char *)TheGlobalData->initialFileData;
	if (initial && *(const unsigned short *)(initial + 4) && !TheGlobalData->alternateShell)
		return;

	if (runInit && screenCount) {
		WindowLayout *layout = screens[screenCount];
		if (layout)
			layout->runInit(0);
	}

	if (!TheGlobalData->shellMapOn && screenCount == 0) {
		if (getenv("_EA_RTS_HEADLESS") == 0 && !TheGlobalData->alternateShell)
			TheShell->push(AsciiString("MainMenu.apt"));
		else
			TheShell->push(AsciiString("Menus/LanLobbyMenu.wnd"));
	}
	shellActive = true;
}
