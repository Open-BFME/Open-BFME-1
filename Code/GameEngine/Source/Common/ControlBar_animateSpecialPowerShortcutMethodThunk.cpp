// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?animateSpecialPowerShortcut@ControlBar@@QAEX_N@Z: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
// Lift the ControlBar::animateSpecialPowerShortcut naked dump to clean C++.
//
// Zero Hour's ControlBar.cpp body, unchanged. The dontAnimate flag does not
// survive as a variable: the loop either finds a button with user data and falls
// straight into the animate section, or runs to completion and returns, which is
// what the flag plus the `if (dontAnimate) return` collapses to.
//
// The button count is re-read from the object on every iteration rather than
// cached, matching the loop condition as ZH writes it.
//
// Retail pins the layout: the animation manager is at this+0x10, the shortcut
// button array at +0xCC, the used-button count at +0xF4 and the shortcut parent
// at +0xFC. reset is the virtual at vtable +0x10 while registerGameWindow and
// reverseAnimateWindow are direct calls.

typedef int Int;
typedef bool Bool;

enum { WIN_ANIMATION_SLIDE_RIGHT = 1 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void *winGetUserData(void);							///< ILT thunk at 0x00046538
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/AnimateWindowManager.h
class AnimateWindowManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();

	virtual void reset(void);							///< vtable +0x10

	void registerGameWindow(GameWindow *win, Int animType, Bool needsToFinish,
			Int ms, Int delayMs);						///< ILT thunk at 0x00045322
	void reverseAnimateWindow(void);					///< ILT thunk at 0x00027B65
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void animateSpecialPowerShortcut(Bool isOn);

private:
	unsigned char m_unreconstructed_00[0x10];
	AnimateWindowManager *m_animateWindowManagerForGenShortcuts;	///< retail this+0x10
	unsigned char m_unreconstructed_14[0xCC - 0x14];
	GameWindow *m_specialPowerShortcutButtons[10];		///< retail this+0xCC
	Int m_currentlyUsedSpecialPowersButtons;			///< retail this+0xF4
	unsigned char m_unreconstructed_F8[4];
	GameWindow *m_specialPowerShortcutParent;			///< retail this+0xFC
};

// ?animateSpecialPowerShortcut@ControlBar@@QAEX_N@Z
void ControlBar::animateSpecialPowerShortcut( Bool isOn )
{
	if(!m_specialPowerShortcutParent || !m_animateWindowManagerForGenShortcuts || !m_currentlyUsedSpecialPowersButtons)
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
	if(dontAnimate)
		return;

	if(isOn)
	{
		m_animateWindowManagerForGenShortcuts->reset();
		m_animateWindowManagerForGenShortcuts->registerGameWindow(m_specialPowerShortcutParent,WIN_ANIMATION_SLIDE_RIGHT,true,500,0);
	}
	else
	{
		m_animateWindowManagerForGenShortcuts->reverseAnimateWindow();
	}
}
