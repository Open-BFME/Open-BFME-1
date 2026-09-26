// ?closeWindows@GameLogic@@QAEXXZ
// partial score=0.72 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
//
// BFME closeWindows, retail RVA 0x00396950 (294 bytes).  The BFME body is
// not the shorter Generals/Zero Hour GameLogicDispatch twin: it closes the
// APT-era menus through both window-manager objects and only tears down the
// background when the pending flag is set.

typedef unsigned int NameKeyType;
typedef unsigned int WindowMsgData;

enum GadgetGameMessage
{
	GBM_SELECTED = 0x4008
};

class GameWindow;

// BFME's WindowLayout vtable, proven by GameLogic::~GameLogic and the
// matched destroyWindows body.  Slot 1 is the scalar/deleting operation used
// by closeWindows with the flag 1; it is deliberately declaration-only.
class WindowLayout
{
public:
	virtual void slot00(void) = 0;
	virtual void deleteInstance(unsigned int) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1C(void) = 0;
	virtual void destroyWindows(void) = 0;
};

// The object at 0x012F19E8 is the older BFME WindowManager.  Its reset
// operation is vtable slot 5 (+0x14), independently visible in both reset
// calls in this body.  The full class is intentionally not invented here.
class WindowManager
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void reset(void) = 0;
};

// GameWindowManager vtable slots used by the options-menu lookup/send path.
// This is the same slot layout as the already matched GameWindowManager
// methods in GameClient/GUI/GameWindowManager.cpp.
class GameWindowManager
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void reset(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1C(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot2C(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot3C(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot48(void) = 0;
	virtual void slot4C(void) = 0;
	virtual void slot50(void) = 0;
	virtual void slot54(void) = 0;
	virtual void slot58(void) = 0;
	virtual void slot5C(void) = 0;
	virtual void slot60(void) = 0;
	virtual void slot64(void) = 0;
	virtual void slot68(void) = 0;
	virtual void slot6C(void) = 0;
	virtual void slot70(void) = 0;
	virtual void slot74(void) = 0;
	virtual void slot78(void) = 0;
	virtual void slot7C(void) = 0;
	virtual void slot80(void) = 0;
	virtual void slot84(void) = 0;
	virtual void slot88(void) = 0;
	virtual void slot8C(void) = 0;
	virtual void slot90(void) = 0;
	virtual void slot94(void) = 0;
	virtual void slot98(void) = 0;
	virtual void slot9C(void) = 0;
	virtual void slotA0(void) = 0;
	virtual void slotA4(void) = 0;
	virtual void slotA8(void) = 0;
	virtual void slotAC(void) = 0;
	virtual void slotB0(void) = 0;
	virtual void slotB4(void) = 0;
	virtual void slotB8(void) = 0;
	virtual void slotBC(void) = 0;
	virtual void slotC0(void) = 0;
	virtual void slotC4(void) = 0;
	virtual void slotC8(void) = 0;
	virtual void slotCC(void) = 0;
	virtual void slotD0(void) = 0;
	virtual int winSendSystemMsg(GameWindow *, unsigned int,
		WindowMsgData, WindowMsgData) = 0;
	virtual void slotD8(void) = 0;
	virtual GameWindow *winGetWindowFromId(GameWindow *, NameKeyType) = 0;
};

class ControlBar
{
public:
	void hidePurchaseScience(void);
	void hideSpecialPowerShortcut(void);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

// The BFME singleton at 0x012F4B40 is only used as a truth guard here; its
// layout is proven by the independent HideSaveLoadMenu body.
class BfmeObj947C;

class GameLogic
{
public:
	void closeWindows(void);
	virtual ~GameLogic(void);

private:
	char m_unmodelled[0x1a0];
	WindowLayout *m_background;
	unsigned char m_backgroundPending;
};

void HideDiplomacy(void);
void HideInGameChat(void);
void ResetInGameChat(void);
void HideQuitMenu(void);
void HideSaveLoadMenu(void);
void ReleaseWindowLayout(WindowLayout *layout);

extern ControlBar *TheControlBar;
extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;
extern WindowManager *g_theWindowManager;
extern BfmeObj947C *g_bfme947ObjC;
extern void *g_quitMenuLayout;

// ?closeWindows@GameLogic@@QAEXXZ
void GameLogic::closeWindows(void)
{
	HideDiplomacy();
	HideInGameChat();
	ResetInGameChat();
	TheControlBar->hidePurchaseScience();
	TheControlBar->hideSpecialPowerShortcut();

	if (g_quitMenuLayout)
		HideQuitMenu();

	g_theWindowManager->reset();

	if (g_bfme947ObjC)
		HideSaveLoadMenu();

	g_theWindowManager->reset();
	TheWindowManager->reset();

	NameKeyType buttonID = TheNameKeyGenerator->nameToKey(
		"OptionsMenu.wnd:ButtonBack");
	GameWindow *button = TheWindowManager->winGetWindowFromId((GameWindow *)0, buttonID);
	NameKeyType zero = buttonID - buttonID;
	GameWindow *window = TheWindowManager->winGetWindowFromId(
		(GameWindow *)zero, TheNameKeyGenerator->nameToKey(
			"OptionsMenu.wnd:OptionsMenuParent"));
	if (window != (GameWindow *)zero)
		TheWindowManager->winSendSystemMsg(window, GBM_SELECTED,
			(WindowMsgData)button, buttonID);

	if (m_backgroundPending != zero)
	{
		WindowLayout *background = m_background;
		m_backgroundPending = zero;
		if (background != (WindowLayout *)zero)
		{
			background->destroyWindows();
			if (m_background != (WindowLayout *)zero)
			{
				m_background->deleteInstance(1);
				m_background = (WindowLayout *)zero;
				return;
			}
		}
		else
		{
			ReleaseWindowLayout((WindowLayout *)zero);
		}
	}
	m_background = (WindowLayout *)zero;
}
