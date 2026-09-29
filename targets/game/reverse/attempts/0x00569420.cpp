// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// partial score=0.474 date=2026-09-29
//
// BfmeAptScreenQuitMenu::_bfme_saveMenu, retail 0x00569420, 154 bytes, and
// BfmeAptScreenQuitMenu::_bfme_loadMenu, retail 0x005694E0, 154 bytes.
// The Apt selector scanner names both: the QuitMenu constructor pushes the
// selector strings "AptQuitMenu::SaveMenu" and "AptQuitMenu::LoadMenu" and
// loads each body's ILT thunk within about eighty bytes, the same shape as
// the landed BfmeAptScreenMainMenu::_bfme_credits row. Neither body touches
// `this`, so the class carries no modelled members here; AptQuitMenu.cpp
// keeps the full layout for the destructor.
//
// The bodies are structurally identical apart from one literal: 3 for save,
// 2 for load, passed as showAptSaveLoad's first argument. Both read a debug
// toggle byte off TheWritableGlobalData at +0xA9E and XOR it against
// Keyboard::isShift(); when that combined flag is set they pick a
// showAptSaveLoad mode from TheGameLogic's m_gameMode (LAN/Internet -> 4,
// Skirmish -> 2, else -> 1) and return without touching the window layout.
// Otherwise they pull Shell's save/load screen layout and run its normal
// open sequence (runInit, hide(false), bringForward). ShowAptSaveLoad.cpp
// and Shell_popImmediate.cpp already witness showAptSaveLoad and the
// WindowLayout vtable order this reuses.

typedef int Int;
typedef bool Bool;

class Keyboard
{
public:
	bool isShift();
};

extern Keyboard *TheKeyboard;	// ?TheKeyboard@@3PAVKeyboard@@A @ 0x012F4C50

// Address-derived: BFME adds this byte past ZH's GlobalData layout, so no ZH
// member name witnesses offset 0xA9E.
class GlobalData
{
public:
	char m_unmodelled[ 0xa9e ];
	bool m_flagA9E;
};

extern GlobalData *TheWritableGlobalData;	// ?TheWritableGlobalData@@3PAVGlobalData@@A @ 0x012ED5C8

enum GameMode
{
	GAME_SINGLE_PLAYER,
	GAME_LAN,
	GAME_SKIRMISH,
	GAME_REPLAY,
	GAME_SHELL,
	GAME_INTERNET
};

class GameLogic
{
public:
	char m_unmodelled[ 0x10c ];
	int m_gameMode;
};

extern GameLogic * const TheGameLogic;

void showAptSaveLoad( void *arg0, int flags, const volatile char extra );

class WindowLayout
{
public:
	virtual void runInit( void * ) = 0;
	virtual ~WindowLayout();
	virtual void runUpdate( void * ) = 0;
	virtual void runShutdown( void * ) = 0;
	virtual void hide( Bool ) = 0;
	virtual void bringForward() = 0;
};

class Shell
{
public:
	WindowLayout *getSaveLoadMenuLayout();
};

extern Shell *TheShell;

class BfmeAptScreenQuitMenu
{
public:
	void _bfme_saveMenu( const char *name );
	void _bfme_loadMenu( const char *name );
};

void BfmeAptScreenQuitMenu::_bfme_saveMenu( const char *name )
{
	(void)name;
	Bool useShift = ( TheWritableGlobalData->m_flagA9E == 0 );
	if ( TheKeyboard->isShift() )
		useShift = !useShift;

	if ( useShift )
	{
		Int gameMode = TheGameLogic->m_gameMode;
		if ( gameMode != GAME_LAN && gameMode != GAME_INTERNET )
		{
			int flags = ( gameMode == GAME_SKIRMISH ) ? 2 : 1;
			showAptSaveLoad( (void *)3, flags, 1 );
			return;
		}
		showAptSaveLoad( (void *)3, 4, 1 );
		return;
	}

	WindowLayout *layout = TheShell->getSaveLoadMenuLayout();
	layout->runInit( 0 );
	layout->hide( false );
	layout->bringForward();
}

void BfmeAptScreenQuitMenu::_bfme_loadMenu( const char *name )
{
	(void)name;
	Bool useShift = ( TheWritableGlobalData->m_flagA9E == 0 );
	if ( TheKeyboard->isShift() )
		useShift = !useShift;

	if ( useShift )
	{
		Int gameMode = TheGameLogic->m_gameMode;
		if ( gameMode == GAME_LAN || gameMode == GAME_INTERNET )
		{
			showAptSaveLoad( (void *)2, 4, 1 );
			return;
		}
		int flags = ( gameMode == GAME_SKIRMISH ) ? 2 : 1;
		showAptSaveLoad( (void *)2, flags, 1 );
		return;
	}

	WindowLayout *layout = TheShell->getSaveLoadMenuLayout();
	layout->runInit( 0 );
	layout->hide( false );
	layout->bringForward();
}
