// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineCustomMatch::_bfme_onInitGadget, retail 0x0053A710,
// 834 bytes. AptOnlineCustomMatch::InitGadgets handler. Named by gadget
// literals GameList/Chat/ChatEntry/Lobbies/GameInfo/GameName/GamePassword/
// GameType/StartingResources and the already-landed +0x1A0/+0x1A4/+0x1AC
// siblings. Guarded on TheBfmeOnlineCustomMatch. Thunk 0x0001F9C9.

extern "C" int __cdecl strcmp( const char *s1, const char *s2 );

template <typename T> struct StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_max;
	T m_text[ 1 ];
};

class UnicodeString;

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringData<T> *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
};

class WinInstanceData;
class GameWindow
{
public:
	void *winGetUserData();
	void winSetUserData( void *data );
	int winSetTooltipFunc( void ( *fn )( GameWindow *, WinInstanceData *, unsigned int ) );
	void winSetStatus( unsigned int status );
};

void GadgetListBoxReset( GameWindow *window );
void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );
void BfmeGadgetListBoxSetAudioFeedback( GameWindow *listBox, bool enabled );
int GadgetComboBoxAddEntry( GameWindow *comboBox, UnicodeString text, int color );
void GadgetComboBoxSetItemData( GameWindow *comboBox, int index, void *data );
void customMatchGameListTooltip( GameWindow *, WinInstanceData *, unsigned int );

class BfmeKeyLC;
class BfmeObjENK;
void bfmeGo924D( BfmeKeyLC *k, unsigned int mask );
void bfmeGo924F( BfmeKeyLC *k, unsigned short w );
void bfmeGoENK( BfmeObjENK *o, char v );

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;
extern int GameSpyColor[];

#define GAMESPY_SLOT( n ) virtual void gamespySlot##n() = 0
class GameSpyInfo
{
public:
	GAMESPY_SLOT( 0 ); GAMESPY_SLOT( 1 ); GAMESPY_SLOT( 2 ); GAMESPY_SLOT( 3 );
	GAMESPY_SLOT( 4 ); GAMESPY_SLOT( 5 ); GAMESPY_SLOT( 6 ); GAMESPY_SLOT( 7 );
	GAMESPY_SLOT( 8 ); GAMESPY_SLOT( 9 ); GAMESPY_SLOT( 10 ); GAMESPY_SLOT( 11 );
	GAMESPY_SLOT( 12 ); GAMESPY_SLOT( 13 ); GAMESPY_SLOT( 14 ); GAMESPY_SLOT( 15 );
	GAMESPY_SLOT( 16 ); GAMESPY_SLOT( 17 ); GAMESPY_SLOT( 18 ); GAMESPY_SLOT( 19 );
	GAMESPY_SLOT( 20 ); GAMESPY_SLOT( 21 ); GAMESPY_SLOT( 22 ); GAMESPY_SLOT( 23 );
	GAMESPY_SLOT( 24 ); GAMESPY_SLOT( 25 ); GAMESPY_SLOT( 26 ); GAMESPY_SLOT( 27 );
	GAMESPY_SLOT( 28 ); GAMESPY_SLOT( 29 ); GAMESPY_SLOT( 30 ); GAMESPY_SLOT( 31 );
	GAMESPY_SLOT( 32 ); GAMESPY_SLOT( 33 ); GAMESPY_SLOT( 34 ); GAMESPY_SLOT( 35 );
	GAMESPY_SLOT( 36 ); GAMESPY_SLOT( 37 ); GAMESPY_SLOT( 38 ); GAMESPY_SLOT( 39 );
	GAMESPY_SLOT( 40 ); GAMESPY_SLOT( 41 ); GAMESPY_SLOT( 42 ); GAMESPY_SLOT( 43 );
	GAMESPY_SLOT( 44 ); GAMESPY_SLOT( 45 ); GAMESPY_SLOT( 46 ); GAMESPY_SLOT( 47 );
	GAMESPY_SLOT( 48 ); GAMESPY_SLOT( 49 ); GAMESPY_SLOT( 50 ); GAMESPY_SLOT( 51 );
	GAMESPY_SLOT( 52 ); GAMESPY_SLOT( 53 ); GAMESPY_SLOT( 54 ); GAMESPY_SLOT( 55 );
	GAMESPY_SLOT( 56 );
	virtual void registerTextWindow( GameWindow *win ) = 0;
};
#undef GAMESPY_SLOT

extern GameSpyInfo *TheGameSpyInfo;
extern class BfmeAptScreenOnlineCustomMatch *TheBfmeOnlineCustomMatch;

class BfmeAptScreenOnlineCustomMatch
{
public:
	void _bfme_onInitGadget( const char *name, void *argument, GameWindow *window );
	void applyStartingSuppliesCombo();

private:
	unsigned char m_pad[ 0x18C ];
	GameWindow *m_gameList;
	GameWindow *m_lobbies;
	GameWindow *m_chatEntry;
	GameWindow *m_chat;
	GameWindow *m_gameInfo;
	GameWindow *m_gameName;
	GameWindow *m_gamePassword;
	GameWindow *m_gameType;
	GameWindow *m_startingResources;
};

void BfmeAptScreenOnlineCustomMatch::_bfme_onInitGadget(
	const char *name, void *, GameWindow *window )
{
	if( !TheBfmeOnlineCustomMatch )
		return;
	if( !window )
		return;

	if( strcmp( name, "GameList" ) == 0 )
	{
		GadgetListBoxReset( window );
		m_gameList = window;
		unsigned char *userData = (unsigned char *)window->winGetUserData();
		userData[ 0x12 ] = 1;
		window->winSetUserData( userData );
		window->winSetTooltipFunc( customMatchGameListTooltip );
		return;
	}

	if( strcmp( name, "Chat" ) == 0 )
	{
		GadgetListBoxReset( window );
		m_chat = window;
		GadgetListBoxReset( window );
		TheGameSpyInfo->registerTextWindow( m_chat );
		bfmeGoENK( (BfmeObjENK *)m_chat, 1 );
		BfmeGadgetListBoxSetAudioFeedback( m_chat, true );
		return;
	}

	if( strcmp( name, "ChatEntry" ) == 0 )
	{
		GadgetTextEntrySetText( window, UnicodeString::TheEmptyString );
		bfmeGo924F( (BfmeKeyLC *)window, 0x6E );
		m_chatEntry = window;
		return;
	}

	if( strcmp( name, "Lobbies" ) == 0 )
	{
		m_lobbies = window;
		return;
	}

	if( strcmp( name, "GameInfo" ) == 0 )
	{
		GadgetListBoxReset( window );
		m_gameInfo = window;
		return;
	}

	if( strcmp( name, "GameName" ) == 0 )
	{
		m_gameName = window;
		bfmeGo924F( (BfmeKeyLC *)window, 20 );
		window->winSetStatus( 2 );
		return;
	}

	if( strcmp( name, "GamePassword" ) == 0 )
	{
		m_gamePassword = window;
		bfmeGo924D( (BfmeKeyLC *)window, 5 );
		bfmeGo924F( (BfmeKeyLC *)window, 20 );
		window->winSetStatus( 2 );
		return;
	}

	if( strcmp( name, "GameType" ) == 0 )
	{
		m_gameType = window;
		return;
	}

	if( strcmp( name, "StartingResources" ) == 0 )
	{
		m_startingResources = window;
		int idx = GadgetComboBoxAddEntry( m_startingResources,
			TheGameText->fetch( "APT:VeryLowResourcesNum", 0 ), GameSpyColor[ 0 ] );
		GadgetComboBoxSetItemData( m_startingResources, idx, (void *)0 );
		idx = GadgetComboBoxAddEntry( m_startingResources,
			TheGameText->fetch( "APT:LowResourcesNum", 0 ), GameSpyColor[ 0 ] );
		GadgetComboBoxSetItemData( m_startingResources, idx, (void *)1 );
		idx = GadgetComboBoxAddEntry( m_startingResources,
			TheGameText->fetch( "APT:MediumResourcesNum", 0 ), GameSpyColor[ 0 ] );
		GadgetComboBoxSetItemData( m_startingResources, idx, (void *)2 );
		idx = GadgetComboBoxAddEntry( m_startingResources,
			TheGameText->fetch( "APT:HighResourcesNum", 0 ), GameSpyColor[ 0 ] );
		GadgetComboBoxSetItemData( m_startingResources, idx, (void *)3 );
		idx = GadgetComboBoxAddEntry( m_startingResources,
			TheGameText->fetch( "APT:VeryHighResourcesNum", 0 ), GameSpyColor[ 0 ] );
		GadgetComboBoxSetItemData( m_startingResources, idx, (void *)4 );
		applyStartingSuppliesCombo();
	}
}
