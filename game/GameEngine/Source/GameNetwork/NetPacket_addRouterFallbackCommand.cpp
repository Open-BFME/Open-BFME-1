// ?addRouterFallbackCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z
// Open-BFME5 readable C++ conversion; retail RVA 0x0067C150, 554 bytes.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The matched addCommand dispatcher names this type-22 arm. Retail opens
// through the matched isRoomForRouterFallbackMessage path, writes T/R/P/C/D,
// then copies the first byte of eight four-byte player-order slots. Keeping
// the source pointer as a local makes MSVC 7.1 preserve retail's indexed loop
// shape instead of strength-reducing it to a pointer-induction loop.

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
#pragma intrinsic(memcpy)

#define NULL 0

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum { MAX_PACKET_SIZE = 0x1DC };


class NetCommandMsg
{
public:
	UnsignedInt getPlayerID() { return m_playerID; }
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

class BFMENetRouterFallbackCommandMsg : public NetCommandMsg
{
public:
	Int m_playerOrder[8];
};

class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);
	~NetCommandRef();
	NetCommandMsg *getCommand() { return m_msg; }
	UnsignedByte getRelay() const { return m_relay; }
	void setRelay(UnsignedByte relay) { m_relay = relay; }
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
	UnsignedInt m_timeLastSent;
};

struct NetPacketAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

class NetPacket
{
public:
	virtual ~NetPacket();

protected:
	Bool isRoomForRouterFallbackMessage(NetCommandRef *msg);
	Bool addRouterFallbackCommand(NetCommandRef *msg);

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

// ?addRouterFallbackCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z
Bool NetPacket::addRouterFallbackCommand(NetCommandRef *msg)
{
	NetCommandRef *ref = msg;
	Bool needNewCommandID;
	needNewCommandID = false;
	if (isRoomForRouterFallbackMessage(ref))
	{
		BFMENetRouterFallbackCommandMsg *cmdMsg =
			(BFMENetRouterFallbackCommandMsg *)(ref->getCommand());
		if (m_lastCommandType != cmdMsg->getNetCommandType())
		{
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ref->getRelay())
		{
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ref->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID())
		{
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)cmdMsg->getID()) ||
			(needNewCommandID == true))
		{
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		const Int *playerOrder = cmdMsg->m_playerOrder;
		for (Int i = 0; i < 8; ++i) {
			m_packet[m_packetLen + i] = (UnsignedByte)playerOrder[i];
		}
		m_packetLen += 8;
		++m_numCommands;
		if (m_lastCommand != NULL)
		{
			delete m_lastCommand;
			m_lastCommand = NULL;
		}
		NetCommandRef *newRef = new NetCommandRef(ref->getCommand());
		m_lastCommand = newRef;
		newRef->setRelay(ref->getRelay());
		return true;
	}
	return false;
}
