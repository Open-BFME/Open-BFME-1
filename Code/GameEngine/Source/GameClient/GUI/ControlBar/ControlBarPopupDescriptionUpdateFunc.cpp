// cl: /DNDEBUG /MD /EHsc

// ControlBar.cpp registers this callback with the build-tooltip WindowLayout
// (m_buildToolTipLayout->setUpdate(ControlBarPopupDescriptionUpdateFunc)).
// The matching ZH callback is
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/
// GameClient/GUI/GUICallbacks/ControlBarPopupDescription.cpp.  BFME inlines
// hideBuildTooltipLayout here; the retail body consequently contains its
// reverse-or-delete decision before the ordinary update test.

typedef int Int;
typedef bool Bool;

class WindowLayout;

// upstream layout: reference/.../GameLogic/ScriptEngine.h.  BFME's field is
// at +0x17080, and the callback inlines isGameEnding as a signed comparison.
class ScriptEngine
{
public:
	Bool isGameEnding(void) const { return m_endGameTimer >= 0; }

private:
	char m_bfmeHead[0x17080];
	Int m_endGameTimer;
};

extern ScriptEngine *TheScriptEngine;                         // 0x012F076C

// The BFME writable global carries the animation switch at +0xBC4.  This
// offset differs from the vendored GlobalData header, so keep the view local.
class GlobalData
{
private:
	char m_bfmeHead[0xBC4];

public:
	Bool m_animateWindows;
};

extern GlobalData *TheWritableGlobalData;                     // 0x012ED5C8
extern Bool g_bfmeReadyPT;                                    // 0x012F3690

// Existing ledger spelling for the pointer at 0x012F368C.  Retail uses this
// same slot as the AnimateWindowManager pointer: +0x10 is m_needsUpdate,
// +0x11 is m_reverse, and vtable slot 5 is update.  The typed cast below
// preserves that proven global address without adding a competing pin/name.
class Glo012F368CType
{
};

extern Glo012F368CType *Glo012F368C;                          // 0x012F368C

class BfmeAnimateWindowManager
{
public:
	// A partial ABI view: one deleting-destructor slot and four unnamed
	// slots place update at the retail offset +0x14.
	virtual ~BfmeAnimateWindowManager();
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void update(void);

	void reverseAnimateWindow(void);                            // ILT 0x00027B65

	Bool isFinished(void) const { return !m_needsUpdate; }
	Bool isReversed(void) const { return m_reverse; }

private:
	char m_bfmeHead[0x0C];
	Bool m_needsUpdate;                                         // +0x10
	Bool m_reverse;                                             // +0x11
};

#define BFME_ANIMATE_WINDOW_MANAGER \
	(reinterpret_cast<BfmeAnimateWindowManager *>(Glo012F368C))

// Retail ControlBar offsets needed by this callback only.  The helper at
// 0x00027336 is the already matched ControlBar::deleteBuildTooltipLayout
// body at 0x004C1450; hideBuildTooltipLayout is inlined by retail here.
class ControlBar
{
public:
	void deleteBuildTooltipLayout(void);

	inline void hideBuildTooltipLayout(void)
	{
		if (BFME_ANIMATE_WINDOW_MANAGER && BFME_ANIMATE_WINDOW_MANAGER->isReversed())
			return;
		if (g_bfmeReadyPT && BFME_ANIMATE_WINDOW_MANAGER
			&& TheWritableGlobalData->m_animateWindows)
			BFME_ANIMATE_WINDOW_MANAGER->reverseAnimateWindow();
		else
			deleteBuildTooltipLayout();
	}

	Bool getShowBuildTooltipLayout(void) const { return m_showBuildToolTipLayout; }

private:
	char m_bfmeHeadA[0x278];
	void *m_bfmeLayout;                                          // +0x278
	Bool m_showBuildToolTipLayout;                               // +0x27C
};

extern ControlBar *TheControlBar;                              // 0x012F33F8

// ?ControlBarPopupDescriptionUpdateFunc@@YAXPAVWindowLayout@@PAX@Z
void ControlBarPopupDescriptionUpdateFunc(WindowLayout *, void *)
{
	if (TheScriptEngine->isGameEnding())
		TheControlBar->hideBuildTooltipLayout();

	if (BFME_ANIMATE_WINDOW_MANAGER && !TheControlBar->getShowBuildTooltipLayout()
		&& !BFME_ANIMATE_WINDOW_MANAGER->isReversed())
		BFME_ANIMATE_WINDOW_MANAGER->reverseAnimateWindow();
	else if (!TheControlBar->getShowBuildTooltipLayout()
		&& (!TheWritableGlobalData->m_animateWindows || !g_bfmeReadyPT))
		TheControlBar->deleteBuildTooltipLayout();

	if (g_bfmeReadyPT && BFME_ANIMATE_WINDOW_MANAGER
		&& TheWritableGlobalData->m_animateWindows)
	{
		Bool wasFinished = BFME_ANIMATE_WINDOW_MANAGER->isFinished();
		BFME_ANIMATE_WINDOW_MANAGER->update();
		if (BFME_ANIMATE_WINDOW_MANAGER
			&& BFME_ANIMATE_WINDOW_MANAGER->isFinished() && !wasFinished
			&& BFME_ANIMATE_WINDOW_MANAGER->isReversed())
		{
			delete BFME_ANIMATE_WINDOW_MANAGER;
			Glo012F368C = 0;
			TheControlBar->deleteBuildTooltipLayout();
		}
	}
}
