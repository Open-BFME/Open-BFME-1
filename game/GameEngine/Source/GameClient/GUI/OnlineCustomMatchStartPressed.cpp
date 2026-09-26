// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
//
// Retail 0x0053DA20, 353 bytes.  This is the Apt custom match screen's copy of
// the StartPressed tail that the landed WOLGameSetupMenu.cpp already carries:
// when every player is ready it queues a PeerRequest of type 15
// (PEERREQUEST_STARTGAME), sends the stats, copies the current staging room
// over TheGameSpyGame and starts it, and otherwise it queues a room UTM whose
// key is "HWS/" and whose value is "true".  The same key and the same pair of
// branches appear in that landed body.
//
// The receiver is the BfmeAptScreenSecondary subobject, which the retail
// constructor at 0x00545310 installs at +0x3C of BfmeAptScreenOnlineCustomMatch.
// The call at +0x51 subtracts 0x3C and lands on
// applyLocalSlotToPreferences@BfmeAptScreenOnlineCustomMatch, matched at
// 0x005392B0, which is what fixes the receiver.  The name keeps the address
// because no caller names the body.

#include <string>
#include <vector>

typedef int Int;
typedef bool Bool;
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

class GameInfo;

class GameSpyStagingRoom
{
public:
	GameSpyStagingRoom &operator=( const GameSpyStagingRoom &other );

	unsigned char m_unmodelled[ 0x460 ];
	Int m_field460;
};

// Slot 0xC0 is amIHost, matched at 0x00630690, and the matched
// getNextSelectablePlayer at 0x004F0B60 reads getCurrentStagingRoom from the
// next slot, 0xC4.
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

// The vtable BFME's GameInfo carries has two slots ahead of the vendored NAT
// shim's, which is why startGame answers at +0x0C here.  Same view as the
// landed WOLGameSetupMenu.cpp uses for the same call.
class BfmeStartGameInfo
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void startGame( Int gameID ) = 0;
};

// upstream layout: game/GameEngine/Source/GameClient/GUI/OnlineCustomMatchUnregister.cpp
class MpGameSetup
{
public:
	virtual void gen525EE0Slot0();
	virtual void gen525EE0Slot1();

private:
	unsigned char m_unmodelled[ 0x130 ];
};

// upstream layout: game/GameEngine/Source/Common/Q3FpsPreferenceGetters.cpp
class Gen000AC870Owner
{
public:
	Int Rva000AC8F0( void );

private:
	unsigned char m_unmodelled[ 0x14 ];
};

class BfmeAptScreenOnlineCustomMatch
{
public:
	void applyLocalSlotToPreferences( void );
};

void SendStatsToOtherPlayers( const GameInfo *game );

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern GameSpyInfo *TheGameSpyInfo;
extern GameSpyStagingRoom *TheGameSpyGame;

// The BfmeAptScreenSecondary subobject at +0x3C of the screen.
class Rva0053DA20Screen
{
public:
	virtual void secondarySlot0() = 0;

	void bfmeStartPressed( Bool everyoneReady, void *window );

	MpGameSetup m_setup;
	Gen000AC870Owner m_preferences;
	Int m_field14C;
};

// ?bfmeStartPressed@Rva0053DA20Screen@@QAEX_NPAX@Z
void Rva0053DA20Screen::bfmeStartPressed( Bool everyoneReady, void * )
{
	m_field14C = 13;

	GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();

	if( everyoneReady )
	{
		m_setup.gen525EE0Slot1();
		( (BfmeAptScreenOnlineCustomMatch *)( (char *)this - 0x3C ) )->applyLocalSlotToPreferences();

		PeerRequest req;
		req.peerRequestType = 15;
		room->m_field460 = m_preferences.Rva000AC8F0();
		req.m_unmodelled[ 0 ] = m_preferences.Rva000AC8F0();
		TheGameSpyPeerMessageQueue->addRequest( req );
		SendStatsToOtherPlayers( (const GameInfo *)room );
		*TheGameSpyGame = *room;
		( (BfmeStartGameInfo *)TheGameSpyGame )->startGame( 0 );
	}
	else
	{
		PeerRequest req;
		req.peerRequestType = 14;
		req.UTM.isStagingRoom = true;
		req.id = "HWS/";
		req.options = "true";
		TheGameSpyPeerMessageQueue->addRequest( req );
	}
}
