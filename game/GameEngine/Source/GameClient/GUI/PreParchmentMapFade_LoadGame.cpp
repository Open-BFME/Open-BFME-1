// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
#include "StringInline.h"

// 0x003BE290 (104B). Load-game parchment fade: setGroup("PreParchmentMapFade_LoadGame", 0)
// on TheTransitionHandler, poke TheShell and TheWindowManager, else poll isFinished.

// Retail defines this singleton once, in
// game/GameEngine/Source/GameClient/GUI/GameWindowTransitions.cpp, as
// GameWindowTransitionsHandler *TheTransitionHandler.  Reference it by that
// class name so the mangled global is ?TheTransitionHandler@@3PAV
// GameWindowTransitionsHandler@@A, the one recorded at 0x012F3330.
class GameWindowTransitionsHandler
{
public:
	void setGroup(AsciiString name, bool immediate);
	bool isFinished(void);
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

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
// Retail's 0x012F19E8 load (8b0d e8192f01) is the WindowManager singleton whose
// one definition is WindowManager.cpp:17, recorded in data_rows.csv as
// ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A. The old g_theWindowManager
// spelling was a guess and is refuted by that row's evidence: EA's real
// TheWindowManager is 0x012F1B40 (a GameWindowManager), a different global.
extern WindowManager *g_rva012F19E8WindowManager;

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
		if (g_rva012F19E8WindowManager)
			g_rva012F19E8WindowManager->unidentified_0002e9a1(-1);
	}
	else if (TheTransitionHandler->isFinished())
		result = 3;
	return result;
}
