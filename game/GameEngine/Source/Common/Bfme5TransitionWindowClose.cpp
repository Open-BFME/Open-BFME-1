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
// BFME member; the call below (ILT 0x27895) lands on the matched 0x005B3270
// Rva005B3270Owner::remove, so the receiver is reinterpreted rather than
// re-owned. ILT 0x10D39 -> 0x00564E10 Rva00564E10 (tools/callees.py 0x588D10 79).
class HotKeyManager;

class Rva005B3270Owner
{
public:
	void remove(GameWindow *window);
};

extern HotKeyManager *TheHotKeyManager;
void Rva00564E10(void);

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
			((Rva005B3270Owner *)TheHotKeyManager)->remove(m_bfmeWindow);
		m_bfmeWindow->winEnable(false);
		m_bfmeWindow->winHide(true);
	}

	Rva00564E10();
	m_bfmeActive = false;
}
