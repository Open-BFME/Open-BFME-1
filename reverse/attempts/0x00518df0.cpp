// ?applySlotPlayerTemplate@BfmeAptScreenLanLobby@@QAE_NPAVGameSlot@@H@Z
// partial score=0.87 date=2026-09-08
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenLanLobby::applySlotPlayerTemplate, retail 0x00518DF0.
// The secondary APT callback updates the LAN slot, sends the new player
// template through LANAPI, and stores the local template in preferences.

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

	GameSlot *getSlot( int index );
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

extern LANAPI *TheLAN;

class BfmeHostGame : public LANGameInfo
{
public:
	char bfmeGo935B();
};

class Open2Option087010
{
public:
	void store( int value );
};

class BfmeAptScreenLanLobby
{
public:
	bool applySlotPlayerTemplate( GameSlot *slot, int playerTemplate );

private:
	unsigned char m_pad[ 0x138 ];
	Open2Option087010 m_playerTemplate;
};

bool BfmeAptScreenLanLobby::applySlotPlayerTemplate(
	GameSlot *slot, int playerTemplate )
{
	if( !TheLAN )
		return false;
	LANGameInfo *game = TheLAN->GetMyGame();
	if( !game )
		return false;

	slot->m_playerTemplate = playerTemplate;
	if( playerTemplate <= -2 )
		slot->m_startPos = -1;

	game->resetAccepted();
	if( ( (BfmeHostGame *)game )->bfmeGo935B() )
	{
		TransportAddress address;
		TheLAN->requestSerializedGameInfo( true, &address );
	}
	else
	{
		AsciiString options;
		options.format( AsciiString( "PlayerTemplate=%d" ),
			slot->m_playerTemplate );
		TheLAN->RequestGameOptions( options, true );
	}

	if( slot->getName().compare(
			game->getSlot( game->getLocalSlotNum() )->getName() ) == 0 )
	{
		m_playerTemplate.store( playerTemplate );
	}
	return true;
}
