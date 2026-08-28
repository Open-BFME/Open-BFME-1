// cl: /DNDEBUG /MD /EHsc

// The no-argument overload: bail if the window is absent or already hidden,
// otherwise set both flags and hand off to the window manager.
//
// Globals are read as addresses, which is this tree's idiom for them. Both flags
// are set to true and retail keeps the 1 in a register across the two stores,
// which falls out of writing them as two assignments of the same value.
//
// The final call is in tail position and compiles to a jmp; nothing in the
// source asks for that beyond the call being last and returning void.
class WindowManager
{
public:
	void hideQuitMenu(void);
};

struct DiplomacyWindow
{
	unsigned char m_head[0x254];
	bool m_hidden;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
struct InGameUI
{
	unsigned char m_head[0x50];
	bool m_diplomacyHidden;
};

// ?HideDiplomacy@@YAXXZ
void HideDiplomacy(void)
{
	DiplomacyWindow *window = *(DiplomacyWindow **)0x012F49E4;

	if (!window)
		return;

	if (window->m_hidden)
		return;

	window->m_hidden = true;
	(*(InGameUI **)0x012F4B58)->m_diplomacyHidden = true;

	(*(WindowManager **)0x012F19E8)->hideQuitMenu();
}
