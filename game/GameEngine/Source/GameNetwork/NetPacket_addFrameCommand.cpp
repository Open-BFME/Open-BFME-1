// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME's frame-command packet writer.  The matched addCommand jump table names
// this arm; the guard and NetCommandRef constructor/destructor remain ILT-backed.

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
#pragma intrinsic(memcpy)

#define NULL 0

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum { MAX_PACKET_SIZE = 0x1DC };

extern void j_000173f0(void);

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

class NetFrameCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt m_frameField0;
	UnsignedInt m_frameField1;
	UnsignedInt m_frameField2;
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
	class FrameRoomReceiver
	{
	public:
		Bool isRoomForFrameMessage(NetCommandRef *msg);
	};

	union FrameRoomCall
	{
		void (*free_function)(void);
		Bool (FrameRoomReceiver::*member_function)(NetCommandRef *msg);
	};

	Bool addFrameCommand(NetCommandRef *msg);

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

// ?addFrameCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z
Bool NetPacket::addFrameCommand(NetCommandRef *msg)
{
	FrameRoomCall call;
	call.free_function = &j_000173f0;
	if ((((FrameRoomReceiver *)this)->*call.member_function)(msg))
	{
		NetFrameCommandMsg *cmdMsg = (NetFrameCommandMsg *)(msg->getCommand());

		if (m_lastCommandType != cmdMsg->getNetCommandType())
		{
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}

		if (m_lastRelay != msg->getRelay())
		{
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
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
		}

		if (m_lastFrame != cmdMsg->getExecutionFrame())
		{
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = cmdMsg->getExecutionFrame();
		}

		m_packet[m_packetLen] = 'C';
		++m_packetLen;
		*(UnsignedShort *)(m_packet + m_packetLen) = cmdMsg->getID();
		m_packetLen += sizeof(UnsignedShort);
		m_lastCommandID = cmdMsg->getID();

		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		*(UnsignedInt *)(m_packet + m_packetLen) = cmdMsg->m_frameField0;
		m_packetLen += sizeof(UnsignedInt);
		*(UnsignedInt *)(m_packet + m_packetLen) = cmdMsg->m_frameField1;
		m_packetLen += sizeof(UnsignedInt);
		*(UnsignedInt *)(m_packet + m_packetLen) = cmdMsg->m_frameField2;
		m_packetLen += sizeof(UnsignedInt);

		if (m_lastCommand != NULL)
		{
			delete m_lastCommand;
			m_lastCommand = NULL;
		}
		NetCommandRef *newRef = new NetCommandRef(msg->getCommand());
		m_lastCommand = newRef;
		newRef->setRelay(msg->getRelay());
		++m_numCommands;
		return true;
	}
	return false;
}
