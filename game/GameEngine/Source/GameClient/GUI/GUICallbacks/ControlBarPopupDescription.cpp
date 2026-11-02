// cl: /DNDEBUG /DWIN32 /MD /EHsc
// ControlBar's build-tooltip popup (Zero Hour GUICallbacks/ControlBarPopupDescription.cpp):
// show (0x004C15D0), delete (0x004C1450), hide (0x004C1940) and the popup
// update callback (0x004C1990). Retail compiled them in one unit that owns the
// animate-window-manager file static at VA 0x012F368C: all eleven retail
// operands of that address are in these four bodies, and only the file static
// reproduces bfmeShowDN's store schedule (an extern leaves 13 bytes).
//
// bfmeShowDN is Zero Hour's showBuildTooltipLayout: three matched callers
// (ControlBarRva004C1B60.cpp, BfmeConv1941.cpp, Rva003BF540_applyOwner.cpp)
// name it ControlBar::bfmeShowDN(BfmeMsgDN*); the previous window became the
// owning handle at ControlBar+0x2F4 holding a cloned tooltip source. The clone
// travels by value into the matched Rva004C1510Handle::operator= (0x004C1510)
// through an STLport auto_ptr_ref-style transfer: the source handle converts to
// a ref that captured its pointer, and the ref's release() clears the source
// before the new handle stores the pointer (retail: pointer in ECX, argument
// slot in EDX).

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

// WINMM timeGetTime through its import slot 0x01359544, read as a plain pointer so
// each call reloads the slot as retail does.
extern "C" unsigned long (__stdcall *__identifier("_imp__timeGetTime@0"))(void);
__declspec(nothrow) inline UnsignedInt bfmeNow(void) { return __identifier("_imp__timeGetTime@0")(); }

class GameWindow;
struct BfmeMsgDN;

// The owning handle a tooltip source's clone returns (its out-of-line
// destructor is the 0x00499F30 body the EH state-0 cleanup calls).
class Rva004C1AE0Handle;
struct Rva004C1AE0HandleRef
{
	Rva004C1AE0Handle &m_r;
	BfmeMsgDN *const m_p;
	Rva004C1AE0HandleRef(Rva004C1AE0Handle &r, BfmeMsgDN *p) : m_r(r), m_p(p) {}
	BfmeMsgDN *release() const;
};
class Rva004C1AE0Handle
{
public:
	~Rva004C1AE0Handle();
	BfmeMsgDN *release(void) { BfmeMsgDN *p = m_ptr; m_ptr = 0; return p; }
	BfmeMsgDN *get(void) const { return m_ptr; }
	operator Rva004C1AE0HandleRef() { return Rva004C1AE0HandleRef(*this, get()); }

	BfmeMsgDN *m_ptr;
};
// ?Rva004C1AE0HandleRef::release present-unmatched
inline BfmeMsgDN *Rva004C1AE0HandleRef::release() const { m_r.m_ptr = 0; return m_p; }

// ControlBar+0x2F4's owning handle; operator= is matched at 0x004C1510.
class Rva004C1510Handle
{
public:
	Rva004C1510Handle(Rva004C1510Handle &other) : m_ptr(other.release()) {}
	Rva004C1510Handle(Rva004C1AE0HandleRef ref) { m_ptr = ref.release(); }
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

// Inline handle members, expanded at every use in this unit (the clone
// handle's out-of-line destructor is the 0x00499F30 body the EH cleanup calls):
// ?Rva004C1AE0Handle::~Rva004C1AE0Handle present-unmatched
inline Rva004C1AE0Handle::~Rva004C1AE0Handle() { delete m_ptr; }
// ?Rva004C1510Handle::~Rva004C1510Handle present-unmatched
inline Rva004C1510Handle::~Rva004C1510Handle() { delete m_ptr; }
// ?Rva004C1510Handle::reset present-unmatched
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

	virtual void update(void);
	Bool isFinished(void) const { return !m_needsUpdate; }
	void registerGameWindow(GameWindow *win, AnimTypes animType, Bool needsToFinish,
		UnsignedInt ms = 0, UnsignedInt delayMs = 0);
	void reverseAnimateWindow(void);
	Bool isReversed(void) const { return m_reverse; }

	char m_pad04[0x10 - 4];
	Bool m_needsUpdate;
	Bool m_reverse;
	char m_pad12[0x34 - 0x12];
};

// Zero Hour's file static theAnimateWindowManager (VA 0x012F368C). Every
// retail reference to it is in this unit's bodies; as a file static the store
// after the new-expression in bfmeShowDN sinks below the EH reset as in retail.
static AnimateWindowManager *theAnimateWindowManager = 0;
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
class AptPalantir;
extern AptPalantir *TheAptPalantir;			// 0x012F4B98

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
	void deleteBuildTooltipLayout(void);
	void hideBuildTooltipLayout(void);
	Bool getShowBuildTooltipLayout(void) const { return m_showBuildToolTipLayout; }
	void doRepopulateBuildTooltipLayout(void);

	char m_bfmeHeadA[0x278];
	BfmeTooltipLayout *m_buildToolTipLayout;		// +0x278
	Bool m_showBuildToolTipLayout;				// +0x27C
	char m_bfmeHeadB[0x2F4 - 0x280];
	Rva004C1510Handle m_bfmeHandle2F4;			// +0x2F4
};

static inline AnimateWindowManager *animateManager(void)
{
	return theAnimateWindowManager;
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
			if (TheAptPalantir)
				reinterpret_cast<Glo012F4B98Type *>(TheAptPalantir)->m_bfmeSub.release();
		}
		return;
	}

	if (!passedWaitTime)
	{
		m_bfmeHandle2F4 = Rva004C1510Handle(source->bfmeCopy04());
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
		theAnimateWindowManager = new AnimateWindowManager;
		animateManager()->reset();
		animateManager()->registerGameWindow(m_buildToolTipLayout->getFirstWindow(), WIN_ANIMATION_SLIDE_RIGHT_FAST, true, 200);
	}
}

void ControlBar::deleteBuildTooltipLayout(void)
{
 m_showBuildToolTipLayout = false;
 m_buildToolTipLayout->hide(true);
 m_bfmeHandle2F4.reset();
 if (TheAptPalantir) reinterpret_cast<Glo012F4B98Type *>(TheAptPalantir)->m_bfmeSub.release();
 delete animateManager();
 theAnimateWindowManager = 0;
}
void ControlBar::hideBuildTooltipLayout(void)
{
 if (animateManager() && animateManager()->isReversed()) return;
 if (g_bfmeReadyPT && animateManager() && TheWritableGlobalData->m_animateWindows)
  animateManager()->reverseAnimateWindow();
 else deleteBuildTooltipLayout();
}
class WindowLayout;
extern ControlBar *TheControlBar;
void ControlBarPopupDescriptionUpdateFunc(WindowLayout *, void *)
{
 if (TheScriptEngine->isGameEnding()) TheControlBar->hideBuildTooltipLayout();
 if (animateManager() && !TheControlBar->getShowBuildTooltipLayout() && !animateManager()->isReversed())
  animateManager()->reverseAnimateWindow();
 else if (!TheControlBar->getShowBuildTooltipLayout() && (!TheWritableGlobalData->m_animateWindows || !g_bfmeReadyPT))
  TheControlBar->deleteBuildTooltipLayout();
 if (g_bfmeReadyPT && animateManager() && TheWritableGlobalData->m_animateWindows) {
  Bool wasFinished = animateManager()->isFinished();
  animateManager()->update();
  if (animateManager() && animateManager()->isFinished() && !wasFinished && animateManager()->isReversed()) {
   delete animateManager(); theAnimateWindowManager = 0;
   TheControlBar->deleteBuildTooltipLayout();
  }
 }
}
