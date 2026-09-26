// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// partial score=0.84 date=2026-09-16
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

class Rva006C9270GlobalData
{
public:
	unsigned char m_padding[ 0xa9e ];
	char m_flagA9E;
};

class Rva00367E30Logic
{
public:
	unsigned char m_padding[ 0x10c ];
	int m_mode;
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
extern Rva006C9270GlobalData *TheWritableGlobalData;
extern Rva00367E30Logic *TheBfmeGameLogic;
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
		int mode = TheBfmeGameLogic->m_mode;
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
		int mode = TheBfmeGameLogic->m_mode;
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
