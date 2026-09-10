// ?roomMessageCallback@@YAXPAXW4RoomType@@PBD2W4MessageType@@0@Z
// partial score=0.9 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy /Ireference/shims/stringinline /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// The PeerCallbacks.roomMessage slot is filled at Thread_Function RVA
// 0x0064FC48 with 0x00649ED0.  The complete retail body runs through
// 0x0064A208 (825 bytes); 0x00649FC0 is an interior address from an old
// structural row, not a function entry.
//
// RoomType keeps the authentic Peer.h values TitleRoom=0, GroupRoom=1 and
// StagingRoom=2.  The BFME response object below is local because its retail
// layout is 0x330 bytes, while the public callback layouts are narrower.

#include <string>
#include <vector>

#include "strtok_r.h"

typedef void *PEER;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum RoomType
{
	TitleRoom,
	GroupRoom,
	StagingRoom
};

// GameSpy's peer callback ABI includes NoticeMessage even though the common
// room-message path only uses NormalMessage and ActionMessage.
enum MessageType
{
	NormalMessage,
	ActionMessage,
	NoticeMessage
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
	QM_STOPPED
};

class PeerResponse
{
public:
	enum ResponseType
	{
		PEERRESPONSE_LOGIN,
		PEERRESPONSE_DISCONNECT,
		PEERRESPONSE_MESSAGE = 2,
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
		PEERRESPONSE_QUICKMATCHSTATUS = 17,
		PEERRESPONSE_GAMESTART,
		PEERRESPONSE_FAILEDTOHOST,
		PEERRESPONSE_MAX = 20
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
			Bool isPrivate;
			Bool isAction;
			Int profileID;
		} message;

		struct
		{
			Int status;
			Int poolSize;
		} qmStatus;

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
	virtual bool isThreadRunning(void) = 0;
	virtual bool isConnected(void) = 0;
	virtual bool isConnecting(void) = 0;
	virtual void addRequest(const PeerRequest &) = 0;
	virtual bool getRequest(PeerRequest &) = 0;
	virtual void addResponse(const PeerResponse &) = 0;
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern std::wstring MultiByteToWideCharSingleLine(const char *);
extern "C" int peerGetPlayerInfoNoWaitA(PEER, const char *, UnsignedInt *, Int *);
extern "C" int atoi(const char *);
extern "C" int strcmp(const char *, const char *);

// These offsets are independently present in the retail body: QM status is
// read at PeerThread+0x228 and ladder at PeerThread+0x320.
class PeerThreadClass
{
	char m_beforeQMStatus[0x228];
	QMStatus m_qmStatus;
	char m_betweenQMStatusAndLadder[0xf4];
	Int m_qmLadder;

public:
	QMStatus getQMStatus(void) { return m_qmStatus; }
	Int getQMLadder(void) { return m_qmLadder; }
};

// This is the static PeerThread.cpp variable at retail VA 0x012F750C.
#define MATCHBOT_PROFILE_ID (*(Int *)0x012F750C)

#pragma comment(linker, "/alternatename:??0PeerResponse@@QAE@XZ=?j_00042069@@YAXXZ")
#pragma comment(linker, "/alternatename:??1PeerResponse@@QAE@XZ=?j_00044733@@YAXXZ")

#pragma optimize("y", on)
void roomMessageCallback(PEER peer, RoomType roomType, const char *nick,
	const char *message, MessageType messageType, void *param)
{
	PeerResponse resp;
	if (messageType == NoticeMessage)
	{
		resp.peerResponseType = PeerResponse::PEERRESPONSE_MAX;
		resp.text = MultiByteToWideCharSingleLine(message);
		TheGameSpyPeerMessageQueue->addResponse(resp);
	}
	else
	{
		resp.peerResponseType = PeerResponse::PEERRESPONSE_MESSAGE;
		resp.nick = nick;
		resp.text = MultiByteToWideCharSingleLine(message);
		resp.message.isPrivate = false;
		resp.message.isAction = (messageType == ActionMessage);
		TheGameSpyPeerMessageQueue->addResponse(resp);

		UnsignedInt IP;
		peerGetPlayerInfoNoWaitA(peer, nick, &IP, &resp.message.profileID);
		PeerThreadClass *t = (PeerThreadClass *)param;
		if (t && (t->getQMStatus() != QM_IDLE && t->getQMStatus() != QM_STOPPED))
		{
			if (resp.message.profileID == MATCHBOT_PROFILE_ID)
			{
				char *lastStr = NULL;
				char *cmd = strtok_r((char *)message, " ", &lastStr);
				if (cmd && strcmp(cmd, "MBOT:POOLSIZE") == 0)
				{
					Int poolSize = 0;

					while (1)
					{
						char *poolStr = strtok_r(NULL, " ", &lastStr);
						char *sizeStr = strtok_r(NULL, " ", &lastStr);
						if (poolStr && sizeStr)
						{
							Int pool = atoi(poolStr);
							Int size = atoi(sizeStr);
							if (pool == t->getQMLadder())
							{
								poolSize = size;
								break;
							}
						}
						else
						{
							break;
						}
					}

					PeerResponse resp;
					resp.peerResponseType = PeerResponse::PEERRESPONSE_QUICKMATCHSTATUS;
					resp.qmStatus.status = QM_POOLSIZE;
					resp.qmStatus.poolSize = poolSize;
					TheGameSpyPeerMessageQueue->addResponse(resp);
				}
			}
		}
	}
}
#pragma optimize("y", off)
