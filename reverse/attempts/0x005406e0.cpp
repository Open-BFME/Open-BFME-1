// ?enterLobby@BfmeAptScreenOnlineCustomMatch@@QAE_NXZ
// partial score=0.39 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineCustomMatch::enterLobby, retail 0x005406E0, 560 bytes.
// Requires GameList/Lobbies/ChatEntry/Chat windows. leaveStagingRoom, bind
// AptLock image, PeerRequest type 7, CallChild ClosePassword / gotoAndPlay
// _lobby / EnableButtonCreateGame / DisableButtonJoinGame, then refresh.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class Image;
class GameWindow;

class MappedImageCollection
{
public:
	const Image *findImageByName( const AsciiString &name );
};

extern MappedImageCollection *TheMappedImageCollection;

class PeerRequest
{
public:
	PeerRequest();
	~PeerRequest();
	int peerRequestType;
	unsigned char m_pad[ 0xE0 ];
	unsigned char m_fieldE4;
	unsigned char m_tail[ 0x194 - 0xE5 ];
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

#define GAMESPY_SLOT( n ) virtual void gamespySlot##n() = 0
class GameSpyInfo
{
public:
	GAMESPY_SLOT( 0 ); GAMESPY_SLOT( 1 ); GAMESPY_SLOT( 2 ); GAMESPY_SLOT( 3 );
	GAMESPY_SLOT( 4 ); GAMESPY_SLOT( 5 );
	virtual void joinGroupRoom( void *room ) = 0;
	GAMESPY_SLOT( 7 ); GAMESPY_SLOT( 8 );
	virtual void joinBestGroupRoom() = 0;
	GAMESPY_SLOT( 10 ); GAMESPY_SLOT( 11 ); GAMESPY_SLOT( 12 ); GAMESPY_SLOT( 13 );
	GAMESPY_SLOT( 14 );
	virtual void *getCurrentGroupRoom() = 0;
	GAMESPY_SLOT( 16 ); GAMESPY_SLOT( 17 ); GAMESPY_SLOT( 18 ); GAMESPY_SLOT( 19 );
	GAMESPY_SLOT( 20 ); GAMESPY_SLOT( 21 ); GAMESPY_SLOT( 22 ); GAMESPY_SLOT( 23 );
	GAMESPY_SLOT( 24 ); GAMESPY_SLOT( 25 ); GAMESPY_SLOT( 26 ); GAMESPY_SLOT( 27 );
	GAMESPY_SLOT( 28 ); GAMESPY_SLOT( 29 ); GAMESPY_SLOT( 30 ); GAMESPY_SLOT( 31 );
	GAMESPY_SLOT( 32 ); GAMESPY_SLOT( 33 ); GAMESPY_SLOT( 34 ); GAMESPY_SLOT( 35 );
	GAMESPY_SLOT( 36 );
	virtual void clearStagingRoomList() = 0;
	GAMESPY_SLOT( 38 ); GAMESPY_SLOT( 39 ); GAMESPY_SLOT( 40 ); GAMESPY_SLOT( 41 );
	GAMESPY_SLOT( 42 ); GAMESPY_SLOT( 43 );
	virtual void leaveStagingRoom() = 0;
};
#undef GAMESPY_SLOT

extern GameSpyInfo *TheGameSpyInfo;

class GameWindowManager
{
public:
	void bindHost( void *host );
};

extern GameWindowManager *TheWindowManager;

class WindowManager
{
public:
	void add( void *ctx, const char *name, int argc, const char *a0,
	          const char *a1, int a, int b, int c );
};

extern WindowManager *g_theWindowManager;

class AptMovieHost
{
public:
	unsigned char m_pad[ 0x250 ];
	void *m_movie;
};

class BfmeCustomMatchMember40
{
public:
	virtual void slot00();
	virtual void notifyLeave();
};

class Unknown70E4
{
public:
	virtual void s00() = 0; virtual void s01() = 0; virtual void s02() = 0;
	virtual void s03() = 0; virtual void s04() = 0; virtual void s05() = 0;
	virtual void s06() = 0; virtual void s07() = 0; virtual void s08() = 0;
	virtual void s09() = 0; virtual void s0a() = 0; virtual void s0b() = 0;
	virtual void s0c() = 0; virtual void s0d() = 0;
	virtual unsigned char getRestrictFlag() = 0;
};

extern Unknown70E4 *g_012F70E4;

class BfmeAptScreenOnlineCustomMatch
{
public:
	bool enterLobby();
	void handleFlag( bool value );
	void prepareLobby();
	void applyStagingRoomRefresh();

private:
	unsigned char m_head[ 0x34 ];
	AptMovieHost *m_host;
	unsigned char m_gap[ 0x40 - 0x38 ];
	BfmeCustomMatchMember40 m_setup;
	unsigned char m_toState[ 0x188 - 0x44 ];
	int m_state;
	GameWindow *m_gameList;
	GameWindow *m_lobbies;
	GameWindow *m_chatEntry;
	GameWindow *m_chat;
	unsigned char m_afterChat[ 0x1B0 - 0x19C ];
	const Image *m_aptLock;
	unsigned char m_flag1B4;
	unsigned char m_pad1B5[ 3 ];
	int m_field1B8;
	unsigned char m_tail[ 0x1D4 - 0x1BC ];
	unsigned char m_joinEnabled;
};

bool BfmeAptScreenOnlineCustomMatch::enterLobby()
{
	if( m_gameList )
	{
		if( m_lobbies )
		{
			if( m_chatEntry )
			{
				if( m_chat )
				{
					if( TheGameSpyInfo )
						TheGameSpyInfo->leaveStagingRoom();

					m_setup.notifyLeave();
					handleFlag( false );
					TheWindowManager->bindHost( m_host );
					m_aptLock = TheMappedImageCollection->findImageByName( AsciiString( "AptLock" ) );
					m_flag1B4 = 0;

					if( TheGameSpyInfo->getCurrentGroupRoom() )
					{
						TheGameSpyInfo->joinGroupRoom( TheGameSpyInfo->getCurrentGroupRoom() );
						m_field1B8 = 0;
					}
					else
					{
						TheGameSpyInfo->joinBestGroupRoom();
					}

					TheGameSpyInfo->clearStagingRoomList();

					PeerRequest req;
					req.peerRequestType = 7;
					req.m_fieldE4 = g_012F70E4->getRestrictFlag();
					TheGameSpyPeerMessageQueue->addRequest( req );

					prepareLobby();
					applyStagingRoomRefresh();

					void *movie = m_host->m_movie;
					g_theWindowManager->add( movie, "CallChild", 1, "ClosePassword", 0, 0, 0, 0 );
					g_theWindowManager->add( movie, "CallChild", 2, "gotoAndPlay", "_lobby", 0, 0, 0 );
					g_theWindowManager->add( movie, "CallChild", 1, "EnableButtonCreateGame", 0, 0, 0, 0 );
					g_theWindowManager->add( movie, "CallChild", 1, "DisableButtonJoinGame", 0, 0, 0, 0 );

					m_joinEnabled = 0;
					m_state = 1;
					return true;
				}
			}
		}
	}
	return false;
}
