// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
//
// Retail 0x0053DEA0, 190 bytes.  When the local player hosts the staging room,
// queue a PeerRequest of type 14 (PEERREQUEST_UTMROOM) carrying the key "EUI/"
// and the value "true".  The retail body reads TheGameSpyPeerMessageQueue at
// 0x012F71C8 and TheGameSpyInfo at 0x012F7194, calls GameSpyInfo slot 0xC0
// (amIHost, matched at 0x00630690), writes the request fields at +0x00, +0x34,
// +0x40 and +0xE4, then calls queue slot 0x18 (addRequest).
//
// The name keeps the address because no caller names this body.  Its ILT thunk
// 0x0042702F appears exactly once in the image, in the dead .rdata pointer run
// at 0x01107474 that also holds the thunks of applySlotColor, applySlotState,
// applySelectedMap and getHostPlayerName, so the body belongs to the
// BfmeAptScreenOnlineCustomMatch compiland but its retail name is unrecovered.

#include <string>
#include <vector>

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
static const Int MAX_SLOTS = 8;

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

// Only slot 0xC0 is named: ?amIHost@GameSpyInfo@@UAE_NXZ is matched at
// 0x00630690, and the matched getNextSelectablePlayer at 0x004F0B60 reads
// getCurrentStagingRoom from the next slot, 0xC4.
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
};
#undef GAMESPY_SLOT

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern GameSpyInfo *TheGameSpyInfo;

// ?Rva0053DEA0SendRoomUtmEUI@@YAXXZ
void Rva0053DEA0SendRoomUtmEUI( void )
{
	if( TheGameSpyPeerMessageQueue && TheGameSpyInfo && TheGameSpyInfo->amIHost() )
	{
		PeerRequest req;
		req.peerRequestType = 14;
		req.UTM.isStagingRoom = true;
		req.id = "EUI/";
		req.options = "true";
		TheGameSpyPeerMessageQueue->addRequest( req );
	}
}
