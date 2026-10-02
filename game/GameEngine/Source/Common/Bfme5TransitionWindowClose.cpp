// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	int winEnable(bool enable);
	int winHide(bool close);
};

// The data slot this body reads at 0x012F4C7C is the GameClient global
// TheHotKeyManager, not a transition manager of its own: the same slot is read
// by ?translateGameMessage@HotKeyTranslator (0x005B3F50) and by
// ?checkForChangedTextData@W3DDisplayString (0x006F4F50), whose retail bytes
// call executeHotKey/searchHotKey on it, and the upstream
// GameClient/HotKey.h header declares `extern HotKeyManager *TheHotKeyManager;`.
// Only the forward declaration is spelled here: the header's class carries no
// BFME member, and the call below still names the pinned callee
// ?bfmeDetach@BfmeTransitionMD@@QAEXPAVGameWindow@@@Z (0x00027895), so the
// receiver is reinterpreted rather than re-owned.
class HotKeyManager;

class BfmeTransitionMD
{
public:
	void bfmeDetach(GameWindow *window);
};

extern HotKeyManager *TheHotKeyManager;
void bfmeTransitionFinished(void);

class Gen_00588D10
{
public:
	void bfmeFinish(void);

private:
	char m_bfme00[0x1A0];
	bool m_bfmeActive;
	char m_bfme1A1[3];
	GameWindow *m_bfmeWindow;
};

// ?bfmeFinish@Gen_00588D10@@QAEXXZ
void Gen_00588D10::bfmeFinish(void)
{
	if (!m_bfmeActive)
		return;

	if (m_bfmeWindow)
	{
		if (TheHotKeyManager)
			((BfmeTransitionMD *)TheHotKeyManager)->bfmeDetach(m_bfmeWindow);
		m_bfmeWindow->winEnable(false);
		m_bfmeWindow->winHide(true);
	}

	bfmeTransitionFinished();
	m_bfmeActive = false;
}
