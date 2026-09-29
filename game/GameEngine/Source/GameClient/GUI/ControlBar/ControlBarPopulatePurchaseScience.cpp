// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/stringbaseascii /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
//
// ControlBar::populatePurchaseScience -- retail 0x004A0B90, 783 bytes.
//
// Identity: the matched callers ControlBar::showPurchaseScience (0x004A2290)
// and ControlBar::togglePurchaseScience (0x004A22F0) in
// ControlBarPurchaseScience.cpp call this body by name; the Zero Hour twin
// (inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/
// GameClient/GUI/ControlBar/ControlBar.cpp) fills the same
// "GeneralsExpPoints.wnd:StaticTextRankPointsAvailable" / ":StaticTextLevel" /
// ":ProgressBarExperience" / ":StaticTextTitle" windows with "SCIENCE:Rank"
// and "SCIENCE:Rank%d" and ends with updateContextPurchaseScience().
//
// BFME keeps a single array of 12 science buttons at ControlBar+0x9c, which
// ControlBar::init (0x004A0F70, +0x4e0) fills from
// "GeneralsExpPoints.wnd:ButtonRank3Number%d" -- Zero Hour's Rank3 array. The
// per-button logic Zero Hour spells in line lives in the matched
// ControlBar::bfmeQueryWD (0x004A09D0), and the "SCIENCE:Rank" level text that
// Zero Hour commented out is live again.
//
// ControlBar::bfmeQueryWD (0x004A09D0, 268 bytes) sits just before this body
// in retail's ControlBar.cpp and is carried here verbatim from
// ControlBar_bfmeQueryWD.cpp (shape_levers.md "Compiler-private ABI: compile
// the static helper with its caller"): with the definition in view VC7.1 sees
// that the query only writes through its out-pointers, so it keeps `found' in
// BL across winHide exactly as retail does instead of re-reading the stack
// slot. The copy compiles byte-identical to the landed 0x004A09D0 body.

#include <wchar.h>

#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"
#include "Lib/BaseType.h"


enum { MAX_PURCHASE_SCIENCE_RANK_3 = 12 };
enum { CP_PURCHASE_SCIENCE = 1 };
enum { WIN_STATUS_ALWAYS_COLOR = 0x01000000 };
enum NameKeyType { NAMEKEY_INVALID = 0 };

// BaseType.h's fast_float2long_round is what retail's `fld; fistp` at
// +0x21e is (shape_levers.md row 17); a C cast would call __ftol2.

class GameWindow
{
public:
	Int winHide(Bool hide);
	Int winEnable(Bool enable);
	UnsignedInt winSetStatus(UnsignedInt status);
	UnsignedInt winClearStatus(UnsignedInt status);
};

void GadgetStaticTextSetText(GameWindow *window, UnicodeString text);
void GadgetProgressBarSetProgress(GameWindow *window, Int progress);

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
	virtual void slot0A8() = 0; virtual void slot0AC() = 0; virtual void slot0B0() = 0;
	virtual void slot0B4() = 0; virtual void slot0B8() = 0; virtual void slot0BC() = 0;
	virtual void slot0C0() = 0; virtual void slot0C4() = 0; virtual void slot0C8() = 0;
	virtual void slot0CC() = 0; virtual void slot0D0() = 0; virtual void slot0D4() = 0;
	virtual void slot0D8() = 0;
	virtual GameWindow *winGetWindowFromId(GameWindow *window, NameKeyType id) = 0; // slot 0xDC
};

// The subsystem slots come first; MSVC lays the two fetch overloads out in
// reverse declaration order, putting fetch(AsciiString) at 0x24 and
// fetch(const char *) at 0x28 as retail calls them.
class GameTextInterface
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0;
	virtual void slot0C() = 0; virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0; virtual void slot20() = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0) = 0;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class ScriptEngine
{
public:
	Bool isGameEnding() const { return m_endGameTimer >= 0; }

private:
	char m_unmodelled00[0x17080];
	Int m_endGameTimer;                // +0x17080
};

// Retail inlines AsciiString::isEmpty() in bfmeQueryWD (`cmp word ptr
// [eax+4],0` at +0x6b); the shim header forwards it out of line.
static inline Bool inlineIsEmpty(const AsciiString &s)
{
	const char *text = *reinterpret_cast<const char *const *>(&s);
	return text == 0 || *reinterpret_cast<const unsigned short *>(text + 4) == 0;
}

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class GameLogicPortraitShim
{
public:
	Bool isInMultiplayerOrSkirmishGame();
};

class PlayerTemplate
{
public:
	char m_beforePurchaseScienceRank1[0xA4];
	AsciiString m_purchaseScienceRank1;
	AsciiString m_purchaseScienceRank3;

	const AsciiString &getPurchaseScienceCommandSetRank1() const
	{
		return m_purchaseScienceRank1;
	}

	const AsciiString &getPurchaseScienceCommandSetRank3() const
	{
		return m_purchaseScienceRank3;
	}
};

class Player
{
public:
	PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }
	Bool hasScience(ScienceType) const;
	Int getRankLevel() const { return m_rankLevel; }
	Real getSkillPoints() const { return m_skillPoints; }
	Int getSciencePurchasePoints() const { return m_sciencePurchasePoints; }
	Int getSkillPointsLevelUp() const { return m_levelUp; }
	Int getSkillPointsLevelDown() const { return m_levelDown; }

private:
	char m_beforePlayerTemplate[4];
	PlayerTemplate *m_playerTemplate;  // +0x04
	char m_unmodelled08[0x258 - 8];
	Int m_rankLevel;                   // +0x258
	Real m_skillPoints;                // +0x25c
	char m_unmodelled260[4];
	Int m_sciencePurchasePoints;       // +0x264
	Int m_levelUp;                     // +0x268
	Int m_levelDown;                   // +0x26c
};

struct ScienceVec
{
	ScienceType *m_begin;
	ScienceType *m_end;

	Bool empty() const
	{
		return m_begin == m_end;
	}

	ScienceType operator[](Int index) const
	{
		return m_begin[index];
	}
};

class CommandButton
{
public:
	char m_beforeScience[0x84];
	ScienceVec m_science;

	const ScienceVec &getScienceVec() const
	{
		return m_science;
	}
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(Int index) const;
};

class ScienceStore
{
public:
	Bool playerHasRootPrereqsForScience(const Player *player, ScienceType science) const;
	Bool playerHasPrereqsForScience(const Player *player, ScienceType science) const;
	Int getSciencePurchaseCost(ScienceType science) const;
};

extern ScriptEngine *TheScriptEngine;
extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;
extern GameTextInterface *TheGameText;

class ControlBar
{
public:
	void bfmeQueryWD(Player *player, Int buttonIndex, const CommandButton **buttonOut,
	                 Bool *found, Bool *canPurchase, Bool *hasScience);
	void setControlCommand(GameWindow *button, const CommandButton *commandButton);
	const CommandSet *findCommandSet(const AsciiString &name);

protected:
	void populatePurchaseScience(Player *player);
	void updateContextPurchaseScience();

private:
	char m_unmodelled00[0x34];
	GameWindow *m_contextParent[2];                                        // +0x34
	char m_unmodelled3c[0x60];
	GameWindow *m_sciencePurchaseWindowsRank3[MAX_PURCHASE_SCIENCE_RANK_3]; // +0x9c
};

class GameLogic;
extern GameLogic *TheGameLogic;
extern ControlBar *TheControlBar;
extern ScienceStore *TheScienceStore;
#define TheBfmeGameLogic ((GameLogicPortraitShim *)TheGameLogic)

// ?bfmeQueryWD@ControlBar@@QAEXPAVPlayer@@HPAPBVCommandButton@@PA_N22@Z present-unmatched
void ControlBar::bfmeQueryWD(
    Player *player,
    Int buttonIndex,
    const CommandButton **buttonOut,
    Bool *found,
    Bool *canPurchaseAtArg5,
    Bool *hasScienceAtArg6)
{
    *(volatile Bool *)found = false;
    *(volatile Bool *)canPurchaseAtArg5 = false;
    *(volatile Bool *)hasScienceAtArg6 = false;

    const AsciiString *commandSetName = 0;
    if (TheBfmeGameLogic->isInMultiplayerOrSkirmishGame())
    {
        if (player == 0)
            goto failure;

        const PlayerTemplate *playerTemplate = player->getPlayerTemplate();
        if (playerTemplate == 0)
            goto failure;

        const AsciiString &rank3Name = playerTemplate->getPurchaseScienceCommandSetRank3();
        if (inlineIsEmpty(rank3Name))
            goto failure;
        commandSetName = &rank3Name;
    }
    else
    {
        if (player == 0)
            goto failure;

        const PlayerTemplate *playerTemplate = player->getPlayerTemplate();
        if (playerTemplate == 0)
            goto failure;

        const AsciiString &rank1Name = playerTemplate->getPurchaseScienceCommandSetRank1();
        if (inlineIsEmpty(rank1Name))
            goto failure;
        commandSetName = &rank1Name;
    }

    const CommandSet *commandSet = TheControlBar->findCommandSet(*commandSetName);
    if (commandSet == 0)
        goto failure;

    const CommandButton *commandButton = commandSet->getCommandButton(buttonIndex);
    *buttonOut = commandButton;
    if (commandButton == 0)
        goto failure;

    *found = true;

    const CommandButton *button = *buttonOut;
    if (button->getScienceVec().empty())
        goto failure;

    ScienceType science = button->getScienceVec()[0];
    if (!TheScienceStore->playerHasRootPrereqsForScience(player, science))
        goto failure;
    if (!player->hasScience(science))
    {
        if (TheScienceStore->playerHasPrereqsForScience(player, science))
        {
            Int purchasePoints = player->getSciencePurchasePoints();
            if (TheScienceStore->getSciencePurchaseCost(science) <= purchasePoints)
                *(volatile Bool *)canPurchaseAtArg5 = true;
        }
    }
    else
    {
        *(volatile Bool *)hasScienceAtArg6 = true;
    }

failure:
    return;
}

void ControlBar::populatePurchaseScience(Player *player)
{
	if (TheScriptEngine->isGameEnding())
		return;

	Int i;
	for (i = 0; i < MAX_PURCHASE_SCIENCE_RANK_3; i++)
		m_sciencePurchaseWindowsRank3[i]->winHide(true);

	for (i = 0; i < MAX_PURCHASE_SCIENCE_RANK_3; i++)
	{
		const CommandButton *commandButton;
		Bool found;
		Bool canPurchase;
		Bool hasScience;
		bfmeQueryWD(player, i, &commandButton, &found, &canPurchase, &hasScience);
		GameWindow *win = m_sciencePurchaseWindowsRank3[i];
		win->winHide(!found);
		if (found)
			setControlCommand(win, commandButton);
		win->winEnable(canPurchase);
		if (hasScience)
			m_sciencePurchaseWindowsRank3[i]->winSetStatus(WIN_STATUS_ALWAYS_COLOR);
		else
			m_sciencePurchaseWindowsRank3[i]->winClearStatus(WIN_STATUS_ALWAYS_COLOR);
	}

	GameWindow *win = 0;
	UnicodeString tempUS;
	win = TheWindowManager->winGetWindowFromId(m_contextParent[CP_PURCHASE_SCIENCE],
		TheNameKeyGenerator->nameToKey("GeneralsExpPoints.wnd:StaticTextRankPointsAvailable"));
	if (win)
	{
		tempUS.format(UnicodeString(L"%d"), player->getSciencePurchasePoints());
		GadgetStaticTextSetText(win, tempUS);
	}

	win = TheWindowManager->winGetWindowFromId(m_contextParent[CP_PURCHASE_SCIENCE],
		TheNameKeyGenerator->nameToKey("GeneralsExpPoints.wnd:StaticTextLevel"));
	if (win)
	{
		tempUS.format(TheGameText->fetch("SCIENCE:Rank"), player->getRankLevel());
		GadgetStaticTextSetText(win, tempUS);
	}

	win = TheWindowManager->winGetWindowFromId(m_contextParent[CP_PURCHASE_SCIENCE],
		TheNameKeyGenerator->nameToKey("GeneralsExpPoints.wnd:ProgressBarExperience"));
	if (win)
	{
		Int progress;
		progress = ((fast_float2long_round((Real)floor(player->getSkillPoints())) - player->getSkillPointsLevelDown()) * 100)
			/ (player->getSkillPointsLevelUp() - player->getSkillPointsLevelDown());
		GadgetProgressBarSetProgress(win, progress);
	}

	win = TheWindowManager->winGetWindowFromId(m_contextParent[CP_PURCHASE_SCIENCE],
		TheNameKeyGenerator->nameToKey("GeneralsExpPoints.wnd:StaticTextTitle"));
	if (win)
	{
		AsciiString tempAs;
		tempAs.format(AsciiString("SCIENCE:Rank%d"), player->getRankLevel());
		GadgetStaticTextSetText(win, TheGameText->fetch(tempAs));
	}

	updateContextPurchaseScience();
}
