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

// EA's GlobalData (Common/GlobalData.h) is only forward declared here; the
// global must be spelled GlobalData * (class, not struct) so the mangled name
// matches the one definition in GameEngine/Source/Common/GlobalData.cpp.
// The local view above supplies the members retail reads here.
class GlobalData;

extern GlobalData *TheWritableGlobalData;
extern Shell *TheShell;
extern "C" __declspec(dllimport) char *getenv(const char *);

void Shell::showShell(bool runInit)
{
	const char *initial = (const char *)reinterpret_cast<RetailGlobalData *>(TheWritableGlobalData)->initialFileData;
	if (initial && *(const unsigned short *)(initial + 4) &&
		!reinterpret_cast<RetailGlobalData *>(TheWritableGlobalData)->alternateShell)
		return;

	if (runInit && screenCount) {
		WindowLayout *layout = screens[screenCount];
		if (layout)
			layout->runInit(0);
	}

	if (!reinterpret_cast<RetailGlobalData *>(TheWritableGlobalData)->shellMapOn && screenCount == 0) {
		if (getenv("_EA_RTS_HEADLESS") == 0 &&
			!reinterpret_cast<RetailGlobalData *>(TheWritableGlobalData)->alternateShell)
			TheShell->push(AsciiString("MainMenu.apt"));
		else
			TheShell->push(AsciiString("Menus/LanLobbyMenu.wnd"));
	}
	shellActive = true;
}
