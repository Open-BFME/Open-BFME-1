// cl: /DNDEBUG /MD /Ireference/shims/stringinline
// Retail 0x00516C10 sibling 0x00517550: if lobby state is 1, advance it to 2;
// if the text-entry gadget at +0x3C8 is live, pass GadgetTextEntryGetText to
// the +0x390 preference object. No /EHsc: retail keeps the by-value stash
// without a registered handler.

#include "StringInline.h"

class GameWindow;

UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);

class LanLobbyUserNamePrefs
{
public:
	void setUserName(UnicodeString text);

private:
	char m_bytes[0x18];
};

class BfmeAptScreenLanLobby
{
public:
	void commitUserName(int unused);

private:
	char m_unmodelled[0x390];
	LanLobbyUserNamePrefs m_prefs;
	int m_state;
	char m_gap3ac[0x1C];
	GameWindow *m_textEntry;
};

// ?commitUserName@BfmeAptScreenLanLobby@@QAEXH@Z
void BfmeAptScreenLanLobby::commitUserName(int)
{
	if (m_state == 1)
		m_state = 2;
	if (m_textEntry)
		m_prefs.setUserName(GadgetTextEntryGetText(m_textEntry));
}
