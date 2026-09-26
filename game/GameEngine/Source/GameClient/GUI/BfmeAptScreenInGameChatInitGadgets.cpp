// cl: /DNDEBUG /MD /EHsc
//
// BfmeAptScreenInGameChat::_bfme_initGadgets, retail 0x00515E60, 510 bytes.
// The in-game chat constructor at 0x005160E0 pushes the selector string
// "AptInGameChat::InitGadgets" at 0x005161C3 and loads this body's ILT thunk a
// few bytes later, which is what names it.
//
// The callback runs once per gadget the APT file declares. It matches the
// gadget name against five literals and wires each window into the screen:
// the chat entry at this+0x260, the friends list at this+0x264, the chat box
// at this+0x268, and the two friend text entries into the slots at this+0x270
// and this+0x280 that BfmeAptScreenInGameChatFriendPanel.cpp already reads.

typedef bool Bool;
typedef int Int;

extern "C" int strcmp( const char *left, const char *right );
#pragma intrinsic( strcmp )

class GameWindow;
class BfmeKeyLC;
class BfmeOwnerEJ;

template <class T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}

	static UnicodeString TheEmptyString;
};

// The gadget's own data block. Retail writes the entry's character limit as a
// sixteen-bit field at +0x10 and a list box flag as a byte at +0x12.
struct Rva00515E60GadgetData
{
	unsigned char m_unmodelled[ 0x10 ];
	short m_maxTextLen;
	unsigned char m_byte12;
};

void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );
void GadgetListBoxSetListLength( GameWindow *listbox, Int length );
void GadgetListBoxAddMultiSelect( GameWindow *listbox );
void GadgetListBoxSetColumnWidths( GameWindow *listbox, Int count, Int *widths );
void bfmeGo924F( BfmeKeyLC *window, unsigned short value );
void bfmeGo924D( BfmeKeyLC *window, unsigned int value );
void Rva004EDED0BuddyMessageNotification( void );

class GameWindow
{
public:
	void *winGetUserData( void );
	void winSetUserData( void *data );
	unsigned int _bfme_winSetStatus( unsigned int status );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
#define WINDOW_MANAGER_SLOT(n) virtual void slot##n() = 0
	WINDOW_MANAGER_SLOT(00); WINDOW_MANAGER_SLOT(01); WINDOW_MANAGER_SLOT(02);
	WINDOW_MANAGER_SLOT(03); WINDOW_MANAGER_SLOT(04); WINDOW_MANAGER_SLOT(05);
	WINDOW_MANAGER_SLOT(06); WINDOW_MANAGER_SLOT(07); WINDOW_MANAGER_SLOT(08);
	WINDOW_MANAGER_SLOT(09); WINDOW_MANAGER_SLOT(10); WINDOW_MANAGER_SLOT(11);
	WINDOW_MANAGER_SLOT(12); WINDOW_MANAGER_SLOT(13); WINDOW_MANAGER_SLOT(14);
	WINDOW_MANAGER_SLOT(15); WINDOW_MANAGER_SLOT(16); WINDOW_MANAGER_SLOT(17);
	WINDOW_MANAGER_SLOT(18); WINDOW_MANAGER_SLOT(19); WINDOW_MANAGER_SLOT(20);
	WINDOW_MANAGER_SLOT(21); WINDOW_MANAGER_SLOT(22); WINDOW_MANAGER_SLOT(23);
	WINDOW_MANAGER_SLOT(24); WINDOW_MANAGER_SLOT(25); WINDOW_MANAGER_SLOT(26);
	WINDOW_MANAGER_SLOT(27); WINDOW_MANAGER_SLOT(28); WINDOW_MANAGER_SLOT(29);
	WINDOW_MANAGER_SLOT(30); WINDOW_MANAGER_SLOT(31); WINDOW_MANAGER_SLOT(32);
	WINDOW_MANAGER_SLOT(33); WINDOW_MANAGER_SLOT(34); WINDOW_MANAGER_SLOT(35);
	WINDOW_MANAGER_SLOT(36); WINDOW_MANAGER_SLOT(37); WINDOW_MANAGER_SLOT(38);
	WINDOW_MANAGER_SLOT(39); WINDOW_MANAGER_SLOT(40); WINDOW_MANAGER_SLOT(41);
	WINDOW_MANAGER_SLOT(42); WINDOW_MANAGER_SLOT(43);
#undef WINDOW_MANAGER_SLOT
	virtual void slot44( GameWindow *window ) = 0;
};

class GameSpyInfo
{
public:
#define GAMESPY_SLOT(n) virtual void slot##n() = 0
	GAMESPY_SLOT(00); GAMESPY_SLOT(01); GAMESPY_SLOT(02); GAMESPY_SLOT(03);
	GAMESPY_SLOT(04); GAMESPY_SLOT(05); GAMESPY_SLOT(06); GAMESPY_SLOT(07);
	GAMESPY_SLOT(08); GAMESPY_SLOT(09); GAMESPY_SLOT(10); GAMESPY_SLOT(11);
	GAMESPY_SLOT(12); GAMESPY_SLOT(13); GAMESPY_SLOT(14); GAMESPY_SLOT(15);
	GAMESPY_SLOT(16); GAMESPY_SLOT(17); GAMESPY_SLOT(18); GAMESPY_SLOT(19);
	GAMESPY_SLOT(20); GAMESPY_SLOT(21); GAMESPY_SLOT(22); GAMESPY_SLOT(23);
	GAMESPY_SLOT(24); GAMESPY_SLOT(25); GAMESPY_SLOT(26); GAMESPY_SLOT(27);
	GAMESPY_SLOT(28); GAMESPY_SLOT(29); GAMESPY_SLOT(30); GAMESPY_SLOT(31);
	GAMESPY_SLOT(32); GAMESPY_SLOT(33); GAMESPY_SLOT(34); GAMESPY_SLOT(35);
	GAMESPY_SLOT(36); GAMESPY_SLOT(37); GAMESPY_SLOT(38); GAMESPY_SLOT(39);
	GAMESPY_SLOT(40); GAMESPY_SLOT(41); GAMESPY_SLOT(42); GAMESPY_SLOT(43);
	GAMESPY_SLOT(44); GAMESPY_SLOT(45); GAMESPY_SLOT(46); GAMESPY_SLOT(47);
	GAMESPY_SLOT(48); GAMESPY_SLOT(49); GAMESPY_SLOT(50); GAMESPY_SLOT(51);
	GAMESPY_SLOT(52); GAMESPY_SLOT(53); GAMESPY_SLOT(54); GAMESPY_SLOT(55);
	GAMESPY_SLOT(56);
#undef GAMESPY_SLOT
	virtual void slot57( GameWindow *window ) = 0;
};

// The eight-byte-mark window that BfmeAptScreenInGameChatFriendPanel.cpp reads
// out of each of these lives at +0x08 of the slot.
class Gen_00479A60
{
public:
	void bfmeAttach( BfmeOwnerEJ *owner );

private:
	unsigned char m_unmodelled[ 0x10 ];
};

extern GameWindowManager *TheWindowManager;
extern GameSpyInfo *TheGameSpyInfo;
extern UnicodeString g_unicode12F498C;

// Layout witnessed by BfmeAptScreenInGameChatConstructor.cpp at 0x005160E0.
class BfmeAptScreenInGameChat
{
public:
	void _bfme_initGadgets( const char *name, void *userData, GameWindow *window );
	void Rva00515810( void );

private:
	unsigned char m_unmodelled000[ 0x260 ];
	GameWindow *m_chatEntry;
	GameWindow *m_friendsList;
	GameWindow *m_chatBox;
	unsigned char m_unmodelled26C[ 4 ];
	Gen_00479A60 m_addFriendSlot;
	Gen_00479A60 m_removeFriendSlot;
};

void BfmeAptScreenInGameChat::_bfme_initGadgets( const char *name, void *userData,
	GameWindow *window )
{
	(void)userData;
	if ( window == 0 )
		return;

	if ( strcmp( name, "InGameChatEntry" ) == 0 )
	{
		GadgetTextEntrySetText( window, g_unicode12F498C );
		Rva00515E60GadgetData *data =
			(Rva00515E60GadgetData *)window->winGetUserData();
		if ( data )
			data->m_maxTextLen = 110;
		TheWindowManager->slot44( window );
		m_chatEntry = window;
	}
	else if ( strcmp( name, "FriendsList" ) == 0 )
	{
		GadgetListBoxSetListLength( window, 1000 );
		GadgetListBoxAddMultiSelect( window );
		Int widths[ 7 ] = { 10, 10, 0x50, 0, 0, 0, 0 };
		GadgetListBoxSetColumnWidths( window, 3, widths );
		m_friendsList = window;
		Rva00515810();
		Rva00515E60GadgetData *data =
			(Rva00515E60GadgetData *)window->winGetUserData();
		data->m_byte12 = 1;
		window->winSetUserData( data );
	}
	else if ( strcmp( name, "ChatBox" ) == 0 )
	{
		GadgetListBoxSetListLength( window, 1000 );
		GadgetListBoxAddMultiSelect( window );
		if ( TheGameSpyInfo )
			TheGameSpyInfo->slot57( window );
		m_chatBox = window;
	}
	else if ( strcmp( name, "AddFriendEntry" ) == 0 )
	{
		GadgetTextEntrySetText( window, UnicodeString::TheEmptyString );
		bfmeGo924F( (BfmeKeyLC *)window, 0x14 );
		bfmeGo924D( (BfmeKeyLC *)window, 4 );
		window->_bfme_winSetStatus( 2 );
		m_addFriendSlot.bfmeAttach( (BfmeOwnerEJ *)window );
	}
	else if ( strcmp( name, "RemoveFriendEntry" ) == 0 )
	{
		GadgetTextEntrySetText( window, UnicodeString::TheEmptyString );
		bfmeGo924F( (BfmeKeyLC *)window, 0x14 );
		bfmeGo924D( (BfmeKeyLC *)window, 4 );
		window->_bfme_winSetStatus( 2 );
		m_removeFriendSlot.bfmeAttach( (BfmeOwnerEJ *)window );
	}

	if ( m_chatEntry && m_friendsList && m_chatBox )
		Rva004EDED0BuddyMessageNotification();
}
