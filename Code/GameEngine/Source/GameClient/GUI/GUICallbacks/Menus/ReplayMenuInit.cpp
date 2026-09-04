// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ReplayMenuInit, retail 0x004E1D00, 808 bytes.
// Converted from gen-dump d_004e1d00. ZH twin is in ReplayMenu.cpp; that TU
// already owns PopulateReplayFileListbox unwind labels, so this lives here.
// BFME clears GameWindow+0x1F4 on the menu parent (same field SaveLoadMenuInit
// writes). GadgetParent uses the const-char nameToKey overload; the six
// child IDs go through a by-value AsciiString temp.

typedef int Int;
typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	StringBase( const T *text );
	~StringBase();

	Header *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}
};

class GameWindow
{
public:
	void winHide( Bool hide );

	char m_pad[ 0x1F4 ];
	void *m_fieldAt1F4;
};

class WindowLayout
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void hide( Bool hide );
};

class Shell
{
public:
	void showShellMap( Bool show );
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

class GameWindowManager
{
public:
#define WM_SLOT(n) virtual void _wm_##n();
	WM_SLOT(0)  WM_SLOT(1)  WM_SLOT(2)  WM_SLOT(3)  WM_SLOT(4)
	WM_SLOT(5)  WM_SLOT(6)  WM_SLOT(7)  WM_SLOT(8)  WM_SLOT(9)
	WM_SLOT(10) WM_SLOT(11) WM_SLOT(12) WM_SLOT(13) WM_SLOT(14)
	WM_SLOT(15) WM_SLOT(16) WM_SLOT(17) WM_SLOT(18) WM_SLOT(19)
	WM_SLOT(20) WM_SLOT(21) WM_SLOT(22) WM_SLOT(23) WM_SLOT(24)
	WM_SLOT(25) WM_SLOT(26) WM_SLOT(27) WM_SLOT(28) WM_SLOT(29)
	WM_SLOT(30) WM_SLOT(31) WM_SLOT(32) WM_SLOT(33) WM_SLOT(34)
	WM_SLOT(35) WM_SLOT(36) WM_SLOT(37) WM_SLOT(38) WM_SLOT(39)
	WM_SLOT(40) WM_SLOT(41) WM_SLOT(42) WM_SLOT(43)
#undef WM_SLOT
	virtual void winSetFocus( GameWindow *window );
#define WM_SLOT(n) virtual void _wm2_##n();
	WM_SLOT(45) WM_SLOT(46) WM_SLOT(47) WM_SLOT(48) WM_SLOT(49)
	WM_SLOT(50) WM_SLOT(51) WM_SLOT(52) WM_SLOT(53) WM_SLOT(54)
#undef WM_SLOT
	virtual GameWindow *winGetWindowFromId( GameWindow *window, NameKeyType id );
};

extern Shell *TheShell;
extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;

void GadgetListBoxReset( GameWindow *listbox );
void PopulateReplayFileListbox( GameWindow *listbox );

static NameKeyType parentReplayMenuID = NAMEKEY_INVALID;
static NameKeyType buttonLoadID = NAMEKEY_INVALID;
static NameKeyType buttonBackID = NAMEKEY_INVALID;
static NameKeyType listboxReplayFilesID = NAMEKEY_INVALID;
static NameKeyType buttonDeleteID = NAMEKEY_INVALID;
static NameKeyType buttonCopyID = NAMEKEY_INVALID;

static Bool isShuttingDown = false;

static GameWindow *parentReplayMenu = 0;
static GameWindow *buttonLoad = 0;
static GameWindow *buttonBack = 0;
static GameWindow *listboxReplayFiles = 0;
static GameWindow *buttonDelete = 0;
static GameWindow *buttonCopy = 0;

static Int initialGadgetDelay = 2;
static Bool justEntered = false;

// ?ReplayMenuInit@@YAXPAVWindowLayout@@PAX@Z
void ReplayMenuInit( WindowLayout *layout, void *userData )
{
	TheShell->showShellMap( true );

	parentReplayMenuID = TheNameKeyGenerator->nameToKey( AsciiString( "ReplayMenu.wnd:ParentReplayMenu" ).str() );
	buttonLoadID = TheNameKeyGenerator->nameToKey( AsciiString( "ReplayMenu.wnd:ButtonLoadReplay" ).str() );
	buttonBackID = TheNameKeyGenerator->nameToKey( AsciiString( "ReplayMenu.wnd:ButtonBack" ).str() );
	listboxReplayFilesID = TheNameKeyGenerator->nameToKey( AsciiString( "ReplayMenu.wnd:ListboxReplayFiles" ).str() );
	buttonDeleteID = TheNameKeyGenerator->nameToKey( AsciiString( "ReplayMenu.wnd:ButtonDeleteReplay" ).str() );
	buttonCopyID = TheNameKeyGenerator->nameToKey( AsciiString( "ReplayMenu.wnd:ButtonCopyReplay" ).str() );

	parentReplayMenu = TheWindowManager->winGetWindowFromId( 0, parentReplayMenuID );
	buttonLoad = TheWindowManager->winGetWindowFromId( parentReplayMenu, buttonLoadID );
	buttonBack = TheWindowManager->winGetWindowFromId( parentReplayMenu, buttonBackID );
	listboxReplayFiles = TheWindowManager->winGetWindowFromId( parentReplayMenu, listboxReplayFilesID );
	buttonDelete = TheWindowManager->winGetWindowFromId( parentReplayMenu, buttonDeleteID );
	buttonCopy = TheWindowManager->winGetWindowFromId( parentReplayMenu, buttonCopyID );

	GadgetListBoxReset( listboxReplayFiles );
	PopulateReplayFileListbox( listboxReplayFiles );

	layout->hide( false );

	TheWindowManager->winSetFocus( parentReplayMenu );
	if ( parentReplayMenu )
		parentReplayMenu->m_fieldAt1F4 = 0;

	justEntered = true;
	initialGadgetDelay = 2;
	GameWindow *win = TheWindowManager->winGetWindowFromId( 0,
		TheNameKeyGenerator->nameToKey( "ReplayMenu.wnd:GadgetParent" ) );
	if ( win )
		win->winHide( true );
	isShuttingDown = false;
}
