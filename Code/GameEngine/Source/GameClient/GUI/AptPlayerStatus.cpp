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
	void ReturnToGame(const char *argument);
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
