// ?bfmeShowDN@ControlBar@@QAEXPAUBfmeMsgDN@@@Z
// partial score=0.976 date=2026-09-28
// ?bfmeShowDN@ControlBar@@QAEXPAUBfmeMsgDN@@@Z
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Retail 0x004C15D0, 678 bytes (ret 4). Three matched callers (ControlBarRva004C1B60.cpp,
// BfmeConv1941.cpp, Rva003BF540_applyOwner.cpp) name it ControlBar::bfmeShowDN(BfmeMsgDN*).
// Shape is Zero Hour's ControlBar::showBuildTooltipLayout (ControlBarPopupDescription.cpp):
// prevWindow became the owning handle at ControlBar+0x2F4 holding a cloned tooltip source.
//
// STATUS (opus-5.5, 2026-09-28): 678/678 bytes, 16 differing with this extern global.
//  * Declaring the animate-manager pointer as a TU-private `static` (ZH's file static
//    theAnimateWindowManager) drops it to 3 bytes: retail compiled this body in the TU
//    that OWNED that static (store to it sinks below the new-expression's EH reset).
//    Do NOT land a private static here: hide/deleteBuildTooltipLayout (matched, other
//    TUs) read the same 0x012F368C through extern Glo012F368C, and build.py skips local
//    statics in the DIR32 check, so a split global would pass unnoticed. The real lever is
//    one ControlBarPopupDescription.cpp TU holding the static and its tooltip siblings.
//  * Remaining 3 bytes (with the static): +0x200 retail puts the stolen clone pointer in
//    ECX and the by-value operator= argument address in EDX; ours swaps them. ~20 spellings
//    of the converting constructor (member/base/template/derived/ref-object/conversion
//    operator) all leave the swap.
//  * timeGetTime: retail never hoists the IAT load and has no EH state around the static
//    initializer; a __declspec(nothrow) inline wrapper over the IAT pointer does both.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

extern int (*g_bfmeNowVNH)(void);
__declspec(nothrow) inline UnsignedInt bfmeNow(void) { return g_bfmeNowVNH(); }

class GameWindow;
struct BfmeMsgDN;

// The owning handle a tooltip source's clone returns (its out-of-line
// destructor is the 0x00499F30 body the EH state-0 cleanup calls).
class Rva004C1AE0Handle
{
public:
	~Rva004C1AE0Handle();
	BfmeMsgDN *release(void) { BfmeMsgDN *p = m_ptr; m_ptr = 0; return p; }

	BfmeMsgDN *m_ptr;
};

// ControlBar+0x2F4's owning handle; operator= is matched at 0x004C1510.
class Rva004C1510Handle
{
public:
	Rva004C1510Handle(Rva004C1510Handle &other) : m_ptr(other.release()) {}
	Rva004C1510Handle(Rva004C1AE0Handle &other) : m_ptr(other.release()) {}
	~Rva004C1510Handle();
	BfmeMsgDN *get(void) const { return m_ptr; }
	void reset(void);
	BfmeMsgDN *release(void) { BfmeMsgDN *p = m_ptr; m_ptr = 0; return p; }
	Rva004C1510Handle &operator=(Rva004C1510Handle other);

private:
	BfmeMsgDN *m_ptr;
};

// The tooltip source (base of the 0x004C1B60 adapter, vtable 0x010EDAA0).
struct BfmeMsgDN
{
	virtual ~BfmeMsgDN();
	virtual Rva004C1AE0Handle bfmeCopy04(void) const;	// slot 1 (0x004C1AE0 in the 4C1B60 adapter)
	virtual Int getTooltipDelay(void) const;		// slot 2
};

inline Rva004C1AE0Handle::~Rva004C1AE0Handle() { delete m_ptr; }
inline Rva004C1510Handle::~Rva004C1510Handle() { delete m_ptr; }
inline void Rva004C1510Handle::reset(void) { delete m_ptr; m_ptr = 0; }

class BfmeThingGX;
int bfmeSameGX(BfmeThingGX *left, BfmeThingGX *right);

class InGameUI
{
public:
	virtual void _bfme_slot0(void);
	virtual void _bfme_slot1(void);
	virtual void _bfme_slot2(void);
	virtual void _bfme_slot3(void);
	virtual void _bfme_slot4(void);
	virtual void _bfme_slot5(void);
	virtual void _bfme_slot6(void);
	virtual void _bfme_slot7(void);
	virtual void _bfme_slot8(void);
	virtual void _bfme_slot9(void);
	virtual void _bfme_slot10(void);
	virtual void _bfme_slot11(void);
	virtual void _bfme_slot12(void);
	virtual void _bfme_slot13(void);
	virtual void _bfme_slot14(void);
	virtual void _bfme_slot15(void);
	virtual void _bfme_slot16(void);
	virtual void _bfme_slot17(void);
	virtual void _bfme_slot18(void);
	virtual void _bfme_slot19(void);
	virtual void _bfme_slot20(void);
	virtual void _bfme_slot21(void);
	virtual void _bfme_slot22(void);
	virtual void _bfme_slot23(void);
	virtual void _bfme_slot24(void);
	virtual void _bfme_slot25(void);
	virtual void _bfme_slot26(void);
	virtual void _bfme_slot27(void);
	virtual void _bfme_slot28(void);
	virtual void _bfme_slot29(void);
	virtual void _bfme_slot30(void);
	virtual void _bfme_slot31(void);
	virtual void _bfme_slot32(void);
	virtual void _bfme_slot33(void);
	virtual void _bfme_slot34(void);
	virtual void _bfme_slot35(void);
	virtual void _bfme_slot36(void);
	virtual void _bfme_slot37(void);
	virtual void _bfme_slot38(void);
	virtual void _bfme_slot39(void);
	virtual void _bfme_slot40(void);
	virtual void _bfme_slot41(void);
	virtual void _bfme_slot42(void);
	virtual void _bfme_slot43(void);
	virtual void _bfme_slot44(void);
	virtual void _bfme_slot45(void);
	virtual void _bfme_slot46(void);
	virtual void _bfme_slot47(void);
	virtual void _bfme_slot48(void);
	virtual void _bfme_slot49(void);
	virtual void _bfme_slot50(void);
	virtual void _bfme_slot51(void);
	virtual void _bfme_slot52(void);
	virtual void _bfme_slot53(void);
	virtual void _bfme_slot54(void);
	virtual void _bfme_slot55(void);
	virtual void _bfme_slot56(void);
	virtual void _bfme_slot57(void);
	virtual void _bfme_slot58(void);
	virtual void _bfme_slot59(void);
	virtual void _bfme_slot60(void);
	virtual void _bfme_slot61(void);
	virtual void _bfme_slot62(void);
	virtual void _bfme_slot63(void);
	virtual void _bfme_slot64(void);
	virtual void _bfme_slot65(void);
	virtual void _bfme_slot66(void);
	virtual void _bfme_slot67(void);
	virtual void _bfme_slot68(void);
	virtual void _bfme_slot69(void);
	virtual void _bfme_slot70(void);
	virtual void _bfme_slot71(void);
	virtual void _bfme_slot72(void);
	virtual void _bfme_slot73(void);
	virtual void _bfme_slot74(void);
	virtual void _bfme_slot75(void);
	virtual void _bfme_slot76(void);
	virtual void _bfme_slot77(void);
	virtual void _bfme_slot78(void);
	virtual void _bfme_slot79(void);
	virtual void _bfme_slot80(void);
	virtual void _bfme_slot81(void);
	virtual void _bfme_slot82(void);
	virtual void _bfme_slot83(void);
	virtual void _bfme_slot84(void);
	virtual Bool isQuitMenuVisible(void);		// slot 85, vtable+0x154
	virtual void _bfme_slot86(void);
	virtual void _bfme_slot87(void);
	virtual void _bfme_slot88(void);
	virtual void _bfme_slot89(void);
	virtual void _bfme_slot90(void);
	virtual void _bfme_slot91(void);
	virtual void _bfme_slot92(void);
	virtual void _bfme_slot93(void);
	virtual void _bfme_slot94(void);
	virtual void _bfme_slot95(void);
	virtual void _bfme_slot96(void);
	virtual void _bfme_slot97(void);
	virtual void _bfme_slot98(void);
	virtual void _bfme_slot99(void);
	virtual void _bfme_slot100(void);
	virtual Bool areTooltipsDisabled(void);		// slot 101, vtable+0x194
};
extern InGameUI *TheInGameUI;

class ScriptEngine
{
public:
	Bool isGameEnding(void) const { return m_endGameTimer >= 0; }

	char m_bfmeHead[0x17080];
	Int m_endGameTimer;
};
extern ScriptEngine *TheScriptEngine;

class GlobalData
{
public:
	char m_bfmeHead[0xBC4];
	Bool m_animateWindows;
};
extern GlobalData *TheWritableGlobalData;

class DisconnectMenu;
extern DisconnectMenu *TheDisconnectMenu;

enum AnimTypes
{
	WIN_ANIMATION_NONE = 0,
	WIN_ANIMATION_SLIDE_RIGHT,
	WIN_ANIMATION_SLIDE_RIGHT_FAST
};

class AnimateWindowManager
{
public:
	AnimateWindowManager(void);
	virtual ~AnimateWindowManager(void);
	virtual void init(void);
	virtual void loadIniFilesFromLegend(void);
	virtual void postProcessLoad(void);
	virtual void reset(void);				// slot 4, vtable+0x10

	void registerGameWindow(GameWindow *win, AnimTypes animType, Bool needsToFinish,
		UnsignedInt ms = 0, UnsignedInt delayMs = 0);
	void reverseAnimateWindow(void);
	Bool isReversed(void) const { return m_reverse; }

	char m_pad04[0x11 - 4];
	Bool m_reverse;
	char m_pad12[0x34 - 0x12];
};

class Glo012F368CType;
Glo012F368CType *Glo012F368C = 0;				// theAnimateWindowManager
extern Bool g_bfmeReadyPT;					// useAnimation

class Rva005929E0
{
public:
	void release(void);
};

class Glo012F4B98Type
{
public:
	char m_bfmeHead[0x488];
	Rva005929E0 m_bfmeSub;
};
extern Glo012F4B98Type *Glo012F4B98;

class BfmeTooltipLayout
{
public:
	virtual void _bfme_slot0(void);
	virtual void _bfme_slot1(void);
	virtual void _bfme_slot2(void);
	virtual void _bfme_slot3(void);
	virtual void hide(Bool hide);				// slot 4, vtable+0x10

	GameWindow *getFirstWindow(void) const { return m_windowList; }
	Bool isHidden(void) const { return m_hidden; }

	char m_pad04[4];
	GameWindow *m_windowList;
	char m_pad0c[0x14 - 0xc];
	Bool m_hidden;
};

class ControlBar
{
public:
	void bfmeShowDN(BfmeMsgDN *source);
	void doRepopulateBuildTooltipLayout(void);

	char m_bfmeHeadA[0x278];
	BfmeTooltipLayout *m_buildToolTipLayout;		// +0x278
	Bool m_showBuildToolTipLayout;				// +0x27C
	char m_bfmeHeadB[0x2F4 - 0x280];
	Rva004C1510Handle m_bfmeHandle2F4;			// +0x2F4
};

static inline AnimateWindowManager *animateManager(void)
{
	return (AnimateWindowManager *)Glo012F368C;
}

void ControlBar::bfmeShowDN(BfmeMsgDN *source)
{
	if (TheInGameUI->areTooltipsDisabled() || TheScriptEngine->isGameEnding())
	{
		return;
	}

	Bool passedWaitTime = false;
	static Bool isInitialized = false;
	static UnsignedInt beginWaitTime = bfmeNow();
	if (m_bfmeHandle2F4.get() && ((Bool (__cdecl *)(BfmeMsgDN *, BfmeMsgDN *))bfmeSameGX)(source, m_bfmeHandle2F4.get()))
	{
		m_showBuildToolTipLayout = true;
		UnsignedInt delay = source->getTooltipDelay();
		if (!isInitialized && beginWaitTime + delay < bfmeNow())
		{
			passedWaitTime = true;
		}

		if (!passedWaitTime)
			return;
	}
	else if (!m_buildToolTipLayout->isHidden())
	{
		if (g_bfmeReadyPT && TheWritableGlobalData->m_animateWindows && !animateManager()->isReversed())
			animateManager()->reverseAnimateWindow();
		else if (g_bfmeReadyPT && TheWritableGlobalData->m_animateWindows && animateManager()->isReversed())
		{
			return;
		}
		else
		{
			m_buildToolTipLayout->hide(true);
			m_bfmeHandle2F4.reset();
			if (Glo012F4B98)
				Glo012F4B98->m_bfmeSub.release();
		}
		return;
	}

	if (!passedWaitTime)
	{
		m_bfmeHandle2F4 = source->bfmeCopy04();
		beginWaitTime = bfmeNow();
		isInitialized = false;
		return;
	}
	isInitialized = true;

	if (TheInGameUI->isQuitMenuVisible())
		return;

	if (TheDisconnectMenu)
		return;

	m_showBuildToolTipLayout = true;
	doRepopulateBuildTooltipLayout();
	m_buildToolTipLayout->hide(false);

	if (g_bfmeReadyPT && TheWritableGlobalData->m_animateWindows)
	{
		Glo012F368C = (Glo012F368CType *)new AnimateWindowManager;
		animateManager()->reset();
		animateManager()->registerGameWindow(m_buildToolTipLayout->getFirstWindow(), WIN_ANIMATION_SLIDE_RIGHT_FAST, true, 200);
	}
}
