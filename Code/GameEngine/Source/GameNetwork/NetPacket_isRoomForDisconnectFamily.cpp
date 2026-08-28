// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// NetPacket::isRoomForDisconnectScreenOffMessage, 0x00677810, 128 bytes.
// NetPacket::isRoomForDisconnectFrameMessage, 0x00677A90, 128 bytes.
// NetPacket::isRoomForInformPlayerLeaveFrameMessage, 0x006778B0, 128 bytes.
// NetPacket::isRoomForFileProgressMessage, 0x00677B30, 114 bytes.
//
// Named from their callers: addDisconnectScreenOffCommand (0x00679810),
// addDisconnectFrameCommand (0x0067A410), addInformPlayerLeaveFrameCommand
// (0x00679B00) and addFileProgressCommand (0x0067A700) each open with a call to
// one of these, and all four callers are already pinned as jump-table arms of
// the matched addCommand dispatcher.
//
// isRoomForInformPlayerLeaveFrameMessage has no counterpart in the vendored
// Zero Hour source at all -- BFME added the command type. Its body here is the
// disconnect-frame one, and the justification is the byte match, not a guess:
// the two charge for the same fields in the same order.
//
// Same ABI slice and the same reason for keeping it local as
// NetPacket_isRoomForWrapperMessage.cpp.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum { MAX_PACKET_SIZE = 0x1DC };

// NetCommandMsg's field set is the one NetPacket_addCommand.cpp already pins
// from a matched dispatcher: vptr, timestamp, frame, player, id, type, and the
// reference count that closes it out at 0x1C.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedInt getExecutionFrame() { return m_executionFrame; }
	UnsignedShort getID() { return m_id; }
	Int getNetCommandType() { return m_commandType; }

	void *m_vptr;									// this+0x00
	UnsignedInt m_timestamp;						// this+0x04
	UnsignedInt m_executionFrame;					// this+0x08
	UnsignedInt m_playerID;							// this+0x0C
	UnsignedShort m_id;								// this+0x10
	Int m_commandType;								// this+0x14
	Int m_referenceCount;							// this+0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandMsg *getCommand() { return m_msg; }
	UnsignedByte getRelay() const { return m_relay; }

	NetCommandMsg *m_msg;							// this+0x00
	NetCommandRef *m_next;							// this+0x04
	NetCommandRef *m_prev;							// this+0x08
	UnsignedByte m_relay;							// this+0x0C
	UnsignedInt m_timeLastSent;						// this+0x10
};

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
	Bool isRoomForDisconnectScreenOffMessage(NetCommandRef *msg);
	Bool isRoomForDisconnectFrameMessage(NetCommandRef *msg);
	Bool isRoomForInformPlayerLeaveFrameMessage(NetCommandRef *msg);
	Bool isRoomForFileProgressMessage(NetCommandRef *msg);

public:

	UnsignedByte m_packet[0x1DC];					// this+0x004
	Int m_packetLen;								// this+0x1E0
	NetPacketAddress m_dest;						// this+0x1E4
	Int m_numCommands;								// this+0x1EC
	NetCommandRef *m_lastCommand;					// this+0x1F0
	UnsignedInt m_lastFrame;						// this+0x1F4
	UnsignedShort m_lastCommandID;					// this+0x1F8
	UnsignedByte m_lastPlayerID;					// this+0x1FA
	UnsignedByte m_lastCommandType;					// this+0x1FB
	UnsignedByte m_lastRelay;						// this+0x1FC
};

Bool NetPacket::isRoomForDisconnectScreenOffMessage(NetCommandRef *msg) {
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = (NetCommandMsg *)(msg->getCommand());
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
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
		len += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	}

	++len; // for 'D'
	len += sizeof(UnsignedInt); // for the disconnect frame
	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

Bool NetPacket::isRoomForDisconnectFrameMessage(NetCommandRef *msg) {
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = (NetCommandMsg *)(msg->getCommand());
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
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
		len += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	}

	++len; // for 'D'
	len += sizeof(UnsignedInt); // for the disconnect frame
	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

Bool NetPacket::isRoomForInformPlayerLeaveFrameMessage(NetCommandRef *msg) {
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = (NetCommandMsg *)(msg->getCommand());
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
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
		len += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	}

	++len; // for 'D'
	// Two words, not one: addInformPlayerLeaveFrameCommand (0x00679B00)
	// writes two dwords after the 'D', each read back through its own getter
	// call on the message, so the trailing total is nine.
	len += sizeof(UnsignedInt);
	len += sizeof(UnsignedInt);
	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

Bool NetPacket::isRoomForFileProgressMessage(NetCommandRef *msg) {
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = (NetCommandMsg *)(msg->getCommand());
	if (m_lastCommandType != cmdMsg->getNetCommandType()) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->getRelay()) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}

	++len; // 'D'
	len += sizeof(UnsignedShort); // m_fileID
	len += sizeof(Int); // m_progress

	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}

	return true;
}
