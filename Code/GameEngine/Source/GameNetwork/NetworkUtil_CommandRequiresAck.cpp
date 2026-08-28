// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// CommandRequiresAck, 0x00682DB0, 116 bytes.
//
// This is the predicate Connection::doSend uses to decide whether a command
// stays in the queue awaiting an ACK or is dropped as soon as it has been
// packed, so it sits directly on the retransmit path.
//
// Two BFME differences from the reference:
//
//  - it returns Int, not Bool. Retail sets the whole register (xor eax,eax /
//    mov eax,1) rather than just al, the same as DoesCommandRequireACommandID.
//    The reference header declares both as Bool.
//
//  - the type set is BFME's twenty, in BFME's order, which is NOT the order
//    DoesCommandRequireACommandID uses even though the two cover the same
//    twenty types: DISCONNECTPLAYER is tested twelfth here and eighteenth
//    there. The order is read straight off the comparison chain.
//
// getNetCommandType() is inlined -- retail loads m_type from msg+0x14 directly,
// which is the same offset Connection::doSend reads when it tests for FRAMEINFO.
//
// Declared locally rather than through the networkutil shim: that shim types
// this function as Bool, and any file under reference/shims/ forces the full
// gate.

typedef int Int;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = 0,
	NETCOMMANDTYPE_ACKBOTH,
	NETCOMMANDTYPE_ACKSTAGE1,
	NETCOMMANDTYPE_FRAMEINFO,						// 3
	NETCOMMANDTYPE_GAMECOMMAND,						// 4
	NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY,	// 5
	NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY,			// 6
	NETCOMMANDTYPE_REQUESTPLAYERLEAVE,				// 7
	NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME,			// 8
	NETCOMMANDTYPE_REQUESTFRAMEDATA,				// 9
	NETCOMMANDTYPE_PLAYERLEAVE,						// 10
	NETCOMMANDTYPE_DESTROYPLAYER,					// 11
	NETCOMMANDTYPE_KEEPALIVE,						// 12
	NETCOMMANDTYPE_DISCONNECTCHAT,					// 13
	NETCOMMANDTYPE_CHAT,							// 14
	NETCOMMANDTYPE_PROGRESS,						// 15
	NETCOMMANDTYPE_LOADCOMPLETE,					// 16
	NETCOMMANDTYPE_TIMEOUTSTART,					// 17
	NETCOMMANDTYPE_WRAPPER,							// 18
	NETCOMMANDTYPE_FILE,							// 19
	NETCOMMANDTYPE_FILEANNOUNCE,					// 20
	NETCOMMANDTYPE_FILEPROGRESS,					// 21
	NETCOMMANDTYPE_UNUSED22,						// 22
	NETCOMMANDTYPE_UNUSED23,						// 23
	NETCOMMANDTYPE_DISCONNECTKEEPALIVE,				// 24
	NETCOMMANDTYPE_DISCONNECTPLAYER,				// 25
	NETCOMMANDTYPE_DISCONNECTVOTE,					// 26
	NETCOMMANDTYPE_DISCONNECTFRAME,					// 27
	NETCOMMANDTYPE_DISCONNECTSCREENOFF				// 28
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	NetCommandType getNetCommandType() { return m_type; }

private:
	char m_padToType[0x14];							// unpinned
	NetCommandType m_type;							// this+0x14
};

Int CommandRequiresAck(NetCommandMsg *msg)
{
	// BFME's own order, read straight off the comparison chain at 0x00682DB0.
	if ((msg->getNetCommandType() == NETCOMMANDTYPE_GAMECOMMAND) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_FRAMEINFO) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_PLAYERLEAVE) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_REQUESTFRAMEDATA) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_REQUESTPLAYERLEAVE) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_DESTROYPLAYER) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_CHAT) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_DISCONNECTVOTE) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_DISCONNECTPLAYER) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_LOADCOMPLETE) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_TIMEOUTSTART) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_WRAPPER) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_FILE) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_FILEANNOUNCE) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_FILEPROGRESS) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_DISCONNECTFRAME) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_DISCONNECTSCREENOFF))
	{
		return 1;
	}

	return 0;
}


// IsCommandSynchronized, 0x00682E50, 33 bytes.
//
// The reference's set minus RUNAHEAD, which BFME does not have -- so four types
// where the reference has five, in the reference's order. Int rather than Bool
// for the same reason CommandRequiresAck is: retail sets the whole register.
Int IsCommandSynchronized(NetCommandType type)
{
	if ((type == NETCOMMANDTYPE_GAMECOMMAND) ||
			(type == NETCOMMANDTYPE_FRAMEINFO) ||
			(type == NETCOMMANDTYPE_PLAYERLEAVE) ||
			(type == NETCOMMANDTYPE_DESTROYPLAYER))
	{
		return 1;
	}

	return 0;
}


// CommandRequiresDirectSend, 0x00682E80, 86 bytes.
//
// The reference's list minus FRAMERESENDREQUEST, which BFME does not have, plus
// BFME's own five appended after it in the order 5, 6, 8, 9, 7 -- the request
// and reply for the GameSpy stats authkey, the inform-player-leave-frame and
// request-frame-data commands, and the request-player-leave command last.
//
// Everything on this list bypasses the packet router and goes straight to its
// destination, which is why the five additions matter: two of them,
// INFORMPLAYERLEAVEFRAME and REQUESTFRAMEDATA, are on the frame path.
Int CommandRequiresDirectSend(NetCommandMsg *msg)
{
	if ((msg->getNetCommandType() == NETCOMMANDTYPE_DISCONNECTVOTE) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_DISCONNECTPLAYER) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_LOADCOMPLETE) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_TIMEOUTSTART) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_FILE) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_FILEANNOUNCE) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_FILEPROGRESS) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_DISCONNECTFRAME) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_DISCONNECTSCREENOFF) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_REQUESTFRAMEDATA) ||
			(msg->getNetCommandType() == NETCOMMANDTYPE_REQUESTPLAYERLEAVE))
	{
		return 1;
	}

	return 0;
}
