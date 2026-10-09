// cl: /DNDEBUG /MD /EHsc
//
// GameLogic::closeWindows, retail 0x00396950 (294 B).  Zero Hour's body lives
// in GameLogicDispatch.cpp; BFME keeps its order (diplomacy, chat, control bar,
// quit menu, options menu) but guards the quit and save/load menus on their
// singletons, resets the window managers through vtable slot 5 and finally
// tears down the pending background layout at GameLogic+0x1A4/+0x1A8.
// Identity: the ILT thunk callers are ScriptActions::doVictory, doDefeat and
// doLocalDefeat, the Zero Hour callers of TheGameLogic->closeWindows().

enum NameKeyType { NAMEKEY_INVALID = 0 };
typedef unsigned int WindowMsgData;
enum { GBM_SELECTED = 0x4008 };

class GameWindow;

class WindowLayout
{
public:
	virtual void vslot00(void);
	virtual ~WindowLayout(void);
	virtual void vslot08(void);
	virtual void vslot0C(void);
	virtual void vslot10(void);
	virtual void vslot14(void);
	virtual void vslot18(void);
	virtual void vslot1C(void);
	virtual void destroyWindows(void);
};

// The BFME WindowManager singleton at 0x012F19E8 (named by HideQuitMenu).
class WindowManager
{
public:
	virtual void vslot00(void);
	virtual void vslot04(void);
	virtual void vslot08(void);
	virtual void vslot0C(void);
	virtual void vslot10(void);
	virtual void vslot14(void);
};

class GameWindowManager
{
public:
	virtual void vslot00(void);
	virtual void vslot04(void);
	virtual void vslot08(void);
	virtual void vslot0C(void);
	virtual void vslot10(void);
	virtual void vslot14(void);
	virtual void vslot18(void);
	virtual void vslot1C(void);
	virtual void vslot20(void);
	virtual void vslot24(void);
	virtual void vslot28(void);
	virtual void vslot2C(void);
	virtual void vslot30(void);
	virtual void vslot34(void);
	virtual void vslot38(void);
	virtual void vslot3C(void);
	virtual void vslot40(void);
	virtual void vslot44(void);
	virtual void vslot48(void);
	virtual void vslot4C(void);
	virtual void vslot50(void);
	virtual void vslot54(void);
	virtual void vslot58(void);
	virtual void vslot5C(void);
	virtual void vslot60(void);
	virtual void vslot64(void);
	virtual void vslot68(void);
	virtual void vslot6C(void);
	virtual void vslot70(void);
	virtual void vslot74(void);
	virtual void vslot78(void);
	virtual void vslot7C(void);
	virtual void vslot80(void);
	virtual void vslot84(void);
	virtual void vslot88(void);
	virtual void vslot8C(void);
	virtual void vslot90(void);
	virtual void vslot94(void);
	virtual void vslot98(void);
	virtual void vslot9C(void);
	virtual void vslotA0(void);
	virtual void vslotA4(void);
	virtual void vslotA8(void);
	virtual void vslotAC(void);
	virtual void vslotB0(void);
	virtual void vslotB4(void);
	virtual void vslotB8(void);
	virtual void vslotBC(void);
	virtual void vslotC0(void);
	virtual void vslotC4(void);
	virtual void vslotC8(void);
	virtual void vslotCC(void);
	virtual void vslotD0(void);
	virtual int winSendSystemMsg(GameWindow *window, unsigned int msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual void vslotD8(void);
	virtual GameWindow *winGetWindowFromId(GameWindow *window, int id);
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

struct BfmeObj947C;

class GameLogic
{
public:
	void closeWindows(void);

private:
	char m_pad000[0x1a4];
	WindowLayout *m_background;
	bool m_backgroundPending;
};

void HideDiplomacy(void);
void HideInGameChat(void);
void ResetInGameChat(void);
void HideQuitMenu(void);
void HideSaveLoadMenu(void);
void ReleaseWindowLayout(WindowLayout *layout);

// Retail ILT 0x20347 reaches the separate five-byte thunk at 0x49D0A0,
// which then jumps to hidePurchaseScience. Use that thunk's ledger name.
extern void j_0049d0a0();

static __forceinline void hidePurchaseScienceThunk(ControlBar *bar)
{
	typedef void (ControlBar::*Function)();
	union { void (*raw)(); Function member; } call;
	call.raw = j_0049d0a0;
	(bar->*call.member)();
}

extern ControlBar *TheControlBar;
extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;
extern WindowManager *g_rva012F19E8WindowManager;
class BfmeAptScreenQuitMenu;
extern BfmeAptScreenQuitMenu *g_obj12F4B40;
class BfmeAptScreenOptions;
extern BfmeAptScreenOptions *g_obj12F4AD4;

// ?closeWindows@GameLogic@@QAEXXZ
void GameLogic::closeWindows(void)
{
	HideDiplomacy();
	HideInGameChat();
	ResetInGameChat();
	hidePurchaseScienceThunk(TheControlBar);
	TheControlBar->hideSpecialPowerShortcut();
	if (reinterpret_cast<void * &>(g_obj12F4AD4))
	{
		HideQuitMenu();
		g_rva012F19E8WindowManager->vslot14();
	}
	if (reinterpret_cast<BfmeObj947C * &>(g_obj12F4B40))
	{
		HideSaveLoadMenu();
		g_rva012F19E8WindowManager->vslot14();
	}
	TheWindowManager->vslot14();

	// hide the options menu
	NameKeyType buttonID = TheNameKeyGenerator->nameToKey("OptionsMenu.wnd:ButtonBack");
	GameWindow *button = TheWindowManager->winGetWindowFromId(0, buttonID);
	GameWindow *window = TheWindowManager->winGetWindowFromId(0, TheNameKeyGenerator->nameToKey("OptionsMenu.wnd:OptionsMenuParent"));
	if (window)
		TheWindowManager->winSendSystemMsg(window, GBM_SELECTED, (WindowMsgData)button, buttonID);

	if (m_backgroundPending)
	{
		m_backgroundPending = false;
		if (m_background)
		{
			m_background->destroyWindows();
			delete m_background;
		}
		else
		{
			ReleaseWindowLayout(m_background);
		}
	}
	m_background = 0;
}
