// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: retail 0x00505C00, 92 bytes. Hides the options gadgets (the
// already-landed hideOptionsGadgets body) then winHide's the info-panel
// windows true and two others false. ret 4: one unused stack argument.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	int winHide(bool hide);
};

struct BfmeQuickMatchHideOptionsGadgetsBody
{
	unsigned char _pad264[0x264];
	GameWindow *m_264;
	unsigned char _pad268[0x28C - 0x268];
	GameWindow *m_stats;
	unsigned char _pad290[4];
	GameWindow *m_options;
	unsigned char _pad298[4];
	GameWindow *m_disabledLadder;
	unsigned char _pad2a0[4];
	GameWindow *m_parent;
	unsigned char _pad2a8[4];
	GameWindow *m_2ac;

	void hide(bool doIt);
	void showInfo(bool unused);
};

void BfmeQuickMatchHideOptionsGadgetsBody::showInfo(bool)
{
	hide(true);
	m_264->winHide(false);
	m_stats->winHide(true);
	m_options->winHide(true);
	m_parent->winHide(true);
	m_disabledLadder->winHide(true);
	m_2ac->winHide(false);
}
