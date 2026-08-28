// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?FillBufferWithLoadCompleteMessage@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?FillBufferWithTimeOutGameStartMessage@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// The load-complete and timeout-start serializers are the two named 58-byte
// siblings after the exact progress body.  Their source declarations and
// packet construction are identical: T/R/P/C/D with no payload.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	Int getNetCommandType(void) { return m_commandType; }
	UnsignedInt getPlayerID(void) { return m_playerID; }
	UnsignedShort getID(void) { return m_id; }

	UnsignedByte m_prefix[0x0c];
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	UnsignedShort m_pad;
	Int m_commandType;
	Int m_referenceCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandMsg *getCommand(void) { return m_msg; }
	UnsignedByte getRelay(void) const { return m_relay; }

	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
protected:
	static void FillBufferWithLoadCompleteMessage(UnsignedByte *buffer, NetCommandRef *msg);
	static void FillBufferWithTimeOutGameStartMessage(UnsignedByte *buffer, NetCommandRef *msg);
};

void NetPacket::FillBufferWithLoadCompleteMessage(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetCommandMsg *cmdMsg = (NetCommandMsg *)msg->getCommand();
	UnsignedShort offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);
	buffer[offset] = 'R';
	++offset;
	buffer[offset] = msg->getRelay();
	offset += sizeof(UnsignedByte);
	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);
	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	*(UnsignedShort *)(buffer + offset) = newID;
	offset += sizeof(UnsignedShort);
	buffer[offset] = 'D';
	++offset;
}

void NetPacket::FillBufferWithTimeOutGameStartMessage(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetCommandMsg *cmdMsg = (NetCommandMsg *)msg->getCommand();
	UnsignedShort offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);
	buffer[offset] = 'R';
	++offset;
	buffer[offset] = msg->getRelay();
	offset += sizeof(UnsignedByte);
	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);
	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	*(UnsignedShort *)(buffer + offset) = newID;
	offset += sizeof(UnsignedShort);
	buffer[offset] = 'D';
	++offset;
}
