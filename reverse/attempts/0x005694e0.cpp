// ?_bfme_loadMenu@BfmeAptScreenQuitMenu@@QAEXPBD@Z
// partial score=0.79 date=2026-09-16
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BfmeAptScreenQuitMenu::_bfme_loadMenu and _bfme_saveMenu, retail 0x005694E0
// and 0x00569420, 154 bytes each. The constructor in
// BfmeAptScreenQuitMenuConstructor.cpp pushes the selector strings
// "AptQuitMenu::LoadMenu" and "AptQuitMenu::SaveMenu" and loads each body's
// ILT thunk right after, which is what names the two bodies. They differ in
// one byte: the first argument to showAptSaveLoad is 2 for load and 3 for save.
//
// Each callback picks the APT save/load screen when the shift key agrees with
// the global flag at GlobalData+0xA9E, and the old window layout otherwise.

class Keyboard
{
public:
	bool isShift();
};

struct Rva006C9270GlobalData
{
	unsigned char m_head[ 0xA9E ];
	bool m_flagA9E;
};

class GameLogic
{
public:
	char m_unmodelled[ 0x10C ];
	int m_gameMode;
};

class GameWindow;
class WindowLayout;

class WindowLayout
{
public:
	virtual void runInit( void *userData );
	virtual ~WindowLayout();
	virtual void runUpdate( void *userData );
	virtual void runShutdown( void *userData );
	virtual void hide( int hide );
	virtual void bringForward( void );
	virtual void addWindow( GameWindow *window );
	virtual void removeWindow( GameWindow *window );
	virtual void destroyWindows( void );
};

class Shell
{
public:
	WindowLayout *getSaveLoadMenuLayout( void );
};

extern Keyboard *TheKeyboard;
extern Rva006C9270GlobalData *TheWritableGlobalData;
extern GameLogic *TheBfmeGameLogic;
extern Shell *TheShell;

// Code/GameEngine/Source/GameClient/GUI/ShowAptSaveLoad.cpp, retail 0x0056BFA0.
void showAptSaveLoad( void *arg0, int flags, const volatile char extra );

class BfmeAptScreenQuitMenu
{
public:
	void _bfme_loadMenu( const char *name );
	void _bfme_saveMenu( const char *name );
};

void BfmeAptScreenQuitMenu::_bfme_loadMenu( const char *name )
{
	(void)name;
	bool useApt = ( TheWritableGlobalData->m_flagA9E == 0 );
	if ( TheKeyboard->isShift() )
		useApt = ( useApt == 0 );
	if ( useApt )
	{
		int mode = TheBfmeGameLogic->m_gameMode;
		int flags;
		if ( mode == 1 || mode == 5 )
			flags = 4;
		else
			flags = ( mode == 2 ) ? 2 : 1;
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

void BfmeAptScreenQuitMenu::_bfme_saveMenu( const char *name )
{
	(void)name;
	bool useApt = ( TheWritableGlobalData->m_flagA9E == 0 );
	if ( TheKeyboard->isShift() )
		useApt = ( useApt == 0 );
	if ( useApt )
	{
		int mode = TheBfmeGameLogic->m_gameMode;
		int flags;
		if ( mode == 1 || mode == 5 )
			flags = 4;
		else
			flags = ( mode == 2 ) ? 2 : 1;
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
