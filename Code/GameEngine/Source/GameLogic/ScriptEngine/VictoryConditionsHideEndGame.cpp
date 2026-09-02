// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
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

class Display
{
public:
	void setUnidentified13c(Bool b) { m_unidentified13c = b; }

private:
	char m_pad[0x13c];
	Bool m_unidentified13c;
};

extern Display *TheDisplay;

class GameLogicShim
{
public:
	Bool unidentified_0001e0ab(void);
};

extern GameLogicShim *TheGameLogic;

class TransitionHandler
{
public:
	void setGroup(AsciiString name, Int i);
};

extern TransitionHandler *TheTransitionHandler;

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

	if (TheGameLogic->unidentified_0001e0ab())
	{
		if (m_singleAllianceRemaining)
			TheTransitionHandler->setGroup("MPorSkirmishFadeToScoreScreen", 0);
	}
}
