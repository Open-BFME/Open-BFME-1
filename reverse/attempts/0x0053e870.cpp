// ?joinSelectedStagingRoom@BfmeAptScreenOnlineCustomMatch@@QAEXXZ
// partial score=0.58 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineCustomMatch::joinSelectedStagingRoom, retail 0x0053E870,
// 1090 bytes. Apt ZH WOLLobbyMenu.cpp buttonJoin twin: listbox at +0x18C,
// CRC trio through Rva0009B4B0 / GlobalData +0xBC8/+0xBD0/+0xBD4, unknown
// ladder, reported-full, EnterPassword CallChild, else PeerRequest type 0xB.

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
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class UnicodeString : private StringBase<unsigned short>
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
class GameSpyStagingRoom;
class LadderInfo;

void GadgetListBoxGetSelected( GameWindow *listbox, int *selectList );
void *GadgetListBoxGetItemData( GameWindow *listbox, int row, int column );
void GSMessageBoxOk( UnicodeString title, UnicodeString body, void ( *cb )() );
int Rva0009B4B0( int a, int b );

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;

struct StagingRoomMapNode
{
	unsigned char m_links[ 0x14 ];
	GameSpyStagingRoom *m_room;
};

struct StagingRoomMapIterator
{
	StagingRoomMapIterator( const StagingRoomMapIterator &other );
	StagingRoomMapNode *m_node;
};

struct StagingRoomMap
{
	StagingRoomMapNode *m_header;
	StagingRoomMapIterator find( const int &key );
};

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
	GAMESPY_SLOT( 36 ); GAMESPY_SLOT( 37 );
	virtual StagingRoomMap *getStagingRoomList() = 0;
	GAMESPY_SLOT( 39 ); GAMESPY_SLOT( 40 ); GAMESPY_SLOT( 41 ); GAMESPY_SLOT( 42 );
	GAMESPY_SLOT( 43 ); GAMESPY_SLOT( 44 ); GAMESPY_SLOT( 45 );
	virtual void markAsStagingRoomJoiner( int id ) = 0;
};
#undef GAMESPY_SLOT

extern GameSpyInfo *TheGameSpyInfo;

class GameSpyStagingRoom
{
public:
	UnicodeString getGameName();
	AsciiString getLadderIP();
	void setLadderIP( AsciiString ip );

	unsigned char m_head[ 0x428 ];
	unsigned char m_hasPassword;
	unsigned char m_mid[ 0x430 - 0x429 ];
	unsigned int m_exeCRC;
	unsigned int m_iniCRC;
	unsigned int m_extraCRC;
	unsigned char m_gap[ 0x450 - 0x43C ];
	unsigned short m_ladderPort;
	unsigned char m_padPort[ 2 ];
	unsigned int m_reportedNumPlayers;
	unsigned int m_reportedMaxPlayers;
};

class Gen004D4880
{
public:
	void bfmeSet( UnicodeString value );
};

extern GameSpyStagingRoom *TheGameSpyGame;

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

class LadderList
{
public:
	const LadderInfo *findLadder( const AsciiString &addr, unsigned short port );
};

class BfmeK1058;
extern BfmeK1058 *g_bfmeK1058;

class WindowManager
{
public:
	void add( void *ctx, const char *name, int kind, const char *value,
	          int a, int b, int c, int d );
};

extern WindowManager *g_theWindowManager;

class AptMovieHost
{
public:
	unsigned char m_pad[ 0x250 ];
	void *m_movie;
};

namespace _STL
{
	template <typename T> struct char_traits {};
	template <typename T> class allocator {};
	template <typename T, typename Traits, typename Alloc>
	class basic_string
	{
	public:
		basic_string &operator=( const T *s );
	private:
		char m_bytes[ 12 ];
	};
}

class StlStr
{
public:
	StlStr &operator=( const char *s );
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
	_STL::basic_string<unsigned short, _STL::char_traits<unsigned short>, _STL::allocator<unsigned short> > text;
	StlStr password;
	unsigned char m_mid[ 0xE4 - 0x28 ];
	int m_stagingRoomId;
	unsigned char m_tail[ 0x194 - 0xE8 ];
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

typedef char PeerRequestSizeCheck[ sizeof( PeerRequest ) == 0x194 ? 1 : -1 ];
typedef char RoomLayoutCheck[ (int)&( (GameSpyStagingRoom *)0 )->m_ladderPort == 0x450 ? 1 : -1 ];

class BfmeAptScreenOnlineCustomMatch
{
public:
	void joinSelectedStagingRoom();
	void applyPreferredGameNamePassword( bool fromPrefs );

private:
	unsigned char m_head[ 0x34 ];
	AptMovieHost *m_host;
	unsigned char m_mid[ 0x188 - 0x38 ];
	int m_state;
	GameWindow *m_gameList;
	unsigned char m_gap[ 0x1B4 - 0x190 ];
	unsigned char m_joining;
	unsigned char m_pad1B5[ 3 ];
	unsigned char m_gap1B8[ 0x1BC - 0x1B8 ];
	int m_joinToken;
	unsigned char m_gap1C0[ 0x1C4 - 0x1C0 ];
	int m_clear1C4;
	unsigned char m_gap1C8[ 0x1CC - 0x1C8 ];
	int m_selectedID;
};

void BfmeAptScreenOnlineCustomMatch::joinSelectedStagingRoom()
{
	int selected = 0;
	int selectedID = 0;
	if( m_joining )
		return;

	m_state = 1;
	m_clear1C4 = 0;
	GadgetListBoxGetSelected( m_gameList, &selected );
	if( selected < 0 )
	{
		GSMessageBoxOk( TheGameText->fetch( "GUI:Error", 0 ),
			TheGameText->fetch( "GUI:NoGameSelected", 0 ), 0 );
		return;
	}

	selectedID = (int)GadgetListBoxGetItemData( m_gameList, selected, 0 );
	if( selectedID <= 0 )
	{
		GSMessageBoxOk( TheGameText->fetch( "GUI:Error", 0 ),
			TheGameText->fetch( "GUI:NoGameInfo", 0 ), 0 );
		return;
	}

	StagingRoomMap *rooms = TheGameSpyInfo->getStagingRoomList();
	StagingRoomMapIterator it = rooms->find( selectedID );
	if( it.m_node == rooms->m_header )
		return;

	GameSpyStagingRoom *room = it.m_node->m_room;
	unsigned char exeOk;
	if( !room )
		exeOk = 0;
	else
	{
		unsigned int exeCRC = TheWritableGlobalData->m_exeCRC;
		if( room->m_exeCRC == (unsigned int)Rva0009B4B0( (int)exeCRC, (int)exeCRC ) )
			exeOk = 1;
		else
			exeOk = 0;
	}
	unsigned char iniOk;
	if( !room )
		iniOk = 0;
	else if( room->m_iniCRC == TheWritableGlobalData->m_iniCRC )
		iniOk = 1;
	else
		iniOk = 0;
	unsigned char extraOk;
	if( !room )
		extraOk = 0;
	else if( room->m_extraCRC == TheWritableGlobalData->m_extraCRC )
		extraOk = 1;
	else
		extraOk = 0;
	if( !exeOk || !iniOk || !extraOk )
	{
		GSMessageBoxOk( TheGameText->fetch( "GUI:JoinFailedDefault", 0 ),
			TheGameText->fetch( "GUI:JoinFailedCRCMismatch", 0 ), 0 );
		return;
	}

	unsigned char unknownLadder;
	if( !room->m_ladderPort )
		unknownLadder = 0;
	else if( ( (LadderList *)g_bfmeK1058 )->findLadder(
			room->getLadderIP(), room->m_ladderPort ) == 0 )
		unknownLadder = 1;
	else
		unknownLadder = 0;
	if( unknownLadder )
	{
		GSMessageBoxOk( TheGameText->fetch( "GUI:JoinFailedDefault", 0 ),
			TheGameText->fetch( "GUI:JoinFailedUnknownLadder", 0 ), 0 );
		return;
	}

	if( room->m_reportedNumPlayers == room->m_reportedMaxPlayers )
	{
		GSMessageBoxOk( TheGameText->fetch( "GUI:JoinFailedDefault", 0 ),
			TheGameText->fetch( "GUI:JoinFailedRoomFull", 0 ), 0 );
		return;
	}

	m_joining = 1;
	m_joinToken = -1;
	if( room->m_hasPassword )
	{
		void *movie = m_host->m_movie;
		m_selectedID = selectedID;
		g_theWindowManager->add( movie, "CallChild", 1,
			"EnterPassword", 0, 0, 0, 0 );
		applyPreferredGameNamePassword( 0 );
		m_state = 10;
		return;
	}

	TheGameSpyInfo->markAsStagingRoomJoiner( selectedID );
	( (Gen004D4880 *)TheGameSpyGame )->bfmeSet( room->getGameName() );
	TheGameSpyGame->setLadderIP( room->getLadderIP() );
	TheGameSpyGame->m_ladderPort = room->m_ladderPort;

	PeerRequest req;
	req.peerRequestType = 0xB;
	req.text = it.m_node->m_room->getGameName().str();
	req.m_stagingRoomId = selectedID;
	req.password = "";
	TheGameSpyPeerMessageQueue->addRequest( req );
	m_state = 0xB;
}
