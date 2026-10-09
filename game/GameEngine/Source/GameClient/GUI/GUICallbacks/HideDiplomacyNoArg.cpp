// cl: /DNDEBUG /MD /EHsc

// The no-argument overload: bail if the window is absent or already hidden,
// otherwise set both flags and hand off to the window manager.
//
// Globals are the named externs dir32_addresses.csv records. Both flags
// are set to true and retail keeps the 1 in a register across the two stores,
// which falls out of writing them as two assignments of the same value.
//
// The final call is in tail position and compiles to a jmp; nothing in the
// source asks for that beyond the call being last and returning void.
//
// Retail global at 0x012F19E8.  Canonical mangled spelling is
// ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A, so the pointee must be the
// class named WindowManager: the callee mangles as
// ?hideQuitMenu@WindowManager@@QAEXXZ.  No WindowManager.h exists in the tree
// (each TU declares the class locally), so this local view stays.
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	unsigned char m_head[0x50];
	bool m_diplomacyHidden;
};

class Shell;
extern void *g_obj12F49E4;
extern Shell *TheShell;
extern WindowManager *g_rva012F19E8WindowManager;

// Matched row ?apply@Rva00465B80@@QAEXXZ at 0x00465B80 (__thiscall void(void)).
class Rva00465B80
{
public:
	void apply(void);
};

// ?HideDiplomacy@@YAXXZ
void HideDiplomacy(void)
{
	DiplomacyWindow *window = (DiplomacyWindow *)g_obj12F49E4;

	if (!window)
		return;

	if (window->m_hidden)
		return;

	window->m_hidden = true;
	((InGameUI *)TheShell)->m_diplomacyHidden = true;

	((Rva00465B80 *)g_rva012F19E8WindowManager)->apply();
}
