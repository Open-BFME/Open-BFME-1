// ?acceptJoinGame@BfmeAptScreenOnlineCustomMatch@@QAEXPBD@Z
// partial score=0.9935 date=2026-10-31
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// BfmeAptScreenOnlineCustomMatch::acceptJoinGame, retail 0x0053DFC0, 772
// bytes (thiscall ret 4).  The screen's constructor 0x00545310 registers this
// body as the "AptOnline::CustomMatch::AcceptJoinGame" selector through ILT
// 0x0002EFBE, which proves both the identity and the const char* argument.
// BFME1's form of the BFME2 twin AptOnlineCustomMatch::AcceptJoinGame
// (Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineCustomMatch
// AcceptJoinGame.cpp, retail 0x005A5632): in the join-password state (+0x188
// == 10) it reads the password entry (+0x1A4), disables both pop-up windows
// (+0x1A0/+0x1A4) and clears the joining flag (+0x1B4).  An empty password or
// a vanished room (findSelectedStagingRoom 0x0053AB30) closes the movie's
// password box ("CallChild" / "ClosePassword") and reports
// GUI:JoinFailedBadPassword or GUI:HostLeft under GUI:JoinFailedDefault
// through GSMessageBoxOk.  Otherwise it marks the joiner
// (GameSpyInfo vslot +0xB8 markAsStagingRoomJoiner, witnessed by the matched
// OnlineCustomMatchRva0053E870.cpp), copies the room's game name, ladder IP
// and ladder port into TheGameSpyGame, builds the 0x194-byte PeerRequest of
// type 0xB (join), and queues it on TheGameSpyPeerMessageQueue addRequest
// (+0x18); state 11, joining flag 1, room record -1 follow the
// GameSpyCloseOverlay(5) that closes the password overlay.
//
// STATUS (banked partial, score 0.92): this source compiles to exactly 772
// bytes with the retail frame, every call site, literal, EH trylevel store
// and stack slot in place; 65 non-relocation bytes remain, all one family:
// MSVC assigns the eax/edx pair in the opposite order from retail everywhere
// (fetch vtable eax vs edx in the empty-password path, the no-room path
// inverted, the markAsStagingRoomJoiner argument, the getGameName sret
// register) plus three scheduler positions: the setLadderPort this-load
// before the room port read, the req.m_stagingRoomId store sunk after the
// password m_data test, and the second getGameName temp in edx.  Tried and
// NOT the lever: pure-virtual interface slots, direct casts instead of the
// windowManager19E() helper, direct member access for the +0x41C id,
// eh_levers throw()/EHsc/_STLP_NO_EXCEPTIONS (9 trials, same shape).

#include <string>

#include "ascii_string.h"
#include "unicode_string.h"

typedef unsigned short UnsignedShort;

class GameWindow
{
public:
	int winEnable( bool enable );
};

UnicodeString GadgetTextEntryGetText( GameWindow *textEntry );

class GameTextInterface
{
public:
	virtual void slot00() ; virtual void slot01(); virtual void slot02();; virtual void slot03();;
	virtual void slot04();; virtual void slot05();; virtual void slot06();; virtual void slot07();;
	virtual void slot08();; virtual void slot09();;
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;

void GSMessageBoxOk( UnicodeString title, UnicodeString body, void ( *cb )() );

enum GSOverlayType
{
	GSOVERLAY_GAMEPASSWORD = 5
};
void GameSpyCloseOverlay( GSOverlayType overlay );

class GenActionSink
{
public:
	void add( void *owner, const char *name, int count, const char *first,
		int second, int third, int fourth, int fifth );
};

class BfmeMgr19E : public GenActionSink
{
};

// retail 0x012F19E8: the one global definition is
// WindowManager *g_rva012F19E8WindowManager (GUI/WindowManager.cpp).
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

static __forceinline BfmeMgr19E *windowManager19E()
{
	return (BfmeMgr19E *)g_rva012F19E8WindowManager;
}

// AsciiString is the single-pointer StringBase<char>; retail inlines the
// empty test as the null-data / zero-Header-length check rather than the
// out-of-line AsciiString::isEmpty most sites call (StringBase.cpp notes 66
// real isEmpty calls; this body's bytes carry the inline form).
static __forceinline bool asciiStringIsEmpty( const AsciiString &text )
{
	const unsigned char *header = *(const unsigned char *const *)&text;
	return header == 0 || *(const unsigned short *)( header + 4 ) == 0;
}

struct Rva00539110Owner
{
	char m_padding00[ 0x250 ];
	void *m_actionOwner;
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
	GAMESPY_SLOT( 36 ); GAMESPY_SLOT( 37 ); GAMESPY_SLOT( 38 ); GAMESPY_SLOT( 39 );
	GAMESPY_SLOT( 40 ); GAMESPY_SLOT( 41 ); GAMESPY_SLOT( 42 ); GAMESPY_SLOT( 43 );
	GAMESPY_SLOT( 44 ); GAMESPY_SLOT( 45 );
	virtual void markAsStagingRoomJoiner( int id ) = 0;
};
#undef GAMESPY_SLOT

extern GameSpyInfo *TheGameSpyInfo;

class GameSpyStagingRoom;

// The BFME +0x418 staging-room wide-string accessor (matched
// OnlineCustomMatchRva0053E870.cpp spelling; ILT 0x0002C7B4).
class Rva00385F20Room
{
public:
	UnicodeString getGameName() const;
};

class GameSpyStagingRoom
{
public:
	AsciiString getLadderIP() const;
	void setLadderIP( AsciiString ip );
	UnsignedShort getLadderPort() const { return m_ladderPort; }
	void setLadderPort( UnsignedShort port ) { m_ladderPort = port; }

	unsigned char m_head[ 0x41C ];
	int m_field41C;
	unsigned char m_mid[ 0x450 - 0x420 ];
	UnsignedShort m_ladderPort;
};

extern GameSpyStagingRoom *TheGameSpyGame;

// The by-value UnicodeString staging-room setter at 0x004D4880 (matched
// Common/P7ByValueStringSetters.cpp; setGameName's out-of-line spelling).
class Gen004D4880
{
public:
	void bfmeSet( UnicodeString value );
};

class PeerRequest
{
public:
	PeerRequest();
	~PeerRequest();

	enum { PEERREQUEST_JOINSTAGINGROOM = 0xB };

	int peerRequestType;
	_STL::string nick;
	_STL::basic_string< UnsignedShort, _STL::char_traits< UnsignedShort >,
		_STL::allocator< UnsignedShort > > text;
	_STL::string password;
	unsigned char m_mid[ 0xE4 - 0x28 ];
	int m_stagingRoomId;
	unsigned char m_tail[ 0x194 - 0xE8 ];
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

class BfmeAptScreenOnlineCustomMatch
{
public:
	void acceptJoinGame( const char *unused );
	GameSpyStagingRoom *findSelectedStagingRoom();

private:
	unsigned char m_head[ 0x34 ];
	Rva00539110Owner *m_owner;
	unsigned char m_mid[ 0x188 - 0x38 ];
	int m_state;
	unsigned char m_gap[ 0x1A0 - 0x18C ];
	GameWindow *m_nameEntry;
	GameWindow *m_passwordEntry;
	unsigned char m_gap2[ 0x1B4 - 0x1A8 ];
	unsigned char m_field1B4;
	unsigned char m_pad1B5[ 0x1BC - 0x1B5 ];
	int m_field1BC;
	unsigned char m_gap3[ 0x1CC - 0x1C0 ];
	int m_selectedID;
};

// ?acceptJoinGame@BfmeAptScreenOnlineCustomMatch@@QAEXPBD@Z
void BfmeAptScreenOnlineCustomMatch::acceptJoinGame( const char *unused )
{
	if( m_state != 10 )
		return;

	GameWindow *passwordEntry = m_passwordEntry;
	AsciiString password( GadgetTextEntryGetText( passwordEntry ) );
	m_field1B4 = false;
	m_nameEntry->winEnable( false );
	m_passwordEntry->winEnable( false );
	if( asciiStringIsEmpty( password ) )
	{
		( (BfmeMgr19E *)g_rva012F19E8WindowManager )->add( m_owner->m_actionOwner, "CallChild", 1, "ClosePassword", 0, 0, 0, 0 );
		m_state = 1;
		GSMessageBoxOk( TheGameText->fetch( "GUI:JoinFailedDefault" ),
			TheGameText->fetch( "GUI:JoinFailedBadPassword" ), 0 );
		return;
	}

	GameSpyStagingRoom *room = findSelectedStagingRoom();
	if( room == 0 )
	{
		void *actionOwner = m_owner->m_actionOwner;
		( (BfmeMgr19E *)g_rva012F19E8WindowManager )->add( actionOwner, "CallChild", 1, "ClosePassword", 0, 0, 0, 0 );
		m_state = 1;
		GSMessageBoxOk( TheGameText->fetch( "GUI:JoinFailedDefault" ),
			TheGameText->fetch( "GUI:HostLeft" ), 0 );
		return;
	}

	TheGameSpyInfo->markAsStagingRoomJoiner( m_selectedID );
	( (Gen004D4880 *)TheGameSpyGame )->bfmeSet( ( (const Rva00385F20Room *)room )->getGameName() );
	TheGameSpyGame->setLadderIP( room->getLadderIP() );
	TheGameSpyGame->setLadderPort( room->getLadderPort() );
	PeerRequest req;
	req.peerRequestType = PeerRequest::PEERREQUEST_JOINSTAGINGROOM;
	req.text = ( (const Rva00385F20Room *)room )->getGameName().str();
	req.m_stagingRoomId = room->m_field41C;
	req.password = password.str();
	TheGameSpyPeerMessageQueue->addRequest( req );
	GameSpyCloseOverlay( GSOVERLAY_GAMEPASSWORD );
	m_state = 11;
	m_field1B4 = 1;
	m_field1BC = -1;
}
