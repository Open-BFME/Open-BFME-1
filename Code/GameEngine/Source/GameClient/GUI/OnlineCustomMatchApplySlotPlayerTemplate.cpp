// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineCustomMatch::applySlotPlayerTemplate, retail
// 0x0053CE60, 622 bytes. Sibling of applySlotColor: write slot+0x14,
// startPos=-1 when template<=-2, resetAccepted (+0x18) always then again
// on host with setGameOptions and this+0x14=1. Guest UTM type 0xD
// "PlayerTemplate=%d" via range-assign. Tail is the Color name-compare
// plus clearLocalStagingState on this-0x3C. Thunk 0x0000ED4F.

extern "C" unsigned int strlen( const char *s );

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

	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}
	void translate( const UnicodeString &src );
	void __cdecl format( AsciiString fmt, ... );
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	int compare( const UnicodeString &other ) const throw();
};

class GameSlot
{
public:
	virtual void reset();

	UnicodeString getName() const;

	int m_state;
	unsigned char m_accepted;
	unsigned char m_hasMap;
	unsigned char m_muted;
	unsigned char m_pad;
	int m_color;
	int m_startPos;
	int m_playerTemplate;
};

class GameSpyStagingRoom
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual int getLocalSlotNum() const;
	virtual void resetAccepted();
	GameSlot *getSlot( int index );
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
	GAMESPY_SLOT( 24 ); GAMESPY_SLOT( 25 );
	virtual AsciiString getLocalName() = 0;
	GAMESPY_SLOT( 27 ); GAMESPY_SLOT( 28 ); GAMESPY_SLOT( 29 ); GAMESPY_SLOT( 30 );
	GAMESPY_SLOT( 31 ); GAMESPY_SLOT( 32 ); GAMESPY_SLOT( 33 ); GAMESPY_SLOT( 34 );
	GAMESPY_SLOT( 35 ); GAMESPY_SLOT( 36 ); GAMESPY_SLOT( 37 ); GAMESPY_SLOT( 38 );
	GAMESPY_SLOT( 39 ); GAMESPY_SLOT( 40 ); GAMESPY_SLOT( 41 ); GAMESPY_SLOT( 42 );
	GAMESPY_SLOT( 43 ); GAMESPY_SLOT( 44 ); GAMESPY_SLOT( 45 ); GAMESPY_SLOT( 46 );
	GAMESPY_SLOT( 47 );
	virtual bool amIHost() = 0;
	virtual GameSpyStagingRoom *getCurrentStagingRoom() = 0;
	GAMESPY_SLOT( 50 );
	virtual void setGameOptions() = 0;
};
#undef GAMESPY_SLOT

extern GameSpyInfo *TheGameSpyInfo;

class StlStr
{
public:
	StlStr &assign( const char *first, const char *last );

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
	char m_mid[ 0x24 ];
	StlStr id;
	StlStr options;
	char m_pad4C[ 0xE4 - 0x4C ];
	unsigned char m_isStagingRoom;
	char m_tail[ 0x194 - 0xE5 ];
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

class BfmeAptScreenOnlineCustomMatch
{
public:
	bool applySlotPlayerTemplate( GameSlot *slot, int playerTemplate );
	void clearLocalStagingState();

private:
	unsigned char m_pad[ 0x14 ];
	unsigned char m_flag14;
};

typedef char PeerRequestSizeCheck[ sizeof( PeerRequest ) == 0x194 ? 1 : -1 ];

bool BfmeAptScreenOnlineCustomMatch::applySlotPlayerTemplate( GameSlot *slot, int playerTemplate )
{
	if( !TheGameSpyInfo )
		return false;
	GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
	if( !room )
		return false;

	int tmpl = playerTemplate;
	slot->m_playerTemplate = tmpl;
	if( tmpl <= -2 )
		slot->m_startPos = -1;

	room->resetAccepted();
	if( TheGameSpyInfo->amIHost() )
	{
		room->resetAccepted();
		TheGameSpyInfo->setGameOptions();
		m_flag14 = 1;
	}
	else
	{
		AsciiString options;
		options.format( AsciiString( "PlayerTemplate=%d" ), tmpl );
		AsciiString hostName;
		hostName.translate( room->getSlot( 0 )->getName() );

		PeerRequest req;
		req.peerRequestType = 0xD;
		req.m_isStagingRoom = 1;
		req.id.assign( "REQ/", "REQ/" + 4 );
		const char *nickStr = hostName.str();
		req.nick.assign( nickStr, nickStr + strlen( nickStr ) );
		const char *optStr = options.str();
		req.options.assign( optStr, optStr + strlen( optStr ) );
		TheGameSpyPeerMessageQueue->addRequest( req );
	}

	if( slot->getName().compare(
			room->getSlot( room->getLocalSlotNum() )->getName() ) == 0 )
	{
		reinterpret_cast<BfmeAptScreenOnlineCustomMatch *>(
			reinterpret_cast<char *>( this ) - 0x3C )->clearLocalStagingState();
	}
	return true;
}
