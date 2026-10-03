// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x0053E390: the custom-match screen's staging-room creation step.
// Owner: the matched OnlineStateUpdate00544E40::update (0x00544E40) calls this
// body through ILT 0x0000FB32 with its own `this` in state 4, and the body
// advances the same state field (+0x188) to 5.  The method name keeps the
// address: no caller, vtable slot or string names it.  The body is the BFME
// form of Zero Hour's PopupHostGame.cpp createGame(): a CREATESTAGINGROOM
// PeerRequest built from the name/password text entries (+0x1A0/+0x1A4), with
// the name and password persisted through the screen's CustomMatchPreferences
// (+0x174).

#include <string>

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;

template <typename T> struct StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_max;
	T m_text[ 1 ];
};

class UnicodeString;
class AsciiString;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	void set( const StringBase<T> &other );

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const UnicodeString &other );
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	void set( const AsciiString &other ) { StringBase<char>::set( other ); }
	AsciiString &operator=( const AsciiString &other ) { set( other ); return *this; }
	void translate( const UnicodeString &src );
	void toLower();

	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<WideChar>( other ) {}
	~UnicodeString() {}

	void set( const UnicodeString &other ) { StringBase<WideChar>::set( other ); }
	UnicodeString &operator=( const UnicodeString &other ) { set( other ); return *this; }

	const WideChar *str() const
	{
		return m_data ? m_data->m_text : (const WideChar *)L"";
	}
};

class GameWindow;

UnicodeString GadgetTextEntryGetText( GameWindow *window );

class LanguageFilter
{
public:
	void filterLine( UnicodeString &line );
};

extern LanguageFilter *TheLanguageFilter;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/CustomMatchPreferences.h
class CustomMatchPreferences
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void storeString1C( AsciiString key, AsciiString value );
	void setAllowsObserver( Bool val );
	AsciiString getPreferredMap();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerThread.h
// BFME inserts an internal-IP word ahead of the Zero Hour staging-room flags.
class PeerRequest
{
public:
	enum { PEERREQUEST_CREATESTAGINGROOM = 8 + 1 };

	PeerRequest();
	~PeerRequest();

	int peerRequestType;			// +0x00
	std::string nick;				// +0x04
	std::wstring text;				// +0x10
	std::string password;			// +0x1C
	std::string email;				// +0x28
	std::string id;					// +0x34
	std::string options;			// +0x40
	std::string ladderIP;			// +0x4C
	std::string hostPingStr;		// +0x58
	char m_mid64[ 0xE4 - 0x64 ];
	UnsignedInt exeCRC;				// +0xE4
	UnsignedInt iniCRC;				// +0xE8
	UnsignedInt gameVersion;		// +0xEC
	UnsignedInt internalIP;			// +0xF0
	Bool allowObservers;			// +0xF4
	Bool useStats;					// +0xF5
	UnsignedShort ladPort;			// +0xF6
	UnsignedInt ladPassCRC;			// +0xF8
	Bool restrictGameList;			// +0xFC
	int numPlayers;					// +0x100
	char m_tail[ 0x194 - 0x104 ];
};

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread() = 0;
	virtual void endThread() = 0;
	virtual int isThreadRunning() = 0;
	virtual int isConnected() = 0;
	virtual int isConnecting() = 0;
	virtual void addRequest( const PeerRequest &request ) = 0;
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

class GameSpyStagingRoom
{
public:
	void setGameName( UnicodeString name ) { m_gameName = name; }
	void setAllowObservers( Bool val ) { m_allowObservers = val; }
	void setLadderIP( AsciiString ladderIP ) { m_ladderIP = ladderIP; }
	void setLadderPort( UnsignedShort port ) { m_ladderPort = port; }

private:
	unsigned char m_head[ 0x418 ];
	UnicodeString m_gameName;			// +0x418
	unsigned char m_mid[ 0x429 - 0x41C ];
	Bool m_allowObservers;				// +0x429
	unsigned char m_gap[ 0x444 - 0x42A ];
	AsciiString m_ladderIP;				// +0x444
	unsigned char m_pingPad[ 0x450 - 0x448 ];
	UnsignedShort m_ladderPort;			// +0x450
};

extern GameSpyStagingRoom *TheGameSpyGame;

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
	GAMESPY_SLOT( 56 ); GAMESPY_SLOT( 57 ); GAMESPY_SLOT( 58 ); GAMESPY_SLOT( 59 );
	GAMESPY_SLOT( 60 ); GAMESPY_SLOT( 61 ); GAMESPY_SLOT( 62 ); GAMESPY_SLOT( 63 );
	GAMESPY_SLOT( 64 ); GAMESPY_SLOT( 65 ); GAMESPY_SLOT( 66 ); GAMESPY_SLOT( 67 );
	GAMESPY_SLOT( 68 );
	virtual AsciiString &getPingString() = 0;
	GAMESPY_SLOT( 70 ); GAMESPY_SLOT( 71 ); GAMESPY_SLOT( 72 ); GAMESPY_SLOT( 73 );
	GAMESPY_SLOT( 74 ); GAMESPY_SLOT( 75 ); GAMESPY_SLOT( 76 ); GAMESPY_SLOT( 77 );
	GAMESPY_SLOT( 78 ); GAMESPY_SLOT( 79 ); GAMESPY_SLOT( 80 ); GAMESPY_SLOT( 81 );
	GAMESPY_SLOT( 82 );
	virtual UnsignedInt getInternalIP() = 0;
};
#undef GAMESPY_SLOT

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;

class GameSpyConfigInterface
{
public:
	virtual ~GameSpyConfigInterface() {}
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual Bool restrictGamesToLobby() = 0;
};

extern GameSpyConfigInterface *TheGameSpyConfig;

class GlobalData
{
public:
	unsigned char m_pad[ 0xBC8 ];
	UnsignedInt m_iniCRC;			// +0xBC8
	unsigned char m_gap[ 4 ];
	UnsignedInt m_exeCRC;			// +0xBD0
	UnsignedInt m_versionBD4;		// +0xBD4
};

extern GlobalData *TheWritableGlobalData;

int Rva0009B4B0( int a, int b );

struct MapCacheNode
{
	unsigned char m_links[ 0x34 ];
	int m_numPlayers;
};

class MapCache
{
public:
	MapCacheNode *find( const AsciiString &name );
	MapCacheNode *m_header;
};

extern MapCache *TheMapCache;

class OnlineStateUpdate00544E40
{
public:
	void createGame0053E390();

private:
	unsigned char m_head[ 0x174 ];
	CustomMatchPreferences m_prefs;			// +0x174
	unsigned char m_mid[ 0x188 - 0x178 ];
	int m_state;							// +0x188
	unsigned char m_gap[ 0x1A0 - 0x18C ];
	GameWindow *m_textEntryGameName;		// +0x1A0
	GameWindow *m_textEntryGamePassword;	// +0x1A4
};

void OnlineStateUpdate00544E40::createGame0053E390()
{
	PeerRequest req;
	UnicodeString gameName = GadgetTextEntryGetText( m_textEntryGameName );
	if( TheLanguageFilter )
		TheLanguageFilter->filterLine( gameName );
	AsciiString asciiGameName( gameName );
	m_prefs.storeString1C( "PreferedGameName", asciiGameName );
	req.peerRequestType = PeerRequest::PEERREQUEST_CREATESTAGINGROOM;
	req.text = gameName.str();
	TheGameSpyGame->setGameName( gameName );

	AsciiString passwd;
	passwd.translate( GadgetTextEntryGetText( m_textEntryGamePassword ) );
	req.password = passwd.str();
	m_prefs.storeString1C( "PreferedGamePassword", passwd );
	m_prefs.setAllowsObserver( true );
	req.allowObservers = true;
	TheGameSpyGame->setAllowObservers( true );

	req.exeCRC = Rva0009B4B0( TheWritableGlobalData->m_exeCRC, TheWritableGlobalData->m_exeCRC );
	req.iniCRC = TheWritableGlobalData->m_iniCRC;
	req.gameVersion = TheWritableGlobalData->m_versionBD4;
	req.internalIP = reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->getInternalIP();
	req.restrictGameList = TheGameSpyConfig->restrictGamesToLobby();

	req.ladderIP = "localhost";
	req.ladPort = 0;
	TheGameSpyGame->setLadderIP( req.ladderIP.c_str() );
	TheGameSpyGame->setLadderPort( req.ladPort );
	req.hostPingStr = reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->getPingString().str();

	req.numPlayers = 2;
	if( TheMapCache )
	{
		AsciiString mapName = m_prefs.getPreferredMap();
		mapName.toLower();
		MapCache *cache = TheMapCache;
		MapCacheNode *node = cache->find( mapName );
		if( node != cache->m_header )
			req.numPlayers = node->m_numPlayers;
	}

	TheGameSpyPeerMessageQueue->addRequest( req );
	m_state = 5;
}
