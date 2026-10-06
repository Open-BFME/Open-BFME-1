// ?_bfme_loadMenu@BfmeAptScreenQuitMenu@@QAEXPBD@Z
// partial score=0.8442 date=2026-10-05
//
// BfmeAptScreenQuitMenu::_bfme_saveMenu at 0x00569420 and
// BfmeAptScreenQuitMenu::_bfme_loadMenu at 0x005694E0, 154 bytes each. The
// constructor at 0x0056A2F0 registers both addresses under the selector
// strings "AptQuitMenu::SaveMenu" and "AptQuitMenu::LoadMenu", and
// BfmeAptScreenQuitMenuConstructor.cpp already declares both method names.
// The two bodies differ in one byte: the first argument to showAptSaveLoad is
// 3 for save and 2 for load.

class Keyboard
{
public:
	bool isShift();
};

class GlobalData
{
public:
	char m_head[ 0xa9e ];
	char m_flagA9E;
};

class GameLogic
{
public:
	char m_unmodelled[ 0x10c ];
	int m_gameMode;
};

class WindowLayout
{
public:
	virtual void runInit( void *userData );
	virtual ~WindowLayout();
	virtual void runUpdate( void *userData );
	virtual void runShutdown( void *userData );
	virtual void hide( int hide );
	virtual void bringForward( void );
};

class Shell
{
public:
	WindowLayout *getSaveLoadMenuLayout( void );
};

extern Keyboard *TheKeyboard;
extern GlobalData *TheWritableGlobalData;
extern GameLogic * const TheGameLogic;
extern Shell *TheShell;

void showAptSaveLoad( void *arg0, int flags, const volatile char extra );

class BfmeAptScreenQuitMenu
{
public:
	void _bfme_saveMenu( const char *name );
	void _bfme_loadMenu( const char *name );
};

void BfmeAptScreenQuitMenu::_bfme_saveMenu( const char *name )
{
	(void)name;
	bool useMenu = ( TheWritableGlobalData->m_flagA9E == 0 );
	if( TheKeyboard->isShift() )
		useMenu = !useMenu;

	if( useMenu )
	{
		int mode = TheGameLogic->m_gameMode;
		int flags;
		if( mode == 1 )
			flags = 4;
		else if( mode == 5 )
			flags = 4;
		else
			flags = mode == 2 ? 2 : 1;
		showAptSaveLoad( (void *)3, flags, 1 );
	}
	else
	{
		WindowLayout *layout = TheShell->getSaveLoadMenuLayout();
		layout->runInit( 0 );
		layout->hide( 0 );
		layout->bringForward();
	}
}

void BfmeAptScreenQuitMenu::_bfme_loadMenu( const char *name )
{
	(void)name;
	bool useMenu = ( TheWritableGlobalData->m_flagA9E == 0 );
	if( TheKeyboard->isShift() )
		useMenu = !useMenu;

	if( useMenu )
	{
		int mode = TheGameLogic->m_gameMode;
		int flags;
		if( mode == 1 )
			flags = 4;
		else if( mode == 5 )
			flags = 4;
		else
			flags = mode == 2 ? 2 : 1;
		showAptSaveLoad( (void *)2, flags, 1 );
	}
	else
	{
		WindowLayout *layout = TheShell->getSaveLoadMenuLayout();
		layout->runInit( 0 );
		layout->hide( 0 );
		layout->bringForward();
	}
}
