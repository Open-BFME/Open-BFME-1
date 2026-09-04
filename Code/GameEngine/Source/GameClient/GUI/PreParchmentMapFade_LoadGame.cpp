// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
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

class Rva0057F100
{
public:
	void giveBack(void);
};
extern Rva0057F100 *g_obj12F4B58;

class WindowManager
{
public:
	void unidentified_0002e9a1(int a);
};
extern WindowManager *g_theWindowManager;

// ?parchmentMapFadeLoadGame@@YAHH_N@Z
int parchmentMapFadeLoadGame(int, bool start)
{
	const bool go = start;
	int result = 1;
	if (go)
	{
		TheTransitionHandler->setGroup(AsciiString("PreParchmentMapFade_LoadGame"), 0);
		if (g_obj12F4B58)
			g_obj12F4B58->giveBack();
		if (g_theWindowManager)
			g_theWindowManager->unidentified_0002e9a1(-1);
	}
	else if (TheTransitionHandler->isFinished())
		result = 3;
	return result;
}
