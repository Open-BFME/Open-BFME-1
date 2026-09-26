// ?update@ControlBar@@UAEXXZ
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// BFME ControlBar::update reconstruction, retail RVA 0x004A2F80.
// Based on the existing bank; completed temporary string lifetime, context
// dispatch, and final update. Code ends at 0x004A3204; its ten-entry switch
// table ends at 0x004A322C before INT3 padding (684 bytes total).
// The retail vtable at VA 0x010FB890 has update at +0x0C through ILT 0x23FB5.
// This TU deliberately models only the BFME fields and callable interfaces
// witnessed by the retail body; the shipped ZH class layout is much larger.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#include "StringInline.h"

class UpdateManager {
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void update() = 0;
};

class AnimateWindowManager : public UpdateManager {
public:
	char m_pad04[12];
	Bool m_needsUpdate;
	Bool m_reverse;
};
class Rva004AD970 { public: void go(); };

class GameWindow {
public:
	Bool winIsHidden();
	Int winHide(Bool hide);
};

// The tooltip layout is polymorphic in BFME; the ZH WindowLayout header
// instead inlines callbacks. Preserve only its witnessed virtual interface.
class Rva004A2F80LayoutView {
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void runUpdate(void *) = 0;
	char m_pad04[16];
	Bool m_hidden;
};

class CommandButton {
public:
	char m_pad[0x144];
	Int m_flashCount;
};

class Drawable { public: char m_pad[0xFC]; void *m_object; };
class Image;
class Player;
class NameKeyGenerator { public: Int nameToKey(const char *text); };
class GameWindowManager {
public:
#define SLOT(n) virtual void slot##n() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
	SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54)
	virtual GameWindow *winGetWindowFromId(GameWindow *, Int) = 0;
#undef SLOT
};
class GameClient {
public:
#define SLOT(n) virtual void slot##n() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25)
	virtual UnsignedInt getFrame() = 0;
#undef SLOT
};
class BfmeMemberRV;
class BfmeThingRV { public: BfmeMemberRV *bfmePickRV(); };
class BfmeHostZA { public: void bfmeTickZA(); };
class BfmeThingZC { public: void bfmeTailZC(); };
class Gen_004a37d0 { public: void m(); };
enum ControlBarContext { CB_CONTEXT_NONE = 0 };

class ControlBar;
// Existing ledger symbols. Both calls take only the receiver in ECX and no
// stack arguments; this one-argument fastcall view has the same machine ABI.
// RVA 004A3163 -> ILT 00023E5C -> dump 004A9620 (multi-select update).
void d_004a9620();
// RVA 004A31C9 -> ILT 00014B28 -> 004AEC80 -> 0000238D -> 004A2500,
// the landed ControlBar::evaluateContextUI body. Keep the witnessed route.
void j_00014b28();
typedef void (__fastcall *Rva004A2F80ReceiverCall)(ControlBar *);

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;
extern GameClient *TheGameClient;
extern BfmeThingRV *Rva004A2F80Players;
extern void *g_obj12F4C38;
void *GadgetButtonGetData(GameWindow *window);

class ControlBar {
public:
	virtual void update();
	const Image *getStarImage();

protected:
	void updateRadarAttackGlow();
	void updateSpecialPowerShortcut();
	void evaluateContextUI();
	void populateSpecialPowerShortcut(Player *player);
public:
	void repopulateBuildTooltipLayout();
protected:
	void updateContextPurchaseScience();
	void updateContextStructureInventory();
	void updateContextUnderConstruction();
private:
	void updateContextOCLTimer();
protected:
	void switchToContext(ControlBarContext context, Drawable *drawable);

	char m_pad04[4];
	UpdateManager *m_videoManager;                    // +08
	AnimateWindowManager *m_animateWindowManager;     // +0C
	AnimateWindowManager *m_animateWindowManagerForGenShortcuts;   // +10
	char m_pad14[0x10];
	Bool m_UIDirty;                      // +24
	char m_pad25[0x0B];
	Rva004AD970 *m_controlBarSchemeManager; // +30
	char m_pad34[0x28];
	Drawable *m_currentSelectedDrawable;              // +5C
	Int m_currContext;                                // +60
	char m_pad64[0x98];
	GameWindow *m_specialPowerShortcutParent;          // +FC
	GameWindow *m_commandWindows[20];                 // +100
	char m_pad150[0x128];
	Rva004A2F80LayoutView *m_buildToolTipLayout;        // +278
	Bool m_showBuildToolTipLayout;                    // +27C
	char m_pad27D[0x73];
	UpdateManager *m_rva2F0;
};

void ControlBar::update()
{
	getStarImage();
	updateRadarAttackGlow();
	if (m_controlBarSchemeManager) m_controlBarSchemeManager->go();
	if (m_videoManager) m_videoManager->update();
	if (m_animateWindowManager) m_animateWindowManager->update();
	if (m_animateWindowManager && !m_animateWindowManager->m_needsUpdate &&
		m_animateWindowManager->m_reverse) {
		Int id;
		{
			AsciiString name("ControlBar.wnd:ControlBarParent");
			id = TheNameKeyGenerator->nameToKey(name.str());
		}
		GameWindow *window = TheWindowManager->winGetWindowFromId(0, id);
		if (window && !window->winIsHidden()) window->winHide(true);
	}
	if (m_animateWindowManagerForGenShortcuts) m_animateWindowManagerForGenShortcuts->update();
	if (m_animateWindowManagerForGenShortcuts && m_specialPowerShortcutParent &&
		!m_animateWindowManagerForGenShortcuts->m_needsUpdate && m_animateWindowManagerForGenShortcuts->m_reverse &&
		!m_specialPowerShortcutParent->winIsHidden())
		m_specialPowerShortcutParent->winHide(true);
	if (m_buildToolTipLayout && !m_buildToolTipLayout->m_hidden) {
		m_buildToolTipLayout->runUpdate(0);
		m_showBuildToolTipLayout = false;
	}
	updateSpecialPowerShortcut();
	for (Int i = 0; i != 20; ++i) {
		GameWindow *button = m_commandWindows[i];
		if (button) {
			CommandButton *command = (CommandButton *)GadgetButtonGetData(button);
			if (command && command->m_flashCount > 0 && TheGameClient->getFrame() % 10 == 0)
				--command->m_flashCount;
		}
	}
	if (g_obj12F4C38 && *((unsigned char *)g_obj12F4C38 + 0x259))
		updateContextPurchaseScience();
	if (m_UIDirty) {
		evaluateContextUI();
		populateSpecialPowerShortcut((Player *)Rva004A2F80Players->bfmePickRV());
		repopulateBuildTooltipLayout();
	}
	if (m_currContext == 7) {
		((Rva004A2F80ReceiverCall)d_004a9620)(this);
		return;
	}
	if (!m_currentSelectedDrawable || !m_currentSelectedDrawable->m_object) {
		if (m_currContext || m_currentSelectedDrawable)
			switchToContext(CB_CONTEXT_NONE, 0);
	}
	switch (m_currContext) {
		case 1: ((BfmeThingZC *)this)->bfmeTailZC(); break;
		case 2: updateContextStructureInventory(); break;
		case 3: ((BfmeHostZA *)this)->bfmeTickZA(); break;
		case 4: ((Rva004A2F80ReceiverCall)j_00014b28)(this); break;
		case 5: ((Gen_004a37d0 *)this)->m(); break;
		case 6: updateContextUnderConstruction(); break;
		case 10: updateContextOCLTimer(); break;
	}
	m_rva2F0->update();
}
