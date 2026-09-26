// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/nat /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// GPL-3.0-or-later, adapted from EA Zero Hour PeerThread.cpp.
// Retail witnesses and measured limitations: build/unclaimed_map/astra_J/IDENTITY.md.
#define Matrix4x4 Matrix4
#define THREAD_H
class ThreadClass {
public:
 virtual ~ThreadClass();
 virtual void Execute();
 static void Switch_Thread();
protected:
 virtual void Thread_Function()=0;
 char Rva0064CEF0Base[0x4c];
};


#include "PreRTS.h"
#define peerSetTitle peerSetTitleA
#define peerMessageRoom peerMessageRoomA
#define peerMessagePlayer peerMessagePlayerA
#define peerConnect peerConnectA
#define peerLeaveRoom peerLeaveRoomA
#define peerCreateStagingRoomWithSocket peerCreateStagingRoomWithSocketA
#define peerStartListingGames peerStartListingGamesA
#define peerJoinStagingRoom peerJoinStagingRoomA
#define peerSetRoomWatchKeys peerSetRoomWatchKeysA
#define peerListGroupRooms peerListGroupRoomsA
#define peerUTMPlayer peerUTMPlayerA
#define peerUTMRoom peerUTMRoomA
#define peerSetRoomKeys peerSetRoomKeysA
#define qr2_register_key qr2_register_keyA
extern "C" {
#include "GameSpy/Peer/Peer.h"
}
#include "GameNetwork/NetworkDefs.h"
#include "Common/Registry.h"
#include "Common/UserPreferences.h"
#include "GameNetwork/IPEnumeration.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "mutex.h"
#define __PEERTHREAD_H__
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
		PEERREQUEST_BFMEUNKNOWN, // worker case 6: leave only group room
		PEERREQUEST_STARTGAMELIST,
		PEERREQUEST_STOPGAMELIST,
		PEERREQUEST_CREATESTAGINGROOM,
		PEERREQUEST_SETGAMEOPTIONS,
		PEERREQUEST_JOINSTAGINGROOM,
		PEERREQUEST_LEAVESTAGINGROOM,
		// Retail worker table 006510AC proves UTMPLAYER=13.
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
            UnsignedInt Rva00650A46CmdCRC;
            Bool useStats;
			UnsignedShort ladPort;
			UnsignedInt ladPassCRC;
			Bool restrictGameList;
            Int Rva00650A2EMaxPlayers;
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
 PeerRequest& operator=(const PeerRequest&);
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

// Four private PeerThreadClass helpers already carry opaque ledger names at
// their bodies (0x00646240, 0x00646290, 0x00649DB0, 0x00649E90). The members
// below forward to those names on the same receiver; they assert no new
// identity. Retail reaches each through its ILT.
class BfmeThingAVA { public: void bfmeGoAVA(); };
class Rva00646290Owner { public: void *lookup00646290(int id); };
class BfmeSessionAJ { public: void bfmeStartAJ(void *peer); };
class BfmeOwnerFP { public: void bfmeStopFP(void *peer); };

class PeerThreadClass : public ThreadClass {
public:
 virtual void Thread_Function();
private:
 void doQuickMatch(PEER);
 void Rva00646240() { reinterpret_cast<BfmeThingAVA *>(this)->bfmeGoAVA(); }
 _SBServer* Rva00646290(Int id) { return (_SBServer *)reinterpret_cast<Rva00646290Owner *>(this)->lookup00646290(id); }
 void Rva00649E90(PEER peer) { reinterpret_cast<BfmeOwnerFP *>(this)->bfmeStopFP(peer); }
 void Rva00643BC0(PEER);
 void Rva00649DB0(PEER peer) { reinterpret_cast<BfmeSessionAJ *>(this)->bfmeStartAJ(peer); }
 void Rva00643C10(PEER);
 static char s_valueBuffers[8][20];
 static const char* s_keys[6];
 static const char* s_values[6];
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

typedef char RequestSize[sizeof(PeerRequest)==0x194?1:-1];
typedef char ResponseSize[sizeof(PeerResponse)==0x330?1:-1];
typedef char ThreadSize[sizeof(PeerThreadClass)==0x3ec?1:-1];
char PeerThreadClass::s_valueBuffers[8][20];
const char* PeerThreadClass::s_keys[6]={"b_locale","b_wins","b_losses","b_points","b_side","b_pre"};
const char* PeerThreadClass::s_values[6]={s_valueBuffers[0],s_valueBuffers[1],s_valueBuffers[2],s_valueBuffers[3],s_valueBuffers[4],s_valueBuffers[5]};
extern int isThreadHosting;
static unsigned s_lastStateChangedHeartbeat;
static bool s_wantStateChangedHeartbeat;
extern unsigned s_heartbeatInterval;
static SOCKET qr2Sock=INVALID_SOCKET;
extern unsigned localIP;
std::string WideCharStringToMultiByte(const wchar_t*);
// Retail passes the peer in ECX to doCDKeyAuthentication (0x00648E30, the
// file-static helper's register convention), so the call is modelled as a
// no-argument thiscall on the peer pointer.
class Rva00648E30Peer { public: SerialAuthResult call(); };
// The ledger already names 0x0085A850 (chatSetLocalIP's one-int store).
struct Rva0085A850 { static void store(int value); };
void checkQR2Queries(PEER,SOCKET);
extern "C" {
 void GSIStartAvailableCheckA(const char*);
 int GSIAvailableCheckThink();
 void peerSetQuietMode(PEER,PEERBool);
}
typedef void* Rva0064FF27ServerBrowser;
extern "C" Rva0064FF27ServerBrowser ServerBrowserNewA(const char*,const char*,const char*,int,int,int,void(*)(void*,int,SBServer,void*),void*);
extern "C" void ServerBrowserClear(void*);
extern "C" int ServerBrowserUpdateA(void*,int,int,unsigned char*,int,const char*);
void Rva00642FB0Callback(void*,int,SBServer,void*);
void Rva00646E10Callback(PEER,PEERBool,int,SBServer,const char*,int,int,int,int,void*);
void disconnectedCallback(PEER peer, const char * reason, void * param);
void roomMessageCallback(PEER peer, RoomType roomType, const char * nick, const char * message, MessageType messageType, void * param);
void playerMessageCallback(PEER peer, const char * nick, const char * message, MessageType messageType, void * param);
void gameStartedCallback(PEER peer, UnsignedInt IP, const char *message, void *param);
void playerJoinedCallback(PEER peer, RoomType roomType, const char * nick, void * param);
void playerLeftCallback(PEER peer, RoomType roomType, const char * nick, const char * reason, void * param);
void playerChangedNickCallback(PEER peer, RoomType roomType, const char * oldNick, const char * newNick, void * param);
void playerFlagsChangedCallback(PEER peer, RoomType roomType, const char * nick, int oldFlags, int newFlags, void * param);
void playerInfoCallback(PEER peer, RoomType roomType, const char * nick, unsigned int IP, int profileID, void * param);
void roomUTMCallback(PEER peer, RoomType roomType, const char * nick, const char * command, const char * parameters, PEERBool authenticated, void * param);
void playerUTMCallback(PEER peer, const char * nick, const char * command, const char * parameters, PEERBool authenticated, void * param);
void globalKeyChangedCallback(PEER peer, const char *nick, const char *key, const char *val, void *param);
void roomKeyChangedCallback(PEER peer, RoomType roomType, const char *nick, const char *key, const char *val, void *param);
void QRServerKeyCallback
(
	PEER peer,
	int key,
	qr2_buffer_t buffer,
	void * param
);
void QRPlayerKeyCallback
(
	PEER peer,
	int key,
	int index,
	qr2_buffer_t buffer,
	void * param
);
void QRTeamKeyCallback
(
	PEER peer,
	int key,
	int index,
	qr2_buffer_t buffer,
	void * param
);
void QRKeyListCallback
(
	PEER peer,
	qr2_key_type type,
	qr2_keybuffer_t keyBuffer,
	void * param
);
int QRCountCallback
(
	PEER peer,
	qr2_key_type type,
	void * param
);
void QRAddErrorCallback
(
	PEER peer,
	qr2_error_t error,
	char * errorString,
	void * param
);
void QRNatNegotiateCallback
(
	PEER peer,
	int cookie,
	void * param
);
void KickedCallback
(
	PEER peer,
	RoomType roomType,
	const char * nick,
	const char * reason,
	void * param
);
void NewPlayerListCallback
(
	PEER peer,
	RoomType roomType,
	void * param
);
void nickErrorCallbackWrapper( PEER peer, Int type, const char *nick, void *param );
void connectCallbackWrapper( PEER peer, PEERBool success, void *param );
void joinRoomCallback(PEER peer, PEERBool success, PEERJoinResult result, RoomType roomType, void *param);
void createRoomCallback(PEER peer, PEERBool success, PEERJoinResult result, RoomType roomType, void *param);
void listingGamesCallback(PEER peer, PEERBool success, const char * name, SBServer server, PEERBool staging, int msg, Int percentListed, void * param);
enum
{
	EXECRC_KEY = NUM_RESERVED_KEYS + 1,
	INICRC_KEY,
    CMDCRC_KEY,
	PW_KEY,
	OBS_KEY,

	LADIP_KEY,
	LADPORT_KEY,
	PINGSTR_KEY,
	NUMPLAYER_KEY,
	MAXPLAYER_KEY,
	NUMOBS_KEY,
	NAME__KEY,
	FACTION__KEY,
	COLOR__KEY,
	WINS__KEY,
	LOSSES__KEY
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


#define CMDCRC_STR "cmdCRC"
#define USE_BROADCAST_KEYS
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
			req.arg.status.status = 3;
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


#include "Common/CustomMatchPreferences.h"
#define STATECHANGED_LOG(x)
// BFME's node is not the polymorphic ZH MemoryPoolObject node.
struct Rva0064FF74IP { void* text; unsigned ip; Rva0064FF74IP* next; };
template<> inline bool StringBase<char>::isNotEmpty() const { return m_data && m_data->length; }
class Rva012F7194Slots { public:
 virtual void slot0()=0;
 virtual void slot1()=0;
 virtual void slot2()=0;
 virtual void slot3()=0;
 virtual void slot4()=0;
 virtual void slot5()=0;
 virtual void slot6()=0;
 virtual void slot7()=0;
 virtual void slot8()=0;
 virtual void slot9()=0;
 virtual void slot10()=0;
 virtual void slot11()=0;
 virtual void slot12()=0;
 virtual void slot13()=0;
 virtual void slot14()=0;
 virtual void slot15()=0;
 virtual void slot16()=0;
 virtual void slot17()=0;
 virtual void slot18()=0;
 virtual const AsciiString* Rva00650F06(const char*)=0;
};
extern Rva012F7194Slots* Rva012F7194;

void PeerThreadClass::Thread_Function()
{
	try {
	char gameName[12];
 char secretKey[7];
 gameName[0]='l';gameName[1]='o';gameName[2]='t';gameName[3]='r';
 gameName[4]='b';gameName[5]='m';gameName[6]='e';gameName[7]=0;
 secretKey[0]='h';secretKey[1]='3';secretKey[2]='D';secretKey[3]='7';
 secretKey[4]='L';secretKey[5]='c';secretKey[6]=0;
 GSIStartAvailableCheckA(gameName);
 int availability;
 while ((availability=GSIAvailableCheckThink())==0) Sleep(10);
 if (availability!=1) return;

	PEER peer;

	// Setup the callbacks.
	///////////////////////
	PEERCallbacks callbacks;
	memset(&callbacks, 0, sizeof(PEERCallbacks));
	callbacks.disconnected = disconnectedCallback;
	//callbacks.readyChanged = readyChangedCallback;
	callbacks.roomMessage = roomMessageCallback;
	callbacks.playerMessage = playerMessageCallback;
	callbacks.gameStarted = gameStartedCallback;
	callbacks.playerJoined = playerJoinedCallback;
	callbacks.playerLeft = playerLeftCallback;
	callbacks.playerChangedNick = playerChangedNickCallback;
	callbacks.playerFlagsChanged = playerFlagsChangedCallback;
	callbacks.playerInfo = playerInfoCallback;
	callbacks.roomUTM = roomUTMCallback;
	callbacks.playerUTM = playerUTMCallback;
	callbacks.globalKeyChanged = globalKeyChangedCallback;
	callbacks.roomKeyChanged = roomKeyChangedCallback;

	callbacks.qrServerKey = QRServerKeyCallback;
	callbacks.qrPlayerKey = QRPlayerKeyCallback;
	callbacks.qrTeamKey = QRTeamKeyCallback;
	callbacks.qrKeyList = QRKeyListCallback;
	callbacks.qrCount = QRCountCallback;
	callbacks.qrAddError = QRAddErrorCallback;
	callbacks.qrNatNegotiateCallback = QRNatNegotiateCallback;

	callbacks.kicked = KickedCallback;
	callbacks.newPlayerList = NewPlayerListCallback;

	callbacks.param = this;

	m_qmGroupRoom = 0;

	peer = peerInitialize( &callbacks );
	DEBUG_ASSERTCRASH( peer != NULL, ("NULL peer!") );
	m_isConnected = m_isConnecting = false;

	qr2_register_key(EXECRC_KEY, EXECRC_STR);
	qr2_register_key(INICRC_KEY, INICRC_STR);
 qr2_register_key(CMDCRC_KEY, CMDCRC_STR);
	qr2_register_key(PW_KEY, PW_STR);
	qr2_register_key(OBS_KEY, OBS_STR);

	qr2_register_key(LADIP_KEY, LADIP_STR);
	qr2_register_key(LADPORT_KEY, LADPORT_STR);
	qr2_register_key(PINGSTR_KEY, PINGSTR_STR);
	qr2_register_key(NUMOBS_KEY, NUMOBS_STR);
	qr2_register_key(NUMPLAYER_KEY, NUMPLAYER_STR);
	qr2_register_key(MAXPLAYER_KEY, MAXPLAYER_STR);
	qr2_register_key(NAME__KEY, NAME__STR "_");
	qr2_register_key(WINS__KEY, WINS__STR "_");
	qr2_register_key(LOSSES__KEY, LOSSES__STR "_");
	qr2_register_key(FACTION__KEY, FACTION__STR "_");
	qr2_register_key(COLOR__KEY, COLOR__STR "_");

 const Int NumKeys=17;
 unsigned char allKeysArray[NumKeys]={5,12,11,3,2,51,52,53,54,55,56,57,58,61,59,60,1};

	const char * key = "username";
	peerSetRoomWatchKeys(peer, StagingRoom, 1, &key, PEERTrue);
	peerSetRoomWatchKeys(peer, GroupRoom, 1, &key, PEERTrue);

	m_localRoomID = 0;
	m_localStagingServerName = L"";

	m_qmStatus = QM_IDLE;

	// Setup which rooms to do pings and cross-pings in.
	////////////////////////////////////////////////////
	PEERBool pingRooms[NumRooms];
	PEERBool crossPingRooms[NumRooms];
	pingRooms[TitleRoom] = PEERFalse;
	pingRooms[GroupRoom] = PEERFalse;
	pingRooms[StagingRoom] = PEERFalse;
	crossPingRooms[TitleRoom] = PEERFalse;
	crossPingRooms[GroupRoom] = PEERFalse;
	crossPingRooms[StagingRoom] = PEERFalse;
	
	
// Set the title.
	/////////////////
	if(!peerSetTitle( peer , gameName, secretKey, gameName, secretKey, GetRegistryVersion(), 30, PEERTrue, pingRooms, crossPingRooms))
	{
		DEBUG_CRASH(("Error setting title"));
		peerShutdown( peer );
		peer = NULL;
		return;
	}

	Rva0064FF27ServerBrowser browser=ServerBrowserNewA(gameName,gameName,secretKey,0,30,1,Rva00642FB0Callback,this);
	OptionPreferences pref;
	UnsignedInt preferredIP = INADDR_ANY;
	UnsignedInt selectedIP = pref.getOnlineIPAddress();
	DEBUG_LOG(("Looking for IP %X\n", selectedIP));
	IPEnumeration IPs;
	Rva0064FF74IP *IPlist = reinterpret_cast<Rva0064FF74IP*>(IPs.getAddresses());
	while (IPlist)
	{
		DEBUG_LOG(("Looking at IP %s\n", IPlist->getIPstring().str()));
		if (selectedIP == IPlist->ip)
		{
			preferredIP = IPlist->ip;
			DEBUG_LOG(("Connecting to GameSpy chat server via IP address %8.8X\n", preferredIP));
			break;
		}
		IPlist = IPlist->next;
	}
	Rva0085A850::store((int)preferredIP);

	UnsignedInt preferredQRPort = 0;
	AsciiString selectedQRPort = pref["GameSpyQRPort"];
	if (selectedQRPort.isNotEmpty())
	{
		preferredQRPort = atoi(selectedQRPort.str());
	}

	PeerRequest incomingRequest;
	while ( true )
	{
		MutexClass::LockClass lock(*m_lock,1);
        if (!lock.Failed()) break;
        // deal with requests
		if (TheGameSpyPeerMessageQueue->getRequest(incomingRequest))
		{
			DEBUG_LOG(("TheGameSpyPeerMessageQueue->getRequest() got request of type %d\n", incomingRequest.peerRequestType));
			switch (incomingRequest.peerRequestType)
			{
			case PeerRequest::PEERREQUEST_LOGIN:
				{
				m_isConnecting = true;
				m_originalName = incomingRequest.nick;
				m_loginName = incomingRequest.nick;
				m_profileID = incomingRequest.login.profileID;
				m_password = incomingRequest.password;
				m_email = incomingRequest.email;
				peerConnect( peer, incomingRequest.nick.c_str(), incomingRequest.login.profileID, nickErrorCallbackWrapper, connectCallbackWrapper, this, PEERTrue );
#ifdef SERVER_DEBUGGING
				DEBUG_LOG(("After peerConnect()\n"));
				CheckServers(peer);
#endif // SERVER_DEBUGGING
				if (m_isConnected)
				{
					SerialAuthResult ret = reinterpret_cast<Rva00648E30Peer*>(peer)->call();
					if (ret != SERIAL_OK)
					{
						m_isConnecting = m_isConnected = false;
						*reinterpret_cast<SerialAuthResult*>(reinterpret_cast<char*>(TheGameSpyPeerMessageQueue)+0x68)=ret;
						peerDisconnect( peer );
					}
				}
				m_isConnecting = false;

				// check our connection
				//if (m_isConnected)
				//{
				//	GetLocalChatConnectionAddress("peerchat.gamespy.com", 6667, localIP);
				//}
				}

				break;

			case PeerRequest::PEERREQUEST_LOGOUT:
				m_isConnecting = m_isConnected = false;
				peerDisconnect( peer );
				break;

			case PeerRequest::PEERREQUEST_JOINGROUPROOM:
				m_groupRoomID = incomingRequest.groupRoom.id;
				isThreadHosting = 0; // debugging
				s_lastStateChangedHeartbeat = 0;
				s_wantStateChangedHeartbeat = FALSE;
				peerStopGame( peer );
                m_openStaging="openstaging";
                m_unknown3D8=false;
                peerSetQuietMode(peer,PEERFalse);
				peerLeaveRoom( peer, GroupRoom, NULL );
				peerLeaveRoom( peer, StagingRoom, NULL );
				if (qr2Sock != INVALID_SOCKET)
				{
					closesocket(qr2Sock);
					qr2Sock = INVALID_SOCKET;
				}
				m_isHosting = false;
				m_localRoomID = m_groupRoomID;
				DEBUG_LOG(("Requesting to join room %d in thread %X\n", m_localRoomID, this));
				peerJoinGroupRoom( peer, incomingRequest.groupRoom.id, joinRoomCallback, (void *)this, PEERTrue );
				break;

			case PeerRequest::PEERREQUEST_LEAVEGROUPROOM:
                if (m_groupRoomID != incomingRequest.groupRoom.id) break;
				m_groupRoomID = 0;
				updateBuddyStatus( BUDDY_ONLINE );
				peerLeaveRoom( peer, GroupRoom, NULL );
				peerLeaveRoom( peer, StagingRoom, NULL ); m_isHosting = false;
				break;

			case PeerRequest::PEERREQUEST_BFMEUNKNOWN:
                if (m_groupRoomID != incomingRequest.groupRoom.id) break;
                m_groupRoomID=0;
                updateBuddyStatus(BUDDY_ONLINE);
                peerLeaveRoom(peer,GroupRoom,NULL);
                break;
            case PeerRequest::PEERREQUEST_JOINSTAGINGROOM:
				{
					m_groupRoomID = 0;
					updateBuddyStatus( BUDDY_ONLINE );
					peerLeaveRoom( peer, GroupRoom, NULL );
					peerLeaveRoom( peer, StagingRoom, NULL ); m_isHosting = false;
					SBServer server = Rva00646290(incomingRequest.stagingRoom.id);
					m_localStagingServerName = incomingRequest.text;
					DEBUG_LOG(("Setting m_localStagingServerName to [%ls]\n", m_localStagingServerName.c_str()));
					m_localRoomID = incomingRequest.stagingRoom.id;
					DEBUG_LOG(("Requesting to join room %d\n", m_localRoomID));
					if (server)
					{
						peerJoinStagingRoom( peer, server, incomingRequest.password.c_str(), joinRoomCallback, (void *)this, PEERTrue );
					}
					else
					{
						PeerResponse resp;
						resp.peerResponseType = PeerResponse::PEERRESPONSE_JOINSTAGINGROOM;
						resp.joinStagingRoom.id = incomingRequest.stagingRoom.id;
						resp.joinStagingRoom.ok = FALSE;
						resp.joinStagingRoom.result = 10;
						TheGameSpyPeerMessageQueue->addResponse(resp);
					}
				}
				break;

			case PeerRequest::PEERREQUEST_LEAVESTAGINGROOM:
				m_groupRoomID = 0;
				updateBuddyStatus( BUDDY_ONLINE );
				peerLeaveRoom( peer, GroupRoom, NULL );
				peerLeaveRoom( peer, StagingRoom, NULL );
				isThreadHosting = 0; // debugging
				s_lastStateChangedHeartbeat = 0;
				s_wantStateChangedHeartbeat = FALSE;
				if (m_isHosting)
				{
					m_numPlayers=1; m_numObservers=0; m_maxPlayers=8;
                    Rva00649E90(peer);
					if (qr2Sock != INVALID_SOCKET)
					{
						closesocket(qr2Sock);
						qr2Sock = INVALID_SOCKET;
					}
					m_isHosting = false;
				}
				break;

			case PeerRequest::PEERREQUEST_MESSAGEPLAYER:
				{
					std::string s = WideCharStringToMultiByte(incomingRequest.text.c_str());
					peerMessagePlayer( peer, incomingRequest.nick.c_str(), s.c_str(), (incomingRequest.message.isAction)?ActionMessage:NormalMessage );
				}
				break;

			case PeerRequest::PEERREQUEST_MESSAGEROOM:
				{
					std::string s = WideCharStringToMultiByte(incomingRequest.text.c_str());
					peerMessageRoom( peer, (m_groupRoomID)?GroupRoom:StagingRoom, s.c_str(), (incomingRequest.message.isAction)?ActionMessage:NormalMessage );
				}
				break;

            case 21: {
                std::string s=WideCharStringToMultiByte(incomingRequest.text.c_str());
                peerMessageRoom(peer,m_groupRoomID?GroupRoom:StagingRoom,s.c_str(),(MessageType)2);
                break;
            }
			case PeerRequest::PEERREQUEST_PUSHSTATS:
				{
					DEBUG_LOG(("PEERREQUEST_PUSHSTATS: stats are %d,%d,%d,%d,%d,%d\n",
						incomingRequest.statsToPush.locale, incomingRequest.statsToPush.wins, incomingRequest.statsToPush.losses, incomingRequest.statsToPush.rankPoints, incomingRequest.statsToPush.side, incomingRequest.statsToPush.preorder));

					// Testing alternate way to push stats
#ifdef USE_BROADCAST_KEYS
					_snprintf(s_valueBuffers[0], 20, "%d", incomingRequest.statsToPush.locale);
					_snprintf(s_valueBuffers[1], 20, "%d", incomingRequest.statsToPush.wins);
					_snprintf(s_valueBuffers[2], 20, "%d", incomingRequest.statsToPush.losses);
					_snprintf(s_valueBuffers[3], 20, "%d", incomingRequest.statsToPush.rankPoints);
					_snprintf(s_valueBuffers[4], 20, "%d", incomingRequest.statsToPush.side);
					_snprintf(s_valueBuffers[5], 20, "%d", incomingRequest.statsToPush.preorder);
					Rva00643BC0(peer);
#else
					const char *keys[6] = { "locale", "wins", "losses", "points", "side", "pre" };
					char valueStrings[6][20];
					char *values[6] = { valueStrings[0], valueStrings[1], valueStrings[2],
						valueStrings[3], valueStrings[4], valueStrings[5]};
					_snprintf(values[0], 20, "%d", incomingRequest.statsToPush.locale);
					_snprintf(values[1], 20, "%d", incomingRequest.statsToPush.wins);
					_snprintf(values[2], 20, "%d", incomingRequest.statsToPush.losses);
					_snprintf(values[3], 20, "%d", incomingRequest.statsToPush.rankPoints);
					_snprintf(values[4], 20, "%d", incomingRequest.statsToPush.side);
					_snprintf(values[5], 20, "%d", incomingRequest.statsToPush.preorder);
					peerSetGlobalKeys(peer, 6, (const char **)keys, (const char **)values);
					peerSetGlobalWatchKeys(peer, GroupRoom,   0, NULL, PEERFalse);
					peerSetGlobalWatchKeys(peer, StagingRoom, 0, NULL, PEERFalse);
					peerSetGlobalWatchKeys(peer, GroupRoom,   6, keys, PEERTrue);
					peerSetGlobalWatchKeys(peer, StagingRoom, 6, keys, PEERTrue);
#endif
				}
				break;
				
            case 25:
                _snprintf(s_valueBuffers[6],20,"%d",incomingRequest.gameOptions.wins[0]);
                _snprintf(s_valueBuffers[7],20,"%d",incomingRequest.gameOptions.wins[1]);
                Rva00643C10(peer);
                break;
			case PeerRequest::PEERREQUEST_SETGAMEOPTIONS:
				{
					m_mapName = incomingRequest.gameOptsMapName;
                    m_unknownBC=incomingRequest.gameOptions.bfmeExtraGameOption;
					m_numPlayers = incomingRequest.gameOptions.numPlayers;
					m_numObservers = incomingRequest.gameOptions.numObservers;
					m_maxPlayers = incomingRequest.gameOptions.maxPlayers;
					DEBUG_LOG(("peerStateChanged(): Marking game options state as changed - %d players, %d observers\n", m_numPlayers, m_numObservers));
					for (Int i=0; i<MAX_SLOTS; ++i)
					{
						m_playerNames[i] = incomingRequest.gameOptsPlayerNames[i];
						m_playerWins[i] = incomingRequest.gameOptions.wins[i];
						m_playerLosses[i] = incomingRequest.gameOptions.losses[i];
						m_playerProfileID[i] = incomingRequest.gameOptions.profileID[i];
						m_playerFactions[i] = incomingRequest.gameOptions.faction[i];
						m_playerColors[i] = incomingRequest.gameOptions.color[i];
					}

					s_wantStateChangedHeartbeat = TRUE;

					

					peerUTMRoom( peer, StagingRoom, "SL/", incomingRequest.options.c_str(), PEERFalse ); // send the full string to people in the room
				}
				break;

            case 24:
                peerUTMRoom(peer,StagingRoom,"PN/",incomingRequest.options.c_str(),PEERFalse);
                break;
			case PeerRequest::PEERREQUEST_GETEXTENDEDSTAGINGROOMINFO:
				{
					SBServer server = Rva00646290( incomingRequest.stagingRoom.id );
					if (server)
					{
						DEBUG_LOG(("Requesting full update on a game\n"));
						peerUpdateGame( peer, server, PEERTrue );
					}
					else
					{
						DEBUG_LOG(("Tried to update non-existent server!\n"));
					}
				}
				break;

			case PeerRequest::PEERREQUEST_CREATESTAGINGROOM:
				{
					Int oldGroupID = m_groupRoomID;
					m_groupRoomID = 0;
					updateBuddyStatus( BUDDY_ONLINE );
					if (!incomingRequest.stagingRoomCreation.restrictGameList)
					{
						peerLeaveRoom( peer, GroupRoom, NULL );
						peerLeaveRoom( peer, StagingRoom, NULL );
					}
					m_isHosting = TRUE;

					Int res = 10;
					if (qr2Sock == INVALID_SOCKET)
					{
						// allocate a port
						if (preferredQRPort < 1024)
						{
							preferredQRPort = 6500 + (ntohl(localIP) & 0xff);
						}
						DEBUG_LOG(("Using %8.8X:%d for QR2\n", ntohl(localIP), preferredQRPort));
					}
					else
					{
						closesocket(qr2Sock);
						qr2Sock = INVALID_SOCKET;
					}
					qr2Sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
					struct sockaddr_in saddr;
					saddr.sin_port=htons(preferredQRPort);
					saddr.sin_addr.s_addr=localIP;
					saddr.sin_family=AF_INET;
					if (bind(qr2Sock, (sockaddr *)&saddr, sizeof(saddr)) != 0)
					{
						DEBUG_LOG(("Could not bind to %d!  Falling back to GameSpy's default port\n", preferredQRPort));
						closesocket(qr2Sock);
						qr2Sock = INVALID_SOCKET;
						preferredQRPort = 0;
					}
					std::string compositeGame = m_loginName;
					compositeGame.append(" ");
					compositeGame.append(WideCharStringToMultiByte(incomingRequest.text.c_str()));
					m_localStagingServerName = incomingRequest.text;
					m_playerNames[0] = m_loginName;
						for (Int i=0; i<MAX_SLOTS; ++i)
						{
							m_playerNames[i] = "";
							m_playerWins[i] = 0;
							m_playerLosses[i] = 0;
							m_playerProfileID[i] = 0;
							m_playerFactions[i] = 0;
							m_playerColors[i] = 0;
						}
						if (incomingRequest.password.length() > 0)
							m_hasPassword = true;
						else
							m_hasPassword = false;
						m_playerNames[0] = m_loginName;
						m_exeCRC = incomingRequest.stagingRoomCreation.exeCRC;
						m_iniCRC = incomingRequest.stagingRoomCreation.iniCRC;
						m_gameVersion = incomingRequest.stagingRoomCreation.gameVersion;
                        m_unknown138=incomingRequest.stagingRoomCreation.Rva00650A46CmdCRC;
                        m_maxPlayers=incomingRequest.stagingRoomCreation.Rva00650A2EMaxPlayers;
						m_localStagingServerName = incomingRequest.text;
						m_ladderIP = incomingRequest.ladderIP;
						m_pingStr = incomingRequest.hostPingStr;
						m_ladderPort = incomingRequest.stagingRoomCreation.ladPort;

                    CustomMatchPreferences custom;
                    m_mapName=custom.getPreferredMap().str();
					peerCreateStagingRoomWithSocket(peer, compositeGame.c_str(), MAX_SLOTS, incomingRequest.password.c_str(), qr2Sock, preferredQRPort, createRoomCallback, (void *)&res, PEERTrue);
					//peerCreateStagingRoomWithSocket(peer, WideCharStringToMultiByte(incomingRequest.text.c_str()).c_str(), MAX_SLOTS, incomingRequest.password.c_str(), qr2Sock, preferredQRPort, createRoomCallback, (void *)&res, PEERTrue);
					DEBUG_LOG(("PEERREQUEST_CREATESTAGINGROOM - creating staging room, name is %ls, passwd is %s, result = %d\n",
						incomingRequest.text.c_str(), incomingRequest.password.c_str(), res));

					PeerResponse resp;
					resp.peerResponseType = PeerResponse::PEERRESPONSE_CREATESTAGINGROOM;
					resp.createStagingRoom.result = res;
					TheGameSpyPeerMessageQueue->addResponse(resp);

					if (res != 0 && res != 5)
					{
						m_localRoomID = oldGroupID;
						DEBUG_LOG(("Requesting to join room %d\n", m_localRoomID));
						if (incomingRequest.stagingRoomCreation.restrictGameList)
						{
							peerLeaveRoom( peer, StagingRoom, NULL );
						}
						else
						{
							peerJoinGroupRoom( peer, oldGroupID, joinRoomCallback, (void *)this, PEERTrue );
						}
						m_isHosting = FALSE;
						m_localStagingServerName = L"";
						m_playerNames[0] = "";
					}
					else
					{
						if (incomingRequest.stagingRoomCreation.restrictGameList)
						{
							peerLeaveRoom( peer, GroupRoom, NULL );
						}
						isThreadHosting = 1; // debugging
						s_lastStateChangedHeartbeat = timeGetTime(); // wait the full interval before updating state
						s_wantStateChangedHeartbeat = FALSE;
						m_isHosting = TRUE;
						
            m_useStats = incomingRequest.stagingRoomCreation.useStats;
						m_mapName = "";

#ifdef USE_BROADCAST_KEYS
						peerSetRoomKeys(peer,GroupRoom,m_loginName.c_str(),6,s_keys,s_values);
                        peerSetRoomKeys(peer,StagingRoom,m_loginName.c_str(),6,s_keys,s_values);
#endif // USE_BROADCAST_KEYS

						DEBUG_LOG(("Setting m_localStagingServerName to [%ls]\n", m_localStagingServerName.c_str()));
						updateBuddyStatus( BUDDY_STAGING, 0, WideCharStringToMultiByte(m_localStagingServerName.c_str()) );
					}
				}
				break;

			case PeerRequest::PEERREQUEST_STARTGAMELIST:
				{
					m_sawCompleteGameList = FALSE;
					PeerResponse resp;
					resp.peerResponseType = PeerResponse::PEERRESPONSE_STAGINGROOM;
					resp.stagingRoom.action = PEER_CLEAR;
					resp.stagingRoom.isStaging = TRUE;
					resp.stagingRoom.percentComplete = 0;
					Rva00646240();
					TheGameSpyPeerMessageQueue->addResponse(resp);
					peerStartListingGames(peer,allKeysArray,NumKeys,"gamemode != 'closedplaying'",listingGamesCallback,this);
				}
				break;

			case PeerRequest::PEERREQUEST_STOPGAMELIST:
				{
					peerStopListingGames( peer );
				}
				break;
				
            case 22: {
                m_sawCompleteGameList=false;
                PeerResponse resp;
                resp.peerResponseType=PeerResponse::PEERRESPONSE_STAGINGROOM;
                resp.stagingRoom.action=PEER_CLEAR;
                resp.stagingRoom.isStaging=true;
                resp.stagingRoom.percentComplete=0;
                Rva00646240();
                TheGameSpyPeerMessageQueue->addResponse(resp);
                ServerBrowserClear(browser);
                ServerBrowserUpdateA(browser,0,1,allKeysArray,NumKeys,NULL);
                break;
            }
			case PeerRequest::PEERREQUEST_STARTGAME:
				{
					m_unknown90=incomingRequest.groupRoom.id;
                    peerSetQuietMode(peer,PEERTrue);
                    peerStopListingGames(peer);
                    Rva00649DB0(peer);
				}
				break;

			case PeerRequest::PEERREQUEST_UTMPLAYER:
				{
					if (incomingRequest.nick.length() > 0)
					{
						const AsciiString* p=Rva012F7194->Rva00650F06(incomingRequest.nick.c_str());
                        if(p) peerUTMPlayer(peer,p->str(),incomingRequest.id.c_str(),incomingRequest.options.c_str(),PEERFalse);
                        else peerUTMPlayer(peer,incomingRequest.nick.c_str(),incomingRequest.id.c_str(),incomingRequest.options.c_str(),PEERFalse);
					}
				}
				break;

			case PeerRequest::PEERREQUEST_UTMROOM:
				{
					peerUTMRoom( peer, (incomingRequest.UTM.isStagingRoom)?StagingRoom:GroupRoom, incomingRequest.id.c_str(), incomingRequest.options.c_str(), PEERFalse );
				}
				break;

			case PeerRequest::PEERREQUEST_STARTQUICKMATCH:
				{
					m_qmInfo = incomingRequest;
					doQuickMatch( peer );
				}
				break;

            case 23:
                m_unknown3E0=0; m_unknown3DC=0;
                if (m_unknown3E4) peerListGroupRooms(peer,"\\roomType",Rva00646E10Callback,this,PEERTrue);
                break;

			}
		}

		if (isThreadHosting && s_wantStateChangedHeartbeat && !m_unknown3D8)
		{
			UnsignedInt now = timeGetTime();
			if (now > s_lastStateChangedHeartbeat + s_heartbeatInterval)
			{
				s_lastStateChangedHeartbeat = now;
				s_wantStateChangedHeartbeat = FALSE;
				peerStateChanged( peer );

#ifdef DEBUG_LOGGING
				static UnsignedInt prev = 0;
				UnsignedInt now = timeGetTime();
				UnsignedInt diff = now - prev;
				prev = now;
#endif
				STATECHANGED_LOG(("peerStateChanged() at time %d (difference of %d ms)\n", now, diff));
			}
		}

		// update the network
		PEERBool isConnected = PEERTrue;
		isConnected = peerIsConnected( peer );
		if ( isConnected == PEERTrue )
		{
			if (qr2Sock != INVALID_SOCKET)
			{
				// check hosting activity
				checkQR2Queries( peer, qr2Sock );
			}
			peerThink( peer );
		}

		// end our timeslice
		
	}

	DEBUG_LOG(("voluntarily ending peer thread %d\n", running));
	peerShutdown( peer );

	} catch ( ... ) {
		DEBUG_CRASH(("Exception in peer thread!"));

		try {
			PeerResponse resp;
			resp.peerResponseType = PeerResponse::PEERRESPONSE_DISCONNECT;
			resp.discon.reason = DISCONNECT_LOSTCON;
			TheGameSpyPeerMessageQueue->addResponse(resp);
		}
		catch (...)
		{
		}
	}
}

