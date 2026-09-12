// cl: /Ireference/shims/stringinline

#include "StringInline.h"

typedef int Int;
typedef bool Bool;

#define TRUE true
#define FALSE false
#define NULL 0

class Drawable;
enum ControlBarContext { CB_CONTEXT_NONE = 0 };

class GameWindow
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	int winEnable(Bool enabled);
	void winHide(Bool hidden);
};

class WindowLayout
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void hide(Bool hidden);
};

class AnimateWindowManager
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void reset(void);
};

class WindowVideoManager : public AnimateWindowManager {};

class GameWindowManager
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void slot58(void);
	virtual void slot5c(void);
	virtual void slot60(void);
	virtual void slot64(void);
	virtual void slot68(void);
	virtual void slot6c(void);
	virtual void slot70(void);
	virtual void slot74(void);
	virtual void winDestroy(GameWindow *window);
};

extern GameWindowManager *TheWindowManager;

class Overridable
{
public:
	virtual ~Overridable(void);

	Overridable *deleteOverrides(void)
	{
		if (m_isOverride)
		{
			delete this;
			return 0;
		}
		if (m_nextOverride)
			m_nextOverride = m_nextOverride->deleteOverrides();
		return this;
	}

	Overridable *m_nextOverride;
	Bool m_isOverride;
};

class CommandButton : public Overridable
{
public:
	CommandButton *friend_getNext(void) { return m_next; }

private:
	char m_padding[0x14 - 0x0c];
	CommandButton *m_next;
	char m_unmodelled[0x144 - 0x18];

public:
	int m_at144;
};

class CommandSet : public Overridable
{
public:
	CommandSet *friend_getNext(void) { return m_next; }

private:
	char m_padding[0x60 - 0x0c];
	CommandSet *m_next;
};

class Rva005929E0
{
public:
	void release(void);
};

class Glo012F4B98Type
{
public:
	char m_padding[0x488];
	Rva005929E0 m_sub;
};

extern Glo012F4B98Type *Glo012F4B98;

class GameWindowTransitionsHandler
{
public:
	void remove(AsciiString groupName, Bool skipPending);
};

void __cdecl j_0003836b(void);
typedef void (__cdecl *CommandWindowReset)(GameWindow *window, Int value);

extern GameWindowTransitionsHandler *TheTransitionHandler;

class ControlBar
{
public:
	virtual void reset(void);

protected:
	void switchToContext(ControlBarContext context, Drawable *draw);

private:
	void hideSpecialPowerShortcut(void)
	{
		if (m_specialPowerShortcutParent)
			m_specialPowerShortcutParent->winHide(TRUE);
	}

	char m_padding00[0x04];
	WindowVideoManager *m_videoManager;
	AnimateWindowManager *m_animateWindowManager;
	AnimateWindowManager *m_animateWindowManagerForGenShortcuts;
	AnimateWindowManager *m_generalsScreenAnimate;
	char m_padding18[0x28 - 0x18];
	CommandButton *m_commandButtons;
	CommandSet *m_commandSets;
	char m_padding30[0x64 - 0x30];
	Int m_rallyPointDrawableID;
	float m_displayedConstructPercent;
	Int m_displayedOCLTimerSeconds;
	char m_padding70[0xfc - 0x70];
	GameWindow *m_specialPowerShortcutParent;
	GameWindow *m_commandWindows[20];
	char m_padding150[0x240 - 0x150];
	Bool m_sideSelectAnimateDown;
	char m_padding241[0x264 - 0x241];
	GameWindow *m_animateDownWindow;
	char m_padding268[0x270 - 0x268];
	Bool m_isObserverCommandBar;
	char m_padding271[0x274 - 0x271];
	void *m_observerLookAtPlayer;
	WindowLayout *m_buildToolTipLayout;
	Bool m_showBuildToolTipLayout;
	char m_padding280[0x2bc - 0x280];
	void *m_genArrow;
	char m_padding2c0[0x2c8 - 0x2c0];
	Bool m_genStarFlash;
	char m_padding2c9[0x2cc - 0x2c9];
	Int m_lastFlashedAtPointValue;
	char m_padding2d0[0x2e0 - 0x2d0];
	Bool m_radarAttackGlowOn;
	char m_padding2e1[3];
	Int m_remainingRadarAttackGlowFrames;
	GameWindow *m_radarAttackGlowWindow;
};

void ControlBar::reset(void)
{
	int zero = 0;
	hideSpecialPowerShortcut();
	m_rallyPointDrawableID = zero;
	if (m_radarAttackGlowWindow)
		m_radarAttackGlowWindow->winEnable(TRUE);
	m_radarAttackGlowOn = zero;
	m_remainingRadarAttackGlowFrames = zero;
	m_displayedConstructPercent = -1.0f;
	m_displayedOCLTimerSeconds = zero;
	m_isObserverCommandBar = zero;
	m_observerLookAtPlayer = (void *)zero;
	if (m_buildToolTipLayout)
		m_buildToolTipLayout->hide(TRUE);
	m_showBuildToolTipLayout = zero;
	if (Glo012F4B98 != (Glo012F4B98Type *)zero)
		Glo012F4B98->m_sub.release();
	if (m_animateWindowManager)
		m_animateWindowManager->reset();
	if (m_animateWindowManagerForGenShortcuts)
		m_animateWindowManagerForGenShortcuts->reset();
	if (m_generalsScreenAnimate)
		m_generalsScreenAnimate->reset();
	if (m_videoManager)
		m_videoManager->reset();
	switchToContext(CB_CONTEXT_NONE, NULL);
	m_sideSelectAnimateDown = zero;
	if (m_animateDownWindow)
	{
		TheWindowManager->winDestroy(m_animateDownWindow);
		m_animateDownWindow = (GameWindow *)zero;
	}
	CommandSet *set, *nextSet;
	set = m_commandSets;
	while (set)
	{
		Bool possibleAdjustment = FALSE;
		nextSet = set->friend_getNext();
		if (set == m_commandSets)
			possibleAdjustment = TRUE;
		Overridable *stillValid = set->deleteOverrides();
		if (stillValid == NULL && possibleAdjustment)
			m_commandSets = nextSet;
		set = nextSet;
	}
	CommandButton *button, *nextButton;
	button = m_commandButtons;
	while (button)
	{
		Bool possibleAdjustment = FALSE;
		nextButton = button->friend_getNext();
		if (button == m_commandButtons)
			possibleAdjustment = TRUE;
		Overridable *stillValid = button->deleteOverrides();
		if (stillValid == NULL && possibleAdjustment)
			m_commandButtons = nextButton;
		button = nextButton;
	}
	button = m_commandButtons;
	while (button)
	{
		button->m_at144 = zero;
		button = button->friend_getNext();
	}
	GameWindow **window = m_commandWindows;
	Int count = 20;
	while (count)
	{
		if (*window)
			((CommandWindowReset)j_0003836b)(*window, zero);
		++window;
		--count;
	}
	if (TheTransitionHandler != (GameWindowTransitionsHandler *)zero)
		TheTransitionHandler->remove("ControlBarArrow", zero);
	m_genArrow = (void *)zero;
	m_lastFlashedAtPointValue = -1;
	m_genStarFlash = TRUE;
}
