// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
#include "StringInline.h"

typedef int Int;
typedef bool Bool;

class WindowManager
{
public:
	void unidentified_00015235(Int a, const char *eventName, Int argCount,
		const void *p1, const void *p2, const void *p3, const void *p4, const void *p5);
};

extern WindowManager *g_theWindowManager;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	void setUnidentified13c(Bool b) { m_unidentified13c = b; }

private:
	char m_pad[0x13c];
	Bool m_unidentified13c;
};

extern Display *TheDisplay;

// Retail global at 0x012F0898 is GameLogic *TheGameLogic (defined once in
// game_logic.cpp). This TU calls through a local view type, so keep the view
// and cast at the use; the global itself uses the canonical spelling.
class GameLogicShim
{
public:
	Bool unidentified_0001e0ab(void);
};

class GameLogic;
extern GameLogic *TheGameLogic;

// The global at retail 0x012F3330 is EA's singleton, declared and defined once
// as GameWindowTransitionsHandler *TheTransitionHandler in
// GameWindowTransitions.cpp (?TheTransitionHandler@@3PAVGameWindowTransitionsHandler@@A).
// The member is reached through this file's own view of the object, cast at
// the use, so the called ILT thunk 0x00045C28 stays the one retail calls.
class GameWindowTransitionsHandler;
extern GameWindowTransitionsHandler *TheTransitionHandler;

class TransitionHandler
{
public:
	void setGroup(AsciiString name, Int i);
};

class VictoryConditions
{
public:
	virtual void hideEndGame(void);

private:
	AsciiString m_name;
	Int m_victoryConditions;
	Bool m_endGameShowing;
	unsigned char m_pad[0xBD - 0x0D];
	Bool m_singleAllianceRemaining;
};

void VictoryConditions::hideEndGame(void)
{
	if (!g_theWindowManager || !m_endGameShowing)
		return;

	g_theWindowManager->unidentified_00015235(0xb, "HideEndGame", 0, 0, 0, 0, 0, 0);
	m_endGameShowing = false;
	TheDisplay->setUnidentified13c(true);

	if (reinterpret_cast<GameLogicShim *>(TheGameLogic)->unidentified_0001e0ab())
	{
		if (m_singleAllianceRemaining)
			((TransitionHandler *)TheTransitionHandler)->setGroup("MPorSkirmishFadeToScoreScreen", 0);
	}
}
