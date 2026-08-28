// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// NetPacket::isRoomForWrapperMessage, 0x00677BC0, 123 bytes.
//
// Named from the caller, not from a byte-prefix vote: addWrapperCommand's five
// call bytes resolve to the ILT thunk 0x00044FEE, whose body is this one, and
// the pin is already in reverse/symbols.csv. The body agrees: it accumulates a
// length from the msg fields, compares against 0x1DC (MAX_PACKET_SIZE) and
// returns through setle.
//
// The body is the reference's, unchanged. What was missing was the ABI, and it
// is supplied here rather than through the shared headers, because BFME drifts
// from the ZH reference on two layouts that other, already-matched rows depend
// on keeping as they are:
//
//   NetPacket    - retail keeps m_port immediately after m_addr as an embedded
//                  ip+port pair, so m_numCommands .. m_lastRelay all sit lower
//                  than the ZH header puts them. NetPacket_init.cpp proves this
//                  ordering across 0x1E0-0x1FC from a matched body.
//   NetCommandRef- retail's is NOT a MemoryPoolObject and carries no vptr:
//                  m_msg at 0, m_next 4, m_prev 8, m_relay 0xC, m_timeLastSent
//                  0x10. The matched ctor at 0x00676240 and the matched dtor at
//                  0x00676280 (NetCommandRef_dtor.cpp) both confirm it.
//
// Only the slice this body touches is declared, at the retail offsets, with the
// correct overall sizes. Editing the shared headers instead would change the
// meaning of three rows that are already matched against the ZH layout, and it
// would run the full gate for no gain -- nothing outside this file needs it.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetWrapperCommandMsg : public NetCommandMsg
{
public:
	// Declared, not defined: retail calls this out of line through the ILT thunk
	// at 0x0003D839, and that call is what forces the register allocation the
	// rest of the body has -- `this` parked in esi, the running length in edi.
	// An inline accessor compiles the load in place and misses by four bytes.
	UnsignedInt getDataLength();

	UnsignedByte *m_data;							// this+0x1C
	UnsignedInt m_dataLength;						// this+0x20
	UnsignedInt m_dataOffset;						// this+0x24
	UnsignedInt m_totalDataLength;					// this+0x28
	UnsignedInt m_chunkNumber;						// this+0x2C
	UnsignedInt m_numChunks;						// this+0x30
	UnsignedShort m_wrappedCommandID;				// this+0x34
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
	Bool isRoomForWrapperMessage(NetCommandRef *msg);

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

Bool NetPacket::isRoomForWrapperMessage(NetCommandRef *msg) {
	Int len = 0;
	Bool needNewCommandID = false;
	NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)(msg->getCommand());
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
	len += sizeof(UnsignedShort); // wrapped command ID
	len += sizeof(UnsignedInt); // chunk number
	len += sizeof(UnsignedInt); // number of chunks
	len += sizeof(UnsignedInt); // total data length
	len += sizeof(UnsignedInt); // data length of this chunk
	len += sizeof(UnsignedInt); // offset of this chunk
	len += cmdMsg->getDataLength(); // for the data of this chunk

	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}

	return true;
}
