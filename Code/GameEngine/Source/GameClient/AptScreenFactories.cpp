// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// FILE: AptScreenFactories.cpp ///////////////////////////////////////////////
//
// BFME-only. Fifteen ninety-eight-byte factories sit between 0x00104AC0 and
// 0x001051C0, one per .apt screen, and a table in .data pairs each with its
// screen name. Each is the same three lines: new a screen object of a fixed
// size, hand the argument to its constructor, return the pointer or null if the
// allocation failed.
//
// The table gives the screen, not the function, so the C++ names here are ours.
// The sizes and the constructor addresses are read off the retail bodies, and
// each object is described only by its size - nothing in these bodies touches a
// member, so there is no layout to recover and none is invented.
//
// Objectives.apt and PlayerStatus.apt share one factory at 0x00104F40; the two
// table entries point at the same body.
//
///////////////////////////////////////////////////////////////////////////////

// LoadScreen.apt, retail 0x00104AC0, object 0x258 bytes.
class BfmeAptScreenLoadScreen
{
public:
	BfmeAptScreenLoadScreen( void *context );

private:
	char m_unmodelled[ 0x258 ];
};

// ?createAptScreenLoadScreen@@YGPAXPAX@Z
void * __stdcall createAptScreenLoadScreen( void *context )
{
	return new BfmeAptScreenLoadScreen( context );
}

// LanLobby.apt, retail 0x00104B40, object 0x3DC bytes.
class BfmeAptScreenLanLobby
{
public:
	BfmeAptScreenLanLobby( void *context );

private:
	char m_unmodelled[ 0x3DC ];
};

// ?createAptScreenLanLobby@@YGPAXPAX@Z
void * __stdcall createAptScreenLanLobby( void *context )
{
	return new BfmeAptScreenLanLobby( context );
}

// MainMenu.apt, retail 0x00104BC0, object 0x280 bytes.
class BfmeAptScreenMainMenu
{
public:
	BfmeAptScreenMainMenu( void *context );

private:
	char m_unmodelled[ 0x280 ];
};

// ?createAptScreenMainMenu@@YGPAXPAX@Z
void * __stdcall createAptScreenMainMenu( void *context )
{
	return new BfmeAptScreenMainMenu( context );
}

// OnlineShell.apt, retail 0x00104C40, object 0x280 bytes.
class BfmeAptScreenOnlineShell
{
public:
	BfmeAptScreenOnlineShell( void *context );

private:
	char m_unmodelled[ 0x280 ];
};

// ?createAptScreenOnlineShell@@YGPAXPAX@Z
void * __stdcall createAptScreenOnlineShell( void *context )
{
	return new BfmeAptScreenOnlineShell( context );
}

// Options.apt, retail 0x00104CC0, object 0x310 bytes.
class BfmeAptScreenOptions
{
public:
	BfmeAptScreenOptions( void *context );

private:
	char m_unmodelled[ 0x310 ];
};

// ?createAptScreenOptions@@YGPAXPAX@Z
void * __stdcall createAptScreenOptions( void *context )
{
	return new BfmeAptScreenOptions( context );
}

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	void set( const StringBase<T> &other );
	void trim();

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

struct UnicodeStringData
{
	unsigned int m_refCount;
	unsigned short m_length;
};

class UnicodeString
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString() : m_data( 0 ) {}
	UnicodeString( const unsigned short *text );
	UnicodeString( const UnicodeString &other )
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&other );
	}
	~UnicodeString();
	void concat( const unsigned short *text, int length );
	void set( const UnicodeString &other )
	{
		((StringBase<unsigned short> *)this)->set(
			*(const StringBase<unsigned short> *)&other );
	}
	void trim()
	{
		((StringBase<unsigned short> *)this)->trim();
	}
	bool isEmpty() const { return !m_data || m_data->m_length == 0; }

private:
	UnicodeStringData *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void format( AsciiString format, ... );
};

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen( const unsigned short *text );
extern "C" __declspec(dllimport) int __cdecl atoi( const char *text );
extern "C" int __cdecl strcmp( const char *left, const char *right );
extern "C" char * __cdecl strcpy( char *destination, const char *source );
extern "C" void * __cdecl memset( void *destination, int value, unsigned int count );
extern "C" __declspec(dllimport) int __cdecl sprintf(
	char *destination, const char *format, ... );

int untranslatedSlotPosition( int slot, int localSlot );

class GameWindow
{
public:
	void *winGetUserData();
};
UnicodeString GadgetTextEntryGetText( GameWindow *textEntry );
void GadgetTextEntrySetText( GameWindow *textEntry, UnicodeString text );
void GadgetListBoxReset( GameWindow *listBox );
__declspec(noinline) void BfmeGadgetListBoxSetAudioFeedback( GameWindow *listBox, bool enabled );
int GadgetListBoxAddEntryText( GameWindow *listBox, UnicodeString text, int color,
	int row, int column = -1, bool overwrite = true );

// ?BfmeGadgetListBoxSetAudioFeedback@@YAXPAVGameWindow@@_N@Z
__declspec(noinline) void BfmeGadgetListBoxSetAudioFeedback( GameWindow *listBox, bool enabled )
{
	if ( listBox )
	{
		unsigned char *userData = (unsigned char *)listBox->winGetUserData();
		userData[ 0x10 ] = (unsigned char)enabled;
	}
}

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;

class NetworkInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29();
	virtual void quitGame();
	virtual void voteForPlayerDisconnect( int slot );
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37();
	virtual unsigned int getLocalPlayerID();
	virtual UnicodeString getPlayerName( int player );
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56();
	virtual bool _bfme_isSlotLocalOrLive( int slot );
};

extern NetworkInterface *TheNetwork;

// DisconnectScreen.apt, retail 0x00104D40, object 0x26C bytes.
class DisconnectMenu
{
public:
	void removePlayer( int slot, UnicodeString playerName );
	void sendChat( UnicodeString text );
	void setPlayerName( int slot, UnicodeString playerName );
	void setPlayerTimeoutTime( int slot, int percent );
};

class WindowManager
{
public:
	void bfme_hideBackground( bool hide );
	void bfme_showBackground( int kind );
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
	void unidentified_00015235( int movie, const char *function, int argumentCount,
		const void *argument, int unused1, int unused2, int unused3, int unused4 );
};

extern WindowManager *g_theWindowManager;
extern DisconnectMenu *TheDisconnectMenu;
void _bfme_closeAptScreen( const AsciiString &name );

class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)( void );

struct FunctorBinding
{
	FunctorBinding( FunctorMethod method, FunctorTarget *target )
		: m_target( target ), m_method( method ) {}

	FunctorTarget *m_target;
	unsigned int m_unmodelled;
	FunctorMethod m_method;
};

class Rva0050F840FunctorHolder
{
public:
	Rva0050F840FunctorHolder( FunctorBinding binding );

private:
	void *m_ptr;
};

class Rva0050F8B0FunctorHolder
{
public:
	Rva0050F8B0FunctorHolder( FunctorBinding binding );

private:
	void *m_ptr;
};

class FunctorWrapperHead
{
public:
	FunctorWrapperHead() : m_refCount( 0 ) {}
	virtual void invoke();

	unsigned int m_refCount;
};

class Rva0050F920FunctorWrapper : public FunctorWrapperHead
{
public:
	Rva0050F920FunctorWrapper( const FunctorBinding &binding )
		: m_binding( binding ) {}
	virtual void invoke();

	FunctorBinding m_binding;
};

class Rva0050F920FunctorHolder
{
public:
	Rva0050F920FunctorHolder( FunctorBinding binding )
	{
		m_ptr = new Rva0050F920FunctorWrapper( binding );
		if( m_ptr )
			++m_ptr->m_refCount;
	}

private:
	Rva0050F920FunctorWrapper *m_ptr;
};

void _bfme_setAptScreenRef( const AsciiString &name,
	Rva0050F840FunctorHolder callback );

class _bfme_AptGameWindow
{
public:
	_bfme_AptGameWindow( void *context );
	virtual ~_bfme_AptGameWindow();
	void _bfme_showAptScreen( const AsciiString &name,
		Rva0050F8B0FunctorHolder callback );
	void _bfme_showAptScreenWithArg( const AsciiString &name, void *argument,
		Rva0050F920FunctorHolder callback );

private:
	char m_unmodelled[ 0x254 ];
};

extern const void *BfmeAptScreenDisconnectScreenSecondaryVftable[];

class BfmeAptFunctorMarker {};

struct BfmeAptDisconnectTail
{
	int first;
	int second;
};

class __multiple_inheritance BfmeAptScreenDisconnectScreen
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	BfmeAptScreenDisconnectScreen( void *context );
	virtual ~BfmeAptScreenDisconnectScreen();
	void _bfme_getPlayerColor( const char *name, void *value, bool setting );
	void _bfme_onChatEnterText( const char *argument );
	void _bfme_onInitGadget( const char *name, void *argument, GameWindow *window );
	void _bfme_onInitialized( const char *argument );
	void _bfme_onKick( const char *argument );
	void _bfme_onQuit( const char *argument );

private:
	GameWindow *m_textDisplayControl;
	GameWindow *m_textEntryWindow;
	char m_unmodelledState;
	bool m_isQuitting;
	char m_unmodelledTail[ 0xA ];
};

BfmeAptScreenDisconnectScreen::BfmeAptScreenDisconnectScreen( void *context )
	: _bfme_AptGameWindow( context )
{
	*(const void ***)( (char *)this + 0x218 ) = BfmeAptScreenDisconnectScreenSecondaryVftable;
	m_textDisplayControl = 0;
	m_textEntryWindow = 0;
	m_unmodelledState = 0;
	m_isQuitting = false;

	if( TheDisconnectMenu == 0 )
	{
		TheDisconnectMenu = (DisconnectMenu *)this;
		memset( m_unmodelledTail, 0, sizeof( BfmeAptDisconnectTail ) );
		g_theWindowManager->bfme_showBackground( 2 );

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenDisconnectScreen::_bfme_onInitGadget;
			AsciiString initGadgets( "DisconnectScreen::InitGadgets" );
			_bfme_setAptScreenRef( initGadgets,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}

		_bfme_AptGameWindow *registry = (_bfme_AptGameWindow *)( (char *)this + 0x218 );

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenDisconnectScreen::_bfme_onInitialized;
			AsciiString initialized( "AptDisconnectScreen::OnInitialized" );
			registry->_bfme_showAptScreen( initialized,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenDisconnectScreen::_bfme_onQuit;
			AsciiString quit( "AptDisconnectScreen::Quit" );
			registry->_bfme_showAptScreen( quit,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenDisconnectScreen::_bfme_onKick;
			AsciiString kick( "AptDisconnectScreen::Kick" );
			registry->_bfme_showAptScreen( kick,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenDisconnectScreen::_bfme_onChatEnterText;
			AsciiString chat( "AptDisconnectScreen::Chat::OnBttnEnterText" );
			registry->_bfme_showAptScreen( chat,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}

		AsciiString playerColor;
		FunctorMethod playerColorCallback =
			(FunctorMethod)&BfmeAptScreenDisconnectScreen::_bfme_getPlayerColor;
		for( int slot = 0; slot < 8; ++slot )
		{
			playerColor.format( (AsciiString)"DisconnectScreen:PlayerColor:%d", slot );
			registry->_bfme_showAptScreenWithArg( playerColor, (void *)slot,
				FunctorBinding( playerColorCallback, (FunctorTarget *)this ) );
			((DisconnectMenu *)this)->removePlayer( slot, UnicodeString::TheEmptyString );
		}
	}
}

void DisconnectMenu::setPlayerName( int slot, UnicodeString playerName )
{
	AsciiString variableName;
	char slotText[ 32 ];
	variableName.format( (AsciiString)"DisconnectScreen::PlayerName%d", slot );

	if( playerName.isEmpty() )
	{
		{
			UnicodeString blank( L" " );
			g_theWindowManager->bfme_setAptText( variableName, blank );
		}
		setPlayerTimeoutTime( slot, 0 );
	}
	else
	{
		g_theWindowManager->bfme_setAptText( variableName, playerName );
		sprintf( slotText, "%d", slot );

		int movie = *(int *)( (char *)this + 0x250 );
		g_theWindowManager->unidentified_00015235(
			movie, "HideKickButton", 1, slotText, 0, 0, 0, 0 );
		*(char *)( (char *)this + 0x262 + slot ) = 0;
		setPlayerTimeoutTime( slot, 100 );
	}
}

BfmeAptScreenDisconnectScreen::~BfmeAptScreenDisconnectScreen()
{
	*(const void ***)( (char *)this + 0x218 ) = BfmeAptScreenDisconnectScreenSecondaryVftable;

	if( TheDisconnectMenu == (DisconnectMenu *)this )
	{
		TheDisconnectMenu = 0;
		if( !m_isQuitting )
			g_theWindowManager->bfme_hideBackground( false );

		AsciiString name( "DisconnectScreen::InitGadgets" );
		_bfme_closeAptScreen( name );
	}

}

// ?_bfme_onQuit@BfmeAptScreenDisconnectScreen@@QAEXPBD@Z
void BfmeAptScreenDisconnectScreen::_bfme_onQuit( const char * )
{
	m_isQuitting = true;

	UnicodeString message = TheNetwork->getPlayerName( TheNetwork->getLocalPlayerID() );
	message.concat( L" has left the game", wcslen( L" has left the game" ) );
	((DisconnectMenu *)this)->sendChat( message );

	for( int slot = 0; slot < 8; ++slot )
	{
		if( !TheNetwork->_bfme_isSlotLocalOrLive( slot ) )
			TheNetwork->voteForPlayerDisconnect( slot );
	}

	TheNetwork->quitGame();
}

// ?_bfme_onChatEnterText@BfmeAptScreenDisconnectScreen@@QAEXPBD@Z
void BfmeAptScreenDisconnectScreen::_bfme_onChatEnterText( const char * )
{
	UnicodeString text;
	if( m_textEntryWindow )
	{
		text.set( GadgetTextEntryGetText( m_textEntryWindow ) );
		GadgetTextEntrySetText( m_textEntryWindow, UnicodeString::TheEmptyString );
		text.trim();
		if( !text.isEmpty() )
			((DisconnectMenu *)this)->sendChat( text );
	}
}

// ?_bfme_onInitGadget@BfmeAptScreenDisconnectScreen@@QAEXPBDPAXPAVGameWindow@@@Z
void BfmeAptScreenDisconnectScreen::_bfme_onInitGadget(
	const char *name, void *, GameWindow *window )
{
	if( strcmp( name, "ChatBox" ) == 0 )
	{
		m_textDisplayControl = window;
		return;
	}

	if( strcmp( name, "ChatEntry" ) == 0 )
	{
		m_textEntryWindow = window;
		GadgetTextEntrySetText( window, UnicodeString::TheEmptyString );
		return;
	}

	if( strcmp( name, "RulesBox" ) == 0 )
	{
		GadgetListBoxReset( window );
		BfmeGadgetListBoxSetAudioFeedback( window, true );
		GadgetListBoxAddEntryText( window,
			TheGameText->fetch( "APT:DisconnectRules" ), -1, -1, -1, true );
	}
}

// ?_bfme_onKick@BfmeAptScreenDisconnectScreen@@QAEXPBD@Z
void BfmeAptScreenDisconnectScreen::_bfme_onKick( const char *argument )
{
	if( argument && *argument )
	{
		int slot = atoi( argument );
		int localSlot = TheNetwork->getLocalPlayerID();
		slot = untranslatedSlotPosition( slot, localSlot );
		TheNetwork->voteForPlayerDisconnect( slot );
	}
}

// ?_bfme_getPlayerColor@BfmeAptScreenDisconnectScreen@@QAEXPBDPAX_N@Z
void BfmeAptScreenDisconnectScreen::_bfme_getPlayerColor(
	const char *, void *value, bool setting )
{
	if( !setting )
		strcpy( (char *)value, "0xFFFFFFFF" );
}

// ?createAptScreenDisconnectScreen@@YGPAXPAX@Z
void * __stdcall createAptScreenDisconnectScreen( void *context )
{
	return new BfmeAptScreenDisconnectScreen( context );
}

// SaveLoad.apt, retail 0x00104DC0, object 0x288 bytes.
class BfmeAptScreenSaveLoad
{
public:
	BfmeAptScreenSaveLoad( void *context );

private:
	char m_unmodelled[ 0x288 ];
};

// ?createAptScreenSaveLoad@@YGPAXPAX@Z
void * __stdcall createAptScreenSaveLoad( void *context )
{
	return new BfmeAptScreenSaveLoad( context );
}

// Skirmish.apt, retail 0x00104E40, object 0x43C bytes.
class BfmeAptScreenSkirmish
{
public:
	BfmeAptScreenSkirmish( void *context );

private:
	char m_unmodelled[ 0x43C ];
};

// ?createAptScreenSkirmish@@YGPAXPAX@Z
void * __stdcall createAptScreenSkirmish( void *context )
{
	return new BfmeAptScreenSkirmish( context );
}

// QuitMenu.apt, retail 0x00104EC0, object 0x260 bytes.
class BfmeAptScreenQuitMenu
{
public:
	BfmeAptScreenQuitMenu( void *context );

private:
	char m_unmodelled[ 0x260 ];
};

// ?createAptScreenQuitMenu@@YGPAXPAX@Z
void * __stdcall createAptScreenQuitMenu( void *context )
{
	return new BfmeAptScreenQuitMenu( context );
}

// Objectives.apt and PlayerStatus.apt, retail 0x00104F40, object 0x290 bytes.
class BfmeAptScreenObjectives
{
public:
	BfmeAptScreenObjectives( void *context );

private:
	char m_unmodelled[ 0x290 ];
};

// ?createAptScreenObjectives@@YGPAXPAX@Z
void * __stdcall createAptScreenObjectives( void *context )
{
	return new BfmeAptScreenObjectives( context );
}

// ScoreScreen.apt, retail 0x00104FC0, object 0x334 bytes.
class BfmeAptScreenScoreScreen
{
public:
	BfmeAptScreenScoreScreen( void *context );

private:
	char m_unmodelled[ 0x334 ];
};

// ?createAptScreenScoreScreen@@YGPAXPAX@Z
void * __stdcall createAptScreenScoreScreen( void *context )
{
	return new BfmeAptScreenScoreScreen( context );
}

// CampaignReview.apt, retail 0x00105040, object 0x258 bytes.
class BfmeAptScreenCampaignReview
{
public:
	BfmeAptScreenCampaignReview( void *context );

private:
	char m_unmodelled[ 0x258 ];
};

// ?createAptScreenCampaignReview@@YGPAXPAX@Z
void * __stdcall createAptScreenCampaignReview( void *context )
{
	return new BfmeAptScreenCampaignReview( context );
}

// InGameChat.apt, retail 0x001050C0, object 0x2A4 bytes.
class BfmeAptScreenInGameChat
{
public:
	BfmeAptScreenInGameChat( void *context );

private:
	char m_unmodelled[ 0x2A4 ];
};

// ?createAptScreenInGameChat@@YGPAXPAX@Z
void * __stdcall createAptScreenInGameChat( void *context )
{
	return new BfmeAptScreenInGameChat( context );
}

// SpellStore.apt, retail 0x00105140, object 0x2D4 bytes.
class BfmeAptScreenSpellStore
{
public:
	BfmeAptScreenSpellStore( void *context );

private:
	char m_unmodelled[ 0x2D4 ];
};

// ?createAptScreenSpellStore@@YGPAXPAX@Z
void * __stdcall createAptScreenSpellStore( void *context )
{
	return new BfmeAptScreenSpellStore( context );
}

class NameKeyGenerator
{
public:
	int nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

class BfmeAptScreenBase
{
public:
	BfmeAptScreenBase( void *context );
	~BfmeAptScreenBase();
	virtual void slot0();

private:
	char m_unmodelled[ 0x214 ];
};

// QuickMatchMenu, retail 0x001051C0, object 0x2B0 bytes.
class BfmeAptScreenQuickMatchMenu : public BfmeAptScreenBase
{
public:
	BfmeAptScreenQuickMatchMenu( void *context );
	virtual void slot0();

private:
	bool m_isMatching;
	char m_pad219[ 3 ];
	int m_matchingLevel;
	bool m_isStopping;
	char m_pad221[ 3 ];
	int m_selectedMap;
	int m_parentOptionsKey;
	void *m_parentOptions;
	int m_maxPingKey;
	void *m_maxPing;
	int m_numPlayersKey;
	void *m_numPlayers;
	int m_ladderKey;
	void *m_ladder;
	int m_maxDisconnectsKey;
	void *m_maxDisconnects;
	int m_sideKey;
	void *m_side;
	int m_colorKey;
	void *m_color;
	int m_backKey;
	void *m_back;
	int m_startKey;
	void *m_start;
	int m_currentMatchingLevelKey;
	void *m_currentMatchingLevel;
	int m_personalInfoKey;
	void *m_personalInfo;
	int m_mapSelectKey;
	void *m_mapSelect;
	int m_parentProgressKey;
	void *m_parentProgress;
	int m_quickMatchListKey;
	void *m_quickMatchList;
	int m_widenKey;
	void *m_widen;
	int m_stopKey;
	void *m_stop;
	int m_parentStatsKey;
	void *m_parentStats;
};

BfmeAptScreenQuickMatchMenu::BfmeAptScreenQuickMatchMenu( void *context )
	: BfmeAptScreenBase( context )
{
	m_isMatching = false;
	m_matchingLevel = 0;
	m_isStopping = false;
	m_selectedMap = 0;
	m_parentOptionsKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ParentOptions" );
	m_parentOptions = 0;
	m_maxPingKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ComboBoxMaxPing" );
	m_maxPing = 0;
	m_numPlayersKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ComboBoxNumPlayers" );
	m_numPlayers = 0;
	m_ladderKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ComboBoxLadder" );
	m_ladder = 0;
	m_maxDisconnectsKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ComboBoxMaxDisconnects" );
	m_maxDisconnects = 0;
	m_sideKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ComboBoxSide" );
	m_side = 0;
	m_colorKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ComboBoxColor" );
	m_color = 0;
	m_backKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ButtonBack" );
	m_back = 0;
	m_startKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ButtonStart" );
	m_start = 0;
	m_currentMatchingLevelKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:currentMatchingLevel" );
	m_currentMatchingLevel = 0;
	m_personalInfoKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:PersonalInfo" );
	m_personalInfo = 0;
	m_mapSelectKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ListBoxMapSelect" );
	m_mapSelect = 0;
	m_parentProgressKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ParentProgress" );
	m_parentProgress = 0;
	m_quickMatchListKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ListboxQuickMatch" );
	m_quickMatchList = 0;
	m_widenKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ButtonWiden" );
	m_widen = 0;
	m_stopKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ButtonStop" );
	m_stop = 0;
	m_parentStatsKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ParentStats" );
	m_parentStats = 0;
}

// ?createAptScreenQuickMatchMenu@@YGPAXPAX@Z
void * __stdcall createAptScreenQuickMatchMenu( void *context )
{
	return new BfmeAptScreenQuickMatchMenu( context );
}

// WOLQuickMatchMenu, retail 0x00506040, object 0x28 bytes. The odd one out: its
// constructor is inlined rather than called, so the factory runs the base
// constructor at 0x00470620, stores its own vtable, zeroes the member at +0x24,
// and then clears the singleton at 0x012F4820 before returning. Only the base
// class is polymorphic-and-separate here; everything else is this one call site.
class BfmeQuickMatchScreenBase
{
public:
	BfmeQuickMatchScreenBase( void *context );
	virtual void slot0();

private:
	char m_unmodelled[ 0x20 ];
};

class BfmeQuickMatchScreen : public BfmeQuickMatchScreenBase
{
public:
	BfmeQuickMatchScreen( void *context );
	virtual void slot0();

private:
	int m_fieldAt24;
};

extern void *TheBfmeQuickMatchScreenSlot;   // 0x012F4820

inline BfmeQuickMatchScreen::BfmeQuickMatchScreen( void *context )
	: BfmeQuickMatchScreenBase( context )
{
	m_fieldAt24 = 0;
	TheBfmeQuickMatchScreenSlot = 0;
}

// ?createAptScreenWOLQuickMatchMenu@@YGPAXPAX@Z
void * __stdcall createAptScreenWOLQuickMatchMenu( void *context )
{
	return new BfmeQuickMatchScreen( context );
}

// OnlineProfile, retail 0x0055BBA0, object 0x3C bytes. Two departures from the
// rest: it is __cdecl rather than __stdcall - retail returns with a bare ret -
// and it refuses to build a second one, returning null when the singleton at
// 0x012F4AB4 is already set.
class BfmeOnlineProfileScreen
{
public:
	BfmeOnlineProfileScreen( void *context );

private:
	char m_unmodelled[ 0x3C ];
};

extern void *TheBfmeOnlineProfileSlot;   // 0x012F4AB4

// ?createAptScreenOnlineProfile@@YAPAXPAX@Z
void *createAptScreenOnlineProfile( void *context )
{
	if( TheBfmeOnlineProfileSlot )
		return 0;

	return new BfmeOnlineProfileScreen( context );
}
