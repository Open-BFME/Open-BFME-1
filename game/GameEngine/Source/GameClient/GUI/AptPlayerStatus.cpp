// cl: /DNDEBUG /MD /EHsc

// Retail global at 0x012F19E8.  Canonical mangled spelling is
// ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A, so the pointee must be
// the class named WindowManager: the hideQuitMenu callee mangles as
// ?hideQuitMenu@WindowManager@@QAEXXZ.  No WindowManager.h exists in the tree
// (each TU declares the class locally), so this local view stays.
class WindowManager
{
public:
	void hideQuitMenu(void);
};

extern WindowManager *g_rva012F19E8WindowManager;

struct AptPlayerStatusWindow
{
	unsigned char m_head[0x254];
	bool m_hidden;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	unsigned char m_head[0x50];
	bool m_playerStatusHidden;
};

extern void *g_obj12F49E4;
extern Shell *TheShell;

class AptPlayerStatus
{
public:
	void ReturnToGame(const char *argument);
};

class Rva00465B80
{
public:
	void apply(void);
};

// The combined Objectives/PlayerStatus screen constructor binds this same
// member through ILT 0x0003244D under both ReturnToGame registration strings.
// ?ReturnToGame@AptPlayerStatus@@QAEXPBD@Z
void AptPlayerStatus::ReturnToGame(const char *)
{
	AptPlayerStatusWindow *window = (AptPlayerStatusWindow *)g_obj12F49E4;

	if (!window)
		return;

	if (window->m_hidden)
		return;

	window->m_hidden = true;
	TheShell->m_playerStatusHidden = true;

	((Rva00465B80 *)g_rva012F19E8WindowManager)->apply();
}
