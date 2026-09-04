// ?createGame@BfmeAptScreenOnlineCustomMatch@@QAEXXZ
// partial score=0.74 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineCustomMatch::createGame, retail 0x0053E390, 992 bytes.
// Apt ZH PopupHostGame.cpp createGame twin: text entries +0x1A0/+0x1A4,
// persist PreferedGameName/PreferedGamePassword via prefs +0x174 setAsciiString
// (+0x1C), LanguageFilter, CREATESTAGINGROOM type 9, localhost ladder,
// CRC trio through AptLivingWorldWindowIndex, MapCache preferred-map
// numPlayers, queue addRequest, state +0x188 = 5.

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

	void translate( const UnicodeString &src );

	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}

	void toLower();
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}

	const unsigned short *str() const
	{
		return m_data ? m_data->m_text : (const unsigned short *)L"";
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

class CustomMatchPreferences
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual AsciiString getAsciiString( AsciiString key, AsciiString defaultValue ) const;
	virtual void setAsciiString( AsciiString key, AsciiString val );
	void setAllowsObserver( bool val );
	AsciiString getPreferredMap();
};

class StlStr
{
public:
	StlStr &assign( const char *first, const char *last );
	const char *c_str() const { return m_start; }

private:
	const char *m_start;
	char m_rest[ 8 ];
};

class StlWStr
{
public:
	StlWStr &assign( const unsigned short *first, const unsigned short *last );

private:
	char m_bytes[ 12 ];
};

class PeerRequest
{
public:
	PeerRequest();
	~PeerRequest();
	int peerRequestType;
	StlStr nick;
	StlWStr text;
	StlStr password;
	char m_mid28[ 0x4C - 0x28 ];
	StlStr ladderIP;
	StlStr hostPingStr;
	char m_mid64[ 0xE4 - 0x64 ];
	unsigned int exeCRC;
	unsigned int iniCRC;
	unsigned int gameVersion;
	unsigned int internalIP;
	unsigned char allowObservers;
	unsigned char useStats;
	unsigned short ladPort;
	char m_padF8[ 4 ];
	unsigned char restrictGameList;
	char m_padFD[ 3 ];
	int numPlayers;
	char m_tail[ 0x194 - 0x104 ];
};

typedef char PeerRequestSizeCheck[ sizeof( PeerRequest ) == 0x194 ? 1 : -1 ];

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
	void setGameName( const UnicodeString &name )
	{
		m_gameName.set( name );
	}
	void setLadderIP( const AsciiString &ip )
	{
		m_ladderIP.set( ip );
	}
	void setLadderPort( unsigned short port )
	{
		m_ladderPort = port;
	}
	void setAllowObservers( unsigned char val )
	{
		m_allowObservers = val;
	}

private:
	unsigned char m_head[ 0x418 ];
	UnicodeString m_gameName;
	unsigned char m_mid[ 0x429 - 0x41C ];
	unsigned char m_allowObservers;
	unsigned char m_gap[ 0x444 - 0x42A ];
	AsciiString m_ladderIP;
	unsigned char m_pingPad[ 0x450 - 0x448 ];
	unsigned short m_ladderPort;
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
	virtual unsigned int getInternalIP() = 0;
};
#undef GAMESPY_SLOT

extern GameSpyInfo *TheGameSpyInfo;

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
	virtual bool restrictGamesToLobby() = 0;
};

extern GameSpyConfigInterface *TheGameSpyConfig;

class GlobalData
{
public:
	unsigned char m_pad[ 0xBC8 ];
	unsigned int m_iniCRC;
	unsigned char m_gap[ 4 ];
	unsigned int m_exeCRC;
	unsigned int m_extraCRC;
};

extern GlobalData *TheWritableGlobalData;

int AptLivingWorldWindowIndex( int low, int high );

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

class BfmeAptScreenOnlineCustomMatch
{
public:
	void createGame();

private:
	unsigned char m_head[ 0x174 ];
	CustomMatchPreferences m_prefs;
	unsigned char m_mid[ 0x188 - 0x178 ];
	int m_state;
	unsigned char m_gap[ 0x1A0 - 0x18C ];
	GameWindow *m_nameEntry;
	GameWindow *m_passwordEntry;
};

void BfmeAptScreenOnlineCustomMatch::createGame()
{
	PeerRequest req;
	UnicodeString nameText = GadgetTextEntryGetText( m_nameEntry );
	LanguageFilter *filter = TheLanguageFilter;
	if( filter )
		filter->filterLine( nameText );

	AsciiString nameAscii( nameText );
	CustomMatchPreferences *prefs = &m_prefs;
	prefs->setAsciiString( AsciiString( "PreferedGameName" ), nameAscii );
	req.peerRequestType = 9;

	const unsigned short *wide = nameText.str();
	int i = 0;
	while( wide[ i ] )
		++i;
	req.text.assign( wide, wide + i );
	TheGameSpyGame->setGameName( nameText );

	int state = 5;
	AsciiString passwd;
	passwd.translate( GadgetTextEntryGetText( m_passwordEntry ) );
	const char *pwd = passwd.str();
	const char *pwdCur = pwd;
	while( *pwdCur )
		++pwdCur;
	req.password.assign( pwd, pwdCur );

	prefs->setAsciiString( AsciiString( "PreferedGamePassword" ), passwd );
	prefs->setAllowsObserver( true );
	req.allowObservers = 1;
	TheGameSpyGame->setAllowObservers( 1 );

	req.exeCRC = (unsigned)AptLivingWorldWindowIndex(
		TheWritableGlobalData->m_exeCRC, TheWritableGlobalData->m_exeCRC );
	req.iniCRC = TheWritableGlobalData->m_iniCRC;
	req.gameVersion = TheWritableGlobalData->m_extraCRC;
	req.internalIP = TheGameSpyInfo->getInternalIP();
	req.restrictGameList = (unsigned char)TheGameSpyConfig->restrictGamesToLobby();

	req.ladderIP.assign( "localhost", "localhost" + 9 );
	req.ladPort = 0;
	TheGameSpyGame->setLadderIP( AsciiString( req.ladderIP.c_str() ) );
	TheGameSpyGame->setLadderPort( req.ladPort );

	AsciiString &ping = TheGameSpyInfo->getPingString();
	const char *pingStr = ping.str();
	const char *pingEnd = pingStr;
	while( *pingEnd )
		++pingEnd;
	req.hostPingStr.assign( pingStr, pingEnd );

	req.numPlayers = 2;
	if( TheMapCache )
	{
		AsciiString mapName = prefs->getPreferredMap();
		mapName.toLower();
		MapCacheNode *node = TheMapCache->find( mapName );
		if( node != TheMapCache->m_header )
			req.numPlayers = node->m_numPlayers;
	}

	TheGameSpyPeerMessageQueue->addRequest( req );
	m_state = state;
}
