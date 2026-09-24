// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// PeerThread.cpp reconstruction bank. GPL-3.0-or-later, derived from EA Zero Hour.
// Identity and boundaries: build/unclaimed_map/astra_J/IDENTITY.md.
#include <string>
#include <vector>
#include <map>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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

#define FALSE false
#define TRUE true
#define DEBUG_LOG(x)
#define DEBUG_CRASH(x)
struct _SBServer;
enum PEERJoinResult { Rva0064ECC0JoinResultUnknown };
enum { PEERFalse, PEERTrue, NormalMessage=0 };
extern "C" {
 int peerIsConnected(PEER);
 unsigned peerGetLocalIP(PEER);
 void peerThink(PEER);
 void peerMessagePlayerA(PEER,const char*,const char*,int);
 void peerLeaveRoomA(PEER,RoomType,const char*);
 void peerJoinGroupRoom(PEER,int,void (*)(PEER,int,PEERJoinResult,RoomType,void*),void*,int);
 void peerEnumPlayers(PEER,RoomType,void(*)(PEER,int,RoomType,int,const char*,int,void*),void*);
 void peerUTMPlayerA(PEER,const char*,const char*,const char*,int);
 __declspec(dllimport) unsigned long __stdcall htonl(unsigned long);
}
#define ntohl htonl
#define peerMessagePlayer peerMessagePlayerA
#define peerLeaveRoom peerLeaveRoomA
#define peerUTMPlayer peerUTMPlayerA
void joinRoomCallback(PEER,int,PEERJoinResult,RoomType,void*);
void quickmatchEnumPlayersCallback(PEER,int,RoomType,int,const char*,int,void*);
static int matchbotProfileID;
class MutexClass {
 void *handle; unsigned locked;
public:
 class LockClass {
  MutexClass &mutex; bool failed;
 public:
  LockClass(MutexClass &,int);
  ~LockClass();
  bool Failed() { return failed; }
 };
};
// ThreadClass::Switch_Thread's body at 0x009DB570 carries the ledger name
// bfmeGoDWI (BfmeConv792.cpp); the static member forwards to it.
void bfmeGoDWI();
class ThreadClass {
public:
 virtual ~ThreadClass();
 virtual void Execute();
 static void Switch_Thread() { bfmeGoDWI(); }
protected:
 virtual void Thread_Function()=0;
 char Rva0064CEF0Base[0x4c];
};

class PeerThreadClass : public ThreadClass {
public:
 virtual void Thread_Function();
private:
 void doQuickMatch(PEER);
 void setQMGroupRoom(int id) { m_qmGroupRoom=id; }
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
	std::map<std::string, int> m_groupRoomStats;
	std::map<std::string, int> m_stagingRoomStats;
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
	std::map<Int, _SBServer *> m_stagingServers;
	std::wstring m_localStagingServerName;
	Int m_localRoomID;
	QMStatus m_qmStatus;
	PeerRequest m_qmInfo;
	Bool m_roomJoined;
	Int m_qmGroupRoom;
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
	MutexClass *m_lock;
};

typedef char PeerThreadSize[sizeof(PeerThreadClass)==0x3ec ? 1:-1];
class BuddyRequest {
public:
 enum { BUDDYREQUEST_SETSTATUS=9 } buddyRequestType;
 union {
  struct { int status; char statusString[256]; char locationString[256]; } status;
  char Rva0064EFF7Payload[692];
 } arg;
};
class GameSpyBuddyMessageQueueInterface {
public:
 virtual ~GameSpyBuddyMessageQueueInterface() {}
 virtual void startThread()=0;
 virtual void endThread()=0;
 virtual bool isThreadRunning()=0;
 virtual bool isConnected()=0;
 virtual bool isConnecting()=0;
 virtual void addRequest(const BuddyRequest&)=0;
};
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
enum GameSpyBuddyStatus { BUDDY_OFFLINE, BUDDY_ONLINE, BUDDY_LOBBY, BUDDY_STAGING, BUDDY_LOADING, BUDDY_PLAYING, BUDDY_MATCHING };
enum { GP_OFFLINE=0, GP_ONLINE=1, GP_CHATTING=4, GP_STAGING=3, GP_PLAYING=2 };
static void updateBuddyStatus( GameSpyBuddyStatus status, Int groupRoom = 0, std::string gameName = "" )
{
	if (!TheGameSpyBuddyMessageQueue)
		return;

	BuddyRequest req;
	req.buddyRequestType = BuddyRequest::BUDDYREQUEST_SETSTATUS;
	switch(status)
	{
		case BUDDY_OFFLINE:
			req.arg.status.status = GP_OFFLINE;
			strcpy(req.arg.status.statusString, "Offline");
			strcpy(req.arg.status.locationString, "");
			break;
		case BUDDY_ONLINE:
			req.arg.status.status = GP_ONLINE;
			strcpy(req.arg.status.statusString, "Online");
			strcpy(req.arg.status.locationString, "");
			break;
		case BUDDY_LOBBY:
			req.arg.status.status = GP_CHATTING;
			strcpy(req.arg.status.statusString, "Chatting");
			sprintf(req.arg.status.locationString, "%d", groupRoom);
			break;
		case BUDDY_STAGING:
			req.arg.status.status = GP_STAGING;
			strcpy(req.arg.status.statusString, "Staging");
			sprintf(req.arg.status.locationString, "%s", gameName.c_str());
			break;
		case BUDDY_LOADING:
			req.arg.status.status = GP_PLAYING;
			strcpy(req.arg.status.statusString, "Loading");
			sprintf(req.arg.status.locationString, "%s", gameName.c_str());
			break;
		case BUDDY_PLAYING:
			req.arg.status.status = GP_PLAYING;
			strcpy(req.arg.status.statusString, "Playing");
			sprintf(req.arg.status.locationString, "%s", gameName.c_str());
			break;
		case BUDDY_MATCHING:
			req.arg.status.status = GP_ONLINE;
			strcpy(req.arg.status.statusString, "Matching");
			strcpy(req.arg.status.locationString, "");
			break;
	}
	DEBUG_LOG(("updateBuddyStatus %d:%s\n", req.arg.status.status, req.arg.status.statusString));
	TheGameSpyBuddyMessageQueue->addRequest(req);
}

void PeerThreadClass::doQuickMatch( PEER peer )
{
	m_qmStatus = QM_JOININGQMCHANNEL;
	Bool done = false;
	matchbotProfileID = m_qmInfo.QM.botID;
	setQMGroupRoom( m_qmInfo.QM.roomID );
	m_sawMatchbot = false;
	updateBuddyStatus( BUDDY_MATCHING );
	while (!done)
	{
        MutexClass::LockClass lock(*m_lock,1);
        if (!lock.Failed()) break;
		if (!peerIsConnected( peer ))
		{
			done = true;
		}
		else
		{
			// update the network
			peerThink( peer );

			// end our timeslice
			Switch_Thread();

			PeerRequest incomingRequest;
			if (TheGameSpyPeerMessageQueue->getRequest(incomingRequest))
			{
				switch (incomingRequest.peerRequestType)
				{
				case PeerRequest::PEERREQUEST_WIDENQUICKMATCHSEARCH:
					{
						if (m_qmStatus != QM_IDLE && m_qmStatus != QM_STOPPED && m_sawMatchbot)
						{
							peerMessagePlayer( peer, m_matchbotName.c_str(), "\\WIDEN", NormalMessage );
						}
					}
					break;
				case PeerRequest::PEERREQUEST_STOPQUICKMATCH:
					{
						m_qmStatus = QM_STOPPED;
						peerLeaveRoom(peer, GroupRoom, "");
						done = true;
					}
					break;
				case PeerRequest::PEERREQUEST_LOGOUT:
					{
						m_qmStatus = QM_STOPPED;
						peerLeaveRoom(peer, GroupRoom, "");
						done = true;
					}
					break;
				case PeerRequest::PEERREQUEST_LEAVEGROUPROOM:
					{
						m_qmStatus = QM_STOPPED;
						peerLeaveRoom(peer, GroupRoom, "");
						done = true;
					}
					break;
				case PeerRequest::PEERREQUEST_UTMPLAYER:
					{
						peerUTMPlayer( peer, incomingRequest.nick.c_str(), incomingRequest.id.c_str(), incomingRequest.options.c_str(), PEERFalse );
					}
					break;
				default:
					{
						DEBUG_CRASH(("Unanticipated request %d to peer thread!", incomingRequest.peerRequestType));
					}
					break;
				}
			}

			if (!done)
			{
				// do the next bit of QM
				switch (m_qmStatus)
				{
				case QM_JOININGQMCHANNEL:
					{
						PeerResponse resp;
						resp.peerResponseType = PeerResponse::PEERRESPONSE_QUICKMATCHSTATUS;
						resp.qmStatus.status = QM_JOININGQMCHANNEL;
						TheGameSpyPeerMessageQueue->addResponse(resp);

						m_groupRoomID = m_qmGroupRoom;
						peerLeaveRoom( peer, GroupRoom, NULL );
						peerLeaveRoom( peer, StagingRoom, NULL ); m_isHosting = false;
						m_localRoomID = m_groupRoomID;
						m_roomJoined = false;
						DEBUG_LOG(("Requesting to join room %d in thread %X\n", m_localRoomID, this));
						peerJoinGroupRoom( peer, m_localRoomID, joinRoomCallback, (void *)this, PEERTrue );
						if (m_roomJoined)
						{
							resp.peerResponseType = PeerResponse::PEERRESPONSE_QUICKMATCHSTATUS;
							resp.qmStatus.status = QM_LOOKINGFORBOT;
							TheGameSpyPeerMessageQueue->addResponse(resp);

							m_qmStatus = QM_LOOKINGFORBOT;
							m_sawMatchbot = false;
							m_sawEndOfEnumPlayers = false;
							peerEnumPlayers( peer, GroupRoom, quickmatchEnumPlayersCallback, this );
						}
						else
						{
							resp.peerResponseType = PeerResponse::PEERRESPONSE_QUICKMATCHSTATUS;
							resp.qmStatus.status = QM_COULDNOTFINDBOT;
							TheGameSpyPeerMessageQueue->addResponse(resp);
							done = true;
							m_qmStatus = QM_STOPPED;
						}
					}
					break;
				case QM_LOOKINGFORBOT:
					{
						if (m_sawEndOfEnumPlayers)
						{
							if (m_sawMatchbot)
							{
								char buf[64];
								buf[63] = '\0';
								std::string msg = "\\CINFO";
								_snprintf(buf, 63, "\\Widen\\%d", m_qmInfo.QM.widenTime);
								msg.append(buf);
								_snprintf(buf, 63, "\\LadID\\%d", m_qmInfo.QM.ladderID);
								msg.append(buf);
								_snprintf(buf, 63, "\\LadPass\\%d", m_qmInfo.QM.ladderPassCRC);
								msg.append(buf);
								_snprintf(buf, 63, "\\PointsMin\\%d", m_qmInfo.QM.minPointPercentage);
								msg.append(buf);
								_snprintf(buf, 63, "\\PointsMax\\%d", m_qmInfo.QM.maxPointPercentage);
								msg.append(buf);
								_snprintf(buf, 63, "\\Points\\%d", m_qmInfo.QM.points);
								msg.append(buf);
								_snprintf(buf, 63, "\\Discons\\%d", m_qmInfo.QM.discons);
								msg.append(buf);
								_snprintf(buf, 63, "\\DisconMax\\%d", m_qmInfo.QM.maxDiscons);
								msg.append(buf);
								_snprintf(buf, 63, "\\NumPlayers\\%d", m_qmInfo.QM.numPlayers);
								msg.append(buf);
								_snprintf(buf, 63, "\\PingMax\\%d", m_qmInfo.QM.maxPing);
                                msg.append(buf);
                                _snprintf(buf, 63, "\\Pings\\%s", m_qmInfo.QM.pings);
								msg.append(buf);
								_snprintf(buf, 63, "\\IP\\%d", ntohl(peerGetLocalIP(peer)));// not ntohl(localIP), as we need EXTERNAL address for proper NAT negotiation!
								msg.append(buf);
								_snprintf(buf, 63, "\\Side\\%d", m_qmInfo.QM.side);
								msg.append(buf);
								_snprintf(buf, 63, "\\Color\\%d", m_qmInfo.QM.color);
								msg.append(buf);
								_snprintf(buf, 63, "\\NAT\\%d", m_qmInfo.QM.NAT);
								msg.append(buf);
								_snprintf(buf, 63, "\\EXE\\%d", m_qmInfo.QM.exeCRC);
								msg.append(buf);
								_snprintf(buf, 63, "\\INI\\%d", m_qmInfo.QM.iniCRC);
								msg.append(buf);
								_snprintf(buf, 63, "\\CMD\\%d", m_qmInfo.QM.Rva0064F68CCmdCRC);
                                msg.append(buf);
                                buf[0] = 0;
								msg.append("\\Maps\\");
								for (Int i=0; i<m_qmInfo.qmMaps.size(); ++i)
								{
									if (m_qmInfo.qmMaps[i])
										msg.append("1");
									else
										msg.append("0");
								}
								DEBUG_LOG(("Sending QM options of [%s] to %s\n", msg.c_str(), m_matchbotName.c_str()));
								peerMessagePlayer( peer, m_matchbotName.c_str(), msg.c_str(), NormalMessage );
								m_qmStatus = QM_WORKING;
								PeerResponse resp;
								resp.peerResponseType = PeerResponse::PEERRESPONSE_QUICKMATCHSTATUS;
								resp.qmStatus.status = QM_SENTINFO;
								TheGameSpyPeerMessageQueue->addResponse(resp);
							}
							else
							{
								// no QM bot.  Bail.
								PeerResponse resp;
								resp.peerResponseType = PeerResponse::PEERRESPONSE_QUICKMATCHSTATUS;
								resp.qmStatus.status = QM_COULDNOTFINDBOT;
								TheGameSpyPeerMessageQueue->addResponse(resp);

								m_qmStatus = QM_STOPPED;
								peerLeaveRoom(peer, GroupRoom, "");
								done = true;
							}
						}
					}
					break;
				case QM_WORKING:
					{
					}
					break;
				case QM_MATCHED:
					{
						// leave QM channel, and clean up.  Our work here is done.
						peerLeaveRoom( peer, GroupRoom, NULL );
						peerLeaveRoom( peer, StagingRoom, NULL ); m_isHosting = false;

						m_qmStatus = QM_STOPPED;
						peerLeaveRoom(peer, GroupRoom, "");
						done = true;
					}
					break;
				case QM_INCHANNEL:
					{
					}
					break;
				case QM_NEGOTIATINGFIREWALLS:
					{
					}
					break;
				case QM_STARTINGGAME:
					{
					}
					break;
				case QM_COULDNOTFINDCHANNEL:
					{
					}
					break;
				case QM_COULDNOTNEGOTIATEFIREWALLS:
					{
					}
					break;
				}
			}
		}
	}
	updateBuddyStatus( BUDDY_ONLINE, 0, std::string("", 0) );
}

