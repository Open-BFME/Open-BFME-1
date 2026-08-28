// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?addCommand@NetPacket@@QAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// NetPacket::addCommand, 0x006811B0, 408 bytes including its jump table.
//
// A pure dispatcher: every arm tail-jumps to the per-type handler with the same
// argument and `this` untouched in ecx. The reference writes this as an
// if-chain; BFME's cases are dense enough over 0..0x1C that the compiler builds
// a table, so the source has to be a switch.
//
// The case order below is not cosmetic. MSVC lays the arms out in source order,
// so the order is read back out of the image: game command first, then the ack
// stages, the frame command, the per-slot frame ratios, and only then the rest.
// It is very nearly the order ConstructNetCommandMsgFromRawData tests in.
//
// The table is also what names the twenty-eight handlers -- their addresses come
// straight out of it, which is why they can be pinned without owning their
// bodies yet. Five of the reference's arms are absent (run-ahead, run-ahead
// metrics, both packet-router arms and frame-resend-request; BFME has no command
// type for any of them) and eight of BFME's own are here instead.
//
// A null reference and command type 23, the one gap in the enum, both fall
// through to the default and return TRUE.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

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
	NETCOMMANDTYPE_DISCONNECTKEEPALIVE = 24,
	NETCOMMANDTYPE_DISCONNECTPLAYER = 25,
	NETCOMMANDTYPE_DISCONNECTVOTE = 26,
	NETCOMMANDTYPE_DISCONNECTFRAME = 27,
	NETCOMMANDTYPE_DISCONNECTSCREENOFF = 28
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	NetCommandType getNetCommandType() { return m_commandType; }

	void *m_vptr;
	UnsignedInt m_timestamp;						// this+0x04
	UnsignedInt m_executionFrame;					// this+0x08
	UnsignedInt m_playerID;							// this+0x0C
	UnsignedShort m_id;								// this+0x10
	NetCommandType m_commandType;					// this+0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandMsg *getCommand() { return m_msg; }

	NetCommandMsg *m_msg;							// this+0x00
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
public:
	Bool addCommand(NetCommandRef *msg);

protected:
	Bool addGameCommand(NetCommandRef *msg);
	Bool addAckStage1Command(NetCommandRef *msg);
	Bool addAckStage2Command(NetCommandRef *msg);
	Bool addAckBothCommand(NetCommandRef *msg);
	Bool addFrameCommand(NetCommandRef *msg);
	Bool addPlayerFrameRatiosCommand(NetCommandRef *msg);
	Bool addPlayerLeaveCommand(NetCommandRef *msg);
	Bool addDestroyPlayerCommand(NetCommandRef *msg);
	Bool addKeepAliveCommand(NetCommandRef *msg);
	Bool addDisconnectKeepAliveCommand(NetCommandRef *msg);
	Bool addDisconnectPlayerCommand(NetCommandRef *msg);
	Bool addDisconnectChatCommand(NetCommandRef *msg);
	Bool addDisconnectVoteCommand(NetCommandRef *msg);
	Bool addChatCommand(NetCommandRef *msg);
	Bool addProgressMessage(NetCommandRef *msg);
	Bool addLoadCompleteMessage(NetCommandRef *msg);
	Bool addTimeOutGameStartMessage(NetCommandRef *msg);
	Bool addWrapperCommand(NetCommandRef *msg);
	Bool addFileCommand(NetCommandRef *msg);
	Bool addFileAnnounceCommand(NetCommandRef *msg);
	Bool addFileProgressCommand(NetCommandRef *msg);
	Bool addInformPlayerLeaveFrameCommand(NetCommandRef *msg);
	Bool addRequestPlayerLeaveCommand(NetCommandRef *msg);
	Bool addRequestFrameDataCommand(NetCommandRef *msg);
	Bool addDisconnectFrameCommand(NetCommandRef *msg);
	Bool addDisconnectScreenOffCommand(NetCommandRef *msg);
	Bool addRequestGameSpyStatsAuthKeyCommand(NetCommandRef *msg);
	Bool addGameSpyStatsAuthKeyCommand(NetCommandRef *msg);
};

Bool NetPacket::addCommand(NetCommandRef *msg)
{
	if (msg == NULL) {
		return TRUE;
	}

	switch (msg->getCommand()->getNetCommandType()) {
	case NETCOMMANDTYPE_GAMECOMMAND:
		return addGameCommand(msg);
	case NETCOMMANDTYPE_ACKSTAGE1:
		return addAckStage1Command(msg);
	case NETCOMMANDTYPE_ACKSTAGE2:
		return addAckStage2Command(msg);
	case NETCOMMANDTYPE_ACKBOTH:
		return addAckBothCommand(msg);
	case NETCOMMANDTYPE_FRAMEINFO:
		return addFrameCommand(msg);
	case NETCOMMANDTYPE_PLAYERFRAMERATIOS:
		return addPlayerFrameRatiosCommand(msg);
	case NETCOMMANDTYPE_PLAYERLEAVE:
		return addPlayerLeaveCommand(msg);
	case NETCOMMANDTYPE_DESTROYPLAYER:
		return addDestroyPlayerCommand(msg);
	case NETCOMMANDTYPE_KEEPALIVE:
		return addKeepAliveCommand(msg);
	case NETCOMMANDTYPE_DISCONNECTKEEPALIVE:
		return addDisconnectKeepAliveCommand(msg);
	case NETCOMMANDTYPE_DISCONNECTPLAYER:
		return addDisconnectPlayerCommand(msg);
	case NETCOMMANDTYPE_DISCONNECTCHAT:
		return addDisconnectChatCommand(msg);
	case NETCOMMANDTYPE_DISCONNECTVOTE:
		return addDisconnectVoteCommand(msg);
	case NETCOMMANDTYPE_CHAT:
		return addChatCommand(msg);
	case NETCOMMANDTYPE_PROGRESS:
		return addProgressMessage(msg);
	case NETCOMMANDTYPE_LOADCOMPLETE:
		return addLoadCompleteMessage(msg);
	case NETCOMMANDTYPE_TIMEOUTSTART:
		return addTimeOutGameStartMessage(msg);
	case NETCOMMANDTYPE_WRAPPER:
		return addWrapperCommand(msg);
	case NETCOMMANDTYPE_FILE:
		return addFileCommand(msg);
	case NETCOMMANDTYPE_FILEANNOUNCE:
		return addFileAnnounceCommand(msg);
	case NETCOMMANDTYPE_FILEPROGRESS:
		return addFileProgressCommand(msg);
	case NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME:
		return addInformPlayerLeaveFrameCommand(msg);
	case NETCOMMANDTYPE_REQUESTPLAYERLEAVE:
		return addRequestPlayerLeaveCommand(msg);
	case NETCOMMANDTYPE_REQUESTFRAMEDATA:
		return addRequestFrameDataCommand(msg);
	case NETCOMMANDTYPE_DISCONNECTFRAME:
		return addDisconnectFrameCommand(msg);
	case NETCOMMANDTYPE_DISCONNECTSCREENOFF:
		return addDisconnectScreenOffCommand(msg);
	case NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY:
		return addRequestGameSpyStatsAuthKeyCommand(msg);
	case NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY:
		return addGameSpyStatsAuthKeyCommand(msg);
	}

	return TRUE;
}
