// ?addFrameCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z
// partial score=0.75 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// NetPacket::addFrameCommand, retail 0x0067C6C0, 576 bytes.
//
// addCommand's jump table pins this address, and it opens with the isRoomFor
// guard landed alongside it in NetPacket_isRoomForFrameFamily.cpp:
// isRoomForFrameMessage at 0x00678180.
//
// Not Zero Hour's addFrameCommand: that body also has an isFrameRepeat 'Z'
// fast path and a single UnsignedShort commandCount payload. Retail's
// disassembly here has neither -- no isFrameRepeat call, and after the 'D'
// tag it writes three raw UnsignedInts straight out of cmdMsg+0x1C, +0x20 and
// +0x24 with no further callee, which is why isRoomForFrameMessage's own
// comment (nine bytes charged: 'D' plus two UnsignedInts) undercounts by one
// field relative to what this body actually emits -- the two functions
// disagree on their own field count, not this reconstruction's arithmetic.
// Field order is T/R/P/F/C/D, matching this body's branch order exactly
// (isRoomForFrameMessage's own guard tests are T/R/P/C/F, so the guard and
// the add function do not even agree with each other on test order either).
//
// Layout and NetCommandRef/NetCommandMsg fields are the other add*Command
// siblings' (NetPacket_addFileCommand.cpp): BFME's de-pooled NetCommandRef
// with no vptr.

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
#pragma intrinsic(memcpy)

#define NULL 0

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum { MAX_PACKET_SIZE = 0x1DC };

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

class NetFrameCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt m_frameField0;						// this+0x1C
	UnsignedInt m_frameField1;						// this+0x20
	UnsignedInt m_frameField2;						// this+0x24
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);				// ILT thunk 0x000079E6
	~NetCommandRef();								// ILT thunk 0x00038960

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
	Bool isRoomForFrameMessage(NetCommandRef *msg);	// 0x00678180, landed
	Bool addFrameCommand(NetCommandRef *msg);

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


Bool NetPacket::addFrameCommand(NetCommandRef *msg) {
	if (isRoomForFrameMessage(msg)) {
		NetFrameCommandMsg *cmdMsg = (NetFrameCommandMsg *)(msg->getCommand());

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

		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);

			m_lastPlayerID = cmdMsg->getPlayerID();
		}

		// If necessary, put the execution frame into the packet.
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);

			m_lastFrame = cmdMsg->getExecutionFrame();
		}

		// Unconditionally specify the command ID of this command.
		m_packet[m_packetLen] = 'C';
		++m_packetLen;
		UnsignedShort newID = cmdMsg->getID();
		memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
		m_packetLen += sizeof(UnsignedShort);
		m_lastCommandID = cmdMsg->getID();

		m_packet[m_packetLen] = 'D';
		++m_packetLen;

		memcpy(m_packet + m_packetLen, &cmdMsg->m_frameField0, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);

		memcpy(m_packet + m_packetLen, &cmdMsg->m_frameField1, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);

		memcpy(m_packet + m_packetLen, &cmdMsg->m_frameField2, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);

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
