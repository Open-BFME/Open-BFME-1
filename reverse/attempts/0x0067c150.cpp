// ?addRunAheadMetricsCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z
// partial score=0.8 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// NetPacket::addRunAheadMetricsCommand, retail 0x0067C150, 554 bytes.
//
// addCommand's jump table pins this address, and it opens with the isRoomFor
// guard already a matched, byte-true row (0x00678050, still a gen-asm dump,
// which a prior attempt (reverse/re_attempts.log) already identified as
// isRoomForRunAheadMetricsMessage from the source/address order and matching
// packet-layout CFG).
//
// Not Zero Hour's addRunAheadMetricsCommand: that body writes a Real
// averageLatency plus an UnsignedShort averageFps (6 payload bytes) through
// two out-of-line getter calls. Retail's disassembly here has neither call:
// after the 'D' tag it loops eight times reading a single byte at
// cmdMsg+0x1C+i*4 (scale 4, byte-sized load) with no further callee, i.e. an
// 8-entry, 4-byte-stride array whose first byte is the payload -- BFME
// replaced the two scalar metrics with a per-player array. Field test order
// is T/R/P/C/D with NO needNewCommandID/lastCommandID-changed test at all:
// the 'C' (command id) tag and value are written unconditionally, which is
// also why this body never touches an ebx-class register the way every
// needNewCommandID sibling does.
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

struct MetricEntry
{
	UnsignedByte value;
	UnsignedByte pad[3];
};

class NetRunAheadMetricsCommandMsg : public NetCommandMsg
{
public:
	MetricEntry m_metrics[8];						// this+0x1C
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
	Bool isRoomForRunAheadMetricsMessage(NetCommandRef *msg);	// 0x00678050
	Bool addRunAheadMetricsCommand(NetCommandRef *msg);

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


Bool NetPacket::addRunAheadMetricsCommand(NetCommandRef *msg) {
	Bool needNewCommandID = false;
	if (isRoomForRunAheadMetricsMessage(msg)) {
		NetRunAheadMetricsCommandMsg *cmdMsg = (NetRunAheadMetricsCommandMsg *)(msg->getCommand());

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

		for (Int i = 0; i < 8; ++i) {
			m_packet[m_packetLen + i] = cmdMsg->m_metrics[i].value;
		}
		m_packetLen += 8;

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
