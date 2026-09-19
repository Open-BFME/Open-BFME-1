// cl: /DNDEBUG /MD /EHsc

class WindowManager
{
public:
	void hideQuitMenu(void);
};

struct AptPlayerStatusWindow
{
	unsigned char m_head[0x254];
	bool m_hidden;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
struct Shell
{
	unsigned char m_head[0x50];
	bool m_playerStatusHidden;
};

class AptPlayerStatus
{
public:
	virtual int input(unsigned int message, unsigned int key, unsigned int state);
	__declspec(noinline) void ReturnToGame(const char *argument);
};

// The combined Objectives/PlayerStatus screen constructor binds this same
// member through ILT 0x0003244D under both ReturnToGame registration strings.
// ?ReturnToGame@AptPlayerStatus@@QAEXPBD@Z
void AptPlayerStatus::ReturnToGame(const char *)
{
	AptPlayerStatusWindow *window = *(AptPlayerStatusWindow **)0x012F49E4;

	if (!window)
		return;

	if (window->m_hidden)
		return;

	window->m_hidden = true;
	(*(Shell **)0x012F4B58)->m_playerStatusHidden = true;

	(*(WindowManager **)0x012F19E8)->hideQuitMenu();
}

enum
{
	GWM_CHAR = 0x15,
	KEY_ESC = 1,
	KEY_TAB = 15,
	KEY_ENTER = 28,
	KEY_STATE_UP = 1
};

// The primary vtable slot immediately after the deleting destructor is the
// input slot on the other identified APT screens. The labels preserve the
// shared ignored block that both the message and key tests branch to.
// ?input@AptPlayerStatus@@UAEHIII@Z
int AptPlayerStatus::input(unsigned int message, unsigned int key, unsigned int state)
{
	if (message != GWM_CHAR)
		goto ignored;

	switch ((unsigned char)key)
	{
	case KEY_ESC:
	case KEY_TAB:
	case KEY_ENTER:
		goto accepted;
	default:
		goto ignored;
	}

ignored:
	return 0;

accepted:
	if (state & KEY_STATE_UP)
		ReturnToGame(0);
	return 1;
}
