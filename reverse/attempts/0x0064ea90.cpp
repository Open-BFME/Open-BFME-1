// ?getRoomKeysCallback@@YAXPAXHW4RoomType@@PBDHPAPAD30@Z
// partial score=0.7 date=2026-09-08
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy
// stlport

#include <string>
#include <cstring>

#define DEBUG_ASSERTCRASH(c, x)

typedef void *PEER;
typedef int Int;
typedef int PEERBool;
typedef unsigned int UnsignedInt;

enum RoomType
{
	GroupRoom,
	StagingRoom
};

class PeerThreadClass
{
public:
	void trackStatsForPlayer(RoomType roomType, const char *nick,
		const char *key, const char *value);
};

class PeerResponse
{
public:
	enum
	{
		PEERRESPONSE_PLAYERINFO = 13
	};

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
			int roomType;
			Int flags;
			UnsignedInt IP;
			Int rankPoints;
			Int side;
			Int preorder;
			char unknown[0x20c];
			Int rank1v1;
			Int rank2v2;
			Int lastLadder;
		} player;
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

extern void getPlayerInfo(PeerThreadClass *thread, PEER peer, const char *nick,
	Int &profileID, UnsignedInt &IP, std::string &locale, Int &wins,
	Int &losses, Int &rankPoints, Int &side, Int &preorder,
	RoomType roomType, Int &flags, Int &rank1v1, Int &rank2v2,
	Int &lastLadder);

#pragma comment(linker, "/alternatename:??0PeerResponse@@QAE@XZ=?j_00042069@@YAXXZ")
#pragma comment(linker, "/alternatename:??1PeerResponse@@QAE@XZ=?j_00044733@@YAXXZ")

#pragma optimize("y", on)
void getRoomKeysCallback(PEER peer, PEERBool success, RoomType roomType,
	const char *nick, int num, char **values, char **keys, void *param)
{
	Int i = 0;
	PeerThreadClass *t = (PeerThreadClass *)param;
	RoomType rt = roomType;
	register Int count = num;
	DEBUG_ASSERTCRASH(t, ("No Peer thread!"));
	if (!t || !nick || !count || !success || !keys || !values)
	{
		DEBUG_ASSERTCRASH(!nick || strcmp(nick, "(END)") == 0,
			("getRoomKeysCallback bad key/value %X/%X, nick=%s", keys, values, nick));
		return;
	}

	for (i = 0; i < count; ++i)
	{
		t->trackStatsForPlayer(rt, nick, values[i], keys[i]);
	}

	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_PLAYERINFO;
	resp.nick = nick;
	resp.player.roomType = rt;

	getPlayerInfo(t, peer, nick, resp.player.profileID, resp.player.IP,
		resp.locale, resp.player.wins, resp.player.losses,
		resp.player.rankPoints, resp.player.side, resp.player.preorder,
		(RoomType)resp.player.roomType, resp.player.flags, resp.player.rank1v1,
		resp.player.rank2v2, resp.player.lastLadder);
	TheGameSpyPeerMessageQueue->addResponse(resp);
}
#pragma optimize("y", off)
