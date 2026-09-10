// ?d_00648220@@YAXXZ
// partial score=0.78 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// Retail 0x00648220 is the complete PeerThread staging-server lookup body
// (978 bytes, ending at RET 4).  The registered listingGamesCallback starts
// at 0x0064B6B0 and calls this body through ILT 0x000210D5.  The public
// PeerThreadClass::findServer spelling is already claimed by a different
// 125-byte hash-map body at 0x00613FF0, so this TU uses an honest RVA-only
// owner view and makes no class-identity claim.  Its +0x208 counter and
// +0x20c std::map layout are the ones used by the canonical PeerThread.cpp
// body and by the neighboring matched addServerToMap body.

#include <map>
#include <string>
#include <string.h>

typedef void *PEER;
typedef int PEERBool;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

enum RoomType
{
	TitleRoom,
	GroupRoom,
	StagingRoom
};

enum
{
	PEER_ADD,
	PEER_UPDATE,
	PEER_REMOVE,
	PEER_CLEAR
};

struct _SBServer;
typedef _SBServer *SBServer;

extern "C"
{
	const char *SBServerGetStringValueA(SBServer server, const char *key, const char *def);
	UnsignedInt SBServerGetPrivateInetAddress(SBServer server);
	UnsignedShort SBServerGetPrivateQueryPort(SBServer server);
	UnsignedInt SBServerGetPublicInetAddress(SBServer server);
}

class PeerResponse
{
public:
	enum
	{
		PEERRESPONSE_LOGIN,
		PEERRESPONSE_DISCONNECT,
		PEERRESPONSE_MESSAGE,
		PEERRESPONSE_GROUPROOM,
		PEERRESPONSE_STAGINGROOM,
		PEERRESPONSE_STAGINGROOMLISTCOMPLETE,
		PEERRESPONSE_STAGINGROOMPLAYERINFO,
		PEERRESPONSE_JOINGROUPROOM,
		PEERRESPONSE_CREATESTAGINGROOM,
		PEERRESPONSE_JOINSTAGINGROOM,
		PEERRESPONSE_PLAYERJOIN,
		PEERRESPONSE_PLAYERLEFT,
		PEERRESPONSE_PLAYERCHANGEDNICK,
		PEERRESPONSE_PLAYERINFO,
		PEERRESPONSE_PLAYERCHANGEDFLAGS,
		PEERRESPONSE_ROOMUTM,
		PEERRESPONSE_PLAYERUTM,
		PEERRESPONSE_QUICKMATCHSTATUS,
		PEERRESPONSE_GAMESTART,
		PEERRESPONSE_FAILEDTOHOST,
		PEERRESPONSE_MAX
	} peerResponseType;

	std::string groupRoomName;
	std::string nick;
	std::string oldNick;
	std::wstring text;
	std::string locale;
	std::string stagingServerGameOptions;
	std::wstring stagingServerName;
	std::string stagingServerPingString;
	std::string stagingServerLadderIP;
	std::string stagingRoomMapName;
	std::string stagingRoomPlayerNames[8];
	std::string command;
	std::string commandOptions;

	union
	{
		struct
		{
			Int profileID;
			Int wins;
			Int losses;
			RoomType roomType;
			Int flags;
			UnsignedInt IP;
			Int rankPoints;
			Int side;
			Int preorder;
			UnsignedInt internalIP;
			UnsignedInt externalIP;
		} player;

		struct
		{
			Int id;
			Int action;
			Bool isStaging;
			Bool requiresPassword;
			Bool allowObservers;
			Bool useStats;
			UnsignedInt version;
			UnsignedInt exeCRC;
			UnsignedInt iniCRC;
			UnsignedShort ladderPort;
			Int wins[8];
			Int losses[8];
			Int profileID[8];
			Int faction[8];
			Int color[8];
			Int numPlayers;
			Int numObservers;
			Int maxPlayers;
			Int percentComplete;
		} stagingRoom;

		Int words[143];
	};

	PeerResponse();
	~PeerResponse();
};

typedef char PeerResponseSizeCheck[sizeof(PeerResponse) == 0x330 ? 1 : -1];

class PeerRequest;

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread(void) = 0;
	virtual void endThread(void) = 0;
	virtual Bool isThreadRunning(void) = 0;
	virtual Bool isConnected(void) = 0;
	virtual Bool isConnecting(void) = 0;
	virtual void addRequest(const PeerRequest &) = 0;
	virtual Bool getRequest(PeerRequest &) = 0;
	virtual void addResponse(const PeerResponse &) = 0;
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

#pragma comment(linker, "/alternatename:??0PeerResponse@@QAE@XZ=?j_00042069@@YAXXZ")
#pragma comment(linker, "/alternatename:??1PeerResponse@@QAE@XZ=?j_00044733@@YAXXZ")

class Rva00648220PeerThreadMapView
{
public:
	__forceinline Int addServerToMap(SBServer server);
	Int lookupServer(SBServer server);

private:
	char m_beforeNextStagingServer[0x208];
	Int m_nextStagingServer;
	std::map<Int, SBServer> m_stagingServers;
};

__forceinline Int Rva00648220PeerThreadMapView::addServerToMap(SBServer server)
{
	Int val = m_nextStagingServer++;
	m_stagingServers[val] = server;
	return val;
}

Int Rva00648220PeerThreadMapView::lookupServer(SBServer server)
{
	char tmp[10] = "";
	const char *newName = SBServerGetStringValueA(server, "gamename", tmp);
	UnsignedInt newPrivateIP = SBServerGetPrivateInetAddress(server);
	UnsignedShort newPrivatePort = SBServerGetPrivateQueryPort(server);
	UnsignedInt newPublicIP = SBServerGetPublicInetAddress(server);

	SBServer serverToRemove = NULL;

	for (std::map<Int, SBServer>::iterator it = m_stagingServers.begin();
		it != m_stagingServers.end(); ++it)
	{
		if (it->second == server)
		{
			return it->first;
		}
		else
		{
			const char *oldName = SBServerGetStringValueA(it->second, "gamename", tmp);
			UnsignedInt oldPrivateIP = SBServerGetPrivateInetAddress(it->second);
			UnsignedShort oldPrivatePort = SBServerGetPrivateQueryPort(it->second);
			UnsignedInt oldPublicIP = SBServerGetPublicInetAddress(it->second);
			if (!strcmp(oldName, newName) &&
				oldPrivateIP == newPrivateIP &&
				oldPublicIP == newPublicIP &&
				oldPrivatePort == newPrivatePort)
			{
				serverToRemove = it->second;
			}
		}
	}

	if (serverToRemove)
	{
		Int removedID = 0;
		for (std::map<Int, SBServer>::iterator it = m_stagingServers.begin();
			it != m_stagingServers.end(); ++it)
		{
			if (it->second == serverToRemove)
			{
				removedID = it->first;
				m_stagingServers.erase(it);
				break;
			}
		}

		PeerResponse resp;
		resp.peerResponseType = PeerResponse::PEERRESPONSE_STAGINGROOM;
		resp.stagingRoom.id = removedID;
		resp.stagingRoom.action = PEER_REMOVE;
		resp.stagingRoom.isStaging = true;
		resp.stagingRoom.percentComplete = -1;
		TheGameSpyPeerMessageQueue->addResponse(resp);
	}

	return addServerToMap(server);
}
