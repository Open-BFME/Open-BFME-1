// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?addWrapperCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// Retail 0x0067A9D0 -- addWrapperCommand, the writer half of the wrapper trio
// whose isRoomForWrapperMessage and readWrapperMessage are already ledgered.
// Named by its seven getters, every one of them ledgered on
// NetWrapperCommandMsg, plus the isRoomFor call it opens with.
//
// Reuses the NetPacket and NetCommandRef layouts from
// NetPacket_isRoomForFrameFamily.cpp; NEW_NETCOMMANDREF is operator new of 0x14
// plus ??0NetCommandRef@@QAE@PAVNetCommandMsg@@@Z, and deleteInstance is that
// class's destructor followed by operator delete.

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
#pragma intrinsic(memcpy)

#define NULL 0

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
	NetCommandRef(NetCommandMsg *msg);		// ILT thunk 0x000079E6
	~NetCommandRef();				// ILT thunk 0x00038960

	NetCommandMsg *getCommand() { return m_msg; }
	UnsignedByte getRelay() const { return m_relay; }
	void setRelay(UnsignedByte relay) { m_relay = relay; }

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
	Bool isRoomForWrapperMessage(NetCommandRef *msg);	// ILT thunk 0x00044FEE
	Bool addWrapperCommand(NetCommandRef *msg);

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


// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetWrapperCommandMsg : public NetCommandMsg
{
public:
	UnsignedShort getWrappedCommandID(void);	// ILT thunk 0x000057C7
	UnsignedInt getChunkNumber(void);		// ILT thunk 0x0003F814
	UnsignedInt getNumChunks(void);			// ILT thunk 0x00018BEC
	UnsignedInt getTotalDataLength(void);		// ILT thunk 0x0000F70E
	UnsignedInt getDataLength(void);		// ILT thunk 0x0003D839
	UnsignedInt getDataOffset(void);		// ILT thunk 0x00027048
	UnsignedByte *getData(void);			// ILT thunk 0x0002D867
};

Bool NetPacket::addWrapperCommand(NetCommandRef *msg) {
	Bool needNewCommandID = false;
	if (isRoomForWrapperMessage(msg)) {
		NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)(msg->getCommand());

		// If necessary, put the NetCommandType into the packet.
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);

			m_lastCommandType = cmdMsg->getNetCommandType();
		}

		// If necessary, put the relay into the packet.
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);

			m_lastRelay = newRelay;
		}

		// If necessary put the player ID into the packet.
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);

			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}

		// If necessary, specify the command ID of this command.
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();

		m_packet[m_packetLen] = 'D';
		++m_packetLen;

		// wrapped command ID
		UnsignedShort wrappedCommandID = cmdMsg->getWrappedCommandID();
		memcpy(m_packet + m_packetLen, &wrappedCommandID, sizeof(wrappedCommandID));
		m_packetLen += sizeof(wrappedCommandID);

		// chunk number
		UnsignedInt chunkNumber = cmdMsg->getChunkNumber();
		memcpy(m_packet + m_packetLen, &chunkNumber, sizeof(chunkNumber));
		m_packetLen += sizeof(chunkNumber);

		// number of chunks
		UnsignedInt numChunks = cmdMsg->getNumChunks();
		memcpy(m_packet + m_packetLen, &numChunks, sizeof(numChunks));
		m_packetLen += sizeof(numChunks);

		// total length of data for all chunks
		UnsignedInt totalDataLength = cmdMsg->getTotalDataLength();
		memcpy(m_packet + m_packetLen, &totalDataLength, sizeof(totalDataLength));
		m_packetLen += sizeof(totalDataLength);

		// data length for this chunk
		UnsignedInt dataLength = cmdMsg->getDataLength();
		memcpy(m_packet + m_packetLen, &dataLength, sizeof(dataLength));
		m_packetLen += sizeof(dataLength);

		// the offset into the data of this chunk
		UnsignedInt dataOffset = cmdMsg->getDataOffset();
		memcpy(m_packet + m_packetLen, &dataOffset, sizeof(dataOffset));
		m_packetLen += sizeof(dataOffset);

		// the data for this chunk
		UnsignedByte *data = cmdMsg->getData();
		memcpy(m_packet + m_packetLen, data, dataLength);
		m_packetLen += dataLength;

		++m_numCommands;
		if (m_lastCommand != NULL) {
			delete m_lastCommand;
			m_lastCommand = NULL;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());

		return true;
	}
	return false;
}
