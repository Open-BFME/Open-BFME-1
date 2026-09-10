// ?joinRoomCallback@@YAXPAXHW4PEERJoinResult@@W4RoomType@@0@Z
// partial score=0.8 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy
// stlport
//
// Retail 0x0064ECC0: PeerThread's joinRoomCallback, including the complete
// 626-byte body.  The callback is registered by both peerJoinGroupRoom and
// peerJoinStagingRoom in PeerThread.cpp.  This TU keeps the measured callback
// ABI local because PeerThread.cpp's current stats-key/class layout is four
// bytes later than this retail body.

#include <map>
#include <string>

typedef void *PEER;
typedef int Int;
typedef int PEERBool;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum
{
	PEERFalse,
	PEERTrue
};

enum RoomType
{
	TitleRoom,
	GroupRoom,
	StagingRoom
};

enum PEERJoinResult
{
	PEERJoinSuccess,
	PEERFullRoom,
	PEERInviteOnlyRoom,
	PEERBannedFromRoom,
	PEERBadPassword,
	PEERAlreadyInRoom,
	PEERNoTitleSet,
	PEERNoConnection,
	PEERAutoMatching,
	PEERJoinFailed
};

enum GameSpyBuddyStatus
{
	BUDDY_OFFLINE,
	BUDDY_ONLINE,
	BUDDY_LOBBY,
	BUDDY_STAGING,
	BUDDY_LOADING,
	BUDDY_PLAYING,
	BUDDY_MATCHING,
	BUDDY_MAX
};

typedef std::map<std::string, int> PlayerStatMap;

class PeerResponse
{
public:
	PeerResponse();
	~PeerResponse();

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
			Int id;
			Bool ok;
		} joinGroupRoom;

		struct
		{
			Int id;
			Bool ok;
			Bool isHostPresent;
			Int result;
		} joinStagingRoom;

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

extern void updateBuddyStatus(volatile GameSpyBuddyStatus status,
	Int groupRoom = 0, std::string gameName = "");
extern std::string WideCharStringToMultiByte(const wchar_t *text);

extern "C" void peerGetRoomKeysA(PEER peer, int roomType, const char *nick,
	int num, const char **keys, void *callback, void *param, int blocking);
extern "C" void peerEnumPlayers(PEER peer, int roomType, void *callback,
	void *param);

typedef void (*RoomKeyCallback)(PEER, PEERBool, RoomType, const char *,
	int, char **, char **, void *);
extern void getRoomKeysCallback(PEER, PEERBool, RoomType, const char *, int,
	char **, char **, void *);

typedef void (*RoomPlayerCallback)(PEER, PEERBool, RoomType, int,
	const char *, int, void *);
extern void stagingRoomPlayerEnum(PEER, PEERBool, RoomType, int,
	const char *, int, void *);

// The retail callback asks for all eight persisted player-stat keys.  The
// matched dispatchSix body separately proves that the first six are also the
// keys pushed when joining a room.
static const char *s_roomKeys[8] =
{
	"b_locale", "b_wins", "b_losses", "b_points", "b_side", "b_pre",
	"b_rank1v1", "b_rank2v2"
};

// 0x00643BC0 and 0x00643C10 are already matched ICF bodies.  Their object
// layouts prove a value at +0x54 and one PEER argument; the join callback's
// two calls use those exact bodies through the corresponding typed methods.
struct DualIndexedDispatchThunk
{
	unsigned char padding[0x54];
	void *value;

	void dispatch(void *target);
	void dispatchSix(void *target);
};

// The measured retail body at 0x00647780 copies the std::wstring at +0x218.
// Its source identity and extent are independently matched in
// RvaStringAccessor.cpp.
class Rva00647780Host
{
public:
	std::wstring copyStringAt218(void);
};

class PeerThreadClass
{
public:
	void clearPlayerStats(RoomType roomType)
	{
		switch (roomType)
		{
		case GroupRoom:
			m_groupRoomStats.clear();
			break;
		case StagingRoom:
			m_stagingRoomStats.clear();
			break;
		}
	}

	Int getLocalRoomID(void)
	{
		return *reinterpret_cast<Int *>(reinterpret_cast<char *>(this) + 0x224);
	}

	void roomJoined(Bool value)
	{
		*reinterpret_cast<Bool *>(reinterpret_cast<char *>(this) + 0x3c0) = value;
	}

	Int getQMGroupRoom(void)
	{
		return *reinterpret_cast<Int *>(reinterpret_cast<char *>(this) + 0x3c4);
	}

private:
	char m_bfmeHead[0x94];
	PlayerStatMap m_groupRoomStats;
	PlayerStatMap m_stagingRoomStats;
};

typedef char PeerThreadStatsOffsetCheck[
	(sizeof(PeerThreadClass) >= 0xac) ? 1 : -1];

#pragma comment(linker, "/alternatename:??0PeerResponse@@QAE@XZ=?j_00042069@@YAXXZ")
#pragma comment(linker, "/alternatename:??1PeerResponse@@QAE@XZ=?j_00044733@@YAXXZ")

#pragma optimize("y", on)
void joinRoomCallback(PEER peer, PEERBool success, PEERJoinResult result,
	RoomType roomType, void *param)
{
	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t)
		return;

	if (success)
	{
		reinterpret_cast<DualIndexedDispatchThunk *>(t)->dispatchSix(peer);
		reinterpret_cast<DualIndexedDispatchThunk *>(t)->dispatch(peer);
		peerGetRoomKeysA(peer, roomType, "*", 8, s_roomKeys,
			(void *)getRoomKeysCallback, t, PEERFalse);
	}

	switch (roomType)
	{
	case GroupRoom:
		{
			t->clearPlayerStats(GroupRoom);
			PeerResponse resp;
			resp.peerResponseType = 7;
			resp.joinGroupRoom.id = t->getLocalRoomID();
			resp.joinGroupRoom.ok = success;
			TheGameSpyPeerMessageQueue->addResponse(resp);
			t->roomJoined(success == PEERTrue);
			if ((!t->getQMGroupRoom()) ||
				(t->getQMGroupRoom() != t->getLocalRoomID()))
			{
				updateBuddyStatus(BUDDY_LOBBY, t->getLocalRoomID());
			}
		}
		break;
	case StagingRoom:
		{
			t->clearPlayerStats(StagingRoom);
			PeerResponse resp;
			resp.peerResponseType = 9;
			resp.joinStagingRoom.id = t->getLocalRoomID();
			resp.joinStagingRoom.ok = success;
			resp.joinStagingRoom.result = result;
			if (success)
			{
				updateBuddyStatus(BUDDY_STAGING, 0,
					WideCharStringToMultiByte(
						reinterpret_cast<Rva00647780Host *>(t)->copyStringAt218().c_str()));
			}

			resp.joinStagingRoom.isHostPresent = false;
			peerEnumPlayers(peer, StagingRoom,
				(void *)stagingRoomPlayerEnum, &resp);
			TheGameSpyPeerMessageQueue->addResponse(resp);
		}
		break;
	}
}
#pragma optimize("y", off)
