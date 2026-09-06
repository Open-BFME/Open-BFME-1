// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: EstablishConnectionsControlSystem, retail 0x004C8570.
//
// The Zero Hour body unchanged: a switch with one arm, which compiles to the
// leading cmp/jne. Everything it touches is spelled locally.
//
// abortGame is called through vtable slot 3, not directly. That agrees with
// what nat.cpp already recorded about this class -- "BFME EstablishConnections-
// Menu declares its five public methods virtual so setPlayerStatus is slot 5"
// -- and fixes another of the five: slot 3 is abortGame.
//
// Two globals are read: TheEstablishConnectionsMenu at 0x012F363C and the
// button's control id at 0x012F39C0. The second is the file-scope buttonQuitID
// the Zero Hour source initialises in the window's init callback.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	int winGetWindowId( void );					///< ILT 0x000188A4
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/EstablishConnectionsMenu.h
class EstablishConnectionsMenu
{
public:
	// Only the one slot is named. The three before it exist to place it: retail
	// calls [eax+0x0c].
	virtual void slot0( void ) = 0;
	virtual void slot1( void ) = 0;
	virtual void slot2( void ) = 0;
	virtual void abortGame( void ) = 0;			///< slot 3
};

extern EstablishConnectionsMenu *TheEstablishConnectionsMenu;	///< retail 0x012F363C
extern int buttonQuitID;										///< retail 0x012F39C0

class BFMERetailAsciiString;

template <typename T> class StringBase
{
	friend class BFMERetailAsciiString;

	private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

private:
	void *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString() : StringBase<char>() {}
	BFMERetailAsciiString( const char *text ) : StringBase<char>( text ) {}
	BFMERetailAsciiString( const BFMERetailAsciiString &other )
		: StringBase<char>( other ) {}
	~BFMERetailAsciiString() {}
};

class BfmeEstablishWindowLayout
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void hide( int hidden ) = 0;

	void *m_filename;
	GameWindow *m_windowList;

	GameWindow *getFirstWindow( void ) { return m_windowList; }
};

class BfmeEstablishWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual BfmeEstablishWindowLayout *winCreateLayout( BFMERetailAsciiString file );
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36();
	virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42();
	virtual void slot43();
	virtual int winSetFocus( GameWindow *window );
};

class BfmeEstablishGameSpyGame
{
public:
	char m_padding[0x43c];
	unsigned char m_isQuickMatch;
};

extern BfmeEstablishWindowManager *TheWindowManager;
extern BfmeEstablishGameSpyGame *TheGameSpyGame;
extern void ShowUnderlyingGUIElements( bool show, const char *layoutFilename,
	const char *parentName, const char **gadgetsToHide,
	const char **perPlayerGadgetsToHide );
extern void d_004c85b0( void );

static BfmeEstablishWindowLayout *establishConnectionsLayout;
static const char *layoutFilename = "GameSpyGameOptionsMenu.wnd";
static const char *parentName = "GameSpyGameOptionsMenuParent";
static const char *gadgetsToHide[] = {
	"MapWindow", "StaticTextGameName", "StaticTextTeam",
	"StaticTextFaction", "StaticTextColor", "StaticTextPlayers",
	"TextEntryMapDisplay", "ButtonSelectMap", "ButtonStart",
	"StaticTextMapPreview", 0
};
static const char *perPlayerGadgetsToHide[] = {
	"ComboBoxTeam", "ComboBoxColor", "ComboBoxPlayerTemplate",
	"ComboBoxPlayer", "ButtonAccept", "GenericPing", 0
};
static const char *qmlayoutFilename = "WOLQuickMatchMenu.wnd";
static const char *qmparentName = "WOLQuickMatchMenuParent";
static const char *qmgadgetsToHide[] = {
	"StaticTextTitle", "ButtonBack", "ButtonOptions", "ButtonBuddies",
	"ButtonWiden", "ButtonStop", "ButtonStart", 0
};
static const char *qmperPlayerGadgetsToHide[] = { 0 };

// ?ShowEstablishConnectionsWindow@@YAXXZ 0x004C8660
void ShowEstablishConnectionsWindow( void )
{
	if( establishConnectionsLayout == 0 )
	{
		establishConnectionsLayout = TheWindowManager->winCreateLayout(
			"Menus/EstablishConnectionsScreen.wnd" );
		d_004c85b0();
	}
	establishConnectionsLayout->hide( 0 );
	TheWindowManager->winSetFocus( establishConnectionsLayout->getFirstWindow() );
	GameWindow *firstWindow = establishConnectionsLayout->getFirstWindow();
	if( firstWindow != 0 )
		*reinterpret_cast<int *>( reinterpret_cast<char *>( firstWindow ) + 0x1f4 ) = 0;
	if( !TheGameSpyGame->m_isQuickMatch )
	{
		ShowUnderlyingGUIElements( 0, layoutFilename, parentName,
			gadgetsToHide, perPlayerGadgetsToHide );
	}
	else
	{
		ShowUnderlyingGUIElements( 0, qmlayoutFilename, qmparentName,
			qmgadgetsToHide, qmperPlayerGadgetsToHide );
	}
}

enum WindowMsgHandledType
{
	MSG_IGNORED = 0,
	MSG_HANDLED = 1
};

typedef unsigned int WindowMsgData;

// Retail compares the message against 0x4008 directly.
enum { GBM_SELECTED = 0x4008 };

// ?EstablishConnectionsControlSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
WindowMsgHandledType EstablishConnectionsControlSystem(GameWindow *window, unsigned int msg,
																											 WindowMsgData mData1, WindowMsgData mData2) {

	switch (msg) {
		case GBM_SELECTED:
			{
				GameWindow *control = (GameWindow *)mData1;
				int controlID = control->winGetWindowId();

				if (controlID == buttonQuitID) {
					TheEstablishConnectionsMenu->abortGame();
				}
				break;
			}
	} // end switch
	return MSG_HANDLED;
}
