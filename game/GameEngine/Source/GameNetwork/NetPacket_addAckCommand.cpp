// cl: /DNDEBUG /MD /EHsc
// BFME's four-argument NetPacket::addAckCommand body.  NetPacket_ackCommands.cpp
// supplies the three caller wrappers; this TU owns the BFME overload body.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef int Bool;
enum { FALSE = 0, TRUE = 1 };
enum { MAX_PACKET_SIZE = 476 };

#include <string.h>

// Local ABI slices are intentional: the BFME executable's NetCommandRef has no
// vptr, and its NetPacket fields differ from the reference header's ordering.
class NetCommandMsg
{
public:
	virtual ~NetCommandMsg();

	UnsignedInt getPlayerID(void) { return m_playerID; }
	Int getNetCommandType(void) { return m_commandType; }

	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	unsigned short m_id;
	Int m_commandType;
	Int m_referenceCount;
};

class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);
	~NetCommandRef();

	NetCommandMsg *getCommand(void) { return m_msg; }
	UnsignedByte getRelay(void) { return m_relay; }
	void setRelay(UnsignedByte v) { m_relay = v; }

private:
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
	UnsignedInt m_timeLastSent;
};

extern void j_0000c70c(void);

class NetPacket
{
	class IsAckRepeatReceiver
	{
	public:
		bool isAckRepeat(NetCommandRef *msg);
	};

	union IsAckRepeatCall
	{
		void (*free_function)(void);
		bool (IsAckRepeatReceiver::*member_function)(NetCommandRef *msg);
	};

protected:
	bool isRoomForAckMessage(NetCommandRef *msg);
	bool addAckCommand(NetCommandRef *msg, UnsignedShort commandID, UnsignedByte originalPlayerID, UnsignedInt playerID);

	unsigned char m_pad000[0x04];
	UnsignedByte m_packet[MAX_PACKET_SIZE];
	Int m_packetLen;
	unsigned char m_pad1E4[0x1EC - 0x1E4];
	Int m_numCommands;
	NetCommandRef *m_lastCommand;
	unsigned char m_pad1F4[0x1FA - 0x1F4];
	UnsignedByte m_lastPlayerID;
	UnsignedByte m_lastCommandType;
};

// ?isRoomForAckMessage@NetPacket@@IAE_NPAVNetCommandRef@@@Z present-unmatched
// The helper is retained only for the force-inline shape of the matched body;
// retail has no separately owned call at this boundary.
__forceinline bool NetPacket::isRoomForAckMessage(NetCommandRef *msg)
{
	Int len = 0;
	NetCommandMsg *cmdMsg = msg->getCommand();
	if (m_lastCommandType != cmdMsg->getNetCommandType())
	{
		++len;
		len += sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID())
	{
		++len;
		len += sizeof(UnsignedByte);
	}
	len += sizeof(UnsignedByte);
	len += sizeof(UnsignedShort);
	len += sizeof(UnsignedByte);
	len += sizeof(UnsignedInt);
	return (len + m_packetLen) <= MAX_PACKET_SIZE;
}

// ?addAckCommand@NetPacket@@IAE_NPAVNetCommandRef@@GEI@Z
bool NetPacket::addAckCommand(NetCommandRef *msg, UnsignedShort commandID, UnsignedByte originalPlayerID, UnsignedInt playerID)
{
	IsAckRepeatCall call;
	call.free_function = &j_0000c70c;
	if ((((IsAckRepeatReceiver *)this)->*call.member_function)(msg))
	{
		if (m_packetLen >= MAX_PACKET_SIZE)
			return FALSE;

		m_packet[m_packetLen] = 'Z';
		++m_packetLen;
		++m_numCommands;

		if (m_lastCommand != 0)
		{
			delete m_lastCommand;
		}
		m_lastCommand = 0;

		NetCommandRef *newRef = new NetCommandRef(msg->getCommand());
		m_lastCommand = newRef;
		newRef->setRelay(msg->getRelay());
		return TRUE;
	}

	if (isRoomForAckMessage(msg))
	{
		NetCommandMsg *cmdMsg = msg->getCommand();
		if (m_lastCommandType != cmdMsg->getNetCommandType())
		{
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = (UnsignedByte)cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);

			m_lastCommandType = (UnsignedByte)cmdMsg->getNetCommandType();
		}

		if (m_lastPlayerID != cmdMsg->getPlayerID())
		{
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = (UnsignedByte)cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);

			m_lastPlayerID = (UnsignedByte)cmdMsg->getPlayerID();
		}

		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		memcpy(m_packet + m_packetLen, &commandID, sizeof(UnsignedShort));
		m_packetLen += sizeof(UnsignedShort);
		memcpy(m_packet + m_packetLen, &originalPlayerID, sizeof(UnsignedByte));
		m_packetLen += sizeof(UnsignedByte);
		memcpy(m_packet + m_packetLen, &playerID, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);

		if (m_lastCommand != 0)
		{
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());

		++m_numCommands;
		return TRUE;
	}
	return FALSE;
}
