// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// DisconnectMenu BFME input, visibility and chat operations.
// Placement follows ZH GameClient/GUI/DisconnectMenu/DisconnectMenu.cpp.
// BFME APT layout differs from ZH: movie +0x250, chat control +0x258,
// per-player visibility +0x262. Keep existing symbol identities and offsets.

typedef int Int;
typedef bool Bool;

class UnicodeString;

#include "string_base.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : public StringBase<unsigned short>	// G is unsigned short: MSVC 7.1 without /Zc:wchar_t
{
};

class GameWindow;

Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, Int color, Int row, Int column, Bool overwrite);	// ILT 0x0003FE86

extern Int chatNormalColor;


extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer,
	const char *format, ...);

class WindowManager
{
public:
	void unidentified_00015235(int movie, const char *function, int argumentCount,
		const void *argument, int unused1, int unused2, int unused3, int unused4);
};

extern WindowManager *g_theWindowManager;


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowLayout.h
class WindowLayout
{
public:
	virtual void destroy();
	virtual void hide(bool hidden);
	virtual void runUpdate(void *context);
};

extern WindowLayout *_disconnectMenuLayout;


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisconnectMenu.h
class DisconnectMenu
{
public:
    bool _bfme_arePlayerControlsShown(int slot);
    void _bfme_showPlayerControls(int slot, bool show);
    void _bfme_updateScreen();
    void showChat(UnicodeString text);
private:
    char m_bfmeHead[0x250];
    int m_bfmeMovie;
    char m_gap254[4];
    GameWindow *m_textDisplayControl; // +0x258
    char m_gap25c[6];
    bool m_playerControlsShown[8];   // +0x262
};

// @?_bfme_arePlayerControlsShown@DisconnectMenu@@QAE_NH@Z 0x0050E6D0
bool DisconnectMenu::_bfme_arePlayerControlsShown(int slot)
{
	return m_playerControlsShown[slot];
}

void DisconnectMenu::_bfme_showPlayerControls(int slot, bool show)
{
	char slotText[32];
	sprintf(slotText, "%d", slot);

	const char *function = show ? "ShowKickButton" : "HideKickButton";
	g_theWindowManager->unidentified_00015235(
		m_bfmeMovie, function, 1, slotText, 0, 0, 0, 0);
	m_playerControlsShown[slot] = show;
}

// @?_bfme_updateScreen@DisconnectMenu@@QAEXXZ 0x0050E5F0
void DisconnectMenu::_bfme_updateScreen()
{
	if (_disconnectMenuLayout != 0)
		_disconnectMenuLayout->runUpdate(0);
}

void DisconnectMenu::showChat(UnicodeString text)
{
	GadgetListBoxAddEntryText(m_textDisplayControl, text, chatNormalColor, -1, -1, true);
}
