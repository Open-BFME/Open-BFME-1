// ?disconnectedCallback@@YAXPAXPBD0@Z
// partial score=0.72 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy /Ireference/shims/stringinline
// stlport
//
// TU-local reconstruction of the callback installed in the disconnected slot
// by PeerThreadClass::Thread_Function.  Retail stores this callback at
// 0x00646F50 and its complete body ends at 0x006470A8 (345 bytes).  The direct
// assignment at Thread_Function+0xAE (0x0064FC3E) supplies the ownership edge.
// The callback uses the BFME 0x330-byte PeerResponse, not the smaller public
// response layout.  The peer RoomType enum is unrelated to this callback and
// remains TitleRoom=0, GroupRoom=1, StagingRoom=2 in the shared ABI.

#include <string>

typedef void *PEER;
typedef bool Bool;
typedef int Int;

enum SerialAuthResult
{
	SERIAL_NONEXISTENT,
	SERIAL_AUTHFAILED,
	SERIAL_BANNED,
	SERIAL_OK
};

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
	DISCONNECT_MAX
};

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
			DisconnectReason reason;
		} discon;

		int words[143];
	};
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
	virtual Bool getResponse(PeerResponse &) = 0;
	virtual SerialAuthResult getSerialAuthResult(void) = 0;
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

// Retail PeerThreadClass has the two connection flags at +0x50 and +0x51.
// Only those bytes are needed here; no wider class identity is claimed.
class PeerThreadClass
{
	char m_prefix[0x50];
	Bool m_isConnecting;
	Bool m_isConnected;

public:
	void markAsDisconnected(void)
	{
		m_isConnecting = m_isConnected = false;
	}
};

#pragma comment(linker, "/alternatename:??0PeerResponse@@QAE@XZ=?j_00042069@@YAXXZ")
#pragma comment(linker, "/alternatename:??1PeerResponse@@QAE@XZ=?j_00044733@@YAXXZ")

#pragma optimize("y", on)
void disconnectedCallback(PEER peer, const char *reason, void *param)
{
	PeerThreadClass *t = (PeerThreadClass *)param;
	if (t)
		t->markAsDisconnected();

	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_DISCONNECT;
	resp.discon.reason = DISCONNECT_LOSTCON;
	SerialAuthResult res = TheGameSpyPeerMessageQueue->getSerialAuthResult();
	switch (res)
	{
		case SERIAL_NONEXISTENT:
			resp.discon.reason = DISCONNECT_SERIAL_NOT_PRESENT;
			break;
		case SERIAL_AUTHFAILED:
			resp.discon.reason = DISCONNECT_SERIAL_INVALID;
			break;
		case SERIAL_BANNED:
			resp.discon.reason = DISCONNECT_SERIAL_BANNED;
			break;
	}
	TheGameSpyPeerMessageQueue->addResponse(resp);
}
#pragma optimize("y", off)
