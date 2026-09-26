// ?listingGamesCallback@@YAXPAXHPBDPAU_SBServer@@HHH0@Z
// partial score=0.9935 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// PeerThread.cpp reconstruction bank. GPL-3.0-or-later, derived from EA Zero Hour.
// Identity and boundaries: build/unclaimed_map/astra_J/IDENTITY.md.
#include <string>
#include <vector>
#include <map>
#include <string.h>
#include <stdlib.h>
#include "ascii_string.h"
// TU inline definition from the observed buffer/null string access at 64BBB8.
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef void *PEER;
typedef int PEERBool;
enum RoomType { TitleRoom, GroupRoom, StagingRoom };
enum { MAX_SLOTS=8 };
enum { PEER_ADD, PEER_UPDATE, PEER_REMOVE, PEER_CLEAR };
enum SerialAuthResult
{
	SERIAL_NONEXISTENT,
	SERIAL_AUTHFAILED,
	SERIAL_BANNED,
	SERIAL_OK
};

// this class encapsulates a request for the peer thread
class PeerRequest
{
public:
	enum
	{
		PEERREQUEST_LOGIN,				// attempt to login
		PEERREQUEST_LOGOUT,				// log out if connected
		PEERREQUEST_MESSAGEPLAYER,
		PEERREQUEST_MESSAGEROOM,
		PEERREQUEST_JOINGROUPROOM,
		PEERREQUEST_LEAVEGROUPROOM,
		PEERREQUEST_STARTGAMELIST,
		PEERREQUEST_STOPGAMELIST,
		PEERREQUEST_CREATESTAGINGROOM,
		PEERREQUEST_SETGAMEOPTIONS,
		PEERREQUEST_JOINSTAGINGROOM,
		PEERREQUEST_LEAVESTAGINGROOM,
		// Both NAT call sites that the reference writes as PEERREQUEST_UTMPLAYER
		// -- notifyTargetOfProbe and notifyUsersOfConnectionFailed -- store 13,
		// not 12. Two independent sites agreeing is much better evidence for the
		// enum having gained a value ahead of UTMPLAYER than for both of them
		// having switched to UTMROOM. Where the extra value really sits is not
		// recoverable from those two stores; putting it here is the minimal
		// assumption, since it shifts UTMPLAYER and everything after it and
		// leaves the values before it alone.
		PEERREQUEST_BFMEUNKNOWN,
		PEERREQUEST_UTMPLAYER,
		PEERREQUEST_UTMROOM,
		PEERREQUEST_STARTGAME,
		PEERREQUEST_STARTQUICKMATCH,
		PEERREQUEST_WIDENQUICKMATCHSEARCH,
		PEERREQUEST_STOPQUICKMATCH,
		PEERREQUEST_PUSHSTATS,
		PEERREQUEST_GETEXTENDEDSTAGINGROOMINFO,
		PEERREQUEST_MAX
	} peerRequestType;

	std::string nick;	// only used by login, but must be outside the union b/c of copy constructor
	std::wstring text;  // can't be in a union
	std::string password;
	std::string email;
	std::string id;
	
	// gameopts
	std::string options; // full string for UTMs
	std::string ladderIP;
	std::string hostPingStr;
	std::string gameOptsMapName;
	std::string gameOptsPlayerNames[MAX_SLOTS];

	std::vector<bool> qmMaps;

	union
	{
		struct
		{
			Int profileID;
		} login;

		struct
		{
			Int id;
		} groupRoom;
		
		struct
		{
			Bool restrictGameList;
		} gameList;

		struct
		{
			Bool isAction;
		} message;

		struct
		{
			Int id;
		} stagingRoom;

		struct
		{
			UnsignedInt exeCRC;
			UnsignedInt iniCRC;
			UnsignedInt gameVersion;
			Bool allowObservers;
      Bool useStats;
			UnsignedShort ladPort;
			UnsignedInt ladPassCRC;
			Bool restrictGameList;
		} stagingRoomCreation;

		struct
		{
			Int wins[MAX_SLOTS];
			Int losses[MAX_SLOTS];
			Int profileID[MAX_SLOTS];
			Int faction[MAX_SLOTS];
			Int color[MAX_SLOTS];
			Int numPlayers;
			Int maxPlayers;
			Int numObservers;
			// BFME's PeerRequest is four bytes larger than the reference's, and
			// the extra dword is somewhere at or after the union: retail puts
			// `id` at +0x34 and the UTM union at +0xE4, both exactly where the
			// reference's layout puts them. gameOptions is the union's largest
			// member at 172 bytes, so one more Int here is what moves sizeof
			// from 0x190 to the 0x194 retail's callers reserve. Nothing landed
			// against this header reads gameOptions, so which field BFME
			// actually added is still open -- only the size is pinned.
			Int bfmeExtraGameOption;
		} gameOptions;

		struct
		{
			Bool isStagingRoom;
		} UTM;

		struct
		{
			Int minPointPercentage, maxPointPercentage, points;
			Int widenTime;
			Int ladderID;
			UnsignedInt ladderPassCRC;
			Int maxPing;
			Int maxDiscons, discons;
			char pings[17]; // 8 servers (0-ff), 1 NULL
			Int numPlayers;
			Int botID;
			Int roomID;
			Int side;
			Int color;
			Int NAT;
			UnsignedInt exeCRC;
			UnsignedInt iniCRC;
			UnsignedInt Rva0064F68CCmdCRC;
		} QM;

		struct
		{
			Int locale;
			Int wins;
			Int losses;
			Int rankPoints;
			Int side;
			Bool preorder;
		} statsToPush;

	};
	PeerRequest();
	~PeerRequest();
};

//-------------------------------------------------------------------------

enum DisconnectReason
{
	DISCONNECT_NICKTAKEN = 1,
	DISCONNECT_BADNICK,
	DISCONNECT_LOSTCON,
	DISCONNECT_COULDNOTCONNECT,
	DISCONNECT_GP_LOGIN_TIMEOUT,
	DISCONNECT_GP_LOGIN_BAD_NICK,
	DISCONNECT_GP_LOGIN_BAD_EMAIL,
	DISCONNECT_GP_LOGIN_BAD_PASSWORD,
	DISCONNECT_GP_LOGIN_BAD_PROFILE,
	DISCONNECT_GP_LOGIN_PROFILE_DELETED,
	DISCONNECT_GP_LOGIN_CONNECTION_FAILED,
	DISCONNECT_GP_LOGIN_SERVER_AUTH_FAILED,
	DISCONNECT_SERIAL_INVALID,
	DISCONNECT_SERIAL_NOT_PRESENT,
	DISCONNECT_SERIAL_BANNED,
	DISCONNECT_GP_NEWUSER_BAD_NICK,
	DISCONNECT_GP_NEWUSER_BAD_PASSWORD,
	DISCONNECT_GP_NEWPROFILE_BAD_NICK,
	DISCONNECT_GP_NEWPROFILE_BAD_OLD_NICK,
	DISCONNECT_MAX,
};

enum QMStatus
{
	QM_IDLE,
	QM_JOININGQMCHANNEL,
	QM_LOOKINGFORBOT,
	QM_SENTINFO,
	QM_WORKING,
	QM_POOLSIZE,
	QM_WIDENINGSEARCH,
	QM_MATCHED,
	QM_INCHANNEL,
	QM_NEGOTIATINGFIREWALLS,
	QM_STARTINGGAME,
	QM_COULDNOTFINDBOT,
	QM_COULDNOTFINDCHANNEL,
	QM_COULDNOTNEGOTIATEFIREWALLS,
	QM_STOPPED,
};

// this class encapsulates an action the peer thread wants from the UI
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

	std::string groupRoomName; // can't be in union

	std::string nick;   // can't be in a union
	std::string oldNick;   // can't be in a union
	std::wstring text;  // can't be in a union
	std::string locale; // can't be in a union

	std::string stagingServerGameOptions; // full string from UTMs

	// game opts sent with PEERRESPONSE_STAGINGROOM
	std::wstring stagingServerName;
	std::string stagingServerPingString;
	std::string stagingServerLadderIP;
	std::string stagingRoomMapName;

	// game opts sent with PEERRESPONSE_STAGINGROOMPLAYERINFO
	std::string stagingRoomPlayerNames[MAX_SLOTS];

	std::string command;
	std::string commandOptions;

	union
	{
		struct
		{
			DisconnectReason reason;
		} discon;

		struct
		{
			Int id;
			Int numWaiting;
			Int maxWaiting;
			Int numGames;
			Int numPlaying;
		} groupRoom;

		struct
		{
			Int id;
			Bool ok;
		} joinGroupRoom;
		
		struct
		{
			Int result;
		} createStagingRoom;
		
		struct
		{
			Int id;
			Bool ok;
			Bool isHostPresent;
			Int result; // for failures
		} joinStagingRoom;
		
		struct
		{
			Bool isPrivate;
			Bool isAction;
			Int profileID;
		} message;

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
			UnsignedInt internalIP; // for us, on connection
			UnsignedInt externalIP; // for us, on connection
		} player;

		struct
		{
			Int id;
			Int action;
			Bool isStaging;
			Bool requiresPassword;
			Bool allowObservers;
      Bool Rva0064B8F0PadFF;
			UnsignedInt version;
			UnsignedInt exeCRC;
			UnsignedInt iniCRC;
			UnsignedInt Rva0064BA37CmdCRC;
			UnsignedShort ladderPort;
			Int wins[MAX_SLOTS];
			Int losses[MAX_SLOTS];
			Int profileID[MAX_SLOTS];
			Int faction[MAX_SLOTS];
			Int color[MAX_SLOTS];
			Int numPlayers;
			Int numObservers;
			Int maxPlayers;
			Int percentComplete;
			Int Rva0064BAF6Teamplay;
		} stagingRoom;

		struct
		{
			QMStatus status;
			Int poolSize;
			Int mapIdx; // when matched
			Int seed; // when matched
			UnsignedInt IP[MAX_SLOTS]; // when matched
			Int side[MAX_SLOTS]; // when matched
			Int color[MAX_SLOTS]; // when matched
			Int nat[MAX_SLOTS];
		} qmStatus;
		Int Rva0064B6B0Payload[143];
	};
	PeerResponse();
	~PeerResponse();
};

//-------------------------------------------------------------------------

// this is the actual message queue used to pass messages between threads
class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread( void ) = 0;
	virtual void endThread( void ) = 0;
	virtual Bool isThreadRunning( void ) = 0;
	virtual Bool isConnected( void ) = 0;
	virtual Bool isConnecting( void ) = 0;

	virtual void addRequest( const PeerRequest& req ) = 0;
	virtual Bool getRequest( PeerRequest& req ) = 0;

	virtual void addResponse( const PeerResponse& resp ) = 0;
	virtual Bool getResponse( PeerResponse& resp ) = 0;

	virtual SerialAuthResult getSerialAuthResult( void ) = 0;

	static GameSpyPeerMessageQueueInterface* createNewMessageQueue( void );
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;


typedef char RequestSize[sizeof(PeerRequest)==0x194 ? 1:-1];
typedef char ResponseSize[sizeof(PeerResponse)==0x330 ? 1:-1];
struct _SBServer;
typedef _SBServer *SBServer;
extern "C" {
 const char *SBServerGetStringValueA(SBServer,const char*,const char*);
 const char *SBServerGetPlayerStringValueA(SBServer,int,const char*,const char*);
 int SBServerGetIntValueA(SBServer,const char*,int);
 int SBServerGetPlayerIntValueA(SBServer,int,const char*,int);
 int SBServerHasBasicKeys(SBServer);
}
#define SBServerGetStringValue SBServerGetStringValueA
#define SBServerGetPlayerStringValue SBServerGetPlayerStringValueA
#define SBServerGetIntValue SBServerGetIntValueA
#define SBServerGetPlayerIntValue SBServerGetPlayerIntValueA
#define FALSE false
#define TRUE true
#define DEBUG_LOG(x)
#define DEBUG_ASSERTCRASH(x,y)
std::wstring MultiByteToWideCharSingleLine(const char *);
// Aligned call at 64B790 takes vector/string storage and the closedplaying literal.
bool Rva0063B2A0(const std::string &,const char *);
extern int Rva012B96D8;
extern unsigned Rva012F76EC;
class Rva012F1464View {
public:
 virtual void slot00()=0;
 virtual void slot01()=0;
 virtual void slot02()=0;
 virtual void slot03()=0;
 virtual void slot04()=0;
 virtual void slot05()=0;
 virtual void slot06()=0;
 virtual void slot07()=0;
 virtual void slot08()=0;
 virtual void slot09()=0;
 virtual void slot10()=0;
 virtual void slot11()=0;
 virtual void slot12()=0;
 virtual void slot13()=0;
 virtual void slot14()=0;
 virtual void slot15()=0;
 virtual void slot16()=0;
 virtual void slot17()=0;
 virtual void slot18()=0;
 virtual void slot19()=0;
 virtual void slot20()=0;
 virtual void slot21()=0;
 virtual void slot22()=0;
 virtual void slot23()=0;
 virtual void slot24()=0;
 virtual void slot25()=0;

 virtual unsigned rva0064BCFC()=0;
};
extern Rva012F1464View *Rva012F1464;
class PeerThreadClass {
public:
 char Rva0064B80DOpaque[0x8c];
 bool m_sawCompleteGameList;
 bool getSawCompleteGameList() { return m_sawCompleteGameList; }
 void setSawCompleteGameList(bool v) { m_sawCompleteGameList=v; }
 int Rva00648220(SBServer);
 int Rva00647F90(SBServer);
 void Rva00646240();
};
#define EXECRC_STR		"exeCRC"
#define INICRC_STR		"iniCRC"
#define PW_STR				"pw"
#define OBS_STR				"obs"
#define USE_STATS_STR "stat"
#define LADIP_STR			"ladIP"
#define LADPORT_STR		"ladPort"
#define PINGSTR_STR		"pings"
#define NUMPLAYER_STR	"numRealPlayers"
#define MAXPLAYER_STR	"maxRealPlayers"
#define NUMOBS_STR		"numObservers"
#define NAME__STR			"name"
#define FACTION__STR	"faction"
#define COLOR__STR		"color"
#define WINS__STR			"wins"
#define LOSSES__STR		"losses"

void listingGamesCallback(PEER peer, PEERBool success, const char * name, SBServer server, PEERBool staging, int msg, Int percentListed, void * param)
{
	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t || !success)
		return;

#ifdef DEBUG_LOGGING
	AsciiString cmdStr = "<Unknown>";
	switch(msg)
	{
		case PEER_ADD:
			cmdStr = "PEER_ADD";
			break;
		case PEER_UPDATE:
			cmdStr = "PEER_UPDATE";
			break;
		case PEER_REMOVE:
			cmdStr = "PEER_REMOVE";
			break;
		case PEER_CLEAR:
			cmdStr = "PEER_CLEAR";
			break;
		case PEER_COMPLETE:
			cmdStr = "PEER_COMPLETE";
			break;
	}
	DEBUG_LOG(("listingGamesCallback() - doing command %s on server %X\n", cmdStr.str(), server));
#endif // DEBUG_LOGGING

//	PeerThreadClass *t = (PeerThreadClass *)param;
	DEBUG_ASSERTCRASH(name || msg==PEER_CLEAR || msg==PEER_COMPLETE, ("Game has no name!\n"));
	if (!t || !success || (!name && (msg == PEER_ADD || msg == PEER_UPDATE)))
	{
		DEBUG_LOG(("Bailing from listingGamesCallback() - success=%d, name=%X, server=%X, msg=%X\n", success, name, server, msg));
		return;
	}
	if (!name)
		name = "bogus";

	if (server && (msg == PEER_ADD || msg == PEER_UPDATE))
	{
		DEBUG_ASSERTCRASH(*(void **)((char *)server + 0x18), ("Looking at an already-freed server for msg type %d!", msg));
		if (!*(void **)((char *)server + 0x18))
        { msg = PEER_REMOVE; }
        else {
            std::string mode = std::string();
            mode=SBServerGetStringValue(server,"gamemode","");
            if (Rva0063B2A0(mode,"closedplaying")) msg=PEER_REMOVE;
        }
	}

	if (server && success && (msg == PEER_ADD || msg == PEER_UPDATE))
	{
		DEBUG_LOG(("Game name is '%s'\n", name));
		const char *newname = SBServerGetStringValue(server, "gamename", (char *)name);
		if (strcmp(newname, "lotrbme"))
			name = newname;
		DEBUG_LOG(("Game name is now '%s'\n", name));
	}

	DEBUG_LOG(("listingGamesCallback - got percent complete %d\n", percentListed));
	if (percentListed == 100)
	{
		if (!t->getSawCompleteGameList())
		{
			t->setSawCompleteGameList(TRUE);
			PeerResponse completeResp;
			completeResp.peerResponseType = PeerResponse::PEERRESPONSE_STAGINGROOMLISTCOMPLETE;
			TheGameSpyPeerMessageQueue->addResponse(completeResp);
		}
	}

	AsciiString gameName = name;
	AsciiString tmp = gameName;
	AsciiString hostName;
	tmp.nextToken(&hostName, " ");
	const char *firstSpace = gameName.find(' ');
	if(firstSpace)
	{
		gameName.set(firstSpace + 1);
		//gameName.trim();
		DEBUG_LOG(("Hostname/Gamename split leaves '%s' hosting '%s'\n", hostName.str(), gameName.str()));
	}
	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_STAGINGROOM;
	resp.stagingRoom.action = msg;
	resp.stagingRoom.isStaging = staging;
	resp.stagingRoom.percentComplete = percentListed;

	if (server && (msg == PEER_ADD || msg == PEER_UPDATE))
	{
		Bool hasPassword = (Bool)SBServerGetIntValue(server, PW_STR, FALSE);
		Bool allowObservers = (Bool)SBServerGetIntValue(server, OBS_STR, FALSE);

		const char *verStr = SBServerGetStringValue(server, "gamever", "000000");
		const char *exeStr = SBServerGetStringValue(server, EXECRC_STR, "000000");
		const char *iniStr = SBServerGetStringValue(server, INICRC_STR, "000000");
		const char *cmdStr = SBServerGetStringValue(server, "cmdCRC", "000000");
		const char *ladIPStr = SBServerGetStringValue(server, LADIP_STR, "000000");
		const char *pingStr = SBServerGetStringValue(server, PINGSTR_STR, "FFFFFFFFFFFFFFFF");
		UnsignedShort ladPort = (UnsignedShort)SBServerGetIntValue(server, LADPORT_STR, 0);
		UnsignedInt verVal = strtoul(verStr, NULL, 10);
		UnsignedInt exeVal = strtoul(exeStr, NULL, 10);
		UnsignedInt iniVal = strtoul(iniStr, NULL, 10);
		UnsignedInt cmdVal = strtoul(cmdStr, NULL, 10);
		resp.stagingRoom.requiresPassword = hasPassword;
		resp.stagingRoom.allowObservers = allowObservers;

		resp.stagingRoom.version = verVal;
		resp.stagingRoom.exeCRC = exeVal;
		resp.stagingRoom.iniCRC = iniVal;
		resp.stagingRoom.Rva0064BA37CmdCRC = cmdVal;
		resp.stagingServerLadderIP = ladIPStr;
		resp.stagingServerPingString = pingStr;
		resp.stagingRoom.ladderPort = ladPort;
		Int numPlayers = SBServerGetIntValue(server, NUMPLAYER_STR, 0);
		if (numPlayers <= 0 || numPlayers > 8) numPlayers=1;
		resp.stagingRoom.numPlayers=numPlayers;
		resp.stagingRoom.numObservers = SBServerGetIntValue(server, NUMOBS_STR, 0);
		Int maxPlayers = SBServerGetIntValue(server, MAXPLAYER_STR, 8);
		if (maxPlayers <= 0) maxPlayers=8;
		resp.stagingRoom.maxPlayers=maxPlayers;
		resp.stagingRoomMapName = SBServerGetStringValue(server, "mapname", "");
		resp.stagingRoom.Rva0064BAF6Teamplay=SBServerGetIntValue(server,"teamplay",0);
		for (Int i=0; i<MAX_SLOTS; ++i)
		{
			resp.stagingRoomPlayerNames[i] = SBServerGetPlayerStringValue(server, i, NAME__STR, "");
			resp.stagingRoom.wins[i] = SBServerGetPlayerIntValue(server, i, WINS__STR, 0);
			resp.stagingRoom.losses[i] = SBServerGetPlayerIntValue(server, i, LOSSES__STR, 0);
			resp.stagingRoom.profileID[i] = SBServerGetPlayerIntValue(server, i, "pid", 0);
			resp.stagingRoom.color[i] = SBServerGetPlayerIntValue(server, i, COLOR__STR, 0);
			resp.stagingRoom.faction[i] = SBServerGetPlayerIntValue(server, i, FACTION__STR, 0);
#ifdef DEBUG_LOGGING
			if (resp.stagingRoomPlayerNames[i].length())
			{
				DEBUG_LOG(("Player %d raw stuff: [%s] [%d] [%d] [%d]\n", i, resp.stagingRoomPlayerNames[i].c_str(), resp.stagingRoom.wins[i], resp.stagingRoom.losses[i], resp.stagingRoom.profileID[i]));
			}
#endif
		}
		if (resp.stagingRoomPlayerNames[0].empty())
		{
			resp.stagingRoomPlayerNames[0] = hostName.str();
		}
		DEBUG_ASSERTCRASH(resp.stagingRoomPlayerNames[0].empty() == false, ("No host!"));
		DEBUG_LOG(("Raw stuff: [%s] [%s] [%s] [%d] [%d] [%d]\n", verStr, exeStr, iniStr, hasPassword, allowObservers, usesStats));
		DEBUG_LOG(("Raw stuff: [%s] [%s] [%d]\n", pingStr, ladIPStr, ladPort));
		DEBUG_LOG(("Saw game with stuff %s %d %X %X %X %s\n", resp.stagingRoomMapName.c_str(), hasPassword, verVal, exeVal, iniVal, SBServerGetStringValue(server, "password", "missing")));
#ifdef PING_TEST
	PING_LOG(("%s\n", pingStr));
#endif
	}

	if (msg == PEER_ADD || msg == PEER_UPDATE)
	{
		if (!resp.stagingRoom.exeCRC || !resp.stagingRoom.iniCRC)
		{
			if (!SBServerHasBasicKeys(server))
			{
				DEBUG_LOG(("Server %x does not have basic keys\n", server));
				return;
			}
			else
			{
				DEBUG_LOG(("Server %x has basic keys, yet has no info\n", server));
			}
			if (msg == PEER_UPDATE)
			{
				PeerRequest req;
				unsigned frame=Rva012F1464->rva0064BCFC();
				req.peerRequestType = PeerRequest::PEERREQUEST_GETEXTENDEDSTAGINGROOMINFO;
				req.stagingRoom.id = t->Rva00648220( server );
				DEBUG_LOG(("Add/update a 0/0 server %X (%d, %s) - requesting full update to see if that helps.\n",
					server, resp.stagingRoom.id, gameName.str()));
				if (Rva012B96D8 != req.stagingRoom.id || frame > Rva012F76EC + 15)
                    TheGameSpyPeerMessageQueue->addRequest(req);
                Rva012B96D8=req.stagingRoom.id; Rva012F76EC=frame;
			}
			return; // don't actually try to list it.
		}
	}

	switch (msg)
	{
		case PEER_CLEAR:
			t->Rva00646240();
			break;
		case PEER_ADD:
		case PEER_UPDATE:
			resp.stagingRoom.id = t->Rva00648220( server );
			DEBUG_LOG(("Add/update on server %X (%d, %s)\n", server, resp.stagingRoom.id, gameName.str()));
			resp.stagingServerName = MultiByteToWideCharSingleLine( gameName.str() );
			DEBUG_LOG(("Server had basic=%d, full=%d\n", SBServerHasBasicKeys(server), SBServerHasFullKeys(server)));
#ifdef DEBUG_LOGGING
			//SBServerEnumKeys(server, enumFunc, NULL);
#endif
			break;
		case PEER_REMOVE:
			DEBUG_LOG(("Removing server %X (%d)\n", server, resp.stagingRoom.id));
			resp.stagingRoom.id = t->Rva00647F90( server );
			break;
	}

	TheGameSpyPeerMessageQueue->addResponse(resp);
}

