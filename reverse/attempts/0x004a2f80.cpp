// ?update@ControlBar@@UAEXXZ
// partial score=0.65 date=2026-09-22
// BFME ControlBar::update reconstruction, retail RVA 0x004A2F80.
// This TU deliberately models only the BFME fields and callable interfaces
// witnessed by the retail body; the shipped ZH class layout is much larger.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class BFMERetailAsciiString {
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString();
	const char *str() const { return m_data ? m_data + 8 : ""; }
private:
	char *m_data;
};

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
	Bool m_finished;
	Bool m_reversed;
};
class ControlBarSchemeManager { public: void update(); };

class GameWindow {
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void runUpdate() = 0;
	Bool winIsHidden();
	Int winHide(Bool hide);
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
class PlayerList { public: Player *getLocalPlayer(); };

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;
extern GameClient *TheGameClient;
extern PlayerList *Rva002EE330ThePlayers;
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
	void repopulateBuildTooltipLayout();
	void updateContextPurchaseScience();
	void updateContextMultiSelect();
	void updateContextCommand();
	void updateContextStructureInventory();
	void switchToContext(Int context, Drawable *drawable);

	char m_pad04[4];
	UpdateManager *m_videoManager;                    // +08
	AnimateWindowManager *m_animateWindowManager;     // +0C
	AnimateWindowManager *m_shortcutAnimateManager;   // +10
	char m_pad14[0x10];
	Bool m_isObserverCommandBar;                      // +24
	char m_pad25[0x0B];
	ControlBarSchemeManager *m_controlBarSchemeManager; // +30
	char m_pad34[0x28];
	Drawable *m_currentSelectedDrawable;              // +5C
	Int m_currContext;                                // +60
	char m_pad64[0x98];
	GameWindow *m_specialPowerShortcutParent;          // +FC
	GameWindow *m_commandWindows[20];                 // +100
	char m_pad150[0x128];
	GameWindow *m_buildToolTipLayout;                 // +278
	Bool m_showBuildToolTipLayout;                    // +27C
};

void ControlBar::update()
{
	getStarImage();
	updateRadarAttackGlow();
	if (m_controlBarSchemeManager) m_controlBarSchemeManager->update();
	if (m_videoManager) m_videoManager->update();
	if (m_animateWindowManager) m_animateWindowManager->update();
	if (m_animateWindowManager && !m_animateWindowManager->m_finished &&
		m_animateWindowManager->m_reversed) {
		BFMERetailAsciiString name("ControlBar.wnd:ControlBarParent");
		GameWindow *window = TheWindowManager->winGetWindowFromId(0,
			TheNameKeyGenerator->nameToKey(name.str()));
		if (window && !window->winIsHidden()) window->winHide(true);
	}
	if (m_shortcutAnimateManager) m_shortcutAnimateManager->update();
	if (m_shortcutAnimateManager && m_specialPowerShortcutParent &&
		m_shortcutAnimateManager->m_finished && m_shortcutAnimateManager->m_reversed &&
		!m_specialPowerShortcutParent->winIsHidden())
		m_specialPowerShortcutParent->winHide(true);
	if (m_buildToolTipLayout && !m_buildToolTipLayout->m_hidden) {
		m_buildToolTipLayout->runUpdate();
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
	if (m_isObserverCommandBar) {
		evaluateContextUI();
		populateSpecialPowerShortcut(Rva002EE330ThePlayers->getLocalPlayer());
		repopulateBuildTooltipLayout();
	}
	if (m_currContext == 7) {
		updateContextMultiSelect();
		return;
	}
	if (!m_currentSelectedDrawable || !m_currentSelectedDrawable->m_object) {
		if (!m_currContext && m_currentSelectedDrawable)
			switchToContext(0, 0);
		return;
	}
	switch (m_currContext) {
		case 1: updateContextCommand(); break;
		case 2: updateContextStructureInventory(); break;
		default: break;
	}
}
