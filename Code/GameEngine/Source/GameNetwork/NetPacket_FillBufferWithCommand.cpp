// cl: /DNDEBUG /MD /EHsc

typedef unsigned char UnsignedByte;

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

class NetCommandMsg
{
public:
	NetCommandType getNetCommandType() { return m_commandType; }

private:
	unsigned char m_header[0x14];
	NetCommandType m_commandType;
};

class NetCommandRef
{
public:
	NetCommandMsg *getCommand() { return m_command; }

private:
	NetCommandMsg *m_command;
};

class Rva00677280Ref;
class Rva006772F0Ref;
class Rva00677450Ref;
class Rva006774C0Ref;
struct Rva00677530Ref;
class Rva00677590Ref;

void Rva00677280(UnsignedByte *buffer, Rva00677280Ref *ref);
void Rva006772F0(UnsignedByte *buffer, Rva006772F0Ref *ref);
void Rva00677450(UnsignedByte *buffer, Rva00677450Ref *ref);
void Rva006774C0(UnsignedByte *buffer, Rva006774C0Ref *ref);
void FillBufferWithRva00677530Message(UnsignedByte *buffer,
	Rva00677530Ref *ref);
void Rva00677590(UnsignedByte *buffer, Rva00677590Ref *ref);

class NetPacket
{
protected:
	static void FillBufferWithCommand(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithGameCommand(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithAckCommand(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithFrameCommand(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithPlayerLeaveCommand(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithDestroyPlayerCommand(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithKeepAliveCommand(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithDisconnectKeepAliveCommand(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithDisconnectChatCommand(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithChatCommand(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithProgressMessage(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithLoadCompleteMessage(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithTimeOutGameStartMessage(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithFileMessage(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithFileAnnounceMessage(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithDisconnectFrameMessage(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithDisconnectScreenOffMessage(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithGameSpyStatsAuthKeyCommand(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithRequestGameSpyStatsAuthKeyCommand(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithPlayerFrameRatiosCommand(UnsignedByte *buffer, NetCommandRef *ref);
};

// ?FillBufferWithCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z
void NetPacket::FillBufferWithCommand(UnsignedByte *buffer, NetCommandRef *ref)
{
	NetCommandMsg *msg = ref->getCommand();

	switch (msg->getNetCommandType())
	{
		case NETCOMMANDTYPE_GAMECOMMAND:
			FillBufferWithGameCommand(buffer, ref);
			break;

		case NETCOMMANDTYPE_ACKSTAGE1:
		case NETCOMMANDTYPE_ACKSTAGE2:
		case NETCOMMANDTYPE_ACKBOTH:
			FillBufferWithAckCommand(buffer, ref);
			break;

		case NETCOMMANDTYPE_FRAMEINFO:
			FillBufferWithFrameCommand(buffer, ref);
			break;

		case NETCOMMANDTYPE_PLAYERFRAMERATIOS:
			FillBufferWithPlayerFrameRatiosCommand(buffer, ref);
			break;

		case NETCOMMANDTYPE_PLAYERLEAVE:
			FillBufferWithPlayerLeaveCommand(buffer, ref);
			break;

		case NETCOMMANDTYPE_DESTROYPLAYER:
			FillBufferWithDestroyPlayerCommand(buffer, ref);
			break;

		case NETCOMMANDTYPE_KEEPALIVE:
			FillBufferWithKeepAliveCommand(buffer, ref);
			break;

		case NETCOMMANDTYPE_DISCONNECTKEEPALIVE:
			FillBufferWithDisconnectKeepAliveCommand(buffer, ref);
			break;

		case NETCOMMANDTYPE_DISCONNECTPLAYER:
			Rva00677280(buffer, (Rva00677280Ref *)ref);
			break;

		case NETCOMMANDTYPE_DISCONNECTCHAT:
			FillBufferWithDisconnectChatCommand(buffer, ref);
			break;

		case NETCOMMANDTYPE_DISCONNECTVOTE:
			Rva006772F0(buffer, (Rva006772F0Ref *)ref);
			break;

		case NETCOMMANDTYPE_CHAT:
			FillBufferWithChatCommand(buffer, ref);
			break;

		case NETCOMMANDTYPE_PROGRESS:
			FillBufferWithProgressMessage(buffer, ref);
			break;

		case NETCOMMANDTYPE_LOADCOMPLETE:
			FillBufferWithLoadCompleteMessage(buffer, ref);
			break;

		case NETCOMMANDTYPE_TIMEOUTSTART:
			FillBufferWithTimeOutGameStartMessage(buffer, ref);
			break;

		case NETCOMMANDTYPE_FILE:
			FillBufferWithFileMessage(buffer, ref);
			break;

		case NETCOMMANDTYPE_FILEANNOUNCE:
			FillBufferWithFileAnnounceMessage(buffer, ref);
			break;

		case NETCOMMANDTYPE_FILEPROGRESS:
			Rva00677450(buffer, (Rva00677450Ref *)ref);
			break;

		case NETCOMMANDTYPE_DISCONNECTFRAME:
			FillBufferWithDisconnectFrameMessage(buffer, ref);
			break;

		case NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME:
			Rva006774C0(buffer, (Rva006774C0Ref *)ref);
			break;

		case NETCOMMANDTYPE_REQUESTPLAYERLEAVE:
			FillBufferWithRva00677530Message(buffer, (Rva00677530Ref *)ref);
			break;

		case NETCOMMANDTYPE_REQUESTFRAMEDATA:
			Rva00677590(buffer, (Rva00677590Ref *)ref);
			break;

		case NETCOMMANDTYPE_DISCONNECTSCREENOFF:
			FillBufferWithDisconnectScreenOffMessage(buffer, ref);
			break;

		case NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY:
			FillBufferWithRequestGameSpyStatsAuthKeyCommand(buffer, ref);
			break;

		case NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY:
			FillBufferWithGameSpyStatsAuthKeyCommand(buffer, ref);
			break;
	}
}
