// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// NetPacket::isRoomForDisconnectVoteMessage, 0x00677DB0, 114 bytes.
// NetPacket::isRoomForDisconnectPlayerMessage, 0x00677E40, 114 bytes.
// NetPacket::isRoomForDestroyPlayerMessage, 0x00677FB0, 128 bytes.
// NetPacket::isRoomForFrameMessage, 0x00678180, 128 bytes.
//
// Four more of the family, each named from the add*Command that opens with a
// call to it -- addDisconnectVoteCommand (0x0067B480), addDisconnectPlayerCommand
// (0x0067B750), addDestroyPlayerCommand (0x0067BE60) and addFrameCommand
// (0x0067C6C0), all of them already pinned as jump-table arms of the matched
// addCommand dispatcher. The four differ only in which fields they charge for
// and in what order they test them, which is exactly what discriminates them:
// the byte-identical prologue these share is why a prefix comparison cannot
// pick between siblings and the branch layout can.
//
// Same ABI slice as NetPacket_isRoomForWrapperMessage.cpp, for the same reason:
// NetPacket's m_port sits immediately after m_addr and NetCommandRef has no
// vptr, and neither correction may go into the shared headers without changing
// the meaning of rows already matched against the vendored Zero Hour layout.
//
// All four bodies are the reference's, unchanged.

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
	Bool isRoomForDisconnectVoteMessage(NetCommandRef *msg);
	Bool isRoomForDisconnectPlayerMessage(NetCommandRef *msg);
	Bool isRoomForDestroyPlayerMessage(NetCommandRef *msg);
	Bool isRoomForFrameMessage(NetCommandRef *msg);

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

Bool NetPacket::isRoomForDisconnectVoteMessage(NetCommandRef *msg) {
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
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		++len;
		len += sizeof(UnsignedByte);
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
		len += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	}

	++len; // the 'D'
	len += sizeof(UnsignedByte); // slot number
	len += sizeof(UnsignedInt); // vote frame

	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

Bool NetPacket::isRoomForDisconnectPlayerMessage(NetCommandRef *msg) {
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
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		++len;
		len += sizeof(UnsignedByte);
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
		len += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	}

	++len; // the 'D'
	len += sizeof(UnsignedByte); // slot number
	len += sizeof(UnsignedInt);	// disconnectFrame
	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

Bool NetPacket::isRoomForDestroyPlayerMessage(NetCommandRef *msg) {
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
	len += sizeof(UnsignedInt);
	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

Bool NetPacket::isRoomForFrameMessage(NetCommandRef *msg) {
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
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		++len;
		len += sizeof(UnsignedByte);
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
		len += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	}
	if (m_lastFrame != cmdMsg->getExecutionFrame()) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}

	++len; // for 'D'
	// Not the reference's single UnsignedShort command count: BFME's frame
	// command carries two UnsignedInts. addFrameCommand (0x0067C6C0) writes them
	// as dwords out of cmdMsg+0x1C and cmdMsg+0x20 right after the 'D', which is
	// where the trailing nine rather than three comes from.
	len += sizeof(UnsignedInt);
	len += sizeof(UnsignedInt);
	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}
