// ?d_0064cef0@@YAXXZ
// partial score=0.7 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Oy /Ireference/shims/stlp_nodealloc /Ireference/shims/nat /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The named GameSpyPeerMessageQueue::startThread body at 0x0064D780
// allocates 0x3EC bytes and calls ILT 0x0001C00D, whose typed entry is
// BFMEPeerThreadView::BFMEPeerThreadView(BFMENetworkLock *).  That ILT jumps
// directly to the complete 815-byte constructor at 0x0064CEF0.  The retail
// constructor stores vtable 0x011196BC and the final lock argument at +0x3E8.
// The field order below follows the raw member-construction offsets, with
// unknown BFME-only fields kept as honest local views rather than guessed names.

#include "PreRTS.h"

#include <map>
#include <string>

class BFMENetworkLock;

// The BFME retail ThreadClass ABI is the 0x50-byte layout used by the matched
// ThreadClassLifecycle.cpp body: vptr, 0x40-byte name, thread ID, handle and
// priority.  Its source header has an obsolete running byte, so keep this view
// TU-local and call the already matched retail constructor by its real symbol.
class ThreadClass
{
public:
	ThreadClass(const char *name);
	virtual ~ThreadClass();
	virtual void Execute();

protected:
	virtual void Thread_Function() = 0;

private:
	char m_name[0x40];
	UnsignedInt m_threadID;
	void *m_handle;
	Int m_priority;
};

// Only the exact size and constructor ABI are needed here.  The full type and
// its matched constructor live in PeerThread.h/PeerDefs.cpp; no invented
// request member names are used in this constructor view.
class PeerRequest
{
public:
	PeerRequest();

private:
	char m_bytes[0x194];
};

typedef std::map<std::string, Int> PlayerStatMap;
struct _SBServer;
typedef _SBServer *SBServer;
typedef std::map<Int, SBServer> StagingServerMap;

class BFMEPeerThreadView : public ThreadClass
{
public:
	BFMEPeerThreadView(BFMENetworkLock *lock);
	virtual ~BFMEPeerThreadView();
	virtual void Execute();
	virtual void Thread_Function();

private:
	Bool m_isConnecting;                         // +0x50
	Bool m_isConnected;                          // +0x51
	char m_pad_52_54[2];                         // +0x52
	std::string m_loginName;                      // +0x54
	std::string m_originalName;                  // +0x60
	std::string m_password;                      // +0x6C
	std::string m_email;                         // +0x78
	Int m_profileID;                             // +0x84
	Int m_groupRoomID;                           // +0x88
	Bool m_sawCompleteGameList;                  // +0x8C
	Int m_unknown90;                             // +0x90
	PlayerStatMap m_groupRoomStats;              // +0x94
	PlayerStatMap m_stagingRoomStats;            // +0xA0
	Bool m_isHosting;                            // +0xAC
	Bool m_hasPassword;                          // +0xAD
	char m_pad_AE_B0[2];                         // +0xAE
	std::string m_mapName;                       // +0xB0
	Int m_unknownBC;                             // +0xBC
	std::string m_openStaging;                   // +0xC0
	std::string m_playerNames[8];                // +0xCC
	Int m_exeCRC;                                // +0x12C
	Int m_iniCRC;                                // +0x130
	Int m_gameVersion;                           // +0x134
	Int m_unknown138;                            // +0x138
	Bool m_useStats;                             // +0x13C
	std::string m_pingStr;                       // +0x140
	std::string m_ladderIP;                      // +0x14C
	UnsignedShort m_ladderPort;                  // +0x158
	char m_pad_15A_15C[2];                       // +0x15A
	Int m_playerWins[8];                         // +0x15C
	Int m_playerLosses[8];                       // +0x17C
	Int m_playerProfileID[8];                    // +0x19C
	Int m_playerFactions[8];                     // +0x1BC
	Int m_playerColors[8];                       // +0x1DC
	Int m_numPlayers;                            // +0x1FC
	Int m_maxPlayers;                            // +0x200
	Int m_numObservers;                          // +0x204
	Int m_nextStagingServer;                     // +0x208
	StagingServerMap m_stagingServers;           // +0x20C
	std::wstring m_localStagingServerName;       // +0x218
	Int m_localRoomID;                            // +0x224
	Int m_qmStatus;                               // +0x228
	PeerRequest m_qmInfo;                         // +0x22C
	Bool m_roomJoined;                            // +0x3C0
	void *m_peer;                                 // +0x3C4
	Bool m_sawEndOfEnumPlayers;                  // +0x3C8
	Bool m_sawMatchbot;                           // +0x3C9
	char m_pad_3CA_3CC[2];                       // +0x3CA
	std::string m_matchbotName;                  // +0x3CC
	Bool m_unknown3D8;                            // +0x3D8
	char m_pad_3D9_3DC[3];                       // +0x3D9
	Int m_unknown3DC;                             // +0x3DC
	Int m_unknown3E0;                             // +0x3E0
	Bool m_unknown3E4;                            // +0x3E4
	char m_pad_3E5_3E8[3];                       // +0x3E5
	BFMENetworkLock *m_lock;                     // +0x3E8
};

typedef char PeerThreadViewSizeCheck[
	sizeof(BFMEPeerThreadView) == 0x3EC ? 1 : -1];
typedef char PeerRequestSizeCheck[sizeof(PeerRequest) == 0x194 ? 1 : -1];

BFMEPeerThreadView::BFMEPeerThreadView(BFMENetworkLock *lock)
	: ThreadClass(0)
{
	m_roomJoined = false;
	m_isHosting = m_hasPassword = false;
	m_useStats = false;
	m_exeCRC = m_iniCRC = 0;
	m_gameVersion = 0;
	m_ladderPort = 0;
	m_localRoomID = 0;
	m_maxPlayers = 8;
	m_numObservers = 0;
	m_numPlayers = 1;
	m_peer = 0;
	m_sawEndOfEnumPlayers = m_sawMatchbot = false;
	m_sawCompleteGameList = false;
	m_qmStatus = 0;
	m_isConnecting = m_isConnected = false;
	m_unknown90 = 0;
	m_groupRoomID = m_profileID = 0;
	m_nextStagingServer = 1;
	m_stagingServers.clear();
	m_pingStr = "";
	m_mapName = "";
	m_ladderIP = "";
	m_openStaging = "openstaging";
	m_unknownBC = 0;
	for (Int i = 0; i < 8; ++i)
	{
		m_playerNames[i] = "";
		m_playerWins[i] = 0;
		m_playerLosses[i] = 0;
		m_playerProfileID[i] = 0;
		m_playerFactions[i] = 0;
		m_playerColors[i] = 0;
	}
	m_unknown3D8 = false;
	m_unknown3DC = 0;
	m_unknown3E0 = 0;
	m_unknown3E4 = false;
	m_lock = lock;
}

BFMEPeerThreadView::~BFMEPeerThreadView()
{
}

void BFMEPeerThreadView::Execute()
{
	ThreadClass::Execute();
}

void BFMEPeerThreadView::Thread_Function()
{
}
