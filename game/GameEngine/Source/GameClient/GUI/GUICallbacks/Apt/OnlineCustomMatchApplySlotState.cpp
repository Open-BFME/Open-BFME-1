// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineCustomMatch::applySlotState, retail 0x0053D3D0, 507
// bytes.  The secondary APT callback kicks a player through the UTM request
// path, or changes an AI/open slot locally, then resets staging acceptance and
// publishes the new options.  GameSlotConnectInfo is the BFME three-field
// connection shim witnessed by GameSlot::setState's retail call.

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
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}
	void translate( const UnicodeString &src );
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	static const UnicodeString TheEmptyString;

	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
};

extern "C" unsigned int strlen( const char *s );

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

struct GameSlotConnectInfo
{
	int m_nat;
	unsigned short m_port;
};

class GameSlot
{
public:
	virtual void reset();

	UnicodeString getName() const;
	bool isAI() const;
	void setState( SlotState state, UnicodeString name,
		const GameSlotConnectInfo *connectInfo );

	int m_state;
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

class Rva0053D3D0BfmeAptScreenOnlineCustomMatch
{
public:
	bool applySlotState( GameSlot *slot, int state, int unused );
};

typedef char PeerRequestSizeCheck[ sizeof( PeerRequest ) == 0x194 ? 1 : -1 ];

// ?applySlotState@BfmeAptScreenOnlineCustomMatch@@QAE_NPAVGameSlot@@HH@Z
bool Rva0053D3D0BfmeAptScreenOnlineCustomMatch::applySlotState(
	GameSlot *slot, int state, int unused )
{
	if( !TheGameSpyInfo )
		return false;
	GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
	if( !room )
		return false;

	if( slot->m_state == SLOT_PLAYER )
	{
		PeerRequest req;
		req.peerRequestType = 0xD;
		req.m_isStagingRoom = 1;

		AsciiString playerName;
		playerName.translate( slot->getName() );
		const char *name = playerName.str();
		req.nick.assign( name, name + strlen( name ) );
		req.id.assign( "KICK/", "KICK/" + 5 );
		req.options.assign( "true", "true" + 4 );
		TheGameSpyPeerMessageQueue->addRequest( req );

		GameSlotConnectInfo connectInfo = { 0, 0 };
		slot->setState( (SlotState)state, UnicodeString::TheEmptyString,
			&connectInfo );
		room->resetAccepted();
		TheGameSpyInfo->setGameOptions();
		return true;
	}

	if( slot->m_state != state )
	{
		bool wasAI = slot->isAI();
		GameSlotConnectInfo connectInfo = { 0, 0 };
		slot->setState( (SlotState)state, UnicodeString::TheEmptyString,
			&connectInfo );
		bool isAI = slot->isAI();
		if( wasAI ^ isAI )
			room->resetAccepted();
		TheGameSpyInfo->setGameOptions();
		return true;
	}
	return false;
}
