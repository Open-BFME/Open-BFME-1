// cl: /DNDEBUG /MD /EHsc

// Same shape as HideDiplomacy with one extra store, and the extra store is the
// interesting part: retail reloads the menu global before writing 0x25C rather
// than reusing the pointer it already has. That is a second read of the global
// in the source, not a spill -- writing it through the local reuses the register
// and loses the reload.
class WindowManager
{
public:
	void hideQuitMenu(void);
};

struct SaveLoadMenu
{
	unsigned char m_head[0x254];
	bool m_hidden;
	unsigned char m_gap255[0x25C - 0x255];
	int m_25c;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	unsigned char m_head[0x50];
	bool m_menuHidden;
};

class Shell;
class BfmeAptScreenQuitMenu;
extern BfmeAptScreenQuitMenu *g_obj12F4B40;
extern Shell *TheShell;
extern WindowManager *g_rva012F19E8WindowManager;	// retail [0x012F19E8]

// ?HideSaveLoadMenu@@YAXXZ
void HideSaveLoadMenu(void)
{
	SaveLoadMenu *menu = static_cast<SaveLoadMenu *>(reinterpret_cast<void * &>(g_obj12F4B40));

	if (!menu)
		return;

	if (menu->m_hidden)
		return;

	menu->m_hidden = true;
	static_cast<SaveLoadMenu *>(reinterpret_cast<void * &>(g_obj12F4B40))->m_25c = 0;
	((InGameUI *)TheShell)->m_menuHidden = true;

	g_rva012F19E8WindowManager->hideQuitMenu();
}
