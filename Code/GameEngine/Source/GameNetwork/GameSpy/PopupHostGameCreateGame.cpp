// cl: /DNDEBUG /MD /EHsc
// Open-BFME: createGame, retail 0x004D58F0, 915 bytes.
// Converted from gen-dump d_004d58f0. ZH twin is in PopupHostGame.cpp; that TU
// already owns LadderInfo-set and wstring helpers, so this lives here.
// PopupHostGameSystem names this body. BFME drops limitArmies/useStats, runs
// exeCRC through AptLivingWorldWindowIndex, and stores an extra CRC/IP dword
// in the 0x194-byte PeerRequest stagingRoomCreation union.

typedef unsigned short WideChar;
typedef unsigned int size_t;

extern "C" size_t __cdecl strlen( const char *s );

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

public:
	void set( const StringBase<T> &other );

private:
	Header *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	void set( const AsciiString &other )
	{
		StringBase<char>::set( *(const StringBase<char> *)&other );
	}

	void translate( const UnicodeString &src );

	const char *str() const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<WideChar>( other ) {}
	~UnicodeString() {}

	void set( const UnicodeString &other )
	{
		StringBase<WideChar>::set( *(const StringBase<WideChar> *)&other );
	}

	const WideChar *str() const
	{
		char *p = (char *)m_data;
		if ( p )
			p += 8;
		else
			p = (char *)0x0107388C;
		return (const WideChar *)p;
	}
};

class StlStr
{
public:
	StlStr &assign( const char *first, const char *last );
	const char *c_str() const { return m_start; }

private:
	const char *m_start;
	char m_rest[8];
};

class StlWStr
{
public:
	StlWStr &assign( const WideChar *first, const WideChar *last );

private:
	char m_bytes[12];
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
	char m_mid28[0x4C - 0x28];
	StlStr ladderIP;
	StlStr hostPingStr;
	char m_mid64[0xE4 - 0x64];
	unsigned int exeCRC;
	unsigned int iniCRC;
	unsigned int gameVersion;
	unsigned int internalIP;
	unsigned char allowObservers;
	unsigned char useStats;
	unsigned short ladPort;
	char m_padF8[4];
	unsigned char restrictGameList;
	char m_tail[0x194 - 0xFD];
};

typedef char PeerRequestSizeCheck[sizeof(PeerRequest) == 0x194 ? 1 : -1];

class GameWindow;

UnicodeString GadgetTextEntryGetText( GameWindow *window );
bool GadgetCheckBoxIsChecked( GameWindow *window );
void GadgetComboBoxGetSelectedPos( GameWindow *combo, int *pos );
void *GadgetComboBoxGetItemData( GameWindow *combo, int index );

class CustomMatchPreferences
{
public:
	CustomMatchPreferences();
	virtual ~CustomMatchPreferences();
	virtual bool write();
	void setAllowsObserver( bool val );

private:
	char m_map[0x10];
};

typedef char CustomPrefSizeCheck[sizeof(CustomMatchPreferences) == 0x14 ? 1 : -1];

class GameSpyStagingRoom
{
public:
	void setGameName( UnicodeString name )
	{
		StringBase<WideChar> *slot = (StringBase<WideChar> *)( (char *)this + 0x418 );
		slot->set( *(const StringBase<WideChar> *)&name );
	}

	void setAllowObservers( unsigned char val )
	{
		m_allowObservers = val;
	}

	void setLadderIP( AsciiString ip )
	{
		StringBase<char> *slot = (StringBase<char> *)( (char *)this + 0x444 );
		slot->set( *(const StringBase<char> *)&ip );
	}

	void setLadderPort( unsigned short port )
	{
		m_ladderPort = port;
	}

private:
	unsigned char m_head[0x418];
	UnicodeString m_gameName;
	unsigned char m_mid[0x429 - 0x41C];
	unsigned char m_allowObservers;
	unsigned char m_gap[0x444 - 0x42A];
	AsciiString m_ladderIP;
	unsigned char m_pingPad[0x450 - 0x448];
	unsigned short m_ladderPort;
};

extern GameSpyStagingRoom *TheGameSpyGame;

#define GSI_SLOT( n ) virtual void gsiSlot##n() = 0
class GameSpyInfo
{
public:
	GSI_SLOT( 0 ); GSI_SLOT( 1 ); GSI_SLOT( 2 ); GSI_SLOT( 3 );
	GSI_SLOT( 4 ); GSI_SLOT( 5 ); GSI_SLOT( 6 ); GSI_SLOT( 7 );
	GSI_SLOT( 8 ); GSI_SLOT( 9 );
	virtual void setCurrentGroupRoom( int groupID ) = 0;
	GSI_SLOT( 11 ); GSI_SLOT( 12 ); GSI_SLOT( 13 ); GSI_SLOT( 14 );
	GSI_SLOT( 15 ); GSI_SLOT( 16 ); GSI_SLOT( 17 ); GSI_SLOT( 18 );
	GSI_SLOT( 19 ); GSI_SLOT( 20 ); GSI_SLOT( 21 ); GSI_SLOT( 22 );
	GSI_SLOT( 23 ); GSI_SLOT( 24 ); GSI_SLOT( 25 ); GSI_SLOT( 26 );
	GSI_SLOT( 27 ); GSI_SLOT( 28 ); GSI_SLOT( 29 ); GSI_SLOT( 30 );
	GSI_SLOT( 31 ); GSI_SLOT( 32 ); GSI_SLOT( 33 ); GSI_SLOT( 34 );
	GSI_SLOT( 35 ); GSI_SLOT( 36 ); GSI_SLOT( 37 ); GSI_SLOT( 38 );
	GSI_SLOT( 39 ); GSI_SLOT( 40 ); GSI_SLOT( 41 ); GSI_SLOT( 42 );
	GSI_SLOT( 43 ); GSI_SLOT( 44 ); GSI_SLOT( 45 ); GSI_SLOT( 46 );
	GSI_SLOT( 47 ); GSI_SLOT( 48 ); GSI_SLOT( 49 ); GSI_SLOT( 50 );
	GSI_SLOT( 51 ); GSI_SLOT( 52 ); GSI_SLOT( 53 ); GSI_SLOT( 54 );
	GSI_SLOT( 55 ); GSI_SLOT( 56 ); GSI_SLOT( 57 ); GSI_SLOT( 58 );
	GSI_SLOT( 59 ); GSI_SLOT( 60 ); GSI_SLOT( 61 ); GSI_SLOT( 62 );
	GSI_SLOT( 63 ); GSI_SLOT( 64 ); GSI_SLOT( 65 ); GSI_SLOT( 66 );
	GSI_SLOT( 67 ); GSI_SLOT( 68 );
	virtual AsciiString &getPingString() = 0;
	GSI_SLOT( 70 ); GSI_SLOT( 71 ); GSI_SLOT( 72 ); GSI_SLOT( 73 );
	GSI_SLOT( 74 ); GSI_SLOT( 75 ); GSI_SLOT( 76 ); GSI_SLOT( 77 );
	GSI_SLOT( 78 ); GSI_SLOT( 79 ); GSI_SLOT( 80 ); GSI_SLOT( 81 );
	GSI_SLOT( 82 );
	virtual unsigned int getInternalIP() = 0;
};
#undef GSI_SLOT

extern GameSpyInfo *TheGameSpyInfo;

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
	unsigned char m_pad[0xBC8];
	unsigned int m_iniCRC;
	unsigned char m_gap[4];
	unsigned int m_exeCRC;
	unsigned int m_extraCRC;
};

extern GlobalData *TheWritableGlobalData;

int AptLivingWorldWindowIndex( int low, int high );

class LadderInfo
{
public:
	unsigned char m_pad[0x28];
	AsciiString address;
	unsigned short port;
};

class LadderList
{
public:
	const LadderInfo *findLadderByIndex( int index );
};

extern LadderList *TheLadderList;

extern GameWindow *textEntryGameName;
extern GameWindow *checkBoxAllowObservers;
extern GameWindow *comboBoxLadderName;
extern GameWindow *textEntryGamePassword;

// ?createGame@@YAXXZ
void createGame( void )
{
	TheGameSpyInfo->setCurrentGroupRoom( 0 );
	PeerRequest req;
	UnicodeString gameName = GadgetTextEntryGetText( textEntryGameName );
	req.peerRequestType = 9;
	const WideChar *wide = gameName.str();
	int wideLen = 0;
	if ( wide[0] )
	{
		do
			++wideLen;
		while ( wide[wideLen] );
	}
	req.text.assign( wide, wide + wideLen );
	TheGameSpyGame->setGameName( gameName );

	AsciiString passwd;
	passwd.translate( GadgetTextEntryGetText( textEntryGamePassword ) );
	const char *pwd = passwd.str();
	req.password.assign( pwd, pwd + strlen( pwd ) );

	CustomMatchPreferences customPref;
	bool aO = GadgetCheckBoxIsChecked( checkBoxAllowObservers );
	customPref.setAllowsObserver( aO );
	customPref.write();
	req.allowObservers = (unsigned char)aO;
	TheGameSpyGame->setAllowObservers( (unsigned char)aO );

	req.exeCRC = (unsigned int)AptLivingWorldWindowIndex(
		(int)TheWritableGlobalData->m_exeCRC,
		(int)TheWritableGlobalData->m_exeCRC );
	req.iniCRC = TheWritableGlobalData->m_iniCRC;
	req.gameVersion = TheWritableGlobalData->m_extraCRC;
	req.internalIP = TheGameSpyInfo->getInternalIP();
	req.restrictGameList = (unsigned char)TheGameSpyConfig->restrictGamesToLobby();

	int ladderSelectPos = -1;
	GadgetComboBoxGetSelectedPos( comboBoxLadderName, &ladderSelectPos );
	req.ladderIP.assign( "localhost", "localhost" + 9 );
	req.ladPort = 0;
	if ( ladderSelectPos >= 0 )
	{
		int ladderID = (int)GadgetComboBoxGetItemData( comboBoxLadderName, ladderSelectPos );
		if ( ladderID != 0 )
		{
			const LadderInfo *info = TheLadderList->findLadderByIndex( ladderID );
			if ( info )
			{
				const char *addr = info->address.str();
				req.ladderIP.assign( addr, addr + strlen( addr ) );
				req.ladPort = info->port;
			}
		}
	}
	TheGameSpyGame->setLadderIP( req.ladderIP.c_str() );
	TheGameSpyGame->setLadderPort( req.ladPort );

	AsciiString &ping = TheGameSpyInfo->getPingString();
	const char *pingStr = ping.str();
	req.hostPingStr.assign( pingStr, pingStr + strlen( pingStr ) );

	TheGameSpyPeerMessageQueue->addRequest( req );
}
