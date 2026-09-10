// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy /Ireference/shims/stringinline
// stlport
//
// This callback uses the retail BFME PeerResponse layout.  Keep its ABI slice
// local so the source conversion does not alter the shared PeerThread header.

#include <string>

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void format( AsciiString format, ... );
	const char *str( void ) const { return m_data ? m_data->m_text : ""; }
};

typedef void *PEER;
typedef int Int;
typedef unsigned int UnsignedInt;

enum RoomType
{
	TitleRoom,
	GroupRoom,
	StagingRoom
};

class PeerThreadClass
{
public:
	Int lookupStatForPlayer(RoomType, const char *, const char *);
};

extern "C" int peerGetPlayerInfoNoWaitA(PEER, const char *, UnsignedInt *, Int *);
extern "C" int peerGetPlayerFlagsA(PEER, const char *, RoomType, Int *);

#define BFME_RANK1V1_KEY ((const char *)0x011193E0)
#define BFME_RANK2V2_KEY ((const char *)0x011193D4)
#define BFME_LAST_LADDER_KEY ((const char *)0x01119568)

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

__declspec(noinline) static void getPlayerInfo(PeerThreadClass *thread,
	PEER peer, const char *nick, Int &id, UnsignedInt &ip, std::string &locale,
	Int &wins, Int &losses, Int &rankPoints, Int &side, Int &preorder,
	RoomType roomType, Int &flags, Int &rank1v1, Int &rank2v2,
	Int &lastLadder)
{
	if (!thread || !nick)
		return;
	peerGetPlayerInfoNoWaitA(peer, nick, &ip, &id);
	Int localeIndex = thread->lookupStatForPlayer(roomType, nick, "b_locale");
	AsciiString tmp;
	tmp.format("%d", localeIndex);
	locale = tmp.str();
	wins = thread->lookupStatForPlayer(roomType, nick, "b_wins");
	losses = thread->lookupStatForPlayer(roomType, nick, "b_losses");
	rankPoints = thread->lookupStatForPlayer(roomType, nick, "b_points");
	side = thread->lookupStatForPlayer(roomType, nick, "b_side");
	preorder = thread->lookupStatForPlayer(roomType, nick, "b_pre");
	flags = 0;
	rank1v1 = thread->lookupStatForPlayer(roomType, nick, BFME_RANK1V1_KEY);
	rank2v2 = thread->lookupStatForPlayer(roomType, nick, BFME_RANK2V2_KEY);
	lastLadder = thread->lookupStatForPlayer(roomType, nick, BFME_LAST_LADDER_KEY);
	peerGetPlayerFlagsA(peer, nick, roomType, &flags);
}

#pragma comment(linker, "/alternatename:??0PeerResponse@@QAE@XZ=?j_00042069@@YAXXZ")
#pragma comment(linker, "/alternatename:??1PeerResponse@@QAE@XZ=?j_00044733@@YAXXZ")

#pragma optimize("y", on)
void playerJoinedCallback(PEER peer, RoomType roomType, const char *nick,
	void *param)
{
	if (!nick)
		return;

	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t)
		return;

	PeerResponse resp;
	resp.peerResponseType = 10;
	resp.nick = nick;
	resp.player.roomType = roomType;

	getPlayerInfo(t, peer, nick, resp.player.profileID, resp.player.IP,
		resp.locale, resp.player.wins, resp.player.losses,
		resp.player.rankPoints, resp.player.side, resp.player.preorder,
		roomType, resp.player.flags, resp.player.rank1v1,
		resp.player.rank2v2, resp.player.lastLadder);
	TheGameSpyPeerMessageQueue->addResponse(resp);
}
#pragma optimize("y", off)
