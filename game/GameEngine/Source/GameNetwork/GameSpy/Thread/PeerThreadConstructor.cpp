// ??0BFMEPeerThreadView@@QAE@PAVBFMENetworkLock@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Oy /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/nat /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "PreRTS.h"

#include <map>
#include <string>

class BFMENetworkLock;

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

class PeerRequest
{
public:
	PeerRequest();
	~PeerRequest();

private:
	char m_bytes[0x194];
};

typedef std::map<std::string, Int> PlayerStatMap;
struct Gen_t_00644050_p4pod
{
    int a[1];
};
typedef std::map<Int, Gen_t_00644050_p4pod> StagingServerMap;

class BFMEPeerThreadView : public ThreadClass
{
public:
	BFMEPeerThreadView(BFMENetworkLock *lock);
	virtual ~BFMEPeerThreadView();
	virtual void Execute();
	virtual void Thread_Function();

private:
	Bool m_isConnecting;
	Bool m_isConnected;
	char m_pad_52_54[2];
	std::string m_loginName;
	std::string m_originalName;
	std::string m_password;
	std::string m_email;
	Int m_profileID;
	Int m_groupRoomID;
	Bool m_sawCompleteGameList;
	Int m_unknown90;
	PlayerStatMap m_groupRoomStats;
	PlayerStatMap m_stagingRoomStats;
	Bool m_isHosting;
	Bool m_hasPassword;
	char m_pad_AE_B0[2];
	std::string m_mapName;
	Int m_unknownBC;
	std::string m_openStaging;
	std::string m_playerNames[8];
	Int m_exeCRC;
	Int m_iniCRC;
	Int m_gameVersion;
	Int m_unknown138;
	Bool m_useStats;
	std::string m_pingStr;
	std::string m_ladderIP;
	UnsignedShort m_ladderPort;
	char m_pad_15A_15C[2];
	Int m_playerWins[8];
	Int m_playerLosses[8];
	Int m_playerProfileID[8];
	Int m_playerColors[8];
	Int m_playerFactions[8];
	Int m_numPlayers;
	Int m_maxPlayers;
	Int m_numObservers;
	Int m_nextStagingServer;
	StagingServerMap m_stagingServers;
	std::wstring m_localStagingServerName;
	Int m_localRoomID;
	Int m_qmStatus;
	PeerRequest m_qmInfo;
	Bool m_roomJoined;
	void *m_peer;
	Bool m_sawEndOfEnumPlayers;
	Bool m_sawMatchbot;
	char m_pad_3CA_3CC[2];
	std::string m_matchbotName;
	Bool m_unknown3D8;
	char m_pad_3D9_3DC[3];
	Int m_unknown3DC;
	Int m_unknown3E0;
	Bool m_unknown3E4;
	char m_pad_3E5_3E8[3];
	BFMENetworkLock *m_lock;
};

typedef char PeerThreadViewSizeCheck[
	sizeof(BFMEPeerThreadView) == 0x3EC ? 1 : -1];
typedef char PeerRequestSizeCheck[sizeof(PeerRequest) == 0x194 ? 1 : -1];

BFMEPeerThreadView::BFMEPeerThreadView(BFMENetworkLock *lock)
	: ThreadClass(0), m_lock(lock)
{
	m_hasPassword = false;
	m_useStats = false;
	m_roomJoined = false;
	m_gameVersion = 0;
	m_exeCRC = m_iniCRC = 0;
	m_unknown138 = 0;
	m_ladderPort = 0;
	m_localRoomID = 0;
	m_numObservers = 0;
	m_numPlayers = 1;
	m_maxPlayers = 8;
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
	m_isHosting = false;
	m_unknownBC = 0;
	m_openStaging = "openstaging";
	for (Int i = 0; i < 8; ++i)
	{
		m_playerNames[i] = "";
		m_playerColors[i] = 0;
		m_playerFactions[i] = 0;
		m_playerLosses[i] = 0;
		m_playerProfileID[i] = 0;
		m_playerWins[i] = 0;
	}
	m_unknown3D8 = false;
	m_unknown3DC = 0;
	m_unknown3E0 = 0;
	m_unknown3E4 = false;
}
