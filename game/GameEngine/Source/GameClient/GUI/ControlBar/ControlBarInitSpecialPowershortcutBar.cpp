// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// ControlBar::initSpecialPowershortcutBar -- retail 0x0049F1C0, 766 bytes.
//
// Identity: the Zero Hour twin (inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/
// Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp) is the same
// body: it concatenates ":GenPowersShortcutBarParent" (0x010FB930),
// ":ButtonCommand%d" (0x010FB91C) and ":ButtonParent%d" (0x010FB908) onto the
// player template's special-power window name and resolves each window.
// Retail callers are GameLogic::startNewGame and the PlayerList destroyNotify
// path, both through the ILT, matching Zero Hour's
// TheControlBar->initSpecialPowershortcutBar(ThePlayerList->getLocalPlayer()).
//
// BFME differences read off retail: MAX_SPECIAL_POWER_SHORTCUTS is 5 (the
// clearing loop and MIN clamp use 5), the window loop runs to
// m_currentlyUsedSpecialPowersButtons, only WIN_STATUS_USE_OVERLAY_STATES
// (0x00200000) is set, and the `!player` test is gone.
//
// ControlBar offsets: 0xcc/0xf4/0xfc are witnessed (tools/name_oracle.py);
// 0xe0 and 0xf8 carry the names Zero Hour's twin writes in the same order
// (parents array beside the buttons, the layout the body destroys/creates).

#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum { MAX_SPECIAL_POWER_SHORTCUTS = 5 };
enum { WIN_STATUS_USE_OVERLAY_STATES = 0x00200000 };
enum NameKeyType { NAMEKEY_INVALID = 0 };

// Retail inlines AsciiString::str() and isEmpty() here; ascii_string.h
// forwards both to out-of-line StringBase<char> bodies. Read the Header
// pointer at +0 (ref count +0, length +4, text +8) in line, as retail does.
extern char Rva006A16B0Empty[];

static inline const char *inlineStr(const AsciiString &s)
{
	const char *text = *reinterpret_cast<const char *const *>(&s);
	return text ? text + 8 : Rva006A16B0Empty;
}

static inline Bool inlineIsEmpty(const AsciiString &s)
{
	const char *text = *reinterpret_cast<const char *const *>(&s);
	return text == 0 || *reinterpret_cast<const unsigned short *>(text + 4) == 0;
}

class GameWindow
{
public:
	UnsignedInt winSetStatus(UnsignedInt status);
};

// BFME makes WindowLayout virtual: slot 1 is the deleting destructor, slot 4
// hide(Bool), slot 8 destroyWindows (ControlBarPrintPositions.cpp, Shell_doPush.cpp).
class WindowLayout
{
public:
	virtual void runInit(void *) = 0;
	virtual ~WindowLayout();
	virtual void runUpdate(void *) = 0;
	virtual void runShutdown(void *) = 0;
	virtual void hide(Bool hide) = 0;
	virtual void bringForward() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void destroyWindows() = 0;
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
	virtual WindowLayout *winCreateLayout(AsciiString filename) = 0;        // slot 0x6C
	virtual void slot070() = 0; virtual void slot074() = 0; virtual void slot078() = 0;
	virtual void slot07C() = 0; virtual void slot080() = 0; virtual void slot084() = 0;
	virtual void slot088() = 0; virtual void slot08C() = 0; virtual void slot090() = 0;
	virtual void slot094() = 0; virtual void slot098() = 0; virtual void slot09C() = 0;
	virtual void slot0A0() = 0; virtual void slot0A4() = 0; virtual void slot0A8() = 0;
	virtual void slot0AC() = 0; virtual void slot0B0() = 0; virtual void slot0B4() = 0;
	virtual void slot0B8() = 0; virtual void slot0BC() = 0; virtual void slot0C0() = 0;
	virtual void slot0C4() = 0; virtual void slot0C8() = 0; virtual void slot0CC() = 0;
	virtual void slot0D0() = 0; virtual void slot0D4() = 0; virtual void slot0D8() = 0;
	virtual GameWindow *winGetWindowFromId(GameWindow *window, NameKeyType id) = 0; // slot 0xDC
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
	NameKeyType nameToKey(const char *name);
};

extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;

class PlayerTemplate
{
public:
	const AsciiString &getSpecialPowerShortcutWinName() const { return m_specialPowerShortcutWinName; }
	Int getSpecialPowerShortcutButtonCount() const { return m_specialPowerShortcutButtonCount; }

private:
	char m_unmodelled00[0xb0];
	AsciiString m_specialPowerShortcutWinName;     // +0xb0
	Int m_specialPowerShortcutButtonCount;         // +0xb4
};

class Player
{
public:
	const PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }
	Bool isLocalPlayer() const;
	Bool isPlayerActive() const;

private:
	char m_unmodelled00[4];
	const PlayerTemplate *m_playerTemplate;        // +0x04
};

class ControlBar
{
public:
	void initSpecialPowershortcutBar(Player *player);

private:
	char m_unmodelled00[0xcc];
	GameWindow *m_specialPowerShortcutButtons[MAX_SPECIAL_POWER_SHORTCUTS];        // +0xcc
	GameWindow *m_specialPowerShortcutButtonParents[MAX_SPECIAL_POWER_SHORTCUTS];  // +0xe0
	Int m_currentlyUsedSpecialPowersButtons;                                       // +0xf4
	WindowLayout *m_specialPowerLayout;                                            // +0xf8
	GameWindow *m_specialPowerShortcutParent;                                      // +0xfc
};

void ControlBar::initSpecialPowershortcutBar(Player *player)
{
	for (Int i = 0; i < MAX_SPECIAL_POWER_SHORTCUTS; ++i)
	{
		m_specialPowerShortcutButtonParents[i] = 0;
		m_specialPowerShortcutButtons[i] = 0;
	}

	if (m_specialPowerLayout)
	{
		m_specialPowerLayout->destroyWindows();
		delete m_specialPowerLayout;
		m_specialPowerLayout = 0;
	}
	m_specialPowerShortcutParent = 0;
	m_currentlyUsedSpecialPowersButtons = 0;
	const PlayerTemplate *pt = player->getPlayerTemplate();

	if (!pt || !player->isLocalPlayer()
			|| pt->getSpecialPowerShortcutButtonCount() == 0
			|| inlineIsEmpty(pt->getSpecialPowerShortcutWinName())
			|| !player->isPlayerActive())
		return;
	m_currentlyUsedSpecialPowersButtons = pt->getSpecialPowerShortcutButtonCount();
	AsciiString layoutName, tempName, windowName, parentName;
	layoutName = pt->getSpecialPowerShortcutWinName();
	m_specialPowerLayout = TheWindowManager->winCreateLayout(layoutName);
	m_specialPowerLayout->hide(true);

	tempName = layoutName;
	tempName.concat(":GenPowersShortcutBarParent");
	NameKeyType id = TheNameKeyGenerator->nameToKey(tempName);
	m_specialPowerShortcutParent = TheWindowManager->winGetWindowFromId(0, id);

	tempName = layoutName;
	tempName.concat(":ButtonCommand%d");
	parentName = layoutName;
	parentName.concat(":ButtonParent%d");
	Int count = pt->getSpecialPowerShortcutButtonCount();
	m_currentlyUsedSpecialPowersButtons = count < MAX_SPECIAL_POWER_SHORTCUTS ? count : MAX_SPECIAL_POWER_SHORTCUTS;
	for (i = 0; i < m_currentlyUsedSpecialPowersButtons; i++)
	{
		windowName.format(tempName, i + 1);
		id = TheNameKeyGenerator->nameToKey(inlineStr(windowName));
		m_specialPowerShortcutButtons[i] =
			TheWindowManager->winGetWindowFromId(m_specialPowerShortcutParent, id);
		m_specialPowerShortcutButtons[i]->winSetStatus(WIN_STATUS_USE_OVERLAY_STATES);

		windowName.format(parentName, i + 1);
		id = TheNameKeyGenerator->nameToKey(inlineStr(windowName));
		m_specialPowerShortcutButtonParents[i] =
			TheWindowManager->winGetWindowFromId(m_specialPowerShortcutParent, id);
	}
}
