// ?playerMessageCallback@@YAXPAXPBD1W4MessageType@@0@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy
// stlport
//
// The PeerCallbacks table built by PeerThreadClass::Thread_Function at
// 0x0064FB90 stores 0x0064A2E0 in its playerMessage slot (+0x14).  The old
// ledger name at this address was a naked nick-error lift; the retail body
// parses the player-message MBOT protocol and is the reference's
// playerMessageCallback at PeerThread.cpp:2478. BFME parses six tokens per
// player; the sixth field has unknown original spelling and is named extra.
// A literal -1 in that field is replaced with -- before the nine-argument
// handleQMMatch call. Retaining the NAT token across parsing the extra field
// reflects the real validity test; it is the fifth token that counts players.
// PeerResponse uses natural STLport strings and the proven 0x330-byte ABI;
// its union includes the handler's port and extra arrays for consistency.

#include <string>
#include <string.h>
#include <stdlib.h>

char *strtok_r(char *text, const char *delimiters, char **lasts);

typedef void *PEER;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
static const Int MAX_SLOTS = 8;

enum MessageType
{
	NormalMessage,
	ActionMessage
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
	int peerResponseType;

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
	std::string stagingRoomPlayerNames[MAX_SLOTS];
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
			QMStatus status;
			Int poolSize;
			Int mapIdx;
			Int seed;
			UnsignedInt IP[MAX_SLOTS];
			unsigned short port[MAX_SLOTS];
			Int side[MAX_SLOTS];
			Int color[MAX_SLOTS];
			Int nat[MAX_SLOTS];
			Int extra[MAX_SLOTS];
		} qmStatus;
		int words[143];
	};
};

typedef char PeerResponseSizeCheck[sizeof(PeerResponse) == 0x330 ? 1 : -1];

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread(void) = 0;
	virtual void endThread(void) = 0;
	virtual bool isThreadRunning(void) = 0;
	virtual bool isConnected(void) = 0;
	virtual bool isConnecting(void) = 0;
	virtual void addRequest(const void *) = 0;
	virtual bool getRequest(void *) = 0;
	virtual void addResponse(const PeerResponse &) = 0;
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern std::wstring MultiByteToWideCharSingleLine(const char *text);
extern "C" int peerGetPlayerInfoNoWaitA(PEER peer, const char *nick,
	UnsignedInt *IP, Int *profileID);


class PeerThreadClass
{
public:
	QMStatus getQMStatus(void) { return *(QMStatus *)((char *)this + 0x228); }
	void handleQMMatch(PEER peer, Int mapIndex, Int seed,
		char *playerName[MAX_SLOTS], char *playerIP[MAX_SLOTS],
		char *playerSide[MAX_SLOTS], char *playerColor[MAX_SLOTS],
		char *playerNAT[MAX_SLOTS], char *playerExtra[MAX_SLOTS]);
};

// PeerThread.cpp's static matchbotProfileID is placed at this proven retail
// address.  A direct TU-local view keeps the callback tied to that state
// without exporting or inventing a second variable.
#define BFME_MATCHBOT_PROFILE_ID (*(Int *)0x012F750C)

#pragma optimize("y", on)
void playerMessageCallback(PEER peer, const char *nick, const char *message,
	MessageType messageType, void *param)
{
	PeerResponse resp;
	resp.peerResponseType = 2;
	resp.nick = nick;
	resp.text = MultiByteToWideCharSingleLine(message);
	resp.message.isPrivate = 1;
	resp.message.isAction = (messageType == ActionMessage);
	UnsignedInt IP;
	peerGetPlayerInfoNoWaitA(peer, nick, &IP, &resp.message.profileID);
	TheGameSpyPeerMessageQueue->addResponse(resp);

	PeerThreadClass *t = (PeerThreadClass *)param;
	if (t && (t->getQMStatus() != QM_IDLE && t->getQMStatus() != QM_STOPPED))
	{
		if (resp.message.isPrivate && resp.message.profileID == BFME_MATCHBOT_PROFILE_ID)
		{
			char *lastStr = NULL;
			char *cmd = strtok_r((char *)message, " ", &lastStr);
			if (cmd && strcmp(cmd, "MBOT:MATCHED") == 0)
			{
				char *mapNumStr = strtok_r(NULL, " ", &lastStr);
				char *seedStr = strtok_r(NULL, " ", &lastStr);
				char *playerStr[MAX_SLOTS];
				char *playerIPStr[MAX_SLOTS];
				char *playerSideStr[MAX_SLOTS];
				char *playerColorStr[MAX_SLOTS];
				char *playerNATStr[MAX_SLOTS];
				char *playerExtraStr[MAX_SLOTS];
				Int numPlayers = 0;
				for (Int i = 0; i < MAX_SLOTS; ++i)
				{
					playerStr[i] = strtok_r(NULL, " ", &lastStr);
					playerIPStr[i] = strtok_r(NULL, " ", &lastStr);
					playerSideStr[i] = strtok_r(NULL, " ", &lastStr);
					playerColorStr[i] = strtok_r(NULL, " ", &lastStr);
					char *natToken = strtok_r(NULL, " ", &lastStr);
					playerNATStr[i] = natToken;
					playerExtraStr[i] = strtok_r(NULL, " ", &lastStr);
					if (playerExtraStr[i] && strcmp(playerExtraStr[i], "-1") == 0)
						playerExtraStr[i] = "--";
					if (natToken)
					{
						++numPlayers;
					}
					else
					{
						playerStr[i] = NULL;
						playerIPStr[i] = NULL;
						playerSideStr[i] = NULL;
						playerColorStr[i] = NULL;
						playerNATStr[i] = NULL;
						playerExtraStr[i] = NULL;
					}
				}

				if (numPlayers > 1)
				{
					t->handleQMMatch(peer, atoi(mapNumStr),
						atoi(seedStr), playerStr, playerIPStr,
						playerSideStr, playerColorStr, playerNATStr, playerExtraStr);
				}
			}
			else if (cmd && strcmp(cmd, "MBOT:WORKING") == 0)
			{
				Int poolSize = 0;
				char *poolStr = strtok_r(NULL, " ", &lastStr);
				if (poolStr)
					poolSize = atoi(poolStr);
				PeerResponse resp;
				resp.peerResponseType = 17;
				resp.qmStatus.status = QM_WORKING;
				resp.qmStatus.poolSize = poolSize;
				TheGameSpyPeerMessageQueue->addResponse(resp);
			}
			else if (cmd && strcmp(cmd, "MBOT:WIDENINGSEARCH") == 0)
			{
				PeerResponse resp;
				resp.peerResponseType = 17;
				resp.qmStatus.status = QM_WIDENINGSEARCH;
				TheGameSpyPeerMessageQueue->addResponse(resp);
			}
		}
	}
}
#pragma optimize("y", off)
