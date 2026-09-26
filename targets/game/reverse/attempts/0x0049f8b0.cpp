// ?setControlBarSchemeByPlayer@ControlBar@@QAEXPAVPlayer@@@Z
// partial score=0.92 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc
//
// ControlBar::setControlBarSchemeByPlayer -- retail 0x0049F8B0, 790 bytes.
//
// Identity: the Zero Hour twin (inputs/reference/CnC_Generals_Zero_Hour/
// GeneralsMD/Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp)
// forwards to ControlBarSchemeManager::setControlBarSchemeByPlayer (retail
// 0x004AE080), caches the "ControlBar.wnd:ButtonPlaceBeacon" (0x010FB954),
// ":ButtonIdleWorker" (0x010F56C0) and ":ButtonGeneral" (0x010FB844) keys in
// function statics and splits on Player::isPlayerActive. Callers are
// GameLogic::startNewGame and the PlayerList destroyNotify path.
//
// Retail's observer arm is switchToContext(CB_CONTEXT_OBSERVER_LIST, NULL)
// (0x0049E780, case 9) expanded in place, including the NULL path of
// showRallyPoint (0x0049DF00); the other arm calls switchToContext out of
// line. BFME ends with the setDefaultControlBarConfig tail that
// ControlBarSetControlBarSchemeByName.cpp also has, not ZH's
// switchControlBarStage.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ControlBarContext { CB_CONTEXT_NONE = 0, CB_CONTEXT_OBSERVER_LIST = 9 };
enum GameMode { GAME_LAN = 1, GAME_SHELL = 4, GAME_INTERNET = 5 };
enum RecorderModeType { RECORDERMODE_PLAYBACK = 1 };

class Drawable;
class Player
{
public:
	Bool isPlayerActive() const;
};

class GameWindow
{
public:
	Int winHide(Bool hide);
	Int winEnable(Bool enable);
};

class GameWindowManager
{
public:
	virtual void slot000() = 0; virtual void slot004() = 0; virtual void slot008() = 0;
	virtual void slot00C() = 0; virtual void slot010() = 0; virtual void slot014() = 0;
	virtual void slot018() = 0; virtual void slot01C() = 0; virtual void slot020() = 0;
	virtual void slot024() = 0; virtual void slot028() = 0; virtual void slot02C() = 0;
	virtual void slot030() = 0; virtual void slot034() = 0; virtual void slot038() = 0;
	virtual void slot03C() = 0; virtual void slot040() = 0; virtual void slot044() = 0;
	virtual void slot048() = 0; virtual void slot04C() = 0; virtual void slot050() = 0;
	virtual void slot054() = 0; virtual void slot058() = 0; virtual void slot05C() = 0;
	virtual void slot060() = 0; virtual void slot064() = 0; virtual void slot068() = 0;
	virtual void slot06C() = 0; virtual void slot070() = 0; virtual void slot074() = 0;
	virtual void slot078() = 0; virtual void slot07C() = 0; virtual void slot080() = 0;
	virtual void slot084() = 0; virtual void slot088() = 0; virtual void slot08C() = 0;
	virtual void slot090() = 0; virtual void slot094() = 0; virtual void slot098() = 0;
	virtual void slot09C() = 0; virtual void slot0A0() = 0; virtual void slot0A4() = 0;
	virtual void slot0A8() = 0; virtual void slot0AC() = 0;
	virtual Int winSetFocus(GameWindow *window) = 0;                          // slot 0xB0
	virtual void slot0B4() = 0; virtual void slot0B8() = 0; virtual void slot0BC() = 0;
	virtual void slot0C0() = 0; virtual void slot0C4() = 0; virtual void slot0C8() = 0;
	virtual void slot0CC() = 0; virtual void slot0D0() = 0; virtual void slot0D4() = 0;
	virtual void slot0D8() = 0;
	virtual GameWindow *winGetWindowFromId(GameWindow *window, NameKeyType id) = 0; // slot 0xDC
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class ControlBarSchemeManager
{
public:
	void setControlBarSchemeByPlayer(Player *p);
};

class RecorderClass
{
public:
	RecorderModeType getMode();
};

// TheGameLogic's mode word, as the matched switchToContext reads it.
class GameLogic
{
public:
	GameMode getGameMode() const { return m_gameMode; }

private:
	char m_unmodelled00[0x10c];
	GameMode m_gameMode;               // +0x10c
};

class GameInfo
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0;
	virtual void slot0C() = 0; virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0; virtual void slot20() = 0;
	virtual void slot24() = 0; virtual void slot28() = 0;
	virtual Bool isMultiPlayer() = 0;                                          // slot 0x2C
};

class InGameUI
{
public:
	virtual void slot000() = 0; virtual void slot004() = 0; virtual void slot008() = 0;
	virtual void slot00C() = 0; virtual void slot010() = 0; virtual void slot014() = 0;
	virtual void slot018() = 0; virtual void slot01C() = 0; virtual void slot020() = 0;
	virtual void slot024() = 0; virtual void slot028() = 0; virtual void slot02C() = 0;
	virtual void slot030() = 0; virtual void slot034() = 0; virtual void slot038() = 0;
	virtual void slot03C() = 0; virtual void slot040() = 0; virtual void slot044() = 0;
	virtual void slot048() = 0; virtual void slot04C() = 0; virtual void slot050() = 0;
	virtual void slot054() = 0; virtual void slot058() = 0; virtual void slot05C() = 0;
	virtual void slot060() = 0; virtual void slot064() = 0; virtual void slot068() = 0;
	virtual void slot06C() = 0; virtual void slot070() = 0; virtual void slot074() = 0;
	virtual void slot078() = 0; virtual void slot07C() = 0; virtual void slot080() = 0;
	virtual void slot084() = 0; virtual void slot088() = 0; virtual void slot08C() = 0;
	virtual void slot090() = 0; virtual void slot094() = 0; virtual void slot098() = 0;
	virtual void slot09C() = 0; virtual void slot0A0() = 0; virtual void slot0A4() = 0;
	virtual void slot0A8() = 0; virtual void slot0AC() = 0; virtual void slot0B0() = 0;
	virtual void slot0B4() = 0; virtual void slot0B8() = 0; virtual void slot0BC() = 0;
	virtual void slot0C0() = 0; virtual void slot0C4() = 0; virtual void slot0C8() = 0;
	virtual void slot0CC() = 0; virtual void slot0D0() = 0; virtual void slot0D4() = 0;
	virtual void slot0D8() = 0; virtual void slot0DC() = 0; virtual void slot0E0() = 0;
	virtual void slot0E4() = 0; virtual void slot0E8() = 0; virtual void slot0EC() = 0;
	virtual void slot0F0() = 0; virtual void slot0F4() = 0; virtual void slot0F8() = 0;
	virtual void slot0FC() = 0; virtual void slot100() = 0; virtual void slot104() = 0;
	virtual void slot108() = 0; virtual void slot10C() = 0; virtual void slot110() = 0;
	virtual void slot114() = 0; virtual void slot118() = 0;
	virtual void setRadiusCursorNone() = 0;                                    // slot 0x11C
};

class GameClient
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0;
	virtual void slot0C() = 0; virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0; virtual void slot20() = 0;
	virtual void slot24() = 0; virtual void slot28() = 0;
	virtual Drawable *slot2C(Int id) = 0;
	virtual void slot30() = 0; virtual void slot34() = 0; virtual void slot38() = 0;
	virtual void slot3C() = 0; virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0; virtual void slot50() = 0;
	virtual void slot54() = 0; virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60(Drawable *draw) = 0;
};

class BfmeTransitionMD
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0;
};

// ControlBar+0x2f0: a virtual at +0x10, and the target of the 0x004AFA80 call.
class BfmeSourceCB;
class Gen_004AFA80
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0;
	void bfmeTake(BfmeSourceCB *source);
};

class Rva0058C040
{
public:
	void invoke();
};

class Rva005127A0InGameChat;

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;
extern RecorderClass *TheRecorder;
extern GameLogic *TheGameLogic;
extern GameInfo *TheGameInfo;
extern InGameUI *TheInGameUI;
extern GameClient *TheGameClient;
extern BfmeTransitionMD *g_bfmeTransitionMD;
extern Rva005127A0InGameChat *g_Rva005127A0InGameChat;
extern void *g_obj12F4C38;
extern Rva0058C040 *Glo012F4B98;
extern Drawable *g_Rva012F340C;

class ControlBar
{
public:
	void setControlBarSchemeByPlayer(Player *p);
	void populateObserverList();

protected:
	void switchToContext(ControlBarContext context, Drawable *draw);
	void setDefaultControlBarConfig();

private:
	char m_unmodelled00[0x30];
	ControlBarSchemeManager *m_controlBarSchemeManager;   // +0x30
	GameWindow *m_contextParent[10];                       // +0x34
	Drawable *m_currentSelectedDrawable;                   // +0x5c
	ControlBarContext m_currContext;                       // +0x60
	Int m_dword64;                                         // +0x64
	char m_unmodelled68[0x208];
	Bool m_isObserverCommandBar;                           // +0x270
	char m_unmodelled271[0x7f];
	Gen_004AFA80 *m_ptr2f0;                                // +0x2f0
};

void ControlBar::setControlBarSchemeByPlayer(Player *p)
{
	if (m_controlBarSchemeManager)
		m_controlBarSchemeManager->setControlBarSchemeByPlayer(p);

	static NameKeyType buttonPlaceBeaconID = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonPlaceBeacon");
	static NameKeyType buttonIdleWorkerID = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonIdleWorker");
	static NameKeyType buttonGeneralID = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonGeneral");
	GameWindow *buttonPlaceBeacon = TheWindowManager->winGetWindowFromId(0, buttonPlaceBeaconID);
	GameWindow *buttonIdleWorker = TheWindowManager->winGetWindowFromId(0, buttonIdleWorkerID);
	GameWindow *buttonGeneral = TheWindowManager->winGetWindowFromId(0, buttonGeneralID);

	if (!p->isPlayerActive())
	{
		m_isObserverCommandBar = true;

		// switchToContext(CB_CONTEXT_OBSERVER_LIST, NULL), as retail expands it.
		if (g_bfmeTransitionMD)
			g_bfmeTransitionMD->slot04();
		TheInGameUI->setRadiusCursorNone();
		if (g_Rva012F340C != 0 && m_currentSelectedDrawable != 0)
			m_ptr2f0->slot04();
		Drawable *oldSelected = m_currentSelectedDrawable;
		m_currentSelectedDrawable = 0;
		if (g_Rva005127A0InGameChat == 0)
		{
			g_Rva012F340C = oldSelected;
			if (g_obj12F4C38 == 0 && TheGameLogic != 0 &&
				TheGameLogic->getGameMode() != 8 && TheGameLogic->getGameMode() != GAME_SHELL)
				TheWindowManager->winSetFocus(0);
		}
		else
		{
			g_Rva012F340C = oldSelected;
		}
		m_ptr2f0->bfmeTake(0);
		if (m_dword64 != 0)
		{
			TheGameClient->slot60(TheGameClient->slot2C(m_dword64));
			m_dword64 = 0;
		}
		if (Glo012F4B98 != 0)
			Glo012F4B98->invoke();
		m_contextParent[2]->winHide(true);
		m_contextParent[9]->winHide(true);
		m_contextParent[3]->winHide(true);
		m_contextParent[4]->winHide(true);
		m_contextParent[5]->winHide(true);
		m_contextParent[8]->winHide(true);
		m_contextParent[6]->winHide(true);
		m_contextParent[7]->winHide(false);
		populateObserverList();
		m_currContext = CB_CONTEXT_OBSERVER_LIST;

		if (buttonPlaceBeacon)
			buttonPlaceBeacon->winHide(true);
		if (buttonIdleWorker)
			buttonIdleWorker->winHide(true);
		if (buttonGeneral)
			buttonGeneral->winEnable(false);
	}
	else
	{
		switchToContext(CB_CONTEXT_NONE, 0);
		m_isObserverCommandBar = false;

		if (buttonPlaceBeacon)
			buttonPlaceBeacon->winHide(
				(TheGameLogic->getGameMode() != GAME_LAN && TheGameLogic->getGameMode() != GAME_INTERNET) ||
				!TheGameInfo->isMultiPlayer());
		if (buttonIdleWorker)
			buttonIdleWorker->winHide(false);
		if (buttonGeneral)
		{
			buttonGeneral->winHide(false);
			buttonGeneral->winEnable(true);
		}
	}

	if (TheRecorder == 0 || TheRecorder->getMode() != RECORDERMODE_PLAYBACK)
		setDefaultControlBarConfig();
}
