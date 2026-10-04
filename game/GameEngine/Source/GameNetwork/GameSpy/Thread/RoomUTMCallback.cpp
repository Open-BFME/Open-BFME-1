// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy
// stlport
//
// TU-local reconstruction of the BFME PeerResponse ABI.  RoomType's values
// are the retail peer-room values: TitleRoom=0, GroupRoom=1, StagingRoom=2.

#include <string>

// Retail constructs and destroys the response through the incremental-link
// thunks at RVA 0x00042069 and 0x00044733, so this TU calls those two bodies
// directly instead of naming the constructor/destructor symbols.  PeerResponse
// below is therefore never instantiated: RespThunkedPeerResponse owns the
// 0x330 bytes, routes both calls itself, and the fields are read back through
// a layout reference.
extern void j_00042069();
extern void j_00044733();

typedef void *PEER;
typedef int PEERBool;

enum RoomType
{
	TitleRoom,
	GroupRoom,
	StagingRoom
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
	std::string stagingRoomPlayerNames[8];
	std::string command;
	std::string commandOptions;

	union
	{
		struct
		{
			int profileID;
			int wins;
			int losses;
			int roomType;
			int flags;
			unsigned int IP;
			int rankPoints;
			int side;
			int preorder;
			char unknown[0x20c];
			int rank1v1;
			int rank2v2;
			int lastLadder;
		} player;
		int words[143];
	};
};

typedef char PeerResponseSizeCheck[sizeof(PeerResponse) == 0x330 ? 1 : -1];

// Empty class only used as the thiscall route type for the two thunks above:
// the union lets the compiler keep this in ecx and still call j_00042069 /
// j_00044733 by name, which is what retail's two call sites do.
class RespThunkRoute {};

class RespThunkedPeerResponse
{
public:
	inline RespThunkedPeerResponse()
	{
		typedef void (RespThunkRoute::*Route)();
		union { void (*fn)(); Route call; } u = { j_00042069 };
		(reinterpret_cast<RespThunkRoute *>(this)->*u.call)();
	}
	inline ~RespThunkedPeerResponse()
	{
		typedef void (RespThunkRoute::*Route)();
		union { void (*fn)(); Route call; } u = { j_00044733 };
		(reinterpret_cast<RespThunkRoute *>(this)->*u.call)();
	}
	char raw[sizeof(PeerResponse)];
};

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

#pragma optimize("y", on)
void roomUTMCallback(PEER peer, RoomType roomType, const char *nick,
	const char *command, const char *parameters, PEERBool authenticated,
	void *param)
{
	if (roomType != StagingRoom)
		return;
	RespThunkedPeerResponse storage;
	PeerResponse &resp = *reinterpret_cast<PeerResponse *>(storage.raw);
	resp.peerResponseType = 15;
	if (nick)
	{
		resp.nick = nick;
		resp.command = command;
		resp.commandOptions = parameters;
		TheGameSpyPeerMessageQueue->addResponse(resp);
	}
}
#pragma optimize("y", off)
