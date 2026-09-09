// cl: /DNDEBUG /MD /EHsc
//
// BfmeAptScreenLanLobby::applySlotTeam, retail 0x00516F00 (265 bytes).
// The vtable at 0x01105A28 routes slot 5 through thunk 0x0001708F to this
// method.  The body updates GameSlot::m_teamNumber, resets LAN acceptance,
// then sends serialized game data for a host or "Team=%d" to the host.

template <typename T> struct StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_max;
	T m_text[ 1 ];
};

template <typename T> class StringBase
{
	friend class AsciiString;

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

	void __cdecl format( AsciiString fmt, ... );
};

class GameSlot
{
public:
	virtual void reset();

	int m_state;
	unsigned char m_accepted;
	unsigned char m_hasMap;
	unsigned char m_muted;
	unsigned char m_pad;
	int m_color;
	int m_startPos;
	int m_playerTemplate;
	int m_teamNumber;

	int getTeamNumber() const
	{
		return m_teamNumber;
	}
};

class LANGameInfo
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

struct TransportAddress
{
	TransportAddress() : m_ip( 0 ), m_port( 0 ) {}

	unsigned int m_ip;
	unsigned short m_port;
};

class LANAPI
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void RequestGameOptions( AsciiString options, bool isPublic,
		const TransportAddress &address = TransportAddress() ) = 0;
	virtual void requestSerializedGameInfo( bool unused, void *destination ) = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual LANGameInfo *GetMyGame() = 0;
};

class BfmeThing935B
{
public:
	char bfmeGo935B();
};

extern LANAPI *TheLAN;

class BfmeAptScreenLanLobby
{
public:
	bool applySlotTeam( GameSlot *slot, int team );
};

// ?applySlotTeam@BfmeAptScreenLanLobby@@QAE_NPAVGameSlot@@H@Z
bool BfmeAptScreenLanLobby::applySlotTeam( GameSlot *slot, int team )
{
	if( !TheLAN )
		return false;
	LANGameInfo *game = TheLAN->GetMyGame();
	if( !game )
		return false;

	slot->m_teamNumber = team;
	game->resetAccepted();
	if( ( (BfmeThing935B *)game )->bfmeGo935B() )
	{
		game->resetAccepted();
		TransportAddress address;
		TheLAN->requestSerializedGameInfo( true, &address );
	}
	else
	{
		AsciiString options;
		options.format( AsciiString( "Team=%d" ), slot->getTeamNumber() );
		TheLAN->RequestGameOptions( options, true );
	}
	return true;
}
