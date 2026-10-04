// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
#include "StringInline.h"

typedef int Int;
typedef bool Bool;

class WindowManager;

extern WindowManager *g_theWindowManager;

class BfmeLevelAN
{
public:
	char *bfmeBuildAN(unsigned int level, int p2, int p3, int p4, int p5,
		int p6, int p7, int p8);

	char m_bfmePadAN[0x1c4];
	char m_bfmeBuiltAN;
};

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
// and cast at the use; the global itself uses the canonical spelling. The
// query itself is an ILT thunk at 0x0001E0AB (?j_0001e0ab@@YAXXZ in
// game/gen_small/thunks_014.cpp), the only name the ledger defines at that
// address, so __identifier spells it and the union's member-pointer view types
// the thiscall.
extern "C" Bool __identifier("?j_0001e0ab@@YAXXZ")();

class GameLogicShim
{
public:
};

class GameLogic;
extern GameLogic *TheGameLogic;

// The global at retail 0x012F3330 is EA's singleton, declared and defined once
// as GameWindowTransitionsHandler *TheTransitionHandler in
// GameWindowTransitions.cpp (?TheTransitionHandler@@3PAVGameWindowTransitionsHandler@@A).
// The member is reached through this file's own view of the object, cast at
// the use, so the called ILT thunk 0x00045C28 (?j_00045c28@@YAXXZ in
// game/gen_small/thunks_033.cpp) stays the one retail calls.
class GameWindowTransitionsHandler;
extern GameWindowTransitionsHandler *TheTransitionHandler;

extern "C" void __identifier("?j_00045c28@@YAXXZ")();

// The transition handler's own view of the object; the callee carries no C++
// name here, only the retail thunk symbol above.
class TransitionHandler
{
public:
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

	reinterpret_cast<BfmeLevelAN *>(g_theWindowManager)->bfmeBuildAN(
		0xb, (int)"HideEndGame", 0, 0, 0, 0, 0, 0);
	m_endGameShowing = false;
	TheDisplay->setUnidentified13c(true);

	union QueryCall {
		Bool (*thunk)();
		Bool (GameLogicShim::*query)(void);
	} queryCall;
	queryCall.thunk = (Bool (*)())&__identifier("?j_0001e0ab@@YAXXZ");

	if ((reinterpret_cast<GameLogicShim *>(TheGameLogic)->*queryCall.query)())
	{
		if (m_singleAllianceRemaining)
		{
			union SetGroupCall {
				void (*thunk)();
				void (TransitionHandler::*setGroup)(AsciiString, Int);
			} setGroupCall;
			setGroupCall.thunk = (void (*)())&__identifier("?j_00045c28@@YAXXZ");
			((TransitionHandler *)TheTransitionHandler->*setGroupCall.setGroup)(
				"MPorSkirmishFadeToScoreScreen", 0);
		}
	}
}
