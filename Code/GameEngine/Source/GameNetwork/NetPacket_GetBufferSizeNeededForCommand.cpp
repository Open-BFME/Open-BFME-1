// cl: /DNDEBUG /MD /EHsc
// readable body of ?GetBufferSizeNeededForCommand@NetPacket@@KAIPAVNetCommandMsg@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?GetGameCommandSize@NetPacket@@KAIPAVNetCommandMsg@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// NetPacket::GetBufferSizeNeededForCommand, 0x0067F2E0, 149 bytes -- the
// per-command-type size dispatcher, and the counterpart of addCommand's own
// jump table.
//
// Its arms are what name it and what it names. Six of them tail-jump to
// Get*CommandSize helpers already ledgered by their own bodies
// (DisconnectChat, Chat, File, FileAnnounce and, landed alongside this,
// the two GameSpy stats auth-key ones). The seventh, for command type 4,
// reaches 0x00676A00 -- pinned here as GetGameCommandSize by exactly the rule
// the other six were named by, and the body there opens with
// constructGameMessage and a GameMessageParser, which is what the reference's
// GetGameCommandSize does.
//
// Everything else in the table is a constant, and that is the interesting
// part: retail's own per-type helpers for those command types are six-byte
// `mov eax, K / ret` bodies, so MSVC inlines every one of them. It does that
// AFTER building the jump table, which is why this compiles to a direct
// twenty-nine-entry dword table rather than the byte-index form: at the point
// the table is chosen there are twenty-six distinct arms, and the folding down
// to seventeen blocks happens in place afterwards. Writing the constants
// directly in the cases instead reproduces the same seventeen blocks in the
// same order but compresses the table, and no combination of optimisation
// flags brings it back. So the helpers are spelled here, inline, as the
// constants the jump table proves they return.
//
// Their names are the family's: the reference's own for the twenty types it
// has, and Get<Type>CommandSize for BFME's four additions, whose type names
// NetPacket_addCommand.cpp already pins from its own table. Only the
// dispatcher is claimed in the ledger -- these inline bodies are a local model
// of retail's, not a claim on the addresses they live at.
//
// The case order is read back out of the image the same way
// NetPacket_addCommand.cpp reads its own: MSVC lays the arms out in source
// order, so the order of the seventeen surviving blocks is the order of the
// first case that reaches each of them.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef float Real;
typedef UnsignedInt ObjectID;
typedef UnsignedInt DrawableID;
typedef bool Bool;
typedef unsigned short WideChar;

struct Coord3D { Real x, y, z; };
struct ICoord2D { Int x, y; };
struct IRegion2D { Int loX, loY, hiX, hiY; };

#define NULL 0
#define TRUE 1

enum NetCommandType
{
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1 = 1,
	NETCOMMANDTYPE_ACKSTAGE2 = 2,
	NETCOMMANDTYPE_FRAMEINFO = 3,
	NETCOMMANDTYPE_GAMECOMMAND = 4,
	NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY = 5,
	NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY = 6,
	NETCOMMANDTYPE_REQUESTPLAYERLEAVE = 7,
	NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME = 8,
	NETCOMMANDTYPE_REQUESTFRAMEDATA = 9,
	NETCOMMANDTYPE_PLAYERLEAVE = 10,
	NETCOMMANDTYPE_DESTROYPLAYER = 11,
	NETCOMMANDTYPE_KEEPALIVE = 12,
	NETCOMMANDTYPE_DISCONNECTCHAT = 13,
	NETCOMMANDTYPE_CHAT = 14,
	NETCOMMANDTYPE_PROGRESS = 15,
	NETCOMMANDTYPE_LOADCOMPLETE = 16,
	NETCOMMANDTYPE_TIMEOUTSTART = 17,
	NETCOMMANDTYPE_WRAPPER = 18,
	NETCOMMANDTYPE_FILE = 19,
	NETCOMMANDTYPE_FILEANNOUNCE = 20,
	NETCOMMANDTYPE_FILEPROGRESS = 21,
	NETCOMMANDTYPE_PLAYERFRAMERATIOS = 22,
	NETCOMMANDTYPE_DISCONNECTSTART = 23,
	NETCOMMANDTYPE_DISCONNECTKEEPALIVE = 24,
	NETCOMMANDTYPE_DISCONNECTPLAYER = 25,
	NETCOMMANDTYPE_DISCONNECTVOTE = 26,
	NETCOMMANDTYPE_DISCONNECTFRAME = 27,
	NETCOMMANDTYPE_DISCONNECTSCREENOFF = 28
};

enum GameMessageArgumentDataType
{
	ARGUMENTDATATYPE_INTEGER = 0,
	ARGUMENTDATATYPE_REAL,
	ARGUMENTDATATYPE_BOOLEAN,
	ARGUMENTDATATYPE_OBJECTID,
	ARGUMENTDATATYPE_DRAWABLEID,
	ARGUMENTDATATYPE_TEAMID,
	ARGUMENTDATATYPE_SQUADID,
	ARGUMENTDATATYPE_LOCATION,
	ARGUMENTDATATYPE_PIXEL,
	ARGUMENTDATATYPE_PIXELREGION,
	ARGUMENTDATATYPE_TIMESTAMP,
	ARGUMENTDATATYPE_WIDECHAR
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	virtual ~GameMessage();
	typedef Int Type;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	NetCommandType getNetCommandType() { return m_commandType; }

	void *m_vptr;
	UnsignedInt m_timestamp;					// this+0x04
	UnsignedInt m_executionFrame;					// this+0x08
	UnsignedInt m_playerID;						// this+0x0C
	UnsignedShort m_id;						// this+0x10
	NetCommandType m_commandType;					// this+0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetGameCommandMsg : public NetCommandMsg
{
public:
	GameMessage *constructGameMessage();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameMessageParser.h
class GameMessageParserArgumentType
{
public:
	GameMessageParserArgumentType *getNext() { return m_next; }
	GameMessageArgumentDataType getType() { return m_type; }
	Int getArgCount() { return m_argCount; }

	void *m_vptr;
	GameMessageParserArgumentType *m_next;
	GameMessageArgumentDataType m_type;
	Int m_argCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameMessageParser.h
class GameMessageParser
{
public:
	GameMessageParser(GameMessage *msg);
	virtual ~GameMessageParser();
	GameMessageParserArgumentType *getFirstArgumentType() { return m_first; }

	GameMessageParserArgumentType *m_first;
	GameMessageParserArgumentType *m_last;
	Int m_argTypeCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
protected:
	static UnsignedInt GetBufferSizeNeededForCommand(NetCommandMsg *msg);

	static UnsignedInt GetGameCommandSize(NetCommandMsg *msg);			// 0x00676A00

	static UnsignedInt GetFrameCommandSize(NetCommandMsg *msg) { return 0x16; }
	static UnsignedInt GetDestroyPlayerCommandSize(NetCommandMsg *msg) { return 0x13; }
	static UnsignedInt GetDisconnectPlayerCommandSize(NetCommandMsg *msg) { return 0xF; }
	static UnsignedInt GetDisconnectVoteCommandSize(NetCommandMsg *msg) { return 0xF; }
	static UnsignedInt GetAckCommandSize(NetCommandMsg *msg) { return 8; }
	static UnsignedInt GetProgressMessageSize(NetCommandMsg *msg) { return 8; }
	static UnsignedInt GetKeepAliveCommandSize(NetCommandMsg *msg) { return 7; }
	static UnsignedInt GetLoadCompleteMessageSize(NetCommandMsg *msg) { return 7; }
	static UnsignedInt GetTimeOutGameStartMessageSize(NetCommandMsg *msg) { return 7; }
	static UnsignedInt GetDisconnectKeepAliveCommandSize(NetCommandMsg *msg) { return 7; }
	static UnsignedInt GetWrapperCommandSize(NetCommandMsg *msg) { return 0x20; }
	static UnsignedInt GetPlayerLeaveCommandSize(NetCommandMsg *msg) { return 0x10; }
	static UnsignedInt GetInformPlayerLeaveFrameCommandSize(NetCommandMsg *msg) { return 0x10; }
	static UnsignedInt GetFileProgressCommandSize(NetCommandMsg *msg) { return 0x10; }
	static UnsignedInt GetRequestFrameDataCommandSize(NetCommandMsg *msg) { return 0x12; }
	static UnsignedInt GetPlayerFrameRatiosCommandSize(NetCommandMsg *msg) { return 0x12; }
	static UnsignedInt GetRequestPlayerLeaveCommandSize(NetCommandMsg *msg) { return 0xE; }
	static UnsignedInt GetDisconnectFrameCommandSize(NetCommandMsg *msg) { return 0xE; }
	static UnsignedInt GetDisconnectScreenOffCommandSize(NetCommandMsg *msg) { return 0xE; }
	static UnsignedInt GetDisconnectChatCommandSize(NetCommandMsg *msg);		// 0x0067D370
	static UnsignedInt GetChatCommandSize(NetCommandMsg *msg);			// 0x0067D3C0
	static UnsignedInt GetFileCommandSize(NetCommandMsg *msg);			// 0x0067D410
	static UnsignedInt GetFileAnnounceCommandSize(NetCommandMsg *msg);		// 0x0067D460
	static UnsignedInt GetRequestGameSpyStatsAuthKeyCommandSize(NetCommandMsg *msg);	// 0x0067D4B0
	static UnsignedInt GetGameSpyStatsAuthKeyCommandSize(NetCommandMsg *msg);	// 0x0067D500
};

UnsignedInt NetPacket::GetGameCommandSize(NetCommandMsg *msg) {
	NetGameCommandMsg *cmdMsg = (NetGameCommandMsg *)msg;
	UnsignedShort msglen = 0;
	msglen += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	msglen += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	msglen += sizeof(UnsignedByte);
	GameMessage *gmsg = cmdMsg->constructGameMessage();
	GameMessageParser *parser = new GameMessageParser(gmsg);
	msglen += sizeof(GameMessage::Type);
	msglen += sizeof(UnsignedByte);
	GameMessageParserArgumentType *arg = parser->getFirstArgumentType();
	while (arg != NULL) {
		msglen += 2 * sizeof(UnsignedByte);
		GameMessageArgumentDataType type = arg->getType();
		if (type == ARGUMENTDATATYPE_INTEGER) {
			msglen += arg->getArgCount() * sizeof(Int);
		} else if (type == ARGUMENTDATATYPE_REAL) {
			msglen += arg->getArgCount() * sizeof(Real);
		} else if (type == ARGUMENTDATATYPE_BOOLEAN) {
			msglen += arg->getArgCount() * sizeof(Bool);
		} else if (type == ARGUMENTDATATYPE_OBJECTID) {
			msglen += arg->getArgCount() * sizeof(ObjectID);
		} else if (type == ARGUMENTDATATYPE_DRAWABLEID) {
			msglen += arg->getArgCount() * sizeof(DrawableID);
		} else if (type == ARGUMENTDATATYPE_TEAMID) {
			msglen += arg->getArgCount() * sizeof(UnsignedInt);
		} else if (type == ARGUMENTDATATYPE_LOCATION) {
			msglen += arg->getArgCount() * sizeof(Coord3D);
		} else if (type == ARGUMENTDATATYPE_PIXEL) {
			msglen += arg->getArgCount() * sizeof(ICoord2D);
		} else if (type == ARGUMENTDATATYPE_PIXELREGION) {
			msglen += arg->getArgCount() * sizeof(IRegion2D);
		} else if (type == ARGUMENTDATATYPE_TIMESTAMP) {
			msglen += arg->getArgCount() * sizeof(UnsignedInt);
		} else if (type == ARGUMENTDATATYPE_WIDECHAR) {
			msglen += arg->getArgCount() * sizeof(WideChar);
		}
		arg = arg->getNext();
	}
	delete parser;
	parser = NULL;
	delete gmsg;
	gmsg = NULL;
	return msglen;
}

// ?GetBufferSizeNeededForCommand@NetPacket@@KAIPAVNetCommandMsg@@@Z
UnsignedInt NetPacket::GetBufferSizeNeededForCommand(NetCommandMsg *msg) {
	// This is where the fun begins...

	if (msg == NULL) {
		return TRUE; // There was nothing to add, so it was successful.
	}

	switch(msg->getNetCommandType())
	{
		case NETCOMMANDTYPE_GAMECOMMAND:
			return GetGameCommandSize(msg);
		case NETCOMMANDTYPE_FRAMEINFO:
			return GetFrameCommandSize(msg);
		case NETCOMMANDTYPE_DESTROYPLAYER:
			return GetDestroyPlayerCommandSize(msg);
		case NETCOMMANDTYPE_DISCONNECTCHAT:
			return GetDisconnectChatCommandSize(msg);
		case NETCOMMANDTYPE_DISCONNECTPLAYER:
			return GetDisconnectPlayerCommandSize(msg);
		case NETCOMMANDTYPE_DISCONNECTVOTE:
			return GetDisconnectVoteCommandSize(msg);
		case NETCOMMANDTYPE_CHAT:
			return GetChatCommandSize(msg);
		case NETCOMMANDTYPE_ACKBOTH:
		case NETCOMMANDTYPE_ACKSTAGE1:
		case NETCOMMANDTYPE_ACKSTAGE2:
			return GetAckCommandSize(msg);
		case NETCOMMANDTYPE_PROGRESS:
			return GetProgressMessageSize(msg);
		case NETCOMMANDTYPE_KEEPALIVE:
			return GetKeepAliveCommandSize(msg);
		case NETCOMMANDTYPE_LOADCOMPLETE:
			return GetLoadCompleteMessageSize(msg);
		case NETCOMMANDTYPE_TIMEOUTSTART:
			return GetTimeOutGameStartMessageSize(msg);
		case NETCOMMANDTYPE_DISCONNECTKEEPALIVE:
			return GetDisconnectKeepAliveCommandSize(msg);
		case NETCOMMANDTYPE_WRAPPER:
			return GetWrapperCommandSize(msg);
		case NETCOMMANDTYPE_FILE:
			return GetFileCommandSize(msg);
		case NETCOMMANDTYPE_FILEANNOUNCE:
			return GetFileAnnounceCommandSize(msg);
		case NETCOMMANDTYPE_PLAYERLEAVE:
			return GetPlayerLeaveCommandSize(msg);
		case NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME:
			return GetInformPlayerLeaveFrameCommandSize(msg);
		case NETCOMMANDTYPE_FILEPROGRESS:
			return GetFileProgressCommandSize(msg);
		case NETCOMMANDTYPE_REQUESTFRAMEDATA:
			return GetRequestFrameDataCommandSize(msg);
		case NETCOMMANDTYPE_PLAYERFRAMERATIOS:
			return GetPlayerFrameRatiosCommandSize(msg);
		case NETCOMMANDTYPE_REQUESTPLAYERLEAVE:
			return GetRequestPlayerLeaveCommandSize(msg);
		case NETCOMMANDTYPE_DISCONNECTFRAME:
			return GetDisconnectFrameCommandSize(msg);
		case NETCOMMANDTYPE_DISCONNECTSCREENOFF:
			return GetDisconnectScreenOffCommandSize(msg);
		case NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY:
			return GetRequestGameSpyStatsAuthKeyCommandSize(msg);
		case NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY:
			return GetGameSpyStatsAuthKeyCommandSize(msg);
		default:
			break;
	}

	return 0;
}
