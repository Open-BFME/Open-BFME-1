// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the ControlBar::showSpecialPowerShortcut naked dump to clean C++.
//
// Zero Hour's ControlBar.cpp body with one BFME simplification: ZH's final
// guard asks two questions -- whether the local player has any shortcut special
// power and whether the control bar has any shortcut selection -- where retail
// asks only the first.
//
// isGameEnding does not survive as a call; it inlines to a signed test of the
// field at TheScriptEngine+0x17080, so the guard is a comparison rather than a
// call. And the array null check is kept even though it cannot fail: retail
// takes the address of the member array with lea and tests that, which is what
// `!m_specialPowerShortcutButtons` compiles to when the member is an array
// rather than a pointer.
//
// The loop and the layout are the same as animateSpecialPowerShortcut: button
// array at this+0xCC, count at +0xF4, shortcut parent at +0xFC, and the count
// re-read on every iteration.

typedef int Int;
typedef bool Bool;

class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void *winGetUserData(void);							///< ILT thunk at 0x00046538
	void winHide(unsigned char hide);					// matches the pin already in symbols.csv							///< ILT thunk at 0x00027F2A
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	Bool isGameEnding(void) const { return m_endGameTimer >= 0; }

private:
	unsigned char m_unreconstructed_00[0x17080];
	Int m_endGameTimer;									///< retail this+0x17080
};

extern ScriptEngine *TheScriptEngine;					///< retail [0x012F076C]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	// returns a 32-bit value: retail tests eax, not al
	Int hasAnyShortcutSpecialPower(void);				///< ILT thunk at 0x0002331C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getLocalPlayer(void) { return m_localPlayer; }

private:
	unsigned char m_unreconstructed_00[0x0C];
	Player *m_localPlayer;								///< retail this+0x0C
};

extern PlayerList *ThePlayerList;						///< retail [0x012ED748]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void showSpecialPowerShortcut(void);

private:
	void populateSpecialPowerShortcut(Player *player);	///< ILT thunk at 0x00024695

	unsigned char m_unreconstructed_00[0xCC];
	GameWindow *m_specialPowerShortcutButtons[10];		///< retail this+0xCC
	Int m_currentlyUsedSpecialPowersButtons;			///< retail this+0xF4
	unsigned char m_unreconstructed_F8[4];
	GameWindow *m_specialPowerShortcutParent;			///< retail this+0xFC
};

// ?showSpecialPowerShortcut@ControlBar@@QAEXXZ
void ControlBar::showSpecialPowerShortcut( void )
{
	if(TheScriptEngine->isGameEnding() || !m_specialPowerShortcutParent
		||!m_specialPowerShortcutButtons || !ThePlayerList || !ThePlayerList->getLocalPlayer())
		return;
	Bool dontAnimate = true;
	for( Int i = 0; i < m_currentlyUsedSpecialPowersButtons; ++i )
	{
		if (m_specialPowerShortcutButtons[i]->winGetUserData())
		{
			dontAnimate = false;
			break;
		}
	}
	if( dontAnimate || !ThePlayerList->getLocalPlayer()->hasAnyShortcutSpecialPower() )
		return;
	m_specialPowerShortcutParent->winHide(false);
	populateSpecialPowerShortcut(ThePlayerList->getLocalPlayer());

}
