// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy /Ireference/shims/stringinline
// stlport
//
// TU-local reconstruction of the BFME PeerThread player-left callback.  The
// callback is installed in PeerThreadClass::Thread_Function at retail
// 0x0064FC70, where the PeerCallbacks.playerLeft slot receives 0x0064AF80.
// Keep the BFME response/request views local: their layouts differ from the
// Zero Hour reference header. RoomType remains Title=0 Group=1 Staging=2.

#include <string>
#include <vector>

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
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
static const Int MAX_SLOTS = 8;

enum RoomType
{
	TitleRoom,
	GroupRoom,
	StagingRoom
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

// This is the BFME request layout used by the matched queue copy body.  The
// callback only writes peerRequestType, but its ctor/dtor still cover the full
// 0x194-byte object before addRequest copies it into the queue.
class PeerRequest
{
public:
	enum
	{
		PEERREQUEST_LOGIN,
		PEERREQUEST_LOGOUT,
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

	std::string nick;
	std::wstring text;
	std::string password;
	std::string email;
	std::string id;
	std::string options;
	std::string ladderIP;
	std::string hostPingStr;
	std::string gameOptsMapName;
	std::string gameOptsPlayerNames[MAX_SLOTS];
	std::vector<bool> qmMaps;

	union
	{
		struct { Int value; } payload0;
		struct { Int value; } payload1;
		struct { Int value; } payload2;
		struct { Bool value; } payload3;
		struct { Bool value; } payload4;
		struct { Int value; } payload5;
		struct { Int words[8]; } payload32;
		struct { Int words[44]; } payload176;
		struct { Bool value; } payload9;
		struct { Int words[23]; } payload92;
		struct { Int words[7]; } payload28;
		struct { Int words[2]; } payload8;
	};
};

typedef char PeerRequestSizeCheck[sizeof(PeerRequest) == 0x194 ? 1 : -1];

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
			Int profileID;
			Int wins;
			Int losses;
			RoomType roomType;
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
		struct
		{
			Int status;
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
	virtual void addRequest(const PeerRequest &) = 0;
	virtual bool getRequest(PeerRequest &) = 0;
	virtual void addResponse(const PeerResponse &) = 0;
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

// The retail callback reads this field at +0x228.  No broader class identity
// is claimed here; the named callback's ownership comes from its registration.
class PeerThreadClass
{
private:
	char m_prefix[0x228];
	QMStatus m_qmStatus;

public:
	QMStatus getQMStatus(void) { return m_qmStatus; }
	Int lookupStatForPlayer(RoomType, const char *, const char *);
};

// Existing matched body at RVA 0x00647920 copies the std::string at +0x3CC.
// Calling its proven address-derived utility preserves the retail by-value
// string ABI without inventing a semantic PeerThread method identity.
class Rva00647920Host
{
public:
	std::string copyStringAt3CC(void);
};

extern "C" int peerGetPlayerInfoNoWaitA(PEER, const char *, UnsignedInt *, Int *);
extern "C" int peerGetPlayerFlagsA(PEER, const char *, RoomType, Int *);

#define BFME_RANK1V1_KEY ((const char *)0x011193E0)
#define BFME_RANK2V2_KEY ((const char *)0x011193D4)
#define BFME_LAST_LADDER_KEY ((const char *)0x01119568)

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
void playerLeftCallback(PEER peer, RoomType roomType, const char *nick,
	const char *reason, void *param)
{
	PeerResponse resp;
	resp.peerResponseType = 11;
	resp.nick = nick;
	resp.player.roomType = roomType;
	resp.player.profileID = 0;

	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t)
		return;

	getPlayerInfo(t, peer, nick, resp.player.profileID, resp.player.IP,
		resp.locale, resp.player.wins, resp.player.losses,
		resp.player.rankPoints, resp.player.side, resp.player.preorder,
		roomType, resp.player.flags, resp.player.rank1v1,
		resp.player.rank2v2, resp.player.lastLadder);
	TheGameSpyPeerMessageQueue->addResponse(resp);

	if (t->getQMStatus() != QM_IDLE && t->getQMStatus() != QM_STOPPED)
	{
		if (!stricmp(((Rva00647920Host *)t)->copyStringAt3CC().c_str(), nick))
		{
			PeerResponse resp;
			resp.peerResponseType = 17;
			resp.qmStatus.status = QM_COULDNOTFINDBOT;
			TheGameSpyPeerMessageQueue->addResponse(resp);

			PeerRequest req;
			req.peerRequestType = PeerRequest::PEERREQUEST_STOPQUICKMATCH;
			TheGameSpyPeerMessageQueue->addRequest(req);
		}
	}
}
#pragma optimize("y", off)
