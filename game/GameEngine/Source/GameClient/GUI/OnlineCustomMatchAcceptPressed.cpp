// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
//
// Retail 0x0053DBE0, 554 bytes.  The Apt custom match screen's accept action.
// It forwards its flag to the screen body at 0x00539110, marks the local slot
// accepted, and then splits: the host queues a room UTM whose key is "DUI/",
// and everyone else translates the host nick and queues a player UTM whose key
// is "accept".  The landed WOLGameSetupMenu.cpp carries the same client half,
// down to the "accept" key, the nick and the "true" value.
//
// The receiver is the BfmeAptScreenSecondary subobject the retail constructor
// at 0x00545310 installs at +0x3C of BfmeAptScreenOnlineCustomMatch, which is
// why the first call subtracts 0x3C.  That callee is pinned in
// targets/game/reverse/symbols.csv at ILT 0x0000C955 as ?handle@Gen0000C955@@QAEX_N@Z.
// No caller names this body, so its name keeps the address.

#include <string>
#include <vector>

typedef int Int;
typedef bool Bool;
static const Int MAX_SLOTS = 8;

extern const char Rva006A16B0Empty[];

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
template <typename T> class StringBase
{
protected:
	StringBase() : m_data( 0 ) {}
	~StringBase() { releaseBuffer(); }

	void *m_data;

private:
	void releaseBuffer();
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	~UnicodeString() {}
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	~AsciiString() {}

	void translate( const UnicodeString &other );

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : Rva006A16B0Empty;
	}
};

// upstream layout: inputs/reference/shims/nat/GameNetwork/GameSpy/PeerThread.h
class PeerRequest
{
public:
	PeerRequest();
	~PeerRequest();

	Int peerRequestType;

	std::string nick;
	std::wstring text;
	std::string password;
	std::string email;
	std::string id;
	std::string options;
	std::string ladderIP;
	std::string hostPingStr;
	std::string gameOptsMapName;
	std::string gameOptsPlayerNames[ MAX_SLOTS ];

	std::vector<bool> qmMaps;

	union
	{
		struct
		{
			Bool isStagingRoom;
		} UTM;

		Int m_unmodelled[ 44 ];
	};
};

typedef char PeerRequestSizeCheck[ sizeof( PeerRequest ) == 0x194 ? 1 : -1 ];

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefsImplementation.h
class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread() = 0;
	virtual void endThread() = 0;
	virtual Int isThreadRunning() = 0;
	virtual Int isConnected() = 0;
	virtual Int isConnecting() = 0;
	virtual void addRequest( const PeerRequest &request ) = 0;
};

class GameSlot
{
public:
	UnicodeString getName() const;

	void setAccept() { m_accepted = true; }

private:
	unsigned char m_unmodelled[ 8 ];
	Bool m_accepted;
};

// GameInfo's BFME vtable has two leading slots that are absent from the
// vendored NAT shim, which puts amIHost at +0x10 and getLocalSlotNum at +0x14.
// Same view the matched getNextSelectablePlayer at 0x004F0B60 records.
class GameInfo
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00C() = 0;
	virtual Bool amIHost() = 0;
	virtual Int getLocalSlotNum() = 0;

	GameSlot *getSlot( Int index );
};

class GameSpyStagingRoom : public GameInfo
{
};

// Slot 0xC0 is amIHost, matched at 0x00630690, and getCurrentStagingRoom sits
// in the next slot, 0xC4.
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
	virtual Bool amIHost() = 0;
	virtual GameSpyStagingRoom *getCurrentStagingRoom() = 0;
};
#undef GAMESPY_SLOT

// Pinned at ILT 0x0000C955 in targets/game/reverse/symbols.csv; the retail body sits at
// 0x00539110 and reads the screen field at +0x1D0.
class Gen0000C955
{
public:
	void handle( Bool value );
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern GameSpyInfo *TheGameSpyInfo;

// The BfmeAptScreenSecondary subobject at +0x3C of the screen.
class Rva0053DBE0Screen
{
public:
	virtual void secondarySlot0() = 0;

	void bfmeAcceptPressed( Bool accepted );
};

// ?bfmeAcceptPressed@Rva0053DBE0Screen@@QAEX_N@Z
void Rva0053DBE0Screen::bfmeAcceptPressed( Bool accepted )
{
	( (Gen0000C955 *)( (char *)this - 0x3C ) )->handle( accepted );

	if( !accepted )
		return;

	GameSlot *localSlot = TheGameSpyInfo->getCurrentStagingRoom()->getSlot(
		TheGameSpyInfo->getCurrentStagingRoom()->getLocalSlotNum() );
	if( localSlot )
		localSlot->setAccept();

	if( !TheGameSpyPeerMessageQueue )
		return;

	if( TheGameSpyInfo->amIHost() )
	{
		PeerRequest req;
		req.peerRequestType = 14;
		req.UTM.isStagingRoom = true;
		req.id = "DUI/";
		req.options = "true";
		TheGameSpyPeerMessageQueue->addRequest( req );
	}
	else if( TheGameSpyInfo )
	{
		UnicodeString hostName = TheGameSpyInfo->getCurrentStagingRoom()->getSlot( 0 )->getName();
		AsciiString asciiName;
		asciiName.translate( hostName );
		PeerRequest req;
		req.peerRequestType = 13;
		req.UTM.isStagingRoom = true;
		req.id = "accept";
		req.nick = asciiName.str();
		req.options = "true";
		TheGameSpyPeerMessageQueue->addRequest( req );
	}
}
