// cl: /DNDEBUG /MD /EHsc
//
// BfmeAptScreenOnlineChat::_bfme_initGadgets, retail 0x00534A60, 1013 bytes.
// Retail 0x005372D3 pushes the selector string "AptOnlineChat::InitGadgets"
// and loads this body's ILT thunk a few bytes later, which is what names it.
//
// The callback runs once per gadget. It clears the gadget, matches its name
// against ten literals, and files the window in the screen. The class is the
// one OnlineChatListButtons.cpp already models, down to the list mode at
// this+0xA4.

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

void GadgetListBoxReset( GameWindow *listbox );
void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );
void GadgetListBoxSetListLength( GameWindow *listbox, Int length );
void GadgetListBoxAddMultiSelect( GameWindow *listbox );
void GadgetListBoxSetColumnWidths( GameWindow *listbox, Int count, Int *widths );
void bfmeGo924F( BfmeKeyLC *window, unsigned short value );
void bfmeGo924D( BfmeKeyLC *window, unsigned int value );
void Rva00533EA0( GameWindow *listbox );

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
	GAMESPY_SLOT(04); GAMESPY_SLOT(05);
#undef GAMESPY_SLOT
	virtual void slot06( void *room ) = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09( Int mode ) = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void *slot13( void ) = 0;
#define GAMESPY_SLOT(n) virtual void slot##n() = 0
	GAMESPY_SLOT(14); GAMESPY_SLOT(15); GAMESPY_SLOT(16); GAMESPY_SLOT(17);
	GAMESPY_SLOT(18); GAMESPY_SLOT(19); GAMESPY_SLOT(20); GAMESPY_SLOT(21);
	GAMESPY_SLOT(22); GAMESPY_SLOT(23); GAMESPY_SLOT(24); GAMESPY_SLOT(25);
	GAMESPY_SLOT(26); GAMESPY_SLOT(27); GAMESPY_SLOT(28); GAMESPY_SLOT(29);
	GAMESPY_SLOT(30); GAMESPY_SLOT(31); GAMESPY_SLOT(32); GAMESPY_SLOT(33);
	GAMESPY_SLOT(34); GAMESPY_SLOT(35); GAMESPY_SLOT(36); GAMESPY_SLOT(37);
	GAMESPY_SLOT(38); GAMESPY_SLOT(39); GAMESPY_SLOT(40); GAMESPY_SLOT(41);
	GAMESPY_SLOT(42); GAMESPY_SLOT(43); GAMESPY_SLOT(44); GAMESPY_SLOT(45);
	GAMESPY_SLOT(46); GAMESPY_SLOT(47); GAMESPY_SLOT(48); GAMESPY_SLOT(49);
	GAMESPY_SLOT(50); GAMESPY_SLOT(51); GAMESPY_SLOT(52); GAMESPY_SLOT(53);
	GAMESPY_SLOT(54); GAMESPY_SLOT(55); GAMESPY_SLOT(56);
#undef GAMESPY_SLOT
	virtual void slot57( GameWindow *window ) = 0;
};

class Gen_00479A60
{
public:
	void bfmeAttach( BfmeOwnerEJ *owner );

private:
	unsigned char m_unmodelled[ 0x10 ];
};

class BfmeAptScreenOnlineChat;

extern BfmeAptScreenOnlineChat *TheBfmeOnlineChat;
extern GameWindowManager *TheWindowManager;
extern GameSpyInfo *TheGameSpyInfo;
extern void *g_obj12F49F4;

// Layout witnessed by OnlineChatListButtons.cpp, which writes the same list
// mode at +0xA4.
class BfmeAptScreenOnlineChat
{
public:
	void _bfme_initGadgets( const char *name, void *userData, GameWindow *window );
	void rva0052E990( void );
	void Rva005337E0( void );
	void Rva00534380( void );

private:
	unsigned char m_unmodelled000[ 0x40 ];
	GameWindow *m_playersList;
	GameWindow *m_friendsList;
	GameWindow *m_ignoreList;
	GameWindow *m_chatLobbies;
	GameWindow *m_chatEntry;
	GameWindow *m_chat;
	Gen_00479A60 m_addIgnoreSlot;
	Gen_00479A60 m_addFriendSlot;
	Gen_00479A60 m_removeIgnoreSlot;
	Gen_00479A60 m_removeFriendSlot;
	unsigned char m_unmodelled098[ 0xa4 - 0x98 ];
	Int m_zA4;
};

void BfmeAptScreenOnlineChat::_bfme_initGadgets( const char *name, void *userData,
	GameWindow *window )
{
	(void)userData;
	if ( TheBfmeOnlineChat == 0 )
		return;
	if ( window == 0 )
		return;

	GadgetListBoxReset( window );

	if ( strcmp( name, "OnlineChat::Chat" ) == 0 )
	{
		GadgetListBoxSetListLength( window, 1000 );
		GadgetListBoxAddMultiSelect( window );
		TheGameSpyInfo->slot57( window );
		m_chat = window;
	}
	else if ( strcmp( name, "OnlineChat::ChatEntry" ) == 0 )
	{
		TheWindowManager->slot44( window );
		GadgetTextEntrySetText( window, UnicodeString::TheEmptyString );
		Rva00515E60GadgetData *data =
			(Rva00515E60GadgetData *)window->winGetUserData();
		if ( data )
			data->m_maxTextLen = 110;
		m_chatEntry = window;
	}
	else if ( strcmp( name, "OnlineChat::ChatLobbies" ) == 0 )
	{
		m_chatLobbies = window;
		if ( TheGameSpyInfo->slot13() )
		{
			TheGameSpyInfo->slot06( TheGameSpyInfo->slot13() );
			g_obj12F49F4 = 0;
		}
		else
		{
			TheGameSpyInfo->slot09( 2 );
		}
		rva0052E990();
	}
	else if ( strcmp( name, "OnlineChat::PlayersList" ) == 0 )
	{
		m_zA4 = 1;
		GadgetListBoxSetListLength( window, 1000 );
		GadgetListBoxAddMultiSelect( window );
		Int widths[ 7 ] = { 10, 10, 0x50, 0, 0, 0, 0 };
		GadgetListBoxSetColumnWidths( window, 3, widths );
		m_playersList = window;
		Rva005337E0();
		Rva00515E60GadgetData *data =
			(Rva00515E60GadgetData *)window->winGetUserData();
		data->m_byte12 = 1;
		window->winSetUserData( data );
	}
	else if ( strcmp( name, "OnlineChat::FriendsList" ) == 0 )
	{
		GadgetListBoxSetListLength( window, 1000 );
		GadgetListBoxAddMultiSelect( window );
		Int widths[ 7 ] = { 10, 10, 0x50, 0, 0, 0, 0 };
		GadgetListBoxSetColumnWidths( window, 3, widths );
		m_friendsList = window;
		Rva00533EA0( window );
		Rva00515E60GadgetData *data =
			(Rva00515E60GadgetData *)window->winGetUserData();
		data->m_byte12 = 1;
		window->winSetUserData( data );
	}
	else if ( strcmp( name, "OnlineChat::IgnoreList" ) == 0 )
	{
		GadgetListBoxSetListLength( window, 1000 );
		GadgetListBoxAddMultiSelect( window );
		Int widths[ 7 ] = { 10, 10, 0x50, 0, 0, 0, 0 };
		GadgetListBoxSetColumnWidths( window, 3, widths );
		m_ignoreList = window;
		Rva00534380();
		Rva00515E60GadgetData *data =
			(Rva00515E60GadgetData *)window->winGetUserData();
		data->m_byte12 = 1;
		window->winSetUserData( data );
	}
	else if ( strcmp( name, "OnlineChat::AddIgnoreEntry" ) == 0 )
	{
		GadgetTextEntrySetText( window, UnicodeString::TheEmptyString );
		bfmeGo924F( (BfmeKeyLC *)window, 0x14 );
		bfmeGo924D( (BfmeKeyLC *)window, 4 );
		window->_bfme_winSetStatus( 2 );
		m_addIgnoreSlot.bfmeAttach( (BfmeOwnerEJ *)window );
	}
	else if ( strcmp( name, "OnlineChat::AddFriendEntry" ) == 0 )
	{
		GadgetTextEntrySetText( window, UnicodeString::TheEmptyString );
		bfmeGo924F( (BfmeKeyLC *)window, 0x14 );
		bfmeGo924D( (BfmeKeyLC *)window, 4 );
		window->_bfme_winSetStatus( 2 );
		m_addFriendSlot.bfmeAttach( (BfmeOwnerEJ *)window );
	}
	else if ( strcmp( name, "OnlineChat::RemoveIgnoreEntry" ) == 0 )
	{
		GadgetTextEntrySetText( window, UnicodeString::TheEmptyString );
		bfmeGo924F( (BfmeKeyLC *)window, 0x14 );
		bfmeGo924D( (BfmeKeyLC *)window, 4 );
		window->_bfme_winSetStatus( 2 );
		m_removeIgnoreSlot.bfmeAttach( (BfmeOwnerEJ *)window );
	}
	else if ( strcmp( name, "OnlineChat::RemoveFriendEntry" ) == 0 )
	{
		GadgetTextEntrySetText( window, UnicodeString::TheEmptyString );
		bfmeGo924F( (BfmeKeyLC *)window, 0x14 );
		bfmeGo924D( (BfmeKeyLC *)window, 4 );
		window->_bfme_winSetStatus( 2 );
		m_removeFriendSlot.bfmeAttach( (BfmeOwnerEJ *)window );
	}
}
