// ?d_00569150@@YAXXZ
// partial score=0.85 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc

// Address-derived near-twin of HideSaveLoadMenu() @
// Code/GameEngine/Source/GameClient/GUI/GUICallbacks/HideSaveLoadMenu.cpp
// (retail 0x005696D0). Same shape, except this one stores a caller-supplied
// value into m_25c instead of hard-coding 0.

class WindowManager_569150
{
public:
	void hideQuitMenu(void);
};

struct SaveLoadMenu_569150
{
	unsigned char m_head[0x254];
	bool m_hidden;
	unsigned char m_gap255[0x25C - 0x255];
	int m_25c;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct InGameUI_569150
{
	unsigned char m_head[0x50];
	bool m_menuHidden;
};

void Rva00569150HideSaveLoadMenuWithValue(int value)
{
	SaveLoadMenu_569150 *menu = *(SaveLoadMenu_569150 **)0x012F4B40;

	if (!menu)
		return;

	if (menu->m_hidden)
		return;

	menu->m_hidden = true;
	_ReadWriteBarrier();

	int v = value;
	_ReadWriteBarrier();
	SaveLoadMenu_569150 *menu2 = *(SaveLoadMenu_569150 **)0x012F4B40;
	menu2->m_25c = v;
	(*(InGameUI_569150 **)0x012F4B58)->m_menuHidden = true;

	(*(WindowManager_569150 **)0x012F19E8)->hideQuitMenu();
}
