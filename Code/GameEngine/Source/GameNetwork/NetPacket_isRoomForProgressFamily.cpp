// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?isRoomForPlayerLeaveMessage@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?isRoomForProgressMessage@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// Load-complete and progress packet room checks use the same independently
// proven NetPacket/NetCommandRef BFME layout as the landed keep-alive family.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;
#define FALSE false
#define TRUE true

enum { MAX_PACKET_SIZE = 0x1DC };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedInt getExecutionFrame() { return m_executionFrame; }
	UnsignedShort getID() { return m_id; }
	Int getNetCommandType() { return m_commandType; }

	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	Int m_commandType;
	Int m_referenceCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandMsg *getCommand() { return m_msg; }
	UnsignedByte getRelay() const { return m_relay; }

	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
	UnsignedInt m_timeLastSent;
};

typedef NetCommandMsg NetPlayerLeaveCommandMsg;

struct NetPacketAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
public:
	virtual ~NetPacket();

protected:
	Bool isRoomForLoadCompleteMessage(NetCommandRef *msg);
	Bool isRoomForProgressMessage(NetCommandRef *msg);
	Bool isRoomForPlayerLeaveMessage(NetCommandRef *msg);

public:
	UnsignedByte m_packet[0x1DC];
	Int m_packetLen;
	NetPacketAddress m_dest;
	Int m_numCommands;
	NetCommandRef *m_lastCommand;
	UnsignedInt m_lastFrame;
	UnsignedShort m_lastCommandID;
	UnsignedByte m_lastPlayerID;
	UnsignedByte m_lastCommandType;
	UnsignedByte m_lastRelay;
};

Bool NetPacket::isRoomForProgressMessage(NetCommandRef *msg)
{
	Int len = 0;
	NetCommandMsg *cmdMsg = (NetCommandMsg *)(msg->getCommand());
	if (m_lastCommandType != cmdMsg->getNetCommandType()) {
		++len;
		len += sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->getRelay()) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		++len;
		len += sizeof(UnsignedByte);
	}
	++len;
	++len;
	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return FALSE;
	}
	return TRUE;
}

Bool NetPacket::isRoomForPlayerLeaveMessage(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = FALSE;
	NetPlayerLeaveCommandMsg *cmdMsg = (NetPlayerLeaveCommandMsg *)(msg->getCommand());
	if (m_lastCommandType != cmdMsg->getNetCommandType()) {
		++len;
		len += sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->getRelay()) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastFrame != cmdMsg->getExecutionFrame()) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		++len;
		len += sizeof(UnsignedByte);
		needNewCommandID = TRUE;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == TRUE)) {
		len += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	}
	++len;
	len += sizeof(UnsignedByte);
	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return FALSE;
	}
	return TRUE;
}
