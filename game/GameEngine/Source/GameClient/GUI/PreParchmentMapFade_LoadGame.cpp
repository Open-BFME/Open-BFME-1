// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
#include "StringInline.h"

// 0x003BE290 (104B). Load-game parchment fade: setGroup("PreParchmentMapFade_LoadGame", 0)
// on TheTransitionHandler, poke TheShell and TheWindowManager, else poll isFinished.

class TransitionHandler
{
public:
	void setGroup(AsciiString name, int immediate);
	bool isFinished(void);
};
extern TransitionHandler *TheTransitionHandler;

// Retail global 0x012F4B58 is EA's shell singleton, defined once under the
// canonical spelling (Shell *TheShell).
class Shell
{
};

// game/GameEngine/Source/Common/S3GuardedIndirectRelease.cpp owns the
// giveBack body at 0x0057F100, so the call is made through that view, exactly
// as Rva0051DD10StartBattleSchool.cpp does.
class Rva0057F100
{
public:
	void giveBack(void);
};
extern Shell *TheShell;

class WindowManager
{
public:
	void unidentified_0002e9a1(int a);
};
extern WindowManager *g_theWindowManager;

// ?parchmentMapFadeLoadGame@@YAHH_N@Z
int parchmentMapFadeLoadGame(int, bool start)
{
	const bool startRequested = start;
	int result = 1;
	if (startRequested)
	{
		TheTransitionHandler->setGroup(AsciiString("PreParchmentMapFade_LoadGame"), 0);
		if (TheShell)
			((Rva0057F100 *)TheShell)->giveBack();
		if (g_theWindowManager)
			g_theWindowManager->unidentified_0002e9a1(-1);
	}
	else if (TheTransitionHandler->isFinished())
		result = 3;
	return result;
}
