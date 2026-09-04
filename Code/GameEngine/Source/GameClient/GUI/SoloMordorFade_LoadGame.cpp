// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
#include "StringInline.h"

typedef bool Bool;

// 0x003BE1F0 (126B). Load-game SoloMordor fade step: WindowManager pop(-1),
// Display stopMovie, Shell hide, optional clearGameData when not GAME_NONE,
// Glo012F7048 vslot+0x10, setGroup("SoloMordorFade_LoadGame"), cursor 0x28.
// Straight-line; unused first int places bool at [esp+8] like sibling steps.
// Always returns 2.

class WindowManager
{
public:
	void unidentified_000144bb(int a);
};
extern WindowManager *g_theWindowManager;

class Display
{
public:
	virtual void slot00(); virtual void slot01();
	virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21();
	virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45();
	virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49();
	virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57();
	virtual void slot58();
	virtual void stopMovie(void);
};
extern Display *TheDisplay;

class Shell
{
public:
	void hide(Bool hide);
};
extern Shell *g_obj12F4B58;

class BfmeGameLogicPause
{
public:
	void clearGameData(Bool showScoreScreen, Bool unknown);

	unsigned char m_pad[0x10C];
	int m_gameMode;
};
extern BfmeGameLogicPause *TheGameLogic;

class Glo012F7048Type
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void unidentified_00000010(Bool a);
};
extern Glo012F7048Type *Glo012F7048;

class GameWindowTransitionsHandler
{
public:
	void setGroup(AsciiString name);
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

class Mouse
{
public:
	virtual void slot00(); virtual void slot04();
	virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24();
	virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual void setCursor(int cursor);
};
extern Mouse *TheMouse;

// ?soloMordorFadeLoadGame@@YAHH_N@Z
int soloMordorFadeLoadGame(int, bool)
{
	g_theWindowManager->unidentified_000144bb(-1);
	TheDisplay->stopMovie();
	g_obj12F4B58->hide(true);
	if (TheGameLogic->m_gameMode != 8)
		TheGameLogic->clearGameData(false, false);
	Glo012F7048->unidentified_00000010(true);
	TheTransitionHandler->setGroup(AsciiString("SoloMordorFade_LoadGame"));
	TheMouse->setCursor(0x28);
	return 2;
}
