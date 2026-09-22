// ?dup_005409a0@@YAXXZ
// partial score=0.3 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
//
// Candidate for the anonymous 0x005409A0 body (2224 bytes).  The retail
// boundary is the EH prologue at +0x0000 through ret at +0x08AF; the older
// carved extent stopped three bytes early.  The body has no named caller.
//
// The first arm is the post-game disconnect/lobby path proved by the matching
// WOLGameSetupMenuInit twin.  The long arm is the Apt OnlineCustomMatch
// initialization path: current-room setup, host/client slot setup, six peer
// messages, and the state-5/state-11 tail.  Rva005409A0Screen is deliberately
// address-derived: the landed CustomMatch neighbours witness these offsets,
// but do not prove a source-level owner for this body.

#include "StringInline.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

extern "C" unsigned int strlen( const char *text );

// StringInline.h supplies the proven one-pointer BFME string layout and its
// inline forwarding copy/dtor shape.  These empty operation views only expose
// the already-witnessed out-of-line member calls without redeclaring the
// covered string types.
class Rva005409A0AsciiOps
{
public:
	void format( AsciiString format, ... );
	void toLower();
	void translate( const UnicodeString &source );
};

class Rva005409A0UnicodeOps
{
public:
	void set( const UnicodeString &source );
	void translate( const AsciiString &source );
};

static Rva005409A0AsciiOps *asciiOps( AsciiString *value )
{
	return reinterpret_cast<Rva005409A0AsciiOps *>( value );
}

static Rva005409A0UnicodeOps *unicodeOps( UnicodeString *value )
{
	return reinterpret_cast<Rva005409A0UnicodeOps *>( value );
}

class Rva005409A0GameSpyGroupRoom
{
public:
	Rva005409A0GameSpyGroupRoom( const Rva005409A0GameSpyGroupRoom &source );
};

class Rva005409A0Slot
{
public:
	void setPingString( AsciiString pingString );
	void setState( int state, UnicodeString name, const void *connectInfo );
	void setMapAvailability( bool value );
	UnicodeString getName();

	unsigned char m_pad[ 8 ];
	unsigned char m_accepted;
	unsigned char m_beforePreferredColor[ 3 ];
	int m_preferredColor;
	int m_startPosition;
	int m_playerTemplate;
	unsigned char m_beforePing[ 0x38 - 0x1C ];
	int m_ping;
};

class Rva005409A0Room
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void adjustSlotsForMap();

	Rva005409A0Slot *getSlot( int index );
	void setMap( AsciiString mapName );
	void setMapCRC( int value );
	void setMapSize( int value );
	int getMapCRC() const;
	int getMapSize() const;
};

class Rva005409A0Game
{
public:
	unsigned char m_pad[ 0x0D ];
	unsigned char m_inProgress;

	Bool isGameInProgress() const
	{
		return m_inProgress != 0;
	}

	void setGameInProgress( Bool value )
	{
		m_inProgress = value ? 1 : 0;
	}
};

class Rva005409A0Info
{
public:
	virtual void slot00();
	virtual void reset();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28( int value );
	virtual void *slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9C();
	virtual void slotA0();
	virtual void slotA4();
	virtual void slotA8();
	virtual void slotAC();
	virtual void slotB0();
	virtual void slotB4();
	virtual void slotB8();
	virtual void slotBC();
	virtual Bool slotC0();
	virtual Rva005409A0Room *slotC4();
	virtual void slotC8();
	virtual void slotCC();
	virtual void slotD0();
	virtual void slotD4();
	virtual void slotD8();
	virtual void slotDC();
	virtual void slotE0();
	virtual void slotE4( void *value );
	virtual void slotE8();
	virtual void slotEC();
	virtual void slotF0();
	virtual void slotF4();
	virtual void slotF8();
	virtual void slotFC();
	virtual void slot100();
	virtual void slot104();
	virtual void slot108();
	virtual void slot10C();
	virtual void slot110();
	virtual const AsciiString &getPingString();
	virtual void slot118();
	virtual void slot11C();
	virtual void slot120();
	virtual void slot124();
	virtual void slot128();
	virtual void slot12C();
	virtual void slot130();
	virtual void slot134();
	virtual void slot138();
	virtual void slot13C();
	virtual void slot140();
	virtual void slot144();
	virtual void slot148();
	virtual void slot14C();
	virtual void slot150();
	virtual void slot154();
	virtual Bool slot158( int *reason );
};

class Rva005409A0Text
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28();
	virtual UnicodeString fetch( const char *key, Bool *exists = 0 );
};

class Rva005409A0Shell
{
public:
	void popImmediate();
};

class Rva005409A0StlStr
{
public:
	Rva005409A0StlStr &assign( const char *first, const char *last );

private:
	char m_bytes[ 12 ];
};

class Rva005409A0QueueRequest
{
public:
	Rva005409A0QueueRequest();
	~Rva005409A0QueueRequest();
	int peerRequestType;
	Rva005409A0StlStr nick;
	char m_mid[ 0x24 ];
	Rva005409A0StlStr id;
	Rva005409A0StlStr options;
	char m_pad4C[ 0xE4 - 0x4C ];
	unsigned char m_isStagingRoom;
	char m_tail[ 0x194 - 0xE5 ];
};

typedef char Rva005409A0QueueRequestSizeCheck[
	sizeof( Rva005409A0QueueRequest ) == 0x194 ? 1 : -1 ];

class Rva005409A0PeerQueue
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual Bool isConnected();
	virtual void slot14();
	virtual void addRequest( const Rva005409A0QueueRequest &request );
};

class Rva005409A0NAT
{
public:
	void close( int value );
};

class Rva005409A0OptionPreferences
{
public:
	Rva005409A0OptionPreferences();
	~Rva005409A0OptionPreferences();
	int getFirewallBehavior();
};

class Rva005409A0CustomMatchPreferences
{
public:
	int getPreferredColor();
	int getPreferredFaction();
	AsciiString getPreferredMap();
};

class Rva005409A0MapNode
{
public:
	unsigned char m_pad[ 0x3C ];
	int m_fileSize;
	int m_crc;
};

class Rva005409A0MapCache
{
public:
	void update();
	Rva005409A0MapNode *find( const AsciiString &name );

	Rva005409A0MapNode *m_header;
};

class Rva005409A0WindowManager
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3C(); virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C(); virtual void slot50();
	virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual void slot6C(); virtual void slot70(); virtual void slot74();
	virtual void slot78(); virtual void slot7C(); virtual void slot80();
	virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98();
	virtual void slot9C(); virtual void slotA0(); virtual void slotA4();
	virtual void slotA8(); virtual void slotAC(); virtual void slotB0( void *window );
	virtual void slotB4(); virtual void slotB8(); virtual void slotBC();
	virtual void slotC0(); virtual void slotC4(); virtual void slotC8();
	virtual void slotCC(); virtual void slotD0();
	virtual void slotD4( void *window, int id, const UnicodeString &text, int flags );
};

class Rva005409A0Panel
{
public:
	unsigned char m_pad[ 0x250 ];
	void *m_250;
};

class Rva005409A0Member40
{
public:
	void finish( Rva005409A0Room *room, int value );
};

class Rva005409A0Manager
{
public:
	void show( void *value, const char *format, int kind,
		const char *title, const char *body,
		void *a, void *b, void *c );
};

class Rva005409A0Screen
{
public:
	void run();
	void routeBackToLobby();

	unsigned char m_head[ 0x34 ];
	Rva005409A0Panel *m_panel;
	unsigned char m_beforeMember[ 8 ];
	Rva005409A0Member40 m_member40;
	unsigned char m_beforePreferences[ 0x174 - 0x44 ];
	Rva005409A0CustomMatchPreferences m_preferences;
	int m_state;
	unsigned char m_before194[ 0x194 - 0x18C ];
	void *m_window194;
	void *m_room198;
	unsigned char m_before1B8[ 0x1B8 - 0x1A0 ];
	void *m_room1B8;
	unsigned char m_before1D5[ 0x1D5 - 0x1BC ];
	unsigned char m_flag1D5;
};

extern Rva005409A0Game *TheGameSpyGame;
extern Rva005409A0Info *TheGameSpyInfo;
extern Rva005409A0Text *TheGameText;
extern Rva005409A0Shell *TheShell;
extern Rva005409A0PeerQueue *TheGameSpyPeerMessageQueue;
extern Rva005409A0NAT *TheNAT;
extern Rva005409A0MapCache *TheMapCache;
extern Rva005409A0WindowManager *TheWindowManager;
extern Rva005409A0Manager *TheManager;
extern const UnicodeString Rva005409A0EmptyUnicodeString;

void Rva005409A0CloseOverlays();
void Rva005409A0MessageBox( UnicodeString title, UnicodeString body );
void Rva005409A0GlobalSetup();
void Rva005409A0ClearRoom( void *room );

void Rva005409A0Screen::run()
{
	Rva005409A0Game *game = TheGameSpyGame;
	if( game && game->isGameInProgress() )
	{
		game->setGameInProgress( false );
		int disconReason;
		if( TheGameSpyInfo->slot158( &disconReason ) )
		{
			AsciiString disconMunkee;
			asciiOps( &disconMunkee )->format(
				AsciiString( "GUI:GSDisconReason%d" ), disconReason );
			UnicodeString title;
			UnicodeString body;
			unicodeOps( &title )->set(
				TheGameText->fetch( "GUI:GSErrorTitle" ) );
			unicodeOps( &body )->set(
				TheGameText->fetch( disconMunkee.str() ) );
			Rva005409A0CloseOverlays();
			Rva005409A0MessageBox( title, body );
			TheGameSpyInfo->reset();
			TheShell->popImmediate();
			return;
		}

		TheShell->popImmediate();
		if( TheGameSpyPeerMessageQueue &&
			TheGameSpyPeerMessageQueue->isConnected() )
		{
			this->routeBackToLobby();
			return;
		}
		return;
	}

	Rva005409A0GlobalSetup();
	if( TheNAT )
	{
		TheNAT->close( 1 );
		TheNAT = 0;
	}

	m_room1B8 = TheGameSpyInfo->slot2C();
	TheGameSpyInfo->slot28( 0 );
	TheGameSpyInfo->slotE4( m_room198 );
	TheMapCache->update();

	Rva005409A0Room *room = TheGameSpyInfo->slotC4();
	Rva005409A0Slot *localSlot = room->getSlot( 0 );
	localSlot->m_accepted = 1;

	if( TheGameSpyInfo->slotC0() )
	{
		Rva005409A0OptionPreferences optionPreferences;
		Rva005409A0CustomMatchPreferences &preferences = m_preferences;
		localSlot->m_preferredColor = preferences.getPreferredColor();
		localSlot->m_playerTemplate = preferences.getPreferredFaction();
		if( localSlot->m_playerTemplate <= -2 )
			localSlot->m_startPosition = -1;
		localSlot->m_ping = optionPreferences.getFirewallBehavior();

		AsciiString pingString = TheGameSpyInfo->getPingString();
		localSlot->setPingString( pingString );

		for( int index = 0; index < 8; ++index )
		{
			Rva005409A0Slot *slot = room->getSlot( index );
			slot->setState( 0, Rva005409A0EmptyUnicodeString, 0 );
		}

		AsciiString mapName = preferences.getPreferredMap();
		asciiOps( &mapName )->toLower();
		Rva005409A0MapNode *node = TheMapCache->find( mapName );
		if( node != TheMapCache->m_header )
		{
			localSlot->setMapAvailability( true );
			room->setMapCRC( node->m_crc );
			room->setMapSize( node->m_fileSize );
			room->adjustSlotsForMap();
		}
	}
	else
	{
		Rva005409A0OptionPreferences optionPreferences;
		UnicodeString hostName = localSlot->getName();
		AsciiString asciiName;
		asciiOps( &asciiName )->translate( hostName );

		Rva005409A0QueueRequest request;
		request.peerRequestType = 0xD;
		request.m_isStagingRoom = 1;
		request.id.assign( "REQ/", "REQ/" + 4 );
		const char *nickString = asciiName.str();
		request.nick.assign( nickString, nickString + strlen( nickString ) );
		AsciiString options;

		asciiOps( &options )->format( AsciiString( "PlayerTemplate=%d" ),
			m_preferences.getPreferredFaction() );
		const char *optionString = options.str();
		request.options.assign( optionString,
			optionString + strlen( optionString ) );
		TheGameSpyPeerMessageQueue->addRequest( request );

		asciiOps( &options )->format( AsciiString( "Color=%d" ),
			m_preferences.getPreferredColor() );
		optionString = options.str();
		request.options.assign( optionString,
			optionString + strlen( optionString ) );
		TheGameSpyPeerMessageQueue->addRequest( request );

		asciiOps( &options )->format( AsciiString( "NAT=%d" ),
			optionPreferences.getFirewallBehavior() );
		optionString = options.str();
		request.options.assign( optionString,
			optionString + strlen( optionString ) );
		TheGameSpyPeerMessageQueue->addRequest( request );

		asciiOps( &options )->format( AsciiString( "Ping=%s" ),
			TheGameSpyInfo->getPingString().str() );
		optionString = options.str();
		request.options.assign( optionString,
			optionString + strlen( optionString ) );
		TheGameSpyPeerMessageQueue->addRequest( request );

		asciiOps( &options )->format( AsciiString( "LadderRank1v1=%d" ),
			*(int *)0x012F73D0 );
		optionString = options.str();
		request.options.assign( optionString,
			optionString + strlen( optionString ) );
		TheGameSpyPeerMessageQueue->addRequest( request );

		room->setMapCRC( room->getMapCRC() );
		room->setMapSize( room->getMapSize() );
		asciiOps( &options )->format( AsciiString( "LadderRank2v2=%d" ),
			*(int *)0x012F73D4 );
		optionString = options.str();
		request.options.assign( optionString,
			optionString + strlen( optionString ) );
		TheGameSpyPeerMessageQueue->addRequest( request );
	}

	m_member40.finish( room, 0 );
	Rva005409A0ClearRoom( m_room198 );
	UnicodeString empty;
	TheWindowManager->slotD4( m_window194, 0x402F, empty, 0 );
	TheGameSpyInfo->slotCC();
	TheWindowManager->slotB0( m_window194 );

	if( m_state == 5 )
	{
		void *value = m_panel->m_250;
		TheManager->show( value, "g_bfmeFmt1057", 2,
			"state5-title", "state5-body", 0, 0, 0 );
		m_flag1D5 = 0;
		m_state = 6;
	}
	else if( m_state == 11 )
	{
		void *value = m_panel->m_250;
		TheManager->show( value, "g_bfmeFmt1057", 1,
			"state11-title", "state11-body", 0, 0, 0 );
		TheManager->show( value, "g_bfmeFmt1057", 2,
			"state11-title2", "state11-body2", 0, 0, 0 );
		m_state = 12;
	}
}
